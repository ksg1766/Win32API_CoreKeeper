#pragma once
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TileManager.h"
#include "PoolManager.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "UIManager.h"

class CManagers
{
public:
	static CManagers& instance()	// Singleton
	{
		static CManagers*	m_instance = new CManagers();
		return *m_instance;
	}
	/*static void		Destroy_Instance(void)
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}*/

	void Initialize();
	void Release();

	CCollisionManager*	Collision() { return m_pCollision; }
	CKeyManager*		Key() { return m_pKey; }
	CScrollManager*		Scroll() { return m_pScroll; }
	CSceneManager*		Scene() { return m_pScene; }
	CPoolManager*		Pool() { return m_pPool; }
	CResourceManager*	Resource() { return m_pResource; }
	CTileManager*		Tile() { return m_pTile; }
	CEventManager*		Event() { return m_pEvent; }
	CEffectManager*		Effect() { return m_pEffect; }
	CSoundManager*		Sound() { return m_pSound; }
	CUIManager*			UI() { return m_pUI; }

private:
	CManagers();
	~CManagers();

	static CManagers*	m_instance;

	CCollisionManager*	m_pCollision;
	CKeyManager*		m_pKey;
	CScrollManager*		m_pScroll;
	CSceneManager*		m_pScene;
	CPoolManager*		m_pPool;
	CResourceManager*	m_pResource;
	CTileManager*		m_pTile;
	CEventManager*		m_pEvent;
	CEffectManager*		m_pEffect;
	CSoundManager*		m_pSound;
	CUIManager*			m_pUI;
};