#include "stdafx.h"
#include "Item.h"
#include "Material.h"
#include "Managers.h"
#include "Collider.h"
//#include "Player.h"

CItem::CItem():CGameObject(), m_eItemType(ITEM::END), m_iRange(0)
{
	m_IsDead = false;
	m_eRender = RENDERID::GAMEOBJECT;
}


CItem::~CItem()
{
}

//CItem * CItem::CreateItem(ITEM _eItem)
//{
//	return;
//}

CItem * CItem::CreateItem(MATERIAL _eMaterial)
{
	CItem*	pMaterial = new CMaterial;
	pMaterial->Initialize();

	switch (_eMaterial)
	{
	case MATERIAL::END:
		pMaterial->SetFrameKey(L"Desert_Block");
		break;

	case MATERIAL::STONE_COPPER:
		static_cast<CMaterial*>(pMaterial)->SetMaterialType(MATERIAL::STONE_COPPER);
		pMaterial->SetFrameKey(L"CopperStone");
		break;

	case MATERIAL::STONE_IRON:
		static_cast<CMaterial*>(pMaterial)->SetMaterialType(MATERIAL::STONE_IRON);
		pMaterial->SetFrameKey(L"IronStone");
		break;
	
	case MATERIAL::INGOT_COPPER:
		static_cast<CMaterial*>(pMaterial)->SetMaterialType(MATERIAL::INGOT_COPPER);
		pMaterial->SetFrameKey(L"CopperIngot");
		break;

	case MATERIAL::INGOT_IRON:
		static_cast<CMaterial*>(pMaterial)->SetMaterialType(MATERIAL::INGOT_IRON);
		pMaterial->SetFrameKey(L"IronIngot");
		break;
	}

	pMaterial->SetScale(Vector2(48.f, 48.f));

	return pMaterial;
}

void CItem::OnCollisionEnter(CCollider * _pOther)
{
	
}

void CItem::OnCollisionStay(CCollider * _pOther)
{
}

void CItem::OnCollisionExit(CCollider * _pOther)
{
}
