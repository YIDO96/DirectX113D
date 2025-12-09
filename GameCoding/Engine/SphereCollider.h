#pragma once
#include "BaseCollider.h"

class SphereCollider : public BaseCollider
{
public:
	SphereCollider();
	virtual ~SphereCollider();

	virtual void Update() override;
	// OUT은 아무런 기능x, 리턴하는 용도로 사용한다는 힌트주는 정도
	virtual bool Intersects(Ray& ray, OUT float& distance) override;
	virtual bool Intersects(shared_ptr<BaseCollider>& other) override;

	BoundingSphere& GetBoundingSphere() { return _boundingSphere; }
	void SetRadius(float radius) { _radius = radius; }

private:

	float _radius = 1.f;
	BoundingSphere _boundingSphere; //충돌 영역 표시
};