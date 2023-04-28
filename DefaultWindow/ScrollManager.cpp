#include "stdafx.h"
#include "ScrollManager.h"


CScrollManager::CScrollManager() :m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollManager::~CScrollManager()
{
	Release();
}

void CScrollManager::Initialize()
{
}

void CScrollManager::Release()
{
}
