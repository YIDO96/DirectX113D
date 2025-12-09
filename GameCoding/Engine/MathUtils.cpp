#include "pch.h"
#include "MathUtils.h"

bool MathUtils::PointInSphere(const Point3D& point, const Sphere3D& sphere)
{
    float magSq = (point - sphere.position).LengthSquared();
    float radSq = sphere.radius * sphere.radius;

    return magSq <= radSq;
}
Point3D MathUtils::ClosestPoint(const Sphere3D& sphere, const Point3D& point)
{
    Vec3 sphereToPointDir = (point - sphere.position);
    sphereToPointDir.Normalize();


    return sphere.position + sphereToPointDir * sphere.radius;
}



bool MathUtils::PointInAABB(const Point3D& point, const AABB3D& aabb)
{
    Point3D min = AABB3D::GetMin(aabb);
    Point3D max = AABB3D::GetMax(aabb);

    if (point.x < min.x || point.y < min.y || point.z < min.z)
        return false;

    if (point.x > max.x || point.y > max.y || point.z > max.z)
        return false;

    return true;
}
Point3D MathUtils::ClosestPoint(const AABB3D& aabb, const Point3D& point)
{
    Point3D result = point;
    Point3D minPt = AABB3D::GetMin(aabb);
    Point3D maxPt = AABB3D::GetMax(aabb);

    result.x = max(result.x, minPt.x);
    result.y = max(result.y, minPt.y);
    result.z = max(result.z, minPt.z);

    result.x = min(result.x, maxPt.x);
    result.y = min(result.y, maxPt.y);
    result.z = min(result.z, maxPt.z);



    return result;
}



bool MathUtils::PointInOBB(const Point3D& point, const OBB3D& obb)
{
    Vec3 dir = point - obb.position;

    Point3D result;
    vector<Vec3> axis;
    axis.push_back(obb.orientation.Right());
    axis.push_back(obb.orientation.Up());
    axis.push_back(obb.orientation.Backward());

    vector<float> size;
    size.push_back(obb.size.x);
    size.push_back(obb.size.y);
    size.push_back(obb.size.z);

    for (int i = 0; i < 3; i++)
    {
        // 내적을 통해서 거리 구하기
        float distance = dir.Dot(axis[i]);

        if (distance > size[i])
            return false;
        if (distance < size[i])
            return false;
    }

    return true;
}
Point3D MathUtils::ClosestPoint(const OBB3D& obb, const Point3D& point)
{
    Point3D result = obb.position;
    Vec3 dir = point - obb.position;

    vector<Vec3> axis;
    axis.push_back(obb.orientation.Right());
    axis.push_back(obb.orientation.Up());
    axis.push_back(obb.orientation.Backward());

    vector<float> size;
    size.push_back(obb.size.x);
    size.push_back(obb.size.y);
    size.push_back(obb.size.z);

    for (int i = 0; i < 3; i++)
    {
        float distance = dir.Dot(axis[i]);

        if (distance > size[i])
            distance = size[i];

        if (distance < -size[i])
            distance = -size[i];

        result += axis[i] * distance;
    }


    return result;
}



bool MathUtils::PointInPlane(const Point3D& point, const Plane3D& plane)
{
    float dot = point.Dot(plane.normal);

    return dot == plane.distance;
}
Point3D MathUtils::ClosestPoint(const Plane3D& plane, const Point3D& point)
{
    float dot = point.Dot(plane.normal);
    float distance = dot - plane.distance;

    return point - plane.normal * distance;
}



bool MathUtils::PointInLine(const Point3D& point, const Line3D& line)
{
    Point3D closest = ClosestPoint(line, point);

    float distanceSq = (closest - point).LengthSquared();

    return distanceSq == 0.f; // 소수점이기에 원래는 불가능이지만 이해를 위해서
}
Point3D MathUtils::ClosestPoint(const Line3D& line, const Point3D& point)
{
    //  C
    //
    //  D   A------B 
    // line.start = A / line.end = B / point = c
    // lVec = A->B 벡터
    // (point - line.start) = A->C 벡터
    // (point - line.start).Dot(lVec) = |AB|*|AD|
    // lVec.Dot(lVec) = |AB|*|AB|
    // t = |AD| / |AB| -> 0 ~ 1 사이의 값이면 선 안에 있다

    Vec3 lVec = line.end - line.start; // Line Vector
    float t = (point - line.start).Dot(lVec) / lVec.Dot(lVec);
    t = fmaxf(t, 0.0f); // Clamp to 0
    t = fminf(t, 1.0f); // Clamp to 1
    return line.start + lVec * t;
}



