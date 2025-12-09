#pragma once
#include "Primitive3D.h"

struct MathUtils
{
	// ------------------
	// Point Test
	// ------------------

	// Sphere to Point
	static bool PointInSphere(const Point3D& point, const Sphere3D& sphere);
	static Point3D ClosestPoint(const Sphere3D& sphere, const Point3D& point);


	// AABB to Point
	static bool PointInAABB(const Point3D& point, const AABB3D& aabb);
	static Point3D ClosestPoint(const AABB3D& aabb, const Point3D& point);


	// OBB to Point
	static bool PointInOBB(const Point3D& point, const OBB3D& obb);
	static Point3D ClosestPoint(const OBB3D& obb, const Point3D& point);


	// Plane to Point
	static bool PointInPlane(const Point3D& point, const Plane3D& plane);
	static Point3D ClosestPoint(const Plane3D& plane, const Point3D& point);


	// Line to Point
	static bool PointInLine(const Point3D& point, const Line3D& line);
	static Point3D ClosestPoint(const Line3D& line, const Point3D& point);


	// Ray to Point
	static bool PointInRay(const Point3D& point, const Ray3D& ray);
	static Point3D ClosestPoint(const Ray3D& ray, const Point3D& point);


	// ------------------
	// Intersection
	// ------------------

	static bool SphereToSphere(const Sphere3D& s1, const Sphere3D& s2);
	static bool SphereToAABB(const Sphere3D& sphere, const AABB3D& aabb);
	static bool SphereToOBB(const Sphere3D& sphere, const OBB3D& obb);
	static bool SphereToPlane(const Sphere3D& sphere, const Plane3D& plane);
	static bool AABBToAABB(const AABB3D& aabb1, const AABB3D& aabb2);

	static Interval3D GetInterval(const AABB3D& aabb, const Vec3& axis);		// AABB의 축에 대한 구간(Interval)계산
	static Interval3D GetInterval(const OBB3D& obb, const Vec3& axis);			// OBB의 축에 대한 구간(Interval)계산
	static bool OverlapOnAxis(const AABB3D& aabb, const OBB3D& obb, const Vec3& axis);
	static bool AABBToOBB(const AABB3D& aabb, const OBB3D& obb);

	static bool AABBToPlane(const AABB3D& aabb, const Plane3D& plane);

	static bool OverlapOnAxis(const OBB3D& obb1, const OBB3D& obb2, const Vec3& axis);
	static bool OBBToOBB(const OBB3D& obb1, const OBB3D& obb2);

	static bool OBBToPlane(const OBB3D& obb, const Plane3D& plane);
	static bool PlaneToPlane(const Plane3D& plane1, const Plane3D& plane2);


	// ------------------
	// Raycast
	// ------------------
	static bool RayCast(const Sphere3D& sphere, const Ray3D& ray, OUT float& distance);
	static bool RayCast(const AABB3D& aabb, const Ray3D& ray, OUT float& distance);
	static bool RayCast(const Plane3D& plane, const Ray3D& ray, OUT float& distance);


	static bool PointInTriangle(const Point3D& p, const Triangle3D& t);

	static Vec3 ProjectVecOnVec(Vec3 from, Vec3 to);
	static Plane3D FromTriangle(const Triangle3D& t);
	static Vec3 Barycentric(const Point3D& p, const Triangle3D& t);
	static bool RayCast(const Triangle3D& triangle, const Ray3D& ray, OUT float& distance);
};
