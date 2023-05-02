#pragma once

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollider;
class CCollisionManager
{
public:
	CCollisionManager();
	~CCollisionManager();

	void LateUpdate();

public:
	map<ULONGLONG, bool>& GetMapColInfo() { return m_mapColInfo; }
	void SetMapColInfo(ULONGLONG ID, bool bCollision) { m_mapColInfo[ID] = bCollision; }
	
	void CheckGroup(TYPE _eLeft, TYPE _eRight);
	void Reset();

private:
	map<ULONGLONG, bool> m_mapColInfo;
	UINT	m_arrCheck[(UINT)TYPE::END];

	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);
	void CheckCollisionByType(TYPE _eTypeLeft, TYPE _eTypeRight);

};

