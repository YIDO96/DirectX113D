#pragma once
#include "IExecute.h"
#include "Geometry.h"


class GameObject;

class AmbientDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	// Shader
	shared_ptr<Shader> _shader;

	// Object
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _obj2;
	// Camera
	shared_ptr<GameObject> _camera;
};