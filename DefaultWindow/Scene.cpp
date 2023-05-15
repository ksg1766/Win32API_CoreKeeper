#include "stdafx.h"
#include "Scene.h"
#include "Struct.h"
#include "Managers.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	Release();
}

void CScene::Release(void)
{
	for (int i = 0; i < (UINT)TYPE::PROJECTILE + 1; ++i)
	{
		for (auto& iter : m_vecObjList[i])
			CManagers::instance().Event()->DeleteObject(iter);
//			Safe_Delete(iter);
		m_vecObjList[i].clear();
	}
}
