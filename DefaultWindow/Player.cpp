#include "stdafx.h"
#include "Player.h"
//#include "Item.h"
#include "PickAxe.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Ray.h"
#include "Input.h"
#include "Managers.h"

CPlayer::CPlayer() :m_parrEquipment{}
{
	//ZeroMemory(m_parrEquipment, (UINT)ITEM::END);
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::PLAYER;
	m_vPosition = Vector2(600.f, 500.f);
	m_vScale = Vector2(44.f, 44.f);

	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;
	m_eDir = DIR::DOWN;

	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;
	//m_pInput = new CInput;

	m_pCollider->Initialize(this);
	m_pRigidBody->Initialize(this);
	m_pGraphics->Initialize(this);

	m_pRay = new CRay;
	m_pRay->SetHost(this);
	m_pRay->Initialize();
	CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::RAY).push_back(m_pRay);

	m_pWallTarget = nullptr;

	// 나중에 아이템 획득한 후 처리 과정에서 수정되어야 할 코드
	CItem* _pPickAxe = new CPickAxe;
	_pPickAxe->SetOwner(this); // Initialize보다 먼저해줘야함.
	_pPickAxe->Initialize();
	m_parrEquipment[(UINT)ITEM::WEAPON] = _pPickAxe;
	CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::ITEM).push_back(_pPickAxe);

	m_fSpeed = 10.f;

//	m_dwTime = 0;

	m_pFrameKey = L"Player";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDERID::GAMEOBJECT;
}

int CPlayer::Update(void)
{ 
	Key_Input();
	Action();
	m_pRigidBody->Update();

	return 0;
}

int CPlayer::LateUpdate(void)
{
	OffSet();

	m_pCollider->LateUpdate();

	MoveFrame();
	SetMotion();

	return 0;
}

void CPlayer::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
}

void CPlayer::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pRigidBody);
	Safe_Delete(m_pGraphics);
}

void CPlayer::Key_Input(void)
{
	if (CManagers::instance().Key()->Key_Pressing(VK_RIGHT))
	{
		m_eCurState = STATE::MOVE;
		m_eDir = DIR::RIGHT;
		if (CManagers::instance().Key()->Key_Pressing(VK_UP))
			m_eDir = DIR::RIGHTUP;
		else if (CManagers::instance().Key()->Key_Pressing(VK_DOWN))
			m_eDir = DIR::RIGHTDOWN;
	}
	else if (CManagers::instance().Key()->Key_Pressing(VK_LEFT))
	{
		m_eCurState = STATE::MOVE;
		m_eDir = DIR::LEFT;
		if (CManagers::instance().Key()->Key_Pressing(VK_UP))
			m_eDir = DIR::LEFTUP;
		else if (CManagers::instance().Key()->Key_Pressing(VK_DOWN))
			m_eDir = DIR::LEFTDOWN;
	}

	else if (CManagers::instance().Key()->Key_Pressing(VK_UP))
	{
		m_eCurState = STATE::MOVE;
		m_eDir = DIR::UP;
	}

	else if (CManagers::instance().Key()->Key_Pressing(VK_DOWN))
	{
		m_eCurState = STATE::MOVE;
		m_eDir = DIR::DOWN;
	}

	else
	{
		m_eCurState = STATE::IDLE;
	}

	if (CManagers::instance().Key()->Key_Pressing(VK_SPACE))
	{
		m_eCurState = STATE::ATTACK;
	}
}

void CPlayer::Action(void)
{
	switch (m_eCurState)
	{
	case STATE::IDLE:
		m_pRigidBody->SetVelocity(Vector2::Zero());
		m_pRay->SetScale(Vector2::Zero());
		m_pRay->SetPosition(m_vPosition);
		break;

	case STATE::MOVE:
		m_pRay->SetScale(Vector2::Zero());
		m_pRay->SetPosition(m_vPosition);
		if (DIR::RIGHT == m_eDir)
			m_pRigidBody->SetVelocity(m_fSpeed * Vector2::Right());
		else if (DIR::RIGHTUP == m_eDir)
			m_pRigidBody->SetVelocity(m_fSpeed * Vector2(1.f, -1.f).Normalize());
		else if (DIR::UP == m_eDir)
			m_pRigidBody->SetVelocity(m_fSpeed * Vector2::Up());
		else if (DIR::LEFTUP == m_eDir)
			m_pRigidBody->SetVelocity(m_fSpeed * -1.f * Vector2::One().Normalize());
		else if (DIR::LEFT == m_eDir)
			m_pRigidBody->SetVelocity(m_fSpeed * Vector2::Left());
		else if (DIR::LEFTDOWN == m_eDir)
			m_pRigidBody->SetVelocity(m_fSpeed * Vector2(-1.f, 1.f).Normalize());
		else if (DIR::DOWN == m_eDir)
			m_pRigidBody->SetVelocity(m_fSpeed * Vector2::Down());
		else
			m_pRigidBody->SetVelocity(m_fSpeed * Vector2::One().Normalize());
		break;

	case STATE::ATTACK:
		Attack();
		break;
	}
}
 
void CPlayer::Attack()
{
	m_parrEquipment[(UINT)ITEM::WEAPON]->SetUsing(true);
}

void CPlayer::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			if (m_eDir == DIR::RIGHT)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::UP)
			{
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::LEFT)
			{
				m_tFrame.iFrameStart = 15;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::DOWN)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			break;

		case STATE::MOVE:
			if (m_eDir == DIR::RIGHT)
			{
				m_tFrame.iFrameStart = 7;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::UP)
			{
				m_tFrame.iFrameStart = 11;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 14;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::LEFT)
			{
				m_tFrame.iFrameStart = 15;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 18;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::DOWN)
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			break;

		case STATE::ATTACK:
			if (m_eDir == DIR::RIGHT)
			{
				m_tFrame.iFrameStart = 24;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 25;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if(m_eDir == DIR::UP)
			{
				m_tFrame.iFrameStart = 26;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 27;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::LEFT)
			{
				m_tFrame.iFrameStart = 20;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 21;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::DOWN)
			{
				m_tFrame.iFrameStart = 22;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 23;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		
		m_tFrame.dwTime = GetTickCount();
	}
}

void CPlayer::OffSet(void)
{
	float fOffSetminX = WINCX / 2 - 50;
	float fOffSetmaxX = WINCX / 2 + 50;

	float fOffSetminY = WINCY / 2 - 50;
	float fOffSetmaxY = WINCY / 2 + 50;

	float	fScrollY = CManagers::instance().Scroll()->Get_ScrollY();
	float	fScrollX = CManagers::instance().Scroll()->Get_ScrollX();

	if (fOffSetminX > m_vPosition.x + fScrollX)	// 플레이어가 왼쪽으로 향하고 있는 경우
		CManagers::instance().Scroll()->Set_ScrollX(m_fSpeed);

	if (fOffSetmaxX < m_vPosition.x + fScrollX)	// 플레이어가 오른쪽으로 향하고 있는 경우
		CManagers::instance().Scroll()->Set_ScrollX(-m_fSpeed);


	if (fOffSetminY > m_vPosition.y + fScrollY)
		CManagers::instance().Scroll()->Set_ScrollY(m_fSpeed);

	if (fOffSetmaxY < m_vPosition.y + fScrollY)
		CManagers::instance().Scroll()->Set_ScrollY(-m_fSpeed);
}
