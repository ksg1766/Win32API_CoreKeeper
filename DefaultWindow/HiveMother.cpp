#include "stdafx.h"
#include "HiveMother.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Shadow.h"
#include "Player.h"
#include "Spawner.h"
#include "HP_Bar_Boss.h"
#include "AcidProjectile.h"
#include "Managers.h"
#include "Statue_HiveMother.h"
#include "GameScene.h"

CHiveMother::CHiveMother()
{
}

CHiveMother::~CHiveMother()
{
	Release();
}

void CHiveMother::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::BOSS;
	m_eBossType = BOSS::HIVEMOTHER;
	//m_vPosition = Vector2(45 * TILECX, 35 * TILECY);
	m_vPosition = Vector2(89 * TILECX, 38 * TILECY);
	m_vScale = Vector2(420.f, 420.f);
	m_iRange = 7 * TILECX;//때리면 깨야함

	m_iBiom = 2;

	m_iMaxHp = 300;
	m_iHp = m_iMaxHp;

	m_pHPBar = new CHP_Bar_Boss;
	static_cast<CHP_Bar_Boss*>(m_pHPBar)->SetHost(this);
	m_pHPBar->Initialize();
	CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::UI).push_back(m_pHPBar);

	m_iDamage = 20;//

	m_vTargetPoint = m_vPosition;
	m_pTarget = nullptr;
	
	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	for (auto& iter : m_pSpawners)
	{
		iter = new CSpawner;
		iter->Initialize();
		CManagers::instance().Event()->CreateObject(iter, TYPE::BOSS);
		//CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::BOSS).push_back(iter);
	}
	m_pSpawners[0]->SetPosition(m_vPosition + Vector2(5.f * TILECX, -4.f * TILECY));
	m_pSpawners[1]->SetPosition(m_vPosition + Vector2(4.f * TILECX, 4.f * TILECY));
	m_pSpawners[2]->SetPosition(m_vPosition + Vector2(-6.f * TILECX, 5.f * TILECY));
	m_pSpawners[3]->SetPosition(m_vPosition + Vector2(-6.f * TILECX, -1.f * TILECY));
	m_pSpawners[4]->SetPosition(m_vPosition + Vector2(-2.f * TILECX, -5.f * TILECY));

	m_pShadow = new CShadow;
	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;
	m_pGraphics2 = new CGraphics;

	m_pShadow->SetHost(this);
	m_pShadow->Initialize();
	m_pShadow->SetScale(Vector2(180.f, 120.f));
	m_pShadow->SetFrameKey(L"Hive_Mother_Shadow");

	m_pCollider->Initialize(this);
	m_pCollider->SetOffset(Vector2(0.f, -m_vScale.y * 0.1f));
	m_pCollider->SetScale(Vector2(m_vScale.x * 0.6f, m_vScale.y * 0.5f));

	m_pGraphics->Initialize(this);
	m_pGraphics2->Initialize(this);

	m_LaunchOnlyOnce = false;
	m_fSpeed = 0.f;

	m_dwTime = 0;

	m_pFrameKey = L"HiveMotherMouth";
	m_tFrame.iFrameStart = 12;
	m_tFrame.iFrameEnd = 12;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 60;
	m_tFrame.dwTime = GetTickCount();

	m_pFrameKey2 = L"HiveMotherBase";
	m_tFrame2.iFrameStart = 0;
	m_tFrame2.iFrameEnd = 14;
	m_tFrame2.iFrameStartBf = m_tFrame2.iFrameStart;
	m_tFrame2.iMotion = 0;
	m_tFrame2.dwSpeed = 80;
	m_tFrame2.dwTime = GetTickCount();

	m_eRender = RENDERID::GAMEOBJECT;
}

int CHiveMother::Update(void)
{
	if (m_iHp < 0)
	{
		m_iHp = 0;
		m_fSpeed = 0;
		m_pFrameKey = L"BigBigBlood";
		m_pFrameKey2 = L"BloodSplat";
		m_eCurState = STATE::DEAD;

		CManagers::instance().Sound()->PlaySound(L"Hive_Mother_Death.wav", CHANNELID::SOUND_EFFECT8, CManagers::instance().Sound()->GetVolume());
		for (auto& iter : m_pSpawners)
			iter->SetState(STATE::IDLE);
		m_vPosition = m_vPosition + 200 * Vector2::Up();
		m_pShadow->SetScale(Vector2::Zero());
	}

	if (STATE::DEAD == m_eCurState)
	{
		//CManagers::instance().Event()->DeleteObject(this);
		//DeadEffect() 는 나중에 손볼 것.    
		return 0;
	}

	if (m_iHp != m_iMaxHp && STATE::IDLE == m_eCurState)
	{
		CManagers::instance().Sound()->StopAll();
		CManagers::instance().Sound()->PlayBGM(L"Boss_Theme_full.wav", CManagers::instance().Sound()->GetVolume());
		CManagers::instance().Sound()->PlaySound(L"hiveMotherwakeUp.wav", CHANNELID::SOUND_EFFECT8, CManagers::instance().Sound()->GetVolume());
		m_eCurState = STATE::ATTACK;
		//CManagers::instance().Sound()->StopAll();
	}

	CGameObject* pPlayer = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front();

	if (STATE::ATTACK == m_eCurState && Vector2::Distance(pPlayer->GetPosition(), m_vPosition) <= m_iRange)
	{
		m_pTarget = pPlayer;
		for(auto& iter:m_pSpawners)
			iter->SetState(STATE::ATTACK);
	}
	else
	{
		m_pTarget = nullptr;
	}

	if (nullptr != m_pTarget && m_eCurState == STATE::ATTACK)
	{
		m_vTargetPoint = pPlayer->GetPosition();
	}
	else
	{
		m_eCurState = STATE::IDLE;

		for (auto& iter : m_pSpawners)
			iter->SetState(STATE::IDLE);

		m_vTargetPoint = m_vPosition;
	}

	Action();

	return 0;
}

