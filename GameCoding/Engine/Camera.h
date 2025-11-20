#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,		// 원근 투형 (3d, 원근법에 따라 크기 차이)
	Orthographic,		// 직교 투영 (2d, 화면에 들어온 모든 오브젝트는 같은 크기)
};

class Camera : public Component
{
	using Super = Component;

public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;
	void UpdateMatrix();


	void SetNear(float nearPlane) { _near = nearPlane; }
	void SetFar(float farPlane) { _far = farPlane; }
	void SetFov(float fov) { _fov = fov; }
	void SetWidth(float width) { _width = width; }
	void SetHeight(float height) { _height = height; }


	Matrix& GetViewMatrix() { return _matView; }
	Matrix& GetProjectionMatrix() { return _matProjection; }
	

private:
	Matrix _matView = Matrix::Identity;
	Matrix _matProjection = Matrix::Identity;

	float _near = 1.f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.f;
	float _width = 0.f;
	float _height = 0.f;

public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

