#include "stdafx.h"
#include "Player.h"
//#include "Item.h"
#include "PickAxe.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
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
	m_eType = TYPE::PLAYER;
	m_vPosition = Vector2(400.f, 300.f);
	m_vScale = Vector2(44.f, 44.f);

	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;
	m_eDir = DIR::DOWN;

	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;
	m_pInput = new CInput;

	m_pCollider->Initialize(this);
	m_pRigidBody->Initialize(this);
	m_pGraphics->Initialize(this);

	// 나중에 아이템 획득한 후 처리 과정에서 수정되어야 할 코드
	CItem* _pPickAxe = new CPickAxe;
	_pPickAxe->Initialize(this);
	m_parrEquipment[(UINT)ITEM::WEAPON] = _pPickAxe;
	for (int i = 0; i < (UINT)ITEM::END; ++i)
	{
		if (nullptr != m_parrEquipment[i])
			m_parrEquipment[i]->Initialize(this);
	}

	m_fSpeed = 5.f;

	m_fTime = 0;

	m_pFrameKey = L"Player";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CPlayer::Update(void)
{ 
	//m_pInput->Update();
	Key_Input();
	Action();
	m_pRigidBody->Update();

	m_parrEquipment[(UINT)ITEM::WEAPON]->Update();

	//__super::Update_Rect();

	return 0;
}

int CPlayer::LateUpdate(void)
{
	m_pCollider->LateUpdate();
	MoveFrame();
	SetMotion();

	//if (STATE::ATTACK == m_eCurState)
		m_parrEquipment[(UINT)ITEM::WEAPON]->LateUpdate();

	return 0;
}

void CPlayer::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_parrEquipment[(UINT)ITEM::WEAPON]->Render(hDC);
	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
	//if(STATE::ATTACK == m_eCurState)
}

void CPlayer::Release(void)
{
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
		if (CManagers::instance().Key()->Key_Down(VK_SPACE))
		{
			// Do Something
		}
		m_pRigidBody->SetVelocity(Vector2::Zero());
		break;

	case STATE::MOVE:
		if (CManagers::instance().Key()->Key_Down(VK_SPACE))
		{
			// Do Something
		}
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
	//if(m_parrEquipment[(UINT)ITEM::WEAPON])
		//m_parrEquipment[(UINT)ITEM::WEAPON]->LateUpdate();

	//m_parrEquipment[(UINT)ITEM::WEAPON]->Render();
		//->LateUpdate();
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

void CPlayer::OnCollisionEnter()
{
}

void CPlayer::OnCollisionStay()
{
}

void CPlayer::OnCollisionExit()
{
}
