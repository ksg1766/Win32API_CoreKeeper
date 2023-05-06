#pragma once
#include "Enum.h"
#include "Vector2.h"

class CGameObject;
class CPoolManager
{
public:
	CPoolManager();
	~CPoolManager();

	void Initialize();

	void CreateMonster() { m_pMonsterPool->CreateMonster(); }
	void ReturnPool(CGameObject* _pGameObject);
	int  MonsterInPool() { return m_pMonsterPool->MonsterInPool(); }

	void PlayEffect(EFFECT_TYPE _eEffect, Vector2 _vPos) { m_pEffectPool->PlayEffect(_eEffect, _vPos); }

	void Release();

private:
	class MonsterPool
	{
	public:
		~MonsterPool();

		list<CGameObject*>* GetMonsterPool() { return &m_MonsterList; }

		void Initialize();
		void CreateMonster();
		void Release();
		int	 MonsterInPool() { return m_MonsterList.size(); }

	private:
		static const int iMaxMonsterPool = 255;
		list<CGameObject*> m_MonsterList;
	};

	class EffectPool
	{
	public:
		~EffectPool();

		list<CGameObject*>* GetEffectPool() { return &m_EffectsList; }

		void Initialize();
		void PlayEffect(EFFECT_TYPE _eEffect, Vector2 _vPos);
		void Release();

	private:
		//vector<CGameObject*> m_vecEffects;
		list<CGameObject*> m_EffectsList;
	};

	//class SoundPool {};

private:
	MonsterPool* m_pMonsterPool;
	EffectPool*	m_pEffectPool;
};
