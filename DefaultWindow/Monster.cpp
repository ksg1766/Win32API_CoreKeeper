#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
	m_IsDead = false;
	m_eRender = RENDERID::GAMEOBJECT;
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
}

int CMonster::Update(void)
{
	return 0;
}

int CMonster::LateUpdate(void)
{
	return 0;
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release(void)
{
}