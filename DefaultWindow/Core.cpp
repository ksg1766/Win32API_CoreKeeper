#include "stdafx.h"
#include "Core.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Graphics.h"
#include "Managers.h"
#include "GameScene.h"
#include "Shadow.h"


CCore::CCore()
{
}

CCore::~CCore()
{
}

void CCore::Initialize(void)
{
	m_eType = TYPE::WALL;
	m_eRender = RENDERID::GAMEOBJECT;
	m_IsDead = false;
	m_vPosition = Vector2(11 * TILECX, 10 * TILECY);
	m_vScale = Vector2(240.f, 240.f);

	m_iHp = INT32_MAX;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = 0;
	m_tFrame.dwSpeed = 200;

	m_pFrameKey = L"Core";
	m_dwTime = 0;
	m_fSpeed = 0.f;

	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);

	m_IsCleared = false;

	m_pBirdShadow = new CShadow;
	//m_pBirdShadow->Initialize();

	CGraphics* pBirdGraphics = new CGraphics;

	pBirdGraphics->Initialize(m_pBirdShadow);
	m_pBirdShadow->SetGraphics(pBirdGraphics);
	m_pBirdShadow->SetFrameKey(L"bird_shadow");
	
	FRAME tBirdShadowFrame;
	tBirdShadowFrame.iFrameStart = 0;
	tBirdShadowFrame.iFrameEnd = 0;
	tBirdShadowFrame.iFrameStartBf;
	tBirdShadowFrame.iMotion = 0;
	tBirdShadowFrame.dwTime = 0;
	tBirdShadowFrame.dwSpeed = 1000;

	m_pBirdShadow->SetFrame(tBirdShadowFrame);

	m_pBirdShadow->SetPosition(Vector2(-45.f * TILECX, (float)WINCY));
	m_pBirdShadow->SetScale(Vector2(640.f, 880.f));
}

int CCore::Update(void)
{
	//SetMotion();
	//MoveFrame();

	return 0;
}

int CCore::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	return 0;
}

void CCore::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	MoveFrame();

	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
	if (m_IsCleared)
	{
		m_pBirdShadow->SetPosition(m_pBirdShadow->GetPosition() + 30.f * Vector2::Right());
		m_pBirdShadow->Render(hDC);			
	}
}

void CCore::Release(void)
{
	Safe_Delete(m_pGraphics);
	Safe_Delete(m_pCollider);
}

//void CCore::OnCollisionEnter(CCollider * _pOther)
//{
//	__super::OnCollisionEnter(_pOther);
//}

void CCore::OnCollisionStay(CCollider * _pOther)
{
	__super::OnCollisionStay(_pOther);

	CGameObject* pOtherObj = _pOther->GetHost();
	if (TYPE::PLAYER == pOtherObj->GetType())
		if (CManagers::instance().Key()->Key_Down('G'))
			if (static_cast<CGameScene*>(CManagers::instance().Scene()->CurrentScene())->GetGlurchDead() && static_cast<CGameScene*>(CManagers::instance().Scene()->CurrentScene())->GetHiveMotherDead())
			{
				m_IsCleared = true;
				m_tFrame.iFrameEnd = 4;
			}
}

void CCore::SetMotion(void)
{
	//if (m_ePreState != m_eCurState)
	//if (!m_IsCleared)
	//{
	//	m_tFrame.iFrameStart = 0;
	//	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	//	m_tFrame.iFrameEnd = 0;
	//	m_tFrame.iMotion = 0;
	//	m_tFrame.dwSpeed = 300;
	//	m_tFrame.dwTime = GetTickCount();
	//}
	//else
	//{
	//	m_tFrame.iFrameStart = 0;
	//	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	//	m_tFrame.iFrameEnd = 4;
	//	m_tFrame.iMotion = 0;
	//	m_tFrame.dwSpeed = 200;
	//	m_tFrame.dwTime = GetTickCount();
	//}
}

void CCore::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			if (m_IsCleared)
			{
				CManagers::instance().Scroll()->StartScrollShaking(10);
				//m_pBirdShadow->GetFrame().dwTime = GetTickCount();
			}
		}
		m_tFrame.dwTime = GetTickCount();
	}
}
