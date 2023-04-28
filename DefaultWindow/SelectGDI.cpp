#include "stdafx.h"
#include "SelectGDI.h"
#include "Managers.h"

CSelectGDI::CSelectGDI(HDC _hDC, PEN_TYPE _eType):m_DC(_hDC), m_hDefaultBrush(nullptr), m_hDefaultPen(nullptr)
{
	HPEN hPen = CManagers::instance().Scene()->GetPen(_eType);
	m_hDefaultPen = (HPEN)SelectObject(_hDC, hPen);
}

CSelectGDI::CSelectGDI(HDC _hDC, BRUSH_TYPE _eType):m_DC(_hDC), m_hDefaultBrush(nullptr), m_hDefaultPen(nullptr)
{
	HBRUSH hBrush = CManagers::instance().Scene()->GetBrush(_eType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_hDC, hBrush);
}

CSelectGDI::~CSelectGDI()
{
	SelectObject(m_DC, m_hDefaultPen);
	SelectObject(m_DC, m_hDefaultBrush);
}
