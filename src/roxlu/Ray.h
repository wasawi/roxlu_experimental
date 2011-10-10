#ifndef VEC3RAYH
#define VEC3RAYH

#include "Vec3.h"

struct Ray {
	Ray() 
		:origin(0)
		,direction(0)
	{
	};
	
	Ray(Vec3 rayOrigin, Vec3 rayDir) 	
		:origin(rayOrigin)
		,direction(rayDir) 
	{
	}
	
	inline Ray& setOrigin(Vec3 o) {
		origin = o;
		return *this;
	}
	
	inline Ray& setDirection(Vec3 d) {
		direction = d;
		return *this;
	}
	
	Vec3 origin;
	Vec3 direction;
};
#endif