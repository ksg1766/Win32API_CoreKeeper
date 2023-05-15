#include "stdafx.h"
#include "Managers.h"
#include "Struct.h"

CManagers::CManagers()
{
}

CManagers::~CManagers()
{
	Release();
}

void CManagers::Initialize()
{
	m_pCollision = new CCollisionManager;
	m_pKey = new CKeyManager;
	m_pScroll = new CScrollManager;
	m_pScene = new CSceneManager;
	m_pResource = new CResourceManager;
	m_pResource->Initialize();
	m_pPool = new CPoolManager;
	m_pPool->Initialize();
	m_pTile = new CTileManager;	// Initialize는 EditScene에서 호출
	m_pEvent = new CEventManager;
	m_pEffect = new CEffectManager;
	m_pSound = new CSoundManager;
	m_pSound->Initialize();
	m_pUI = new CUIManager;
	m_pUI->Initialize();
}

void CManagers::Release()
{
	Safe_Delete(m_pCollision);
	Safe_Delete(m_pKey);
	Safe_Delete(m_pScroll);
	Safe_Delete(m_pScene);
	Safe_Delete(m_pPool);
	Safe_Delete(m_pResource);
	Safe_Delete(m_pTile);
	Safe_Delete(m_pEvent);
	Safe_Delete(m_pEffect);
	Safe_Delete(m_pSound);
	Safe_Delete(m_pUI);
}