int CHiveMother::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	SetMotion();
	MoveFrame();

	return 0;
}

void CHiveMother::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);
	HDC		hMemDC2 = CManagers::instance().Resource()->Find_Image(m_pFrameKey2);

	m_pShadow->Render(hDC);
	m_pGraphics2->Render(hDC, hMemDC2);
	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
	
	m_pHPBar->Render(hDC);
}

void CHiveMother::Release(void)
{
	Safe_Delete(m_pShadow);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
	CManagers::instance().Event()->DeleteObject(m_pHPBar);
}

void CHiveMother::OnCollisionEnter(CCollider * _pOther)
{
}

void CHiveMother::OnCollisionStay(CCollider * _pOther)
{
}

void CHiveMother::OnCollisionExit(CCollider * _pOther)
{
}

void CHiveMother::Action()
{
	if (STATE::ATTACK == m_eCurState)
	{
		if (10 == m_tFrame.iFrameStart && !m_LaunchOnlyOnce)
		{
			LaunchAcid();
			m_LaunchOnlyOnce = true;
		}
		else if (0 == m_tFrame.iFrameStart)
		{
			m_LaunchOnlyOnce = false;
		}
	}
}

void CHiveMother::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			m_tFrame.iFrameStart = 12;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStartBf;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			m_tFrame2.iFrameStart = 0;
			m_tFrame2.iFrameEnd = 0;
			m_tFrame2.iFrameStartBf = m_tFrame2.iFrameStart;
			m_tFrame2.iMotion = 0;
			m_tFrame2.dwSpeed = 100;
			m_tFrame2.dwTime = GetTickCount();
			break;

		case STATE::ATTACK:		// Take down in this case
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			m_tFrame2.iFrameStart = 0;
			m_tFrame2.iFrameEnd = 14;
			m_tFrame2.iFrameStartBf = m_tFrame2.iFrameStart;
			m_tFrame2.iMotion = 0;
			m_tFrame2.dwSpeed = 100;
			m_tFrame2.dwTime = GetTickCount();
			break;

		case STATE::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();

			m_tFrame2.iFrameStart = 0;
			m_tFrame2.iFrameEnd = 9;
			m_tFrame2.iFrameStartBf = m_tFrame2.iFrameStart;
			m_tFrame2.iMotion = 0;
			m_tFrame2.dwSpeed = 100;
			m_tFrame2.dwTime = GetTickCount();
			break;
		}
		
		m_ePreState = m_eCurState;
	}
}

void CHiveMother::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (STATE::IDLE == m_eCurState)
		{
			m_tFrame.iFrameStart = 12;
		}
		else if (STATE::ATTACK == m_eCurState)
		{
			++m_tFrame.iFrameStart;
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		else if (STATE::DEAD == m_eCurState)
		{
			++m_tFrame.iFrameStart;
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
				CManagers::instance().Event()->DeleteObject(this);
				static_cast<CGameScene*>(CManagers::instance().Scene()->CurrentScene())->SetHiveMotherDead(true);
				CManagers::instance().Sound()->StopAll();
				CManagers::instance().Sound()->PlayBGM(L"Nature_Biome_3.wav", CManagers::instance().Sound()->GetVolume());
			}
		}
		m_tFrame.dwTime = GetTickCount();
	}
	// 하나로 합칩시다.
	if (m_tFrame2.dwTime + m_tFrame2.dwSpeed < GetTickCount())
	{
		if (STATE::IDLE == m_eCurState)
		{
			m_tFrame2.iFrameStart = 0;
		}
		else if (STATE::ATTACK == m_eCurState)
		{
			++m_tFrame2.iFrameStart;
			if (m_tFrame2.iFrameStart > m_tFrame2.iFrameEnd)
				m_tFrame2.iFrameStart = m_tFrame2.iFrameStartBf;
		}
		else if (STATE::DEAD == m_eCurState)
			//CManagers::instance().Event()->DeleteObject(this);
		{
			++m_tFrame2.iFrameStart;
			if (m_tFrame2.iFrameStart > m_tFrame2.iFrameEnd)
			{
				m_tFrame2.iFrameStart = m_tFrame2.iFrameStartBf;
			}
		}
		m_tFrame2.dwTime = GetTickCount();
	}
}

void CHiveMother::LaunchAcid()
{
	CManagers::instance().Sound()->PlaySound(L"hiveMotherShoot.wav", CHANNELID::SOUND_EFFECT6, CManagers::instance().Sound()->GetVolume());
	CGameObject* pAcidProjectile = new CAcidProjectile;
	pAcidProjectile->Initialize();
	pAcidProjectile->SetPosition(m_vPosition + 40 * Vector2::Up());
	CManagers::instance().Event()->CreateObject(pAcidProjectile, TYPE::BOSS);
}