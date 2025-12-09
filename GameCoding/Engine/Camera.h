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

	void SetProjectionType(ProjectionType type) { _type = type; }
	ProjectionType GetRrojectionType() { return _type; }
	void UpdateMatrix();


	void SetNear(float nearPlane) { _near = nearPlane; }
	void SetFar(float farPlane) { _far = farPlane; }
	void SetFov(float fov) { _fov = fov; }
	void SetWidth(float width) { _width = width; }
	void SetHeight(float height) { _height = height; }


	Matrix& GetViewMatrix() { return _matView; }
	Matrix& GetProjectionMatrix() { return _matProjection; }
	
	float GetWidth() { return _width; }
	float GetHeight() { return _height; }

private:
	ProjectionType _type = ProjectionType::Perspective;
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


public:
	// 관련된 문체들을 가져오기
	void SortGameObject();
	void Render_Forward();

	void SetCullingMaskLayerOnOff(uint8 layer, bool on)
	{
		if (on)
			_cullingMask |= (1 << layer);
		else
			_cullingMask &= ~(1 << layer);
	}

	// 아무것도 그리지 않겠다.
	void SetCullingMaskAll() { SetCullingMask(UINT32_MAX); }
	void SetCullingMask(uint32 mask) { _cullingMask = mask; }
	// 비트연산을 통해서 그려줄지 안그려줄지 판단
	bool IsCulled(uint8 layer) { return (_cullingMask & (1 << layer)) != 0; }

private:
	// 비트마스크 - 그릴지 안그릴지에 대한 규칙
	uint32 _cullingMask = 0;
	vector<shared_ptr<GameObject>> _vecForward;
};

