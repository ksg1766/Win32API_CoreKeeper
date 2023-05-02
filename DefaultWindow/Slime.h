#pragma once
#include "Monster.h"
class CSlime :
	public CMonster
{
public:
	CSlime();

	virtual ~CSlime();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int Update(void)		override;
	virtual int LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

private:
	int				m_iRange;
	CGameObject*	m_pTarget;
	Vector2			m_vTargetPoint;

	CShadow*		m_pShadow;

	STATE			m_eCurState;
	STATE			m_ePreState;

	void			Action();
	void			Attack();
	void			SetMotion(void);
	void			MoveFrame(void);
};

