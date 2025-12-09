#include "pch.h"
#include "ModelInstancingDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "IndexBuffer.h"



void ModelInstancingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"22.AnimInstancing.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	shared_ptr<class Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Tower/Tower");
	m1->ReadMaterial(L"Tower/Tower");

	for (int32 i = 0; i < 500; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		//obj->GetOrAddTransform()->SetRotation(Vec3(0.5f, 0, 0));
		obj->GetOrAddTransform()->SetScale(Vec3(0.5f));
		obj->AddComponent(make_shared<ModelRenderer>(_shader));
		{
			obj->GetModelRenderer()->SetModel(m1);
		}

		_objs.push_back(obj);


	}
	
	RENDER->Init(_shader);

}

void ModelInstancingDemo::Update()
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

void ModelInstancingDemo::Render()
{
}
