#pragma once
#include "Effect.h"
class CGlowEffect :
	public CEffect
{
public:
	CGlowEffect();
	virtual ~CGlowEffect();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	virtual void SetMotion(void) override;
	virtual void MoveFrame(void) override;
};

