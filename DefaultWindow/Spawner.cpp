#include "stdafx.h"
#include "Spawner.h"
#include "Collider.h"
#include "Graphics.h"
#include "Cocoon.h"
#include "Managers.h"

CSpawner::CSpawner()
{
}

CSpawner::~CSpawner()
{
	Release();
}

void CSpawner::Initialize(void)
{
	m_eType = TYPE::BOSS;
	m_IsDead = false;
	m_eDir = DIR::END;
	m_eRender = RENDERID::BACKGROUND;

	m_iBiom = 2;

	//m_vPosition = Vector2();
	m_vScale = Vector2(150.f, 150.f);

	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	//m_pCocoon = new CCocoon;
	//m_pCocoon->Initialize();
	//m_pCocoon->SetPosition(m_vPosition);

	m_HasCocoon = false;

	m_pGraphics = new CGraphics;

	m_pGraphics->Initialize(this);

	m_pFrameKey = L"HiveMotherSpawner";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 3000;
	m_tFrame.dwTime = 0;
	m_tFrame.dwTime = GetTickCount();
}

int CSpawner::Update(void)
{
	//if (STATE::IDLE == m_eCurState)
	if (STATE::ATTACK == m_eCurState && !m_HasCocoon && 0 == m_tFrame.iFrameStart)
	{
		m_pCocoon = new CCocoon;
		m_pCocoon->Initialize();
		m_pCocoon->SetPosition(m_vPosition);
		CManagers::instance().Event()->CreateObject(m_pCocoon, TYPE::BOSS);
		//CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::BOSS).push_back(m_pCocoon);
		m_HasCocoon = true;
	}

	return 0;
}

int CSpawner::LateUpdate(void)
{
	SetMotion();
	MoveFrame();

	return 0;
}

void CSpawner::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
}

void CSpawner::Release(void)
{
	Safe_Delete(m_pGraphics);
}

void CSpawner::Action()
{
}

void CSpawner::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 3000;
			m_tFrame.dwTime = GetTickCount();
			break;

		case STATE::ATTACK:		// Take down in this case
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 3000;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CSpawner::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (STATE::IDLE == m_eCurState)
		{
			m_tFrame.iFrameStart = 3;
		}
		else if (STATE::ATTACK == m_eCurState)
		{
			++m_tFrame.iFrameStart;
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
			
			if (3 == m_tFrame.iFrameStart)
				m_HasCocoon = false;
			// iFrameStart == 0 에서 Cocoon생성
		}
		else if (STATE::DEAD == m_eCurState)
			CManagers::instance().Event()->DeleteObject(this);;

		m_tFrame.dwTime = GetTickCount();
	}
}
