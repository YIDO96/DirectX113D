#include "pch.h"
#include "AnimInstancingDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "IndexBuffer.h"
#include "ModelAnimator.h"



void AnimInstancingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"22.AnimInstancing.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	shared_ptr<class Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Kachujin/Kachujin");
	m1->ReadMaterial(L"Kachujin/Kachujin");
	m1->ReadAnimation(L"Kachujin/Idle");
	m1->ReadAnimation(L"Kachujin/Run");
	m1->ReadAnimation(L"Kachujin/Slash");

	for (int32 i = 0; i < 1; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(0.001f));
		obj->AddComponent(make_shared<ModelAnimator>(_shader));
		{
			obj->GetModelAnimator()->SetModel(m1);
		}
		_objs.push_back(obj);
	}
	
	RENDER->Init(_shader);

}

void AnimInstancingDemo::Update()
{
	_camera->Update();

	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.f);
		lightDesc.diffuse = Vec4(0.f);
		lightDesc.specular = Vec4(0.f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f); // right, look
		RENDER->PushLightData(lightDesc);
	}

	INSTANCING->Render(_objs);
}

void AnimInstancingDemo::Render()
{
}
