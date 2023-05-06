#pragma once
#include "GameObject.h"
class CEffect :
	public CGameObject
{
public:
	CEffect();
	virtual ~CEffect();

	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual int		LateUpdate(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

	EFFECT_TYPE		GetEffectType() { return m_eEffectType; }

protected:
	virtual void	SetMotion(void)		PURE;
	virtual	void	MoveFrame(void)		PURE;
	EFFECT_TYPE		m_eEffectType;
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
//
//protected:
//	CCollider*		m_pCollider;
//	CRigidBody*		m_pRigidBody;
//	CGraphics*		m_pGraphics;
};

