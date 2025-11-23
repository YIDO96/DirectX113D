#include "pch.h"
#include "16. LightingDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "RenderManager.h"

void LightingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"13.Lighting.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"../Resources/Textures/veigar.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}

	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{ 0.5f, 0.f, 2.f });
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"../Resources/Textures/veigar.jpg");
		_obj2->GetMeshRenderer()->SetTexture(texture);
	}

	RENDER->Init(_shader);
}

void LightingDemo::Update()
{
	_camera->Update();

	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		RENDER->PushLightData(lightDesc);
	}

	{
		MaterialDesc materialDesc;
		materialDesc.ambient = Vec4(0.2f);
		materialDesc.diffuse = Vec4(1.f);
		materialDesc.specular = Vec4(1.f);
		//materialDesc.emissive = Color(0.3f, 0.f, 0.f, 0.5f);

		RENDER->PushMaterialData(materialDesc);
		_obj->Update();
	}

	{
		MaterialDesc materialDesc;
		//mateirlaDesc.ambient = Vec4(0.2f);
		materialDesc.diffuse = Vec4(1.f);
		//mateirlaDesc.specular = Vec4(1.f);
		//mateirlaDesc.emissive = Color(0.3f, 0.f, 0.f, 0.5f);

		RENDER->PushMaterialData(materialDesc);
		_obj2->Update();
	}
}

void LightingDemo::Render()
{
}
