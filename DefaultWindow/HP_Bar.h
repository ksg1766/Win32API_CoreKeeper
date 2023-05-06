#pragma once
#include "UI.h"
class CHP_Bar :
	public CUI
{
public:
	CHP_Bar();
	virtual ~CHP_Bar();

	// CUI을(를) 통해 상속됨
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual int		LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

	CUI*			GetFrontBar() { return m_pHPfront; }

private:
	CUI*			m_pHPfront;
	CGameObject*	m_pHost;
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
//
//	friend class CCollider;
//	friend class RigidBody;
//	friend class Graphics;
//	friend class CShadow;
//	friend class CEventManager;
//	friend class CPoolManager;
};

