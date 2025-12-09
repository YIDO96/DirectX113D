#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "AssimpTool.h"
#include "StaticMeshDemo.h"
#include "ImGuiDemo.h"
#include "TweenDemo.h"
#include "AnimationDemo.h"
#include "SkyDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameDesc desc;
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.f, 0.f, 0.f, 0.f);
	//desc.app = make_shared<StaticMeshDemo>();
	//desc.app = make_shared<TweenDemo>();
	//desc.app = make_shared<SkyDemo>();
	desc.app = make_shared<AnimationDemo>();
	//desc.app = make_shared<AssimpTool>();
	//desc.app = make_shared<ImGuiDemo>();



	GAME->Run(desc);

	return 0;
}