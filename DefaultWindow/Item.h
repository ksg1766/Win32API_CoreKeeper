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
	virtual void Initialize(CPlayer* _pOwner)		PURE;
	virtual int Update(void)						PURE;
	virtual int LateUpdate(void)					PURE;
	virtual void Render(HDC hDC)					PURE;
	virtual void Release(void)						PURE;

	ITEM		GetItemType()	{ return m_eItemType; }
	CPlayer*	GetOwner()		{ return m_pOwner; }

	virtual void OnCollisionEnter()	PURE;
	virtual void OnCollisionStay()	PURE;
	virtual void OnCollisionExit()	PURE;

protected:
	virtual void		SetMotion(void)		PURE;
	virtual void		MoveFrame(void)		PURE;

	ITEM		m_eItemType;
	CPlayer*	m_pOwner;

	STATE		m_eCurState;
	STATE		m_ePreState;
};

