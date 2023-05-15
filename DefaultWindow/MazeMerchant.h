#pragma once
#include "Monster.h"
class CMazeMerchant :
	public CMonster
{
public:
	CMazeMerchant();
	virtual ~CMazeMerchant();

	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual int		LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

private:
	void			StartRace()			{ m_bRaceStart = true; }

	virtual void	Action()			override;
	virtual void	Attack()			override;
	virtual void	SetMotion(void)		override;
	virtual void	MoveFrame(void)		override;

	virtual void	OnCollisionEnter(CCollider* _pOther) override;
	virtual void	OnCollisionStay(CCollider* _pOther) override;

private:
	bool	m_bRaceStart;
	bool	m_IsTamed;
};

