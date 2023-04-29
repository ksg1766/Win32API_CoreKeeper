#include "stdafx.h"
#include "TileManager.h"
#include "Tile.h"
#include "Wall.h"
#include "GameObject.h"
#include "Managers.h"

CTileManager::CTileManager()
{
}

CTileManager::~CTileManager()
{
	Release();
}

void CTileManager::Initialize(void)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float(TILECX * j) + (TILECX >> 1);
			float	fY = float(TILECY * i) + (TILECY >> 1);

			CGameObject*	pObj = new CTile;
			pObj->SetPosition(Vector2(fX, fY));
			pObj->Initialize();
			m_vecTile.push_back(pObj);
		}
	}
}

void CTileManager::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileManager::LateUpdate(void)
{
	for (auto& iter : m_vecTile)
		iter->LateUpdate();
}

void CTileManager::Render(HDC hDC)
{
	int	iCullX = abs((int)CManagers::instance().Scroll()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CManagers::instance().Scroll()->Get_ScrollY() / TILECY);

	int	iMaxX = iCullX + WINCX / TILECX + 2;
	int	iMaxY = iCullY + WINCY / TILECY + 2;

	for (int i = iCullY; i < iMaxY; ++i)
	{
		for (int j = iCullX; j < iMaxX; ++j)
		{
			int	iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}
}

void CTileManager::Release(void)
{
}

void CTileManager::CreateWall(Vector2 _vPos)
{
	// Create~~~
	int		j = _vPos.x / TILECX;
	int		i = _vPos.y / TILECY;

	int		iIndex = i * TILEX + j;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	float	fX = float(TILECX * j) + (TILECX >> 1);
	float	fY = float(TILECY * i) + (TILECY >> 1);

	CGameObject*	pObj = new CWall;

	pObj->SetPosition(Vector2(fX, fY));
	pObj->Initialize();
	Safe_Delete(m_vecTile[iIndex]);
	m_vecTile[iIndex] = pObj;

	Invoke(_vPos, true);
}

void CTileManager::DestroyWall(Vector2 _vPos)
{
	// Destroy~~~
	Invoke(_vPos, false);
}

void CTileManager::CreateTile(Vector2 _vPos)
{
	int		j = _vPos.x / TILECX;
	int		i = _vPos.y / TILECY;

	int		iIndex = i * TILEX + j;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	float	fX = float(TILECX * j) + (TILECX >> 1);
	float	fY = float(TILECY * i) + (TILECY >> 1);

	CGameObject*	pObj = new CTile;
	
	if (TYPE::WALL == m_vecTile[iIndex]->GetType())
		DestroyWall(_vPos);

	Safe_Delete(m_vecTile[iIndex]);
	pObj->SetPosition(Vector2(fX, fY));
	pObj->Initialize();
	Safe_Delete(m_vecTile[iIndex]);
	m_vecTile[iIndex] = pObj;
	//dynamic_cast<CTile*>(m_vecTile[iIndex])->SetTile(_iDrawIDX, _iDrawIDY, _iOption);
}

void CTileManager::DestroyTile(Vector2 _vPos)
{

}

void CTileManager::Invoke(Vector2 _pPos, bool _IsCreated)
{
	int		j = _pPos.x / TILECX;
	int		i = _pPos.y / TILECY;
	int		iIndex = i * TILEX + j;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	if (TYPE::WALL == m_vecTile[iIndex + 1]->GetType())	// Right
	{
		dynamic_cast<CWall*>(m_vecTile[iIndex + 1])->OnUpdate(DIR::LEFT, _IsCreated);
		if(_IsCreated)
			dynamic_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::RIGHT, _IsCreated);
	}

	if (TYPE::WALL == m_vecTile[iIndex + 1 - TILEX - 1]->GetType())	// Up
	{
		dynamic_cast<CWall*>(m_vecTile[iIndex + 1 - TILEX - 1])->OnUpdate(DIR::DOWN, _IsCreated);
		if (_IsCreated)
			dynamic_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::UP, _IsCreated);
	}
	else
	{
		dynamic_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX - 1])->OnUpdate(DIR::DOWN, _IsCreated);
		if (_IsCreated)
		{
			dynamic_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::UP, _IsCreated);
			if (TYPE::TILE == (m_vecTile[iIndex + 1 - TILEX - 2])->GetType())
				dynamic_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX - 2])->OnUpdate(DIR::RIGHT, _IsCreated);
			if (TYPE::TILE == (m_vecTile[iIndex + 1 - TILEX + 1])->GetType())
				dynamic_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX + 1])->OnUpdate(DIR::LEFT, _IsCreated); 
		}
		else
		{
			dynamic_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX - 1])->OnUpdate(DIR::DOWN, _IsCreated);
		}
	}

	if (TYPE::WALL == m_vecTile[iIndex - 1]->GetType())	// Left
	{
		dynamic_cast<CWall*>(m_vecTile[iIndex - 1])->OnUpdate(DIR::RIGHT, _IsCreated);
		if (_IsCreated)
			dynamic_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::LEFT, _IsCreated);
	}
	if (TYPE::WALL == m_vecTile[iIndex + TILEX]->GetType())	// Down
	{
		dynamic_cast<CWall*>(m_vecTile[iIndex + TILEX])->OnUpdate(DIR::UP, _IsCreated);
		if (_IsCreated)
			dynamic_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::DOWN, _IsCreated);
	}
}

