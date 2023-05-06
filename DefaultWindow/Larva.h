#pragma once
#include "Monster.h"
class CLarva :
	public CMonster
{
public:
	CLarva();
	virtual ~CLarva();

	virtual void Initialize(void)	override;
	virtual int Update(void)		override;
	virtual int LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

	virtual void Action()			override;
	virtual void Attack()			override;
	virtual void SetMotion(void)	override;
	virtual void MoveFrame(void)	override;
};

