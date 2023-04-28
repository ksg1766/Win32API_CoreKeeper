#pragma once
#include "Enum.h"

class CSelectGDI
{
public:
	CSelectGDI(HDC _hDC, PEN_TYPE _eType);
	CSelectGDI(HDC _hDC, BRUSH_TYPE _eType);
	~CSelectGDI();

private:
	HDC	m_DC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;
};