void CTileManager::PickingTile(POINT _pt, int _iDrawIDX, int _iDrawIDY, int _iOption)
{
	switch (_iOption)
	{
	case 0:
	{
		CreateTile(Vector2(_pt.x, _pt.y));
		break;
	}
	case 1:
	{
		CreateWall(Vector2(_pt.x, _pt.y));
		//dynamic_cast<CWall*>(m_vecTile[iIndex])->SetTile(_iDrawIDX, _iDrawIDY, _iOption);
		break;
	}
	}
}

void CTileManager::SaveTile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
	{
		MessageBox(g_hWnd, _T("save File"), L"Fail", MB_OK);
		return;
	}

	int		iDrawIDX = 0, iDrawIDY = 0, iOption = 0;
	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		if (TYPE::TILE == iter->GetType())
		{
			iDrawIDX = dynamic_cast<CTile*>(iter)->GetDrawIDX();
			iDrawIDY = dynamic_cast<CTile*>(iter)->GetDrawIDY();
			iOption = dynamic_cast<CTile*>(iter)->GetOption();
		}
		else if(TYPE::WALL == iter->GetType())
		{
			iDrawIDX = dynamic_cast<CWall*>(iter)->GetDrawIDX();
			iDrawIDY = dynamic_cast<CWall*>(iter)->GetDrawIDY();
			iOption = dynamic_cast<CWall*>(iter)->GetOption();
		}
		WriteFile(hFile, &(iter->GetPosition()), sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &iDrawIDX, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iDrawIDY, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Save success"), L"Success", MB_OK);
}

void CTileManager::LoadTile(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	for (auto& iter : m_vecTile)
		Safe_Delete(iter);
	m_vecTile.clear();

	Vector2 vPosition{};

	int		iDrawIDX = 0, iDrawIDY = 0, iOption = 0;
	DWORD	dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &vPosition, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &iDrawIDX, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iDrawIDY, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		//CGameObject*	pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		if (0 == iOption)
		{
			CGameObject*	pObj = new CTile();
			pObj->Initialize();
			pObj->SetPosition(vPosition);
			dynamic_cast<CTile*>(pObj)->SetTile(iDrawIDX, iDrawIDY, iOption);

			m_vecTile.push_back(pObj);
		}
		else if (1 == iOption)
		{
			CGameObject*	pObj = new CWall();
			pObj->Initialize();
			pObj->SetPosition(vPosition);
			dynamic_cast<CWall*>(pObj)->SetTile(iDrawIDX, iDrawIDY, iOption);

			m_vecTile.push_back(pObj);
		}
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load success"), L"Success", MB_OK);
}
