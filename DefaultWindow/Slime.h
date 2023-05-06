#pragma once
#include "Monster.h"
class CSlime :
	public CMonster
{
public:
	CSlime();

	virtual ~CSlime();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int Update(void)		override;
	virtual int LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

private:
	virtual void		Action()		override;
	virtual void		Attack()		override;
	virtual void		SetMotion(void)	override;
	virtual void		MoveFrame(void)	override;

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);
};

