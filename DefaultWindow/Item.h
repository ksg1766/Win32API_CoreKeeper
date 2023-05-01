#pragma once
#include "GameObject.h"

class CPlayer;
class CItem :
	public CGameObject
{
public:
	CItem();
	virtual ~CItem();

	// CGameObject을(를) 통해 상속됨
	virtual void	Initialize()				PURE;
	virtual int		Update(void)				PURE;
	virtual int		LateUpdate(void)			PURE;
	virtual void	Render(HDC hDC)				PURE;
	virtual void	Release(void)				PURE;

	ITEM			GetItemType()	{ return m_eItemType; }
	CPlayer*		GetOwner()		{ return m_pOwner; }
	STATE			GetCurState()	{ return m_eCurState; }

	void			SetOwner(CPlayer* _pOwner) { m_pOwner = _pOwner; }
	virtual void	SetUsing(bool _isUsig)		PURE;//

protected:
	virtual void		SetMotion(void)			PURE;
	virtual void		MoveFrame(void)			PURE;

	bool				m_IsUsing;

	ITEM		m_eItemType;
	CPlayer*	m_pOwner;

	STATE		m_eCurState;
	STATE		m_ePreState;
};

