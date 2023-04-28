#pragma once

#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "Vector2.h"

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual void	Initialize(void) {};
	virtual int		Update(void)		PURE;
	virtual int		LateUpdate(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	virtual void	OnCollisionEnter()	PURE;
	virtual void	OnCollisionStay()	PURE;
	virtual void	OnCollisionExit()	PURE;

public:
	TYPE			GetType()						{ return m_eType; }
	bool			IsDead()						{ return !m_IsDead; }
	Vector2			GetPosition()					{ return m_vPosition; }
	Vector2			GetScale()						{ return m_vScale; }
	FRAME			GetFrame()						{ return m_tFrame; }

	DIR				GetDir()						{ return m_eDir; }

public:
	void			SetDead(bool _IsDead)			{ m_IsDead = _IsDead; }
	void			SetPosition(Vector2 _vPosition) { m_vPosition = _vPosition; }
	void			SetScale(Vector2 _vScale)		{ m_vScale = _vScale; }
	void			SetDir(DIR _eDir)				{ m_eDir = _eDir; }

protected:
	//void			Update_Rect(void);
	
	friend class	CPoolManager;

protected:
	TYPE		m_eType;
	bool		m_IsDead;

	DIR			m_eDir;

	Vector2		m_vPosition;
	Vector2		m_vScale;

	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;
	float		m_fTime;

	float		m_fSpeed;
};

