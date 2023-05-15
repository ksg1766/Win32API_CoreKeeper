#include "stdafx.h"
#include "MazeMerchant.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Shadow.h"
#include "Item.h"
#include "Player.h"
#include "Glurch.h"
#include "HiveMother.h"
#include "Managers.h"
#include "SelectGDI.h"

CMazeMerchant::CMazeMerchant()
{
}


CMazeMerchant::~CMazeMerchant()
{
}

void CMazeMerchant::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::MONSTER;
	//m_vPosition = Vector2(600.f, 700.f);

	m_iBiom = 1;

	//m_iMaxHp = 100;
	m_iHp = 1;

	m_iDamage = 5;

	m_pTarget = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front();
	//m_vPosition = Vector2(49.5f * TILECX, 6.5f * TILECY);
	m_vPosition = Vector2(49.5f * TILECX, 7.5f * TILECY);
	m_vScale = Vector2(60.f, 60.f);
	m_iRange = 50 * TILECX;

	m_vTargetPoint = m_pTarget->GetPosition();
	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_pathIndex = 0;

	m_pShadow = new CShadow;
	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;

	m_pShadow->SetHost(this);
	m_pShadow->Initialize();
	m_pShadow->SetScale(Vector2(32.f, 8.f));
	m_pShadow->SetFrameKey(L"Slime_Shadow");

	FRAME _tShadowFrame;
	_tShadowFrame.iFrameStart = 0;
	_tShadowFrame.iFrameStartBf = _tShadowFrame.iFrameStart;
	_tShadowFrame.iFrameEnd = 0;
	_tShadowFrame.iMotion = 0;
	_tShadowFrame.dwSpeed = 100;
	_tShadowFrame.dwTime = GetTickCount();
	m_pShadow->SetFrame(_tShadowFrame);

	m_pCollider->Initialize(this);
	m_pRigidBody->Initialize(this);
	m_pGraphics->Initialize(this);

	m_fSpeed = 3.f;

	m_dwTime = 0;

	m_pFrameKey = L"MazeMonster";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDERID::GAMEOBJECT;

	m_bRaceStart = false;
	m_IsTamed = false;
}

int CMazeMerchant::Update(void)
{
	if (m_vPosition.x < 40.5f * TILECX)
		m_eCurState = STATE::DEAD;
	//Vector2(40.5f * TILECX, 44.5f * TILECY);

	if (m_iHp <= 0)
	{
		m_iHp = 0;
		m_fSpeed = 0;
		m_eCurState = STATE::DEAD;
	}

	if (STATE::DEAD == m_eCurState)
		return 0;

	int i = (m_pTarget->GetPosition().x - (TILECX >> 1)) / TILECX;
	int j = (m_pTarget->GetPosition().y - (TILECY >> 1)) / TILECY;

	if (!m_IsTamed && !m_bRaceStart && 30 <= i && 6 >= j)
	{
		m_bRaceStart = true;
	}

	if (STATE::IDLE == m_eCurState)
	{
		if (m_IsTamed)
		{
			if (m_dwTime + 300 < GetTickCount())
			{
				m_vTargetPoint = m_pTarget->GetPosition();
				AStar();
				m_dwTime = GetTickCount();
				m_eCurState = STATE::MOVE;
			}
			/*if (Vector2::Distance(m_pTarget->GetPosition(), m_vPosition) <= 2 * TILECX)
			{
				m_path.clear();
				m_pRigidBody->SetVelocity(Vector2::Zero());
				m_eCurState = STATE::IDLE;
			}*/
				//m_fSpeed = 0;
		}
		else
		{
			if (m_bRaceStart)
			{
				AStar();
				m_eCurState = STATE::MOVE;
			}
		}
	}

	Action();
	m_pRigidBody->Update();

	return 0;
}

int CMazeMerchant::LateUpdate(void)
{
	if (STATE::DEAD != m_eCurState)
		m_pCollider->LateUpdate();

	MoveFrame();
	SetMotion();

	return 0;
}

void CMazeMerchant::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);
	m_pShadow->Render(hDC);
	m_pGraphics->Render(hDC, hMemDC);

	if (CManagers::instance().Scene()->GetAStarGrid())
	{
		PEN_TYPE ePen = PEN_TYPE::BLUE;

		CSelectGDI temp1(hDC, ePen);
		CSelectGDI temp2(hDC, BRUSH_TYPE::HOLLOW);

		float	fScrollX = CManagers::instance().Scroll()->Get_ScrollX();
		float	fScrollY = CManagers::instance().Scroll()->Get_ScrollY();

		for (auto& iter : m_path)
		{
			int	iX = (TILECX * iter.x) + (TILECX >> 1);
			int	iY = (TILECY * iter.y) + (TILECY >> 1);
			Rectangle(hDC,
				(int)(iX - TILECX / 2.f + fScrollX),
				(int)(iY - TILECY / 2.f + fScrollY),
				(int)(iX + TILECX / 2.f + fScrollX),
				(int)(iY + TILECY / 2.f + fScrollY)
			);
		}
	}
	if (STATE::DEAD != m_eCurState)
		m_pCollider->Render(hDC);
}

