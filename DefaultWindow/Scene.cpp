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
	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_cObjList[i])
			Safe_Delete(iter);
		m_cObjList[i].clear();
	}
}
