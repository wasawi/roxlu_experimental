#ifndef ROXLU_CONVEX_HULL3DH
#define ROXLU_CONVEX_HULL3DH

#include <vector>

#include "Wm5Core.h"
#include "Wm5Mathematics.h"
#include "Wm5Images.h"
#include "Wm5Imagics.h"

using std::vector;

namespace roxlu {

class ConvexHull3D {

public:

	ConvexHull3D();
	~ConvexHull3D();
	
	void addPosition(float *p);
	void addPosition(float x, float y, float z);
	void create();
	
	const Wm5::Vector3f* getVertices();
	const int* getIndices();
	
	size_t getNumPositions();
	size_t getNumVertices();
	size_t getNumIndices();
	

	// -----------------------
	void clear();
	
	size_t num_triangles;
	size_t num_indices;
	size_t num_vertices;
		
	vector<float> positions;
	Wm5::Vector3f* vertices;
	const int* indices;
	Wm5::Query::Type query_type;
	Wm5::ConvexHullf* chull;	

};

inline void ConvexHull3D::addPosition(float* p) {
	addPosition(*p, *(p+1), *(p+2));
}

inline void ConvexHull3D::addPosition(float x, float y, float z) {
	positions.push_back(x);
	positions.push_back(y);
	positions.push_back(z);
}

inline const int* ConvexHull3D::getIndices() {
	return indices;
}

inline const Wm5::Vector3f* ConvexHull3D::getVertices() {
	return vertices;
}

inline size_t ConvexHull3D::getNumPositions() {
	return positions.size()/3;
}

inline size_t ConvexHull3D::getNumVertices() {
	return num_vertices;
}

inline size_t ConvexHull3D::getNumIndices() {
	return num_indices;
}

} // roxlu


#endif