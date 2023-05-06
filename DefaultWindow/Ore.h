#pragma once
#include "Item.h"
class COre :
	public CItem
{
public:
	COre();
	virtual ~COre();

	// CItem을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void SetUsing(bool _isUsig) override;
	virtual void SetMotion(void) override;
	virtual void MoveFrame(void) override;
};

 