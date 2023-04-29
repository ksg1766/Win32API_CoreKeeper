#pragma once
#include "Graphics.h"
class CTileGraphics :
	public CGraphics
{
public:
	CTileGraphics();
	virtual ~CTileGraphics();

	virtual void Initialize(CGameObject* _pHost) override;
	virtual void Render(HDC hDC, HDC hMemDC) override;
};

