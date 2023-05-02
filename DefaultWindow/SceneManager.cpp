#include "stdafx.h"
#include "Struct.h"
#include "SceneManager.h"
#include "Scene.h"

CSceneManager::CSceneManager() : m_pCurrentScene(nullptr)
{
	CreateBrushPen();
}

void CSceneManager::Initialize()
{
}

void CSceneManager::LoadPrevScene()
{
	m_pCurrentScene = m_sceneStack.top();
}

void CSceneManager::LoadScene(CScene* _pNewScene)
{
	m_pCurrentScene = _pNewScene;
	m_pCurrentScene->Initialize();	// 초기 상태의 씬이 호출되는 점 주의
	if (!m_sceneStack.empty())
	{
		m_sceneStack.top()->Release();
		Safe_Delete(m_sceneStack.top());
	}
	m_sceneStack.push(m_pCurrentScene);
}

void CSceneManager::TerminateScene()
{
	m_pCurrentScene->Release();
	m_sceneStack.pop();
	if (!m_sceneStack.empty())
		LoadPrevScene();
	else
		;	// Terminate Game

}

void CSceneManager::Release()
{
	while (!m_sceneStack.empty())
	{
		Safe_Delete(m_sceneStack.top());
		m_sceneStack.pop();
	}

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CSceneManager::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

CSceneManager::~CSceneManager()
{
	Release();
}
