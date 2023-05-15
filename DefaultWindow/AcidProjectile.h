#pragma once
#include "Projectile.h"
class CAcidProjectile :
	public CProjectile
{
public:
	CAcidProjectile();
	virtual ~CAcidProjectile();

	// CProjectile을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void	OnCollisionEnter(CCollider* _pOther);

private:
	void		Action(void);
	void		Explode();
	void		SetMotion(void);
	void		MoveFrame(void);

	int				m_iDamage;

	int				m_iRange;
	CGameObject*	m_pTarget;
	Vector2			m_vTargetPoint;

	STATE			m_eCurState;
	STATE			m_ePreState;

//protected:
//	TYPE		m_eType;
//	RENDERID	m_eRender;
//
//	bool		m_IsDead;
//
//	DIR			m_eDir;
//
//	Vector2		m_vPosition;
//	Vector2		m_vScale;
//
//	FRAME		m_tFrame;
//	TCHAR*		m_pFrameKey;
//	DWORD		m_dwTime;
//
//	float		m_fSpeed;
};