void CMazeMerchant::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pRigidBody);
	Safe_Delete(m_pGraphics);
	Safe_Delete(m_pShadow);
}

void CMazeMerchant::Action()
{
	switch (m_eCurState)
	{
	case STATE::IDLE:
	case STATE::MOVE:
	case STATE::ATTACK:
		if (true == m_bRaceStart)
		{
			int	i = (m_vPosition.x - (TILECX >> 1)) / TILECX;
			int	j = (m_vPosition.y - (TILECY >> 1)) / TILECY;
			if (m_path.size() == 0)
				break;
			if (Pos(i, j) == m_path[m_pathIndex])
			{
				if (m_path.size() > m_pathIndex + 2)
					m_pathIndex += 1;
				else
					++m_pathIndex;
			}

			//Vecto2 to Pos
			float	fX = (TILECX * m_path[m_pathIndex].x) + (TILECX >> 1);
			float	fY = (TILECY * m_path[m_pathIndex].y) + (TILECY >> 1);
			//Vector2 next_path = Vector2(fX+0.1f, fY+0.1f) - m_vPosition;
			m_pRigidBody->SetVelocity(m_fSpeed * (Vector2(fX + m_vPosition.x * 0.01f, fY + m_vPosition.y * 0.01f) - m_vPosition).Normalize());
			//m_path[m_pathIndex];

		}
		else
		{
			if (m_IsTamed)
			{
				if (Vector2::Distance(m_pTarget->GetPosition(), m_vPosition) <= 2 * TILECX)
				{
					m_path.clear();
					m_pRigidBody->SetVelocity(Vector2::Zero());
					m_eCurState = STATE::IDLE;
				}
				else
					m_pRigidBody->SetVelocity(m_fSpeed * (m_pTarget->GetPosition() - m_vPosition).Normalize());
			}
			else
				m_pRigidBody->SetVelocity(Vector2::Zero());
		}
		break;

	/*case STATE::ATTACK:
		Attack();
		break;*/
	}
	m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
}

void CMazeMerchant::Attack()
{
}

void CMazeMerchant::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
		case STATE::MOVE:
			//CManagers::instance().Sound()->PlaySound(L"merchantCaveling.wav", CHANNELID::SOUND_EFFECT3, CManagers::instance().Sound()->GetVolume());
			m_vScale = Vector2(60.f, 60.f);
			m_pFrameKey = L"MazeMonster";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::ATTACK:
			//m_vScale = Vector2(120.f, 120.f);
			//m_pFrameKey = L"MazeMonsterEnergy";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::DEAD:
			
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMazeMerchant::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		if (STATE::IDLE == m_eCurState || STATE::MOVE == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		else if (STATE::ATTACK == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
				m_ePreState = m_eCurState;
				m_eCurState = STATE::IDLE;
			}
		}
		if (STATE::DEAD == m_eCurState)
		{
			CManagers::instance().Event()->DeleteObject(this);
		}

		m_tFrame.dwTime = GetTickCount();
	}
}

void CMazeMerchant::OnCollisionEnter(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (!m_IsTamed)
	{
		if (TYPE::ITEM == pOtherObj->GetType())
		{
			m_pTarget = static_cast<CItem*>(pOtherObj)->GetOwner();	//Tamer
			m_IsTamed = true;
			m_iHp = 200;
			m_bRaceStart = false;
			m_path.clear();
			m_pRigidBody->SetVelocity(Vector2::Zero());
		}
	}	//static_cast<CItem*>(pOtherObj)->GetOwner()
}

void CMazeMerchant::OnCollisionStay(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (m_IsTamed)
	{
		if (TYPE::MONSTER == pOtherObj->GetType())
		{
			if (m_dwTime + 1000 < GetTickCount())
			{
				//m_pCollider->SetScale(Vector2(120.f, 120.f));
				m_ePreState = m_eCurState;
				m_eCurState = STATE::ATTACK;

				m_vScale = Vector2(120.f, 120.f);
				m_pFrameKey = L"MazeMonsterEnergy";

				static_cast<CMonster*>(pOtherObj)->SetHp(static_cast<CMonster*>(pOtherObj)->GetHp() - m_iDamage);
				m_dwTime = GetTickCount();
			}
		}
		else if (TYPE::BOSS == pOtherObj->GetType())
		{
			if (m_dwTime + 1000 < GetTickCount())
			{
				m_ePreState = m_eCurState;
				m_eCurState = STATE::ATTACK;

				m_vScale = Vector2(120.f, 120.f);
				m_pFrameKey = L"MazeMonsterEnergy";

				if(BOSS::GLURCH == pOtherObj->GetBossType())
					static_cast<CGlurch*>(pOtherObj)->SetHp(static_cast<CGlurch*>(pOtherObj)->GetHp() - m_iDamage);
				else if (BOSS::HIVEMOTHER == pOtherObj->GetBossType())
					static_cast<CHiveMother*>(pOtherObj)->SetHp(static_cast<CHiveMother*>(pOtherObj)->GetHp() - m_iDamage);
				m_dwTime = GetTickCount();
			}
		}
	}
}
