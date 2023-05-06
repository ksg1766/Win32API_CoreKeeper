#pragma once
#include "Effect.h"
class CHitEffect :
	public CEffect
{
public:
	CHitEffect();
	virtual ~CHitEffect();

	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual int		LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

private:
	virtual void	SetMotion(void)		override;
	virtual	void	MoveFrame(void)		override;
};

