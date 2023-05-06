#include "stdafx.h"
#include "Struct.h"
#include "Managers.h"

CResourceManager::CResourceManager()
{
}


CResourceManager::~CResourceManager()
{
	Release();
}

void CResourceManager::Initialize()
{
	Insert_Bmp(L"../Image/BackGround/FullBackBuffer.bmp", L"FullBackBuffer");
	Insert_Bmp(L"../Image/Background/FullStartScene.bmp", L"StartScene");
	Insert_Bmp(L"../Image/Object/Player/Miner.bmp", L"Player");
	Insert_Bmp(L"../Image/Object/Item/PickAxeWood.bmp", L"PickAxeWood");

	//Insert_Bmp(L"../Image/Object/Tileset/tileset0_ground_state0_BMP.bmp", L"tileset0_ground_state0_BMP");
	//Insert_Bmp(L"../Image/Object/Tileset/Wall0.bmp", L"Wall0");
	Insert_Bmp(L"../Image/Object/Tileset/Desert_Ground.bmp", L"Desert_Ground");
	Insert_Bmp(L"../Image/Object/Tileset/Desert_Wall.bmp", L"Desert_Wall");
	Insert_Bmp(L"../Image/Object/Tileset/Nature_Ground.bmp", L"Nature_Ground");
	Insert_Bmp(L"../Image/Object/Tileset/Nature_Wall.bmp", L"Nature_Wall");
	Insert_Bmp(L"../Image/Object/Tileset/LarvaHive_Ground.bmp", L"LarvaHive_Ground");
	Insert_Bmp(L"../Image/Object/Tileset/LarvaHive_Wall.bmp", L"LarvaHive_Wall");

	Insert_Bmp(L"../Image/Object/Boss/Glurch.bmp", L"Glurch");
	Insert_Bmp(L"../Image/Object/Boss/Glurch_Shadow.bmp", L"Glurch_Shadow");
	Insert_Bmp(L"../Image/Object/Monster/Slime.bmp", L"Slime");
	Insert_Bmp(L"../Image/Object/Monster/Slime_Shadow.bmp", L"Slime_Shadow");
	Insert_Bmp(L"../Image/Object/Monster/Larva.bmp", L"Larva");
	Insert_Bmp(L"../Image/Object/Monster/BigLarva.bmp", L"BigLarva");
	Insert_Bmp(L"../Image/Object/Monster/Larva_Shadow.bmp", L"Larva_Shadow");

	Insert_Bmp(L"../Image/Effect/HitEffect_1_5x.bmp", L"HitEffect");

	Insert_Bmp(L"../Image/UI/UI_HealthBar_Window.bmp", L"HealthBarWindow");
	Insert_Bmp(L"../Image/UI/UI_HealthBar_Red.bmp", L"HealthBarRed");
	Insert_Bmp(L"../Image/UI/UI_HungerBar_Window.bmp", L"HungerBarWindow");
	Insert_Bmp(L"../Image/UI/UI_HungerBar_Orange.bmp", L"HungerBarOrange");

	Insert_Bmp(L"../Image/UI/UI_Quick_Slot.bmp", L"QuickSlot");
	Insert_Bmp(L"../Image/UI/UI_Quick_Slot_Using.bmp", L"QuickSlotUsing");

	//Insert_Bmp(L"../Image/UI/UI_HealthBar_Black.bmp", L"HealthBarBlack");
	//Insert_Bmp(L"../Image/UI/UI_HealthBar_Limiter.bmp", L"HealthBarLimiter");
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
