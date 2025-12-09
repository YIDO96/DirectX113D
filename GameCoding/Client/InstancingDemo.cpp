#include "pch.h"
#include "InstancingDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "IndexBuffer.h"



void InstancingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"19.Instancing.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(_shader);
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"../Resources/Textures/veigar.jpg");
		material->SetDiffuseMap(texture);
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		RESOURCES->Add(L"Veigar", material);

		// INSTANCING
		_material = material;
	}

	for (int32 i = 0; i < 10000; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->AddComponent(make_shared<MeshRenderer>());
		{
			obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Veigar"));
		}
		{
			auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
			obj->GetMeshRenderer()->SetMesh(mesh);

			// INSTANCING
			_mesh = mesh;
		}

		_objs.push_back(obj);


	}
	
	RENDER->Init(_shader);

	// INSTANCING
	_instanceBuffer = make_shared<VertexBuffer>();

	for (auto& obj : _objs)
	{
		Matrix world = obj->GetTransform()->GetWorldMatrix();
		_worlds.push_back(world);
	}
	_instanceBuffer->Create(_worlds, /*slot*/1);
}

void InstancingDemo::Update()
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

	_material->Update();


	_mesh->GetVertexBuffer()->PushData();
	_instanceBuffer->PushData();
	_mesh->GetIndexBuffer()->PushData();
	_shader->DrawIndexedInstanced(0, 0, _mesh->GetIndexBuffer()->GetCount(), _objs.size());
}

void InstancingDemo::Render()
{
}
