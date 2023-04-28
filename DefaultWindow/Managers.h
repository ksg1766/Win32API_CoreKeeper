#pragma once
#include "SceneManager.h"
#include "ResourceManager.h"
#include "EditManager.h"
#include "PoolManager.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "CollisionManager.h"

class CManagers
{
public:
	static CManagers& instance()	// Singleton
	{
		static CManagers*	m_instance = new CManagers();
		return *m_instance;
	}

	void Initialize();
	void Release();

	CCollisionManager*	Collision() { return m_pCollision; }
	CKeyManager*		Key() { return m_pKey; }
	CScrollManager*		Scroll() { return m_pScroll; }
	CSceneManager*		Scene() { return m_pScene; }
	CPoolManager*		Pool() { return m_pPool; }
	CResourceManager*	Resource() { return m_pResource; }
	CEditManager*		Edit() { return m_pEdit; }

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
	CEditManager*		m_pEdit;
};