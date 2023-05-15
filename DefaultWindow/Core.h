#pragma once
#include "Wall.h"
class CCore :
	public CWall
{
public:
	CCore();
	virtual ~CCore();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	//virtual void	OnCollisionEnter(CCollider* _pOther) override;
	virtual void	OnCollisionStay(CCollider* _pOther) override;
	//virtual void	OnCollisionExit(CCollider* _pOther) override;

private:
	void		SetMotion(void);
	void		MoveFrame(void);

	//int			m_iHp;

	bool		m_IsCleared;

	CShadow*	m_pBirdShadow;	//엔딩
/*
protected:
	TYPE		m_eType;
	RENDERID	m_eRender;

	bool		m_IsDead;

	DIR			m_eDir;

	Vector2		m_vPosition;
	Vector2		m_vScale;

	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;
	DWORD		m_dwTime;

	float		m_fSpeed;

protected:
	CCollider*		m_pCollider;
	CRigidBody*		m_pRigidBody;
	CGraphics*		m_pGraphics;
*/
};

