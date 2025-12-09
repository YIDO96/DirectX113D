#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	//{
	//	shared_ptr<Converter> converter = make_shared<Converter>();
	//
	//	// FBX -> Memory
	//	converter->ReadAssetFile(L"House/House.fbx");
	//
	//	// Memory -> CustomData(file)
	//	converter->ExportMaterialData(L"House/House");		// Material 추출
	//	converter->ExportModelData(L"House/House");			// Model 추출
	//
	//	// CUstumData(file) -> Memory
	//}

	//{
	//	shared_ptr<Converter> converter = make_shared<Converter>();
	//
	//	// FBX -> Memory
	//	converter->ReadAssetFile(L"Tank/Tank.fbx");
	//
	//	// Memory -> CustomData(file)
	//	converter->ExportMaterialData(L"Tank/Tank");		// Material 추출
	//	converter->ExportModelData(L"Tank/Tank");			// Model 추출
	//
	//	// CUstumData(file) -> Memory
	//}

	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Kachujin/Mesh.fbx");
		converter->ExportMaterialData(L"Kachujin/Kachujin");		// Material 추출
		converter->ExportModelData(L"Kachujin/Kachujin");			// Model 추출

		converter->ReadAssetFile(L"Kachujin/Idle.fbx");
		converter->ExportAnimationData(L"kachujin/Idle");

		converter->ReadAssetFile(L"Kachujin/Run.fbx");
		converter->ExportAnimationData(L"kachujin/Run");

		converter->ReadAssetFile(L"Kachujin/Slash.fbx");
		converter->ExportAnimationData(L"kachujin/Slash");
	}
}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
