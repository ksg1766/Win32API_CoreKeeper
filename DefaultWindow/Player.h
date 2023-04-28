#pragma once
#include "GameObject.h"

class CCollider;
class CRigidBody;
class CGraphics;
class CInput;
class CItem;
class CPlayer :	public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual int  LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

public:
	STATE		GetState()			{ return m_eCurState; }
	Vector2		GetVelocity()		{ return m_vVelocity; }
	FRAME		GetFrame()			{ return m_tFrame; }

	void		SetState(STATE _eState) { m_eCurState = _eState; }
	void		SetVelocity(Vector2 _tVelocity) { m_vVelocity = _tVelocity; }

public:
	virtual void OnCollisionEnter()	override;
	virtual void OnCollisionStay()	override;
	virtual void OnCollisionExit()	override;

private:
	void		Key_Input(void);
	void		Action(void);
	void		Attack(void);
	void		SetMotion(void);
	void		MoveFrame(void);

	STATE		m_eCurState;
	STATE		m_ePreState;
	Vector2		m_vVelocity;

	CItem*		m_parrEquipment[(UINT)ITEM::END];

	CCollider*		m_pCollider;
	CRigidBody*		m_pRigidBody;
	CGraphics*		m_pGraphics;
	CInput*			m_pInput;
};

