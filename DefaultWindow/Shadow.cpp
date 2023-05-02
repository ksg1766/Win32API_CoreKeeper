#include "stdafx.h"
#include "Shadow.h"
#include "Managers.h"
#include "Graphics.h"

CShadow::CShadow() : m_pHost(nullptr)
{
}


CShadow::~CShadow()
{
	Release();
}

void CShadow::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::END;
	m_vPosition = m_pHost->m_vPosition;
	m_vScale = m_pHost->m_vScale;
	//m_vScale = Vector2(144.f, 96.f);

	m_fSpeed = 30.f;

	m_fTime = 0;

	m_pFrameKey = L"Glurch_Shadow";
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	
	m_pGraphics = new CGraphics;
	m_pGraphics->Initialize(this);

	m_eRender = RENDERID::GAMEOBJECT;
}

int CShadow::Update(void)
{
	//m_vPosition = m_pHost->m_vPosition;

	return 0;
}

int CShadow::LateUpdate(void)
{
	return 0;
}

void CShadow::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
}

void CShadow::Release(void)
{
	Safe_Delete(m_pGraphics);
}
