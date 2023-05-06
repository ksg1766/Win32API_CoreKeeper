#pragma once
#include "Graphics.h"
class CUIGraphics :
	public CGraphics
{
public:
	CUIGraphics();
	virtual ~CUIGraphics();

	virtual void Initialize(CGameObject* _pHost) override;
	virtual void Render(HDC hDC, HDC hMemDC) override;
};

