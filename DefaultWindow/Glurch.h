#pragma once
#include "GameObject.h"
class CGlurch :
	public CGameObject
{
public:
	CGlurch();
	virtual ~CGlurch();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	void		Action();
	void		SetMotion(void);
	void		MoveFrame(void);

	int			m_iRange;

	STATE		m_eCurState;
	STATE		m_ePreState;
	Vector2		m_vVelocity;

//protected:
//	TYPE		m_eType;
//	bool		m_IsDead;
//
//	DIR			m_eDir;
//
//	Vector2		m_vPosition;
//	Vector2		m_vScale;
//
//	FRAME		m_tFrame;
//	TCHAR*		m_pFrameKey;
//	float		m_fTime;
//
//	float		m_fSpeed;
//
//protected:
//	CCollider*		m_pCollider;
//	CRigidBody*		m_pRigidBody;
//	CGraphics*		m_pGraphics;
};

