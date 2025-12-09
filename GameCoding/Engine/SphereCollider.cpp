#include "pch.h"
#include "SphereCollider.h"
#include "AABBBoxCollider.h"
#include "OBBBoxCollider.h"

SphereCollider::SphereCollider() : BaseCollider(ColliderType::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Update()
{
	_boundingSphere.Center = GetGameObject()->GetTransform()->GetPosition();

	Vec3 scale = GetGameObject()->GetTransform()->GetScale();
	_boundingSphere.Radius = _radius * max(max(scale.x, scale.y), scale.z); // x y z중에 가장 큰값으로 설정

}

bool SphereCollider::Intersects(Ray& ray, OUT float& distance)
{
	// 피격이 되면 거기를 distance에 리턴해주겠다
	return _boundingSphere.Intersects(ray.position, ray.direction, OUT distance);
}

bool SphereCollider::Intersects(shared_ptr<BaseCollider>& other)
{
	ColliderType type = other->GetColliderType();
	switch (type)
	{
	case ColliderType::Sphere:
		return _boundingSphere.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case ColliderType::AABB:
		return _boundingSphere.Intersects(dynamic_pointer_cast<AABBBoxCollider>(other)->GetBoundingBox());
	case ColliderType::OBB:
		return _boundingSphere.Intersects(dynamic_pointer_cast<OBBBoxCollider>(other)->GetBoundingOrientedBox());
	}

	return false;
}
