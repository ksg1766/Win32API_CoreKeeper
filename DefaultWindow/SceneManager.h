#pragma once
#include "Scene.h"

//class CScene;
class CSceneManager
{
public:
	CSceneManager();

	void Initialize();
	void LoadPrevScene();
	void LoadScene(CScene* _pCurrentScene);
	void TerminateScene();
	void Release();

	CScene* CurrentScene() { return m_pCurrentScene; };
	void*	SetCurrentScene(CScene* _pCurrentScene) { m_pCurrentScene = _pCurrentScene; };
	HBRUSH	GetBrush(BRUSH_TYPE _eBrush) { return m_arrBrush[(UINT)_eBrush]; }
	HPEN	GetPen(PEN_TYPE _ePen) { return m_arrPen[(UINT)_ePen]; }

	void CreateBrushPen();

	~CSceneManager();

private:
	CScene*			m_pCurrentScene;
	stack<CScene*>	m_sceneStack;

	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];
};

