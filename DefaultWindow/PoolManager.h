#pragma once

class CGameObject;
class CPoolManager
{
public:
	CPoolManager();
	~CPoolManager();

	void Initialize();
	void Create_Monster(CGameObject* _cFrom) { m_cMonsterPool->Create_Monster(_cFrom); }
	void Return_Monster(CGameObject* _cBullet);
	int Monster_in_Pool() { return m_cMonsterPool->Monster_in_Pool(); }
	void Release();

private:
	class MonsterPool
	{
	public:
		~MonsterPool();

		list<CGameObject*>* Get_MonsterPool() { return &m_MonsterList; }

		void Initialize();
		void Create_Monster(CGameObject* _pPlayer);
		void Release();
		int	Monster_in_Pool() { return m_MonsterList.size(); }

	private:
		static const int iMaxMonsterPool = 255;
		list<CGameObject*> m_MonsterList;
	};

private:
	MonsterPool* m_cMonsterPool;
};
