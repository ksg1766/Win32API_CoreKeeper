#include "stdafx.h"
#include "Item.h"


CItem::CItem():CGameObject(), m_eItemType(ITEM::END)
{
	m_IsDead = false;
}


CItem::~CItem()
{
}