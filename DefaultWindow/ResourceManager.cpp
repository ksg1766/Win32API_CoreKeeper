#include "stdafx.h"
#include "Struct.h"
#include "ResourceManager.h"


CResourceManager::CResourceManager()
{
}


CResourceManager::~CResourceManager()
{
}

void CResourceManager::Initialize()
{
	Insert_Bmp(L"../Image/BackGround/FullBackBuffer.bmp", L"FullBackBuffer");
	Insert_Bmp(L"../Image/Background/FullStartScene.bmp", L"FullStartScene");
	Insert_Bmp(L"../Image/Object/Player/Miner.bmp", L"Player");
	Insert_Bmp(L"../Image/Object/Item/PickAxeWood.bmp", L"PickAxeWood");
	Insert_Bmp(L"../Image/Object/Tileset/tileset0_ground_state0_BMP.bmp", L"tileset0_ground_state0_BMP");
	Insert_Bmp(L"../Image/Object/Tileset/Wall0.bmp", L"Wall0");
}

void CResourceManager::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CResources*		pBmp = new CResources;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImgKey, pBmp);
	}
}

HDC CResourceManager::Find_Image(const TCHAR * pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

template<typename T>
auto& lamDeleteMap = [&](T& Temp)
{
	if (Temp.second)
	{
		delete Temp.second;
		Temp.second = nullptr;
	}
};

void CResourceManager::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