bool MathUtils::PointInRay(const Point3D& point, const Ray3D& ray)
{
    if (point == ray.origin)
        return true;

    Vec3 norm = point - ray.origin;
    norm.Normalize();

    float diff = norm.Dot(ray.direction);
    return diff == 1.0f;
}
Point3D MathUtils::ClosestPoint(const Ray3D& ray, const Point3D& point)
{
    float t = (point - ray.origin).Dot(ray.direction);

    t = fmaxf(t, 0.0f);

    return Point3D(ray.origin + ray.direction * t);
}



bool MathUtils::SphereToSphere(const Sphere3D& s1, const Sphere3D& s2)
{
    float sum = s1.radius + s2.radius;

    // 제곱으로 비교
    float sqDistance = (s1.position - s2.position).LengthSquared();

    return sqDistance <= sum * sum;
}
bool MathUtils::SphereToAABB(const Sphere3D& sphere, const AABB3D& aabb)
{
    Point3D closestPoint = ClosestPoint(aabb, sphere.position);
    float distSq = (sphere.position - closestPoint).LengthSquared();
    float radiusSq = sphere.radius * sphere.radius;

    return distSq < radiusSq;
}
bool MathUtils::SphereToOBB(const Sphere3D& sphere, const OBB3D& obb)
{
    Point3D closestPoint = ClosestPoint(obb, sphere.position);
    float distSq = (sphere.position - closestPoint).LengthSquared();
    float radiusSq = sphere.radius * sphere.radius;

    return distSq < radiusSq;
}
bool MathUtils::SphereToPlane(const Sphere3D& sphere, const Plane3D& plane)
{
    Point3D closestPoint = ClosestPoint(plane, sphere.position);
    float distSq = (sphere.position - closestPoint).LengthSquared();
    float radiusSq = sphere.radius * sphere.radius;

    return distSq < radiusSq;
}
bool MathUtils::AABBToAABB(const AABB3D& aabb1, const AABB3D& aabb2)
{
    Point3D aMin = AABB3D::GetMin(aabb1);   // aabb1의 최소 좌표
    Point3D aMax = AABB3D::GetMax(aabb1);   // aabb1의 최대 좌표
    Point3D bMin = AABB3D::GetMin(aabb2);   // aabb2의 최소 좌표
    Point3D bMax = AABB3D::GetMax(aabb1);   // aabb2의 최대 좌표


    // 모든 축에 대해서 겹치면 true
    return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
            (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
            (aMin.z <= bMax.z && aMax.z >= bMin.z);
}

Interval3D MathUtils::GetInterval(const AABB3D& aabb, const Vec3& axis)
{
    Vec3 i = AABB3D::GetMin(aabb); // 최소 좌표
    Vec3 a = AABB3D::GetMax(aabb); // 최대 좌표

    Vec3 vertex[8] =
    {
        Vec3(i.x, a.y, a.z),
        Vec3(i.x, a.y, i.z),
        Vec3(i.x, i.y, a.z),
        Vec3(i.x, i.y, i.z),
        Vec3(a.x, a.y, a.z),
        Vec3(a.x, a.y, i.z),
        Vec3(a.x, i.y, a.z),
        Vec3(a.x, i.y, i.z)
    };

    // 최소, 최대 구하기
    Interval3D result;
    result.min = result.max = axis.Dot(vertex[0]); // 첫꼭짓점으로 초기화

    for (int i = 1; i < 8; i++)
    {
        float projection = axis.Dot(vertex[i]);
        result.min = min(result.min, projection);
        result.max = max(result.max, projection);
    }

    return result;
}
Interval3D MathUtils::GetInterval(const OBB3D& obb, const Vec3& axis)
{
    Vec3 vertex[8]; // OBB 꼭짓점을 저장할 배열

    Vec3 C = obb.position;  // OBB Center
    Vec3 E = obb.size;      // OBB extents

    vector<Vec3> A;         // OBB Axis
    A.push_back(obb.orientation.Right());
    A.push_back(obb.orientation.Up());
    A.push_back(obb.orientation.Backward());

    // 각 좌표를 구해주기
    vertex[0] = C + A[0] * E.x + A[1] * E.y + A[2] * E.z;
    vertex[1] = C - A[0] * E.x + A[1] * E.y + A[2] * E.z;
    vertex[2] = C + A[0] * E.x - A[1] * E.y + A[2] * E.z;
    vertex[3] = C + A[0] * E.x + A[1] * E.y - A[2] * E.z;
    vertex[4] = C - A[0] * E.x - A[1] * E.y - A[2] * E.z;
    vertex[5] = C + A[0] * E.x - A[1] * E.y - A[2] * E.z;
    vertex[6] = C - A[0] * E.x + A[1] * E.y - A[2] * E.z;
    vertex[7] = C - A[0] * E.x - A[1] * E.y + A[2] * E.z;

    // 최소/ 최대 구하기
    Interval3D result;
    result.min = result.max = axis.Dot(vertex[0]);

    for (int i = 1; i < 8; i++)
    {
        float projection = axis.Dot(vertex[i]);
        result.min = min(result.min, projection);
        result.max = max(result.max, projection);
    }

    return result;
}
bool MathUtils::OverlapOnAxis(const AABB3D& aabb, const OBB3D& obb, const Vec3& axis)
{
    Interval3D a = GetInterval(aabb, axis);         // AABB 구간 계산
    Interval3D b = GetInterval(obb, axis);          // OBB 구간 계산
    return ((b.min <= a.max) && (a.min <= b.max));  // 구간이 겹칠 경우 true반환
}
bool MathUtils::AABBToOBB(const AABB3D& aabb, const OBB3D& obb)
{
    Vec3 test[15] =
    {
        Vec3(1, 0, 0),                  // AABB axis 1
        Vec3(0, 1, 0),                  // AABB axis 2
        Vec3(0, 0, 1),                  // AABB axis 3
        obb.orientation.Right(),        // OBB  axis 1
        obb.orientation.Up(),           // OBB  axis 2
        obb.orientation.Backward(),     // OBB  axis 3
        // 외적으로 생성된 추가 축
    };

    // 추가 축 계산 (AABB축과 OBB축의 외적)
    for (int i = 0; i < 3; ++i)
    {
        test[6 + i * 3 + 0] = test[i].Cross(test[3]);
        test[6 + i * 3 + 1] = test[i].Cross(test[4]);
        test[6 + i * 3 + 2] = test[i].Cross(test[5]);
    }

    // 모든 축에 대해서 겹치는지 검사
    for (int i = 0; i < 15; ++i)
    {
        if (OverlapOnAxis(aabb, obb, test[i]) == false)
            return false;   // 하나라도 겹치지 않으면 false 반환
    }

    return true; // 모두 겹쳐야 true 반환
}

bool MathUtils::AABBToPlane(const AABB3D& aabb, const Plane3D& plane)
{
    float pLen = aabb.size.x * fabsf(plane.normal.x) +
        aabb.size.y * fabsf(plane.normal.y) +
        aabb.size.z * fabsf(plane.normal.z);

    float dot = plane.normal.Dot(aabb.position);    // 평면의 법선과 AABB 중심의 내적
    float dist = dot - plane.distance;              // 평면 상수와의 차이 계산

    return fabsf(dist) <= pLen;
}

bool MathUtils::OverlapOnAxis(const OBB3D& obb1, const OBB3D& obb2, const Vec3& axis)
{
    Interval3D a = GetInterval(obb1, axis);         // obb2 구간 계산
    Interval3D b = GetInterval(obb2, axis);         // obb1 구간 계산
    return ((b.min <= a.max) && (a.min <= b.max));  // 구간이 겹칠 경우 true반환
}
bool MathUtils::OBBToOBB(const OBB3D& obb1, const OBB3D& obb2)
{
    Vec3 test[15] =
    {
        obb1.orientation.Right(),
        obb1.orientation.Up(),
        obb1.orientation.Backward(),
        obb2.orientation.Right(),
        obb2.orientation.Up(),
        obb2.orientation.Backward(),
        // 외적 축
    };

    // 추가 축 계산 (AABB축과 OBB축의 외적)
    for (int i = 0; i < 3; ++i)
    {
        test[6 + i * 3 + 0] = test[i].Cross(test[3]);
        test[6 + i * 3 + 1] = test[i].Cross(test[4]);
        test[6 + i * 3 + 2] = test[i].Cross(test[5]);
    }

    // 모든 축에 대해서 겹치는지 검사
    for (int i = 0; i < 15; ++i)
    {
        if (OverlapOnAxis(obb1, obb2, test[i]) == false)
            return false;   // 하나라도 겹치지 않으면 false 반환
    }

    return true; // 모두 겹쳐야 true 반환
}

bool MathUtils::OBBToPlane(const OBB3D& obb, const Plane3D& plane)
{
    float pLen = obb.size.x * fabsf(plane.normal.x) +
        obb.size.y * fabsf(plane.normal.y) +
        obb.size.z * fabsf(plane.normal.z);

    float dot = plane.normal.Dot(obb.position);    // 평면의 법선과 AABB 중심의 내적
    float dist = dot - plane.distance;              // 평면 상수와의 차이 계산

    return fabsf(dist) <= pLen;
}
bool MathUtils::PlaneToPlane(const Plane3D& plane1, const Plane3D& plane2)
{
    Vec3 d = plane1.normal.Cross(plane2.normal); // 두 평면의 법선 벡터의 외적

    return d.Dot(d) != 0;       // 외적의 결과가 0이 아니라면 두 평변은 평행하지 않은 것으로 간주
}




bool MathUtils::RayCast(const Sphere3D& sphere, const Ray3D& ray, OUT float& distance)
{
    Vec3 e = sphere.position - ray.origin;          // 레이의 시작점에서 구의 중심까지의 벡터

    float rSq = sphere.radius * sphere.radius;      // 구의 반지름 제곱값
    float eSq = e.LengthSquared();                  // e 벡터 길이의 제곱값

    float a = e.Dot(ray.direction);                 // 레이 방향과 e 벡터의 내적

    float bSq = eSq - (a * a);                      // b의 제곱 (삼각형의 한 변의 제곱)
    float f = sqrt(rSq - bSq);                      // f는 삼각형의 다른 변 (구의 반지금에서 b를 뺀 값)


    // 충돌이 발생하지 않는 경우 -> 내적값으로 구한 반지름이랑 차이가 난다면
    if ((rSq - bSq) < 0.0f)
        return false;

    // 레이의 시작점이 구 내부에 있을 경우
    if (eSq < rSq)
    {
        distance = a + f;
        return true;
    }

    // 구 외부에서 시작하여 구에 닿지 않는 경우
    distance = a - f;       // 구에서 가장 가까운 거리
    return false;
}
bool MathUtils::RayCast(const AABB3D& aabb, const Ray3D& ray, OUT float& distance)
{
    // Cyrus-Beck Clipping
    // AABB를 구성하는 6개의 평면에 대해 클리핑 진행
    // Point3D point = ray.origin +ray.direction * t;

    Vec3 min = AABB3D::GetMin(aabb);
    Vec3 max = AABB3D::GetMax(aabb);

    // 각 축에 대해서 레이가 AABB의 두 평면(최소값, 최대값)과 만나는 t값 계산
    float t1 = (min.x - ray.origin.x) / ray.direction.x;
    float t2 = (max.x - ray.origin.x) / ray.direction.x;

    float t3 = (min.y - ray.origin.y) / ray.direction.y;
    float t4 = (max.y - ray.origin.y) / ray.direction.y;

    float t5 = (min.z - ray.origin.z) / ray.direction.z;
    float t6 = (max.z - ray.origin.z) / ray.direction.z;


    // 가장 큰 최소 t값(tmin)과 가장 작은 최대 t값(tmax)을 계산
    float tmin = fmaxf(fmaxf(fminf(t1, t2), fminf(t3, t4)), fminf(t5, t6));
    float tmax = fminf(fminf(fmaxf(t1, t2), fmaxf(t3, t4)), fmaxf(t5, t6));

    // tmax가 0보다 작으면 레이가 AABB의 뒤쪽을 향함
    if (tmax < 0)
        return false;

    // tmin이 tmax보다 크면 레이는 AABB를 교차하지 않음
    if (tmin > tmax)
        return false;

    // 실제 충돌 거리 계산
    distance = (tmin < 0.0f) ? tmax : tmin;
    return true;
}
bool MathUtils::RayCast(const Plane3D& plane, const Ray3D& ray, OUT float& distance)
{
    float nd = ray.direction.Dot(plane.normal); // 레이 방향과 평면의 법선의 내적
    float pn = ray.origin.Dot(plane.normal);    // 레이 시작점과 평면의 법선 내적

    // nd가 0보다 크거나 같으면 레이와 평면은 평행하거나 레이가 평면에서 멀어짐
    if (nd >= 0.0f)
        return false;

    // 실제 충돌 거리 계산
    float t = (plane.distance - pn) / nd;
    if (t >= 0.0f)
    {
        distance = t; // 충돌 지점까지의 거리
        return true;
    }

    return false;
}

bool MathUtils::PointInTriangle(const Point3D& p, const Triangle3D& t)
{
    Vec3 a = t.a - p;           // p에서 꼭짓점 a로의 벡터
    Vec3 b = t.b - p;           // p에서 꼭짓점 b로의 벡터
    Vec3 c = t.c - p;           // p에서 꼭짓점 c로의 벡터

    Vec3 normPBC = b.Cross(c);  // PBC의 법선 벡터
    Vec3 normPCA = c.Cross(a);  // PCA의 법선 벡터
    Vec3 normPAB = a.Cross(b);  // PAB의 법선 벡터

    // 번선 벡터들의 방향이 모두 같은지 확인해서 점이 삼각형 내부에 있는지를 판단.
    // PBC와 PCA 법선 벡터가 서로 반대 방향이라면
    if (normPBC.Dot(normPCA) < 0.0f)
        return false;
    // PBC와 PAB 법선 벡터가 서로 반대 방향이라면
    else if (normPBC.Dot(normPAB) < 0.0f)
        return false;

    return true;
}

Vec3 MathUtils::ProjectVecOnVec(Vec3 from, Vec3 to)
{
    to.Normalize();

    float dist = from.Dot(to);

    return to * dist;
}

Plane3D MathUtils::FromTriangle(const Triangle3D& t)
{//삼각형이 있을 때 삼각형을 이용해서 플레인을 만드는 유틸
    Plane3D result;

    result.normal = (t.b - t.a).Cross(t.c - t.a);
    result.normal.Normalize();

    result.distance = result.normal.Dot(t.a);

    return result;
}

Vec3 MathUtils::Barycentric(const Point3D& p, const Triangle3D& t)
{
    return Vec3();
}

bool MathUtils::RayCast(const Triangle3D& triangle, const Ray3D& ray, OUT float& distance)
{
    
    Plane3D plane = FromTriangle(triangle);

    float t = 0;
    // 평면과 레이 충돌 검사
    if (RayCast(plane, ray, OUT t) == false)
        return false;

    Point3D result = ray.origin + ray.direction * t;

    Vec3 barycentric = Barycentric(result, triangle);

    if (barycentric.x >= 0.0f && barycentric.x <= 1.0f &&
        barycentric.y >= 0.0f && barycentric.y <= 1.0f &&
        barycentric.z >= 0.0f && barycentric.z <= 1.0f)
    {
        distance = t;
        return true;
    }

    return false;
}
