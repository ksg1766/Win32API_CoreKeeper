#include "stdafx.h"
#include "Scene.h"
#include "Struct.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	Release();
}

void CScene::Release(void)
{
	for (int i = 0; i < (int)TYPE::WALL; ++i)
	{
		for (auto& iter : m_vecObjList[i])
			Safe_Delete(iter);
		m_vecObjList[i].clear();
	}
}
