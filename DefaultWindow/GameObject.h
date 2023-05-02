#pragma once

#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "Vector2.h"

class CCollider;
class CRigidBody;
class CGraphics;
class CEventManager;
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual int		LateUpdate(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
 	TYPE			GetType()						{ return m_eType; }
	bool			IsDead()						{ return m_IsDead; }
	Vector2			GetPosition()					{ return m_vPosition; }
	Vector2			GetScale()						{ return m_vScale; }
	FRAME			GetFrame()						{ return m_tFrame; }
	DIR				GetDir()						{ return m_eDir; }

	RENDERID		GetRenderID()					{ return m_eRender; }
	CCollider*		GetCollider()					{ return m_pCollider; }
	CRigidBody*		GetRigidBody()					{ return m_pRigidBody; }
	CGraphics*		GetGraphics()					{ return m_pGraphics; }

public:
	void			SetRenderID(RENDERID _eRender)	{ m_eRender = _eRender; }
	void			SetDead(bool _IsDead)			{ m_IsDead = _IsDead; }
	void			SetPosition(Vector2 _vPosition) { m_vPosition = _vPosition; }
	void			SetScale(Vector2 _vScale)		{ m_vScale = _vScale; }
	void			SetDir(DIR _eDir)				{ m_eDir = _eDir; }
	void			SetFrame(FRAME _tFrame)			{ m_tFrame = _tFrame; }

	virtual void	OnCollisionEnter(CCollider* _pOther) {}
	virtual void	OnCollisionStay(CCollider* _pOther) {}
	virtual void	OnCollisionExit(CCollider* _pOther) {}

protected:
	TYPE		m_eType;
	RENDERID	m_eRender;

	bool		m_IsDead;

	DIR			m_eDir;

	Vector2		m_vPosition;
	Vector2		m_vScale;

	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;
	float		m_fTime;

	float		m_fSpeed;

protected:
	CCollider*		m_pCollider;
	CRigidBody*		m_pRigidBody;
	CGraphics*		m_pGraphics;

	friend class CCollider;
	friend class RigidBody;
	friend class Graphics;
	friend class CShadow;
	friend class CEventManager;
	friend class CPoolManager;
};

