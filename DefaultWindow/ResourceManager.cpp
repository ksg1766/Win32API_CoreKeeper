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
	Insert_Bmp(L"../Image/BackGround/BackBuffer.bmp", L"FullBackBuffer");
	Insert_Bmp(L"../Image/Background/StartScene.bmp", L"StartScene");
	Insert_Bmp(L"../Image/Background/IntroSlide1.bmp", L"IntroSlide1");
	Insert_Bmp(L"../Image/Background/IntroSlide2.bmp", L"IntroSlide2");
	Insert_Bmp(L"../Image/Background/IntroSlide3.bmp", L"IntroSlide3");
	Insert_Bmp(L"../Image/Background/IntroSlide4.bmp", L"IntroSlide4");
	Insert_Bmp(L"../Image/Background/IntroSlide5.bmp", L"IntroSlide5");
	Insert_Bmp(L"../Image/Background/BlackSolid.bmp", L"BlackSolid");
	Insert_Bmp(L"../Image/Background/EndingScene.bmp", L"EndingScene");

	Insert_Bmp(L"../Image/Background/title_background.bmp", L"title_background");

	Insert_Bmp(L"../Image/Object/Player/Miner.bmp", L"Player");
	Insert_Bmp(L"../Image/Object/Item/PickAxeWood.bmp", L"PickAxeWood");
	Insert_Bmp(L"../Image/Object/Item/Trap.bmp", L"Trap");

	//Insert_Bmp(L"../Image/Object/Tileset/CopperWall.bmp", L"CopperWall");
	Insert_Bmp(L"../Image/Object/Item/Copper_Stone.bmp", L"CopperStone");
	
	//Insert_Bmp(L"../Image/Object/Tileset/tileset0_ground_state0_BMP.bmp", L"tileset0_ground_state0_BMP");
	//Insert_Bmp(L"../Image/Object/Tileset/Wall0.bmp", L"Wall0");
	Insert_Bmp(L"../Image/Object/Tileset/Desert_Ground.bmp", L"Desert_Ground");
	Insert_Bmp(L"../Image/Object/Tileset/Desert_Wall.bmp", L"Desert_Wall");
	Insert_Bmp(L"../Image/Object/Item/Desert_Block.bmp", L"Desert_Block");
	Insert_Bmp(L"../Image/Object/Tileset/Nature_Ground.bmp", L"Nature_Ground");
	Insert_Bmp(L"../Image/Object/Tileset/Nature_Wall.bmp", L"Nature_Wall");
	Insert_Bmp(L"../Image/Object/Tileset/LarvaHive_Ground.bmp", L"LarvaHive_Ground");
	Insert_Bmp(L"../Image/Object/Tileset/LarvaHive_Wall.bmp", L"LarvaHive_Wall");

	Insert_Bmp(L"../Image/Object/Tileset/HartcoreTile.bmp", L"HartcoreTile");
	Insert_Bmp(L"../Image/Object/Core.bmp", L"Core");
	Insert_Bmp(L"../Image/Object/Statue_Glurch.bmp", L"Statue_Glurch");
	Insert_Bmp(L"../Image/Object/Statue_HiveMother.bmp", L"Statue_HiveMother");

	Insert_Bmp(L"../Image/Object/Boss/GlurchBig.bmp", L"Glurch");
	Insert_Bmp(L"../Image/Object/Boss/Glurch_Shadow_Big.bmp", L"Glurch_Shadow");

	Insert_Bmp(L"../Image/Object/Boss/HiveMotherMouth.bmp", L"HiveMotherMouth");
	Insert_Bmp(L"../Image/Object/Boss/HiveMotherBase.bmp", L"HiveMotherBase");
	Insert_Bmp(L"../Image/Object/Boss/Hive_Mother_Shadow.bmp", L"Hive_Mother_Shadow");
	Insert_Bmp(L"../Image/Object/Boss/HiveMotherSpawner.bmp", L"HiveMotherSpawner");
	Insert_Bmp(L"../Image/Object/Boss/Cocoon.bmp", L"Cocoon");
	Insert_Bmp(L"../Image/Object/Boss/AcidProjectile.bmp", L"AcidProjectile");
	Insert_Bmp(L"../Image/Object/Boss/AcidSplat.bmp", L"AcidSplat");

	Insert_Bmp(L"../Image/Object/Monster/Slime.bmp", L"Slime");
	Insert_Bmp(L"../Image/Object/Monster/Slime_Shadow.bmp", L"Slime_Shadow");
	Insert_Bmp(L"../Image/Object/Monster/Larva.bmp", L"Larva");
	Insert_Bmp(L"../Image/Object/Monster/BigLarva.bmp", L"BigLarva");
	Insert_Bmp(L"../Image/Object/Monster/Larva_Shadow.bmp", L"Larva_Shadow");
	
	Insert_Bmp(L"../Image/Effect/HitEffect_1_5x.bmp", L"HitEffect");
	Insert_Bmp(L"../Image/Effect/MyGlowSmall.bmp", L"GlowEffect");
	Insert_Bmp(L"../Image/Effect/BigBigBlood.bmp", L"BigBigBlood");
	Insert_Bmp(L"../Image/Effect/BloodSplat.bmp", L"BloodSplat");
	Insert_Bmp(L"../Image/Effect/SlimeExplosion.bmp", L"SlimeExplosion");
	Insert_Bmp(L"../Image/Effect/SlimeImpact.bmp", L"SlimeImpact");
	Insert_Bmp(L"../Image/Effect/MortalWarning.bmp", L"MortalWarning");

	Insert_Bmp(L"../Image/Object/Monster/MazeMonster.bmp", L"MazeMonster");
	Insert_Bmp(L"../Image/Object/Monster/MazeMonsterEnergy.bmp", L"MazeMonsterEnergy");

	Insert_Bmp(L"../Image/UI/UI_HealthBar_Window.bmp", L"HealthBarWindow");
	Insert_Bmp(L"../Image/UI/UI_HealthBar_Red.bmp", L"HealthBarRed");
	Insert_Bmp(L"../Image/UI/UI_HungerBar_Window.bmp", L"HungerBarWindow");
	Insert_Bmp(L"../Image/UI/UI_HungerBar_Orange.bmp", L"HungerBarOrange");

	Insert_Bmp(L"../Image/UI/UI_HealthBar_Boss.bmp", L"UI_HealthBar_Boss");
	Insert_Bmp(L"../Image/UI/UI_HealthBar_Red_Boss.bmp", L"UI_HealthBar_Red_Boss");
	
	Insert_Bmp(L"../Image/UI/UI_Quick_Slot.bmp", L"QuickSlot");
	Insert_Bmp(L"../Image/UI/UI_Quick_Slot_Using.bmp", L"QuickSlotUsing");
	
	Insert_Bmp(L"../Image/UI/FontNumber.bmp", L"FontNumber");
	Insert_Bmp(L"../Image/UI/Font0.bmp", L"Font0");
	Insert_Bmp(L"../Image/UI/Font1.bmp", L"Font1");
	Insert_Bmp(L"../Image/UI/Font2.bmp", L"Font2");
	Insert_Bmp(L"../Image/UI/Font3.bmp", L"Font3");
	Insert_Bmp(L"../Image/UI/Font4.bmp", L"Font4");
	Insert_Bmp(L"../Image/UI/Font5.bmp", L"Font5");
	Insert_Bmp(L"../Image/UI/Font6.bmp", L"Font6");
	Insert_Bmp(L"../Image/UI/Font7.bmp", L"Font7");
	Insert_Bmp(L"../Image/UI/Font8.bmp", L"Font8");
	Insert_Bmp(L"../Image/UI/Font9.bmp", L"Font9");

	Insert_Bmp(L"../Image/Object/Boss/bird_shadow.bmp", L"bird_shadow");
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
