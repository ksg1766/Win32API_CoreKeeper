#pragma once

class CGameObject;
class CPoolManager
{
public:
	CPoolManager();
	~CPoolManager();

	void Initialize();
	void CreateMonster() { m_cMonsterPool->CreateMonster(); }
	void ReturnMonster(CGameObject* _cBullet);
	int MonsterInPool() { return m_cMonsterPool->MonsterInPool(); }
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
		int	MonsterInPool() { return m_MonsterList.size(); }

	private:
		static const int iMaxMonsterPool = 255;
		list<CGameObject*> m_MonsterList;
	};

private:
	MonsterPool* m_cMonsterPool;
};
