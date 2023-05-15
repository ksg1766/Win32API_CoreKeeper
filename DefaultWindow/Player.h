#pragma once
#include "GameObject.h"

//class CInput;
class CRay;
class CItem;
class CStorage;
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
	int			GetHp()				{ return m_iHp; }
	STATE		GetState()			{ return m_eCurState; }
	Vector2		GetVelocity()		{ return m_vVelocity; }
	FRAME		GetFrame()			{ return m_tFrame; }

	CCollider*	GetWallTarget()		{ return m_pWallTarget; }
	CRay*		GetRay()			{ return m_pRay; }
	//
	CGameObject**			GetQuickSlot()		{ return m_parrQuickSlot; }
	UINT*					GetQuickSlotCount() { return m_iQuickSlotCount; }
	//vector<CGameObject*>*	GetStorage();

	void		SetHp(int _iHp)		{ m_iHp = _iHp; }
	void		SetState(STATE _eState) { m_eCurState = _eState; }
	void		SetVelocity(Vector2 _tVelocity) { m_vVelocity = _tVelocity; }
	void		SetWallTarget(CCollider* _pWallTarget) { m_pWallTarget = _pWallTarget; }

	//void		SetQuickSlotCount(UINT _iIndex, int _iNum) { m_iQuickSlotCount[_iIndex] = _iNum; }

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	void		Key_Input(void);
	void		Action(void);
	void		Attack(void);
	void		SetMotion(void);
	void		MoveFrame(void);

	void		OffSet(void);

	int			m_iMaxHp;
	int			m_iHp;

	DWORD		m_dwAttackSpeed;

	STATE		m_eCurState;
	STATE		m_ePreState;
	Vector2		m_vVelocity;
	// 벽은 한번에 한 개만 충돌해야 하므로

	CCollider*	m_pWallTarget;	// 상위 클래스로 옮기는 것 고려

	//CStorage*		m_pStorage;
	CGameObject*	m_parrQuickSlot[10];
	UINT			m_iQuickSlotCount[10];

	CRay*		m_pRay;
	//CInput*			m_pInput;

	bool		m_bFootStepSound;

	friend class CHP_Bar;
};

