#include "stdafx.h"
#include "Material.h"
#include "Graphics.h"
#include "Collider.h"
#include "Managers.h"
#include "Player.h"
#include "Trap.h"

CMaterial::CMaterial()
{
}

CMaterial::CMaterial(const CMaterial & rhs):CMaterial()
{
	m_pCollider = rhs.m_pCollider;
}

CMaterial::~CMaterial()
{
	Release();
}

void CMaterial::Initialize()
{
	// SetHost 먼저하고 Initialize 호출
	m_IsDead = false;
	m_eCurState = STATE::END;
	m_eRender = RENDERID::GAMEOBJECT;
	//m_eMaterialType = MATERIAL::END;

	//m_vPosition = m_pHostWall->GetPosition();
	//m_vScale = Vector2(48.f, 48.f);

	//m_pFrameKey = L"MyGlow";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	//m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	//m_tFrame.dwTime = 0;
	//m_tFrame.dwSpeed = 100;
	m_eType = TYPE::ITEM;
	m_eItemType = ITEM::MATERIAL;
	m_eMaterialType = MATERIAL::END;

	m_IsUsing = false;

	m_pCollider = new CCollider;
	m_pCollider->Initialize(this);
	m_pGraphics = new CGraphics;
	m_pGraphics->Initialize(this);
}

int CMaterial::Update(void)
{
	return 0;
}

int CMaterial::LateUpdate(void)
{
	m_pCollider->LateUpdate();
	return 0;
}

void CMaterial::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
}

void CMaterial::Release(void)
{
	Safe_Delete(m_pGraphics);
}

void CMaterial::SetUsing(bool _isUsig)
{
	m_IsUsing = _isUsig;
}

//CItem * CMaterial::clone()
//{
//	return CMaterial(this);
//}

void CMaterial::SetMotion(void)
{
}

void CMaterial::MoveFrame(void)
{
}

void CMaterial::OnCollisionEnter(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (TYPE::PLAYER == pOtherObj->GetType())
	{
		CGameObject** m_parrQuickSlot = static_cast<CPlayer*>(pOtherObj)->GetQuickSlot();
		UINT* m_parrQuickCount = static_cast<CPlayer*>(pOtherObj)->GetQuickSlotCount();

		for (size_t i = 0; i < 10; ++i)
		{
			if (nullptr != m_parrQuickSlot[i] && m_eType == m_parrQuickSlot[i]->GetType())
			{
				if (ITEM::MATERIAL == static_cast<CItem*>(m_parrQuickSlot[i])->GetItemType() && m_eMaterialType == static_cast<CMaterial*>(m_parrQuickSlot[i])->GetMaterialType())
				{
					++m_parrQuickCount[i];
					CManagers::instance().Event()->DeleteObject(this);
					if (m_parrQuickCount[i] >= 5)
					{
						m_parrQuickCount[i] -= 5;

						if (nullptr == m_parrQuickSlot[i + 1])
						{
							CTrap* pTrap = new CTrap;
							pTrap->SetOwner(static_cast<CPlayer*>(pOtherObj));
							pTrap->Initialize();
							m_parrQuickSlot[i + 1] = pTrap;
							m_parrQuickCount[i + 1] += 2;
							CManagers::instance().Event()->DeleteObject(pTrap);
							//static_cast<CItem*>(pTrap)->SetOwner(static_cast<CPlayer*>(pOtherObj));
						}
						//pTrap->Initialize();
						else
						{
							//m_parrQuickSlot[i + 1] = pTrap;
							++m_parrQuickCount[i + 1];
						}//CManagers::instance().Event()->DeleteObject(this);
					}
				}
				else
				{
					continue;
					/*m_parrQuickSlot[i] = this;
					++m_parrQuickCount[i];
					CManagers::instance().Event()->DeleteObject(this);*/
				}
			}
			else if (nullptr == m_parrQuickSlot[i])
			{
				m_parrQuickSlot[i] = this;
				++m_parrQuickCount[i];
				CManagers::instance().Event()->DeleteObject(this);
			}
			break;
		}

		/*for (size_t i = 0; i < 10; ++i)
		{

			if (nullptr == m_parrQuickSlot[i])
			{
				m_parrQuickSlot[i] = this;
				CManagers::instance().Event()->DeleteObject(this);
				break;
			}

		}*/
	}
}

void CMaterial::OnCollisionStay(CCollider * _pOther)
{
}

void CMaterial::OnCollisionExit(CCollider * _pOther)
{
}

void CMaterial::Use()
{
}
