#pragma once
#include "Item.h"
class CTrap :
	public CItem
{
public:
	CTrap();
	virtual ~CTrap();

	// CGameObject을(를) 통해 상속됨
	virtual void	Initialize()				override;
	virtual int		Update(void)				override;
	virtual int		LateUpdate(void)			override;
	virtual void	Render(HDC hDC)				override;
	virtual void	Release(void)				override;

	virtual	void	Use()						override;

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);

private:
	virtual void	SetMotion(void)				override;
	virtual void	MoveFrame(void)				override;

	int				m_iDamage;

	//virtual CItem*	clone() {}				//PURE;

//protected:
//	virtual void	SetMotion(void)				PURE;
//	virtual void	MoveFrame(void)				PURE;
//
//	int			m_iRange;
//
//	bool		m_IsUsing;
//
//	ITEM		m_eItemType;
//	CPlayer*	m_pOwner;
//
//	STATE		m_eCurState;
//	STATE		m_ePreState;
};

