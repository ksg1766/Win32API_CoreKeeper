#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void)	PURE;
	virtual int	 Update(void)		PURE;
	virtual int	 LateUpdate(void)	PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release(void)		PURE;

//protected:
//	void		Update_Rect(void);
//	void		SetDead(bool _IsDead) { m_IsDead = _IsDead; }
//
//protected:
//	bool		m_IsDead;
//
//	INFO		m_tInfo;
//	RECT		m_tRect;
//
//	Vector2		m_tVelocity;
//	float		m_fSpeed;
};

