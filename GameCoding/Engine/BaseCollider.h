#pragma once
#include "Component.h"

enum class ColliderType
{
	Sphere,
	AABB,
	OBB,
};

class BaseCollider : public Component
{
public:
	BaseCollider(ColliderType colliderType);
	virtual ~BaseCollider();


	// Ray는 SimpleMath::Ray를 사용 (Types.h에서 using사용)
	virtual bool Intersects(Ray& ray, OUT float& distance) = 0;
	virtual bool Intersects(shared_ptr<BaseCollider>& other) = 0;

	ColliderType GetColliderType() { return _colliderType; }


private:
	ColliderType _colliderType;
};

