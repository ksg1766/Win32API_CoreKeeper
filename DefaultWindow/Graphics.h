#pragma once
#include "Component.h"
class CGraphics :
	public CComponent
{
public:
	CGraphics() = default;
	CGraphics(CGameObject* _pHost) : CComponent(_pHost) {}
	void Initialize(CGameObject* _pHost);
	void Render(HDC hDC, HDC hMemDC);

	virtual ~CGraphics();
};

