#include "pch.h"
#include "SceneManager.h"

void SceneManager::Update()
{
	if (_currentScene == nullptr)
		return;

	_currentScene->Update();		
	_currentScene->LateUpdate();	// 카메라가 들어감 
	_currentScene->Render();
}