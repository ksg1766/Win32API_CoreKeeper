#include "stdafx.h"
#include "Copper.h"


CCopper::CCopper()
{
}


CCopper::~CCopper()
{
}

void CCopper::Initialize()
{
	__super::Initialize();
	m_vScale = Vector2(48.f, 48.f);
	m_pFrameKey = L"CopperWall";

	//m_eMaterialType = MATERIAL::COPPER;
}

int CCopper::Update(void)
{
	return 0;
}

int CCopper::LateUpdate(void)
{
	return 0;
}

void CCopper::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CCopper::Release(void)
{
}

void CCopper::SetUsing(bool _isUsig)
{
}

void CCopper::SetMotion(void)
{
}

void CCopper::MoveFrame(void)
{
}
