#pragma once
#include "GameObject.h"
class CHartCoreTile :
	public CGameObject
{
public:
	CHartCoreTile();
	virtual ~CHartCoreTile();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

