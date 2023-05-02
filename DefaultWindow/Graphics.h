#pragma once
#include "Component.h"
class CGraphics :
	public CComponent
{
public:
	CGraphics() = default;
	virtual ~CGraphics();

	CGraphics(CGameObject* _pHost) : CComponent(_pHost) {}
	virtual void Initialize(CGameObject* _pHost) override;
	virtual void Render(HDC hDC, HDC hMemDC);

};

