#include "experimental/Texture.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "SceneItem.h"
#include "Shader.h"
#include "IcoSphere.h"
#include "File.h"
#include "Ply.h"
#include "Light.h"
#include "OBJ.h"
#include "experimental/StringUtil.h"
#include "experimental/UVSphere.h"
#include "experimental/Plane.h"
#include "experimental/Box.h"
#include "experimental/Material.h"
#include "experimental/ShaderGenerator.h"
#include <iostream>
#include <map>

using namespace std;

namespace roxlu {

Renderer::Renderer(float screenWidth, float screenHeight) 
:cam(NULL)
,scene(NULL)
,use_fill(true)
,screen_width(screenWidth)
,screen_height(screenHeight)
{
	// create camera
	cam = new EasyCam();
	cam->setup(screen_width, screen_height);
	cam->translate(0,0,-10);
	
	// create a scene instance (which is just a container for all created scene  items.
	scene = new Scene();
	effect = new Effect(); // our default effect
}

Renderer::~Renderer() {
}

void Renderer::render() {
	if(cam == NULL || scene == NULL) {
		printf("No cam, shader or scene set!\n");
		exit(1);
	}
	
	glEnable(GL_DEPTH_TEST);
	if(!use_fill) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	// create matrices for shaders
	cam->updateViewMatrix();
	Mat4& view_matrix = cam->vm();
	Mat4& projection_matrix = cam->pm();

	// draw all scene items.
	Scene::scene_item_iterator it = scene->scene_items.begin();
	while(it != scene->scene_items.end()) {
		SceneItem& si = *(it->second);
		si.draw(view_matrix, projection_matrix);
		++it;
	}

}

void Renderer::renderSceneItem(string name) {
	cam->updateViewMatrix();
	Mat4& view_matrix = cam->vm();
	Mat4& projection_matrix = cam->pm();
	
	SceneItem& si = *getSceneItem(name);
	si.draw(view_matrix, projection_matrix);
}

SceneItem* Renderer::createIcoSphere(string name, int detail, float radius) {
	VertexData* vd = new VertexData();
	SceneItem* si = new SceneItem(name);

	// Create vertex data for ico sphere.	
	IcoSphere ico_sphere;
	ico_sphere.create(detail, radius, *vd);
	
	// Create scene item from vertex data and make sure shader is set.
	si->setEffect(effect);
	si->createFromVertexData(vd);
	si->setDrawMode(SceneItem::TRIANGLES);
	
	// Keep track of the created data.
	scene->addSceneItem(name, si);
	scene->addVertexData(name, vd);

	return si;
}

SceneItem* Renderer::createUVSphere(string name, int phi, int theta, float radius) {
	VertexData* vd = new VertexData();
	SceneItem* si = new SceneItem(name);

	// Create vertex data for ico sphere.	
	UVSphere uv_sphere;
	uv_sphere.create(radius, phi, theta, *vd);
	
	// Create scene item from vertex data and make sure shader is set.
	si->setEffect(effect);
	si->createFromVertexData(vd);
	si->setDrawMode(SceneItem::QUAD_STRIP);

	// Keep track of the created data.
	scene->addSceneItem(name, si);
	scene->addVertexData(name, vd);
	return si;
}

SceneItem* Renderer::createBox(string name, float width, float height, float depth) {
	VertexData* vd = new VertexData();
	SceneItem* si = new SceneItem(name);

	// Create vertex data for ico sphere.	
	Box box;
	box.create(width, height, depth, *vd);
	
	// Create scene item from vertex data and make sure shader is set.
	si->setEffect(effect);
	si->createFromVertexData(vd);
	si->setDrawMode(SceneItem::QUADS);
	
	// Keep track of the created data.
	scene->addSceneItem(name, si);
	scene->addVertexData(name, vd);
	return si;
}

SceneItem* Renderer::createPlane(string name, float width, float height) {
	VertexData* vd = new VertexData();
	SceneItem* si = new SceneItem(name);

	// Create vertex data for ico sphere.	
	Plane plane;
	plane.create(width, height, *vd);
	
	// Create scene item from vertex data and make sure shader is set.
	si->setEffect(effect);
	si->createFromVertexData(vd);
	si->setDrawMode(SceneItem::QUADS);
	
	// Keep track of the created data.
	scene->addSceneItem(name, si);
	scene->addVertexData(name, vd);
	return si;
}


void Renderer::onMouseDown(float x, float y) {
	cam->onMouseDown(x,y);
}

void Renderer::onMouseDragged(float x, float y) {
	cam->onMouseDragged(x,y);
}

// exports given vertex data to .ply format.
void Renderer::exportToPly(string sceneItemName, string fileName) {
	SceneItem* si = getSceneItem(sceneItemName);
	string path = File::toDataPath(fileName);
	Ply ply;
	ply.save(path, *si->getVertexData());
	printf("Saved: '%s'\n", path.c_str());
}

Texture* Renderer::createTexture(string name, string fileName) {
	Texture* tex = new Texture();
	tex->loadImage(fileName);
	scene->addTexture(name, tex);
	return tex;
}

// Create a diffuse material.
Material* Renderer::createDiffuseTexture(
		 string materialName
		,string textureName
		,string diffuseFileName
		,GLuint imageFormat) 
{
	// @todo create a function: getMaterialOrCreateIfNotExist
	Material* mat = getMaterial(materialName);
	if(mat == NULL) {
		mat =  new Material(materialName, effect->getShaderPtr());
	}
	
	effect->enableDiffuseTexture();
	
	Texture* tex = mat->loadDiffuseTexture(diffuseFileName, imageFormat);
	scene->addMaterial(materialName, mat);
	scene->addTexture(textureName, tex);
	return mat;
}

Material* Renderer::createNormalTexture(
	 string materialName
	,string textureName
	,string normalFileName
	,GLuint imageFormat) 
{
	// @todo create a function: getMaterialOrCreateIfNotExist
	Material* mat = getMaterial(materialName);
	if(mat == NULL) {
		mat =  new Material(materialName, effect->getShaderPtr());
	}
	
	effect->enableNormalTexture();
	
	Texture* tex = mat->loadNormalTexture(normalFileName, imageFormat);
	scene->addMaterial(materialName, mat);
	scene->addTexture(textureName, tex);

	return mat;
}


Light* Renderer::createLight(string name, float r, float g, float b, float a) {
	Light* l = new Light();
	l->setDiffuseColor(r,g,b, a);
	scene->addLight(name, l);
	effect->addLight(l);
	return l;
}

void Renderer::setLightPosition(string name, float x, float y, float z) {
	Light* l = scene->getLight(name);
	l->setPosition(x,y,z);
}

void Renderer::setLightDiffuseColor(string name, float r, float g, float b, float a) {
	Light* l = scene->getLight(name);
	l->setDiffuseColor(r,g,b,a);
}

void Renderer::setLightSpecularColor(string name, float r, float g, float b, float a) {
	Light* l = scene->getLight(name);
	l->setSpecularColor(r,g,b,a);
}

void Renderer::exportToOBJ(string fileName) {
	printf("export!");
	OBJ obj;
	
	// add scene items.
	const map<string, SceneItem*>& items = scene->getSceneItems();
	map<string, SceneItem*>::const_iterator items_it = items.begin();
	while(items_it != items.end()) {
		obj.addSceneItem(items_it->second);
		++items_it;
	}
	
	// add materials.
	const map<string, Material*>& maps = scene->getMaterials();
	map<string, Material*>::const_iterator map_it = maps.begin();
	while(map_it != maps.end()) {
		obj.addMaterial(map_it->second);
		++map_it;
	}
	
	obj.save("test.obj");
}



} // roxlu