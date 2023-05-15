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

			int iDrawID = 0;
			if (0 == static_cast<CTile*>(pObj)->GetBiom())// || 3 == static_cast<CTile*>(pObj)->GetBiom())
			{
				iDrawID = rand() % 100 - 93;
				if (iDrawID < 0)
					iDrawID = 0;
			}
			static_cast<CTile*>(pObj)->SetTile(iDrawID, 0, 0b00000000);

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
	//for (auto& iter : m_vecTile)
	//	Safe_Delete(iter);
}

void CTileManager::CreateWall(Vector2 _vPos, int _iBiom, int _iDrawID)
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
	static_cast<CWall*>(pObj)->SetTile(_iDrawID, _iBiom, 0b00000000);
	Safe_Delete(m_vecTile[iIndex]);
	m_vecTile[iIndex] = pObj;

	Invoke(_vPos, true);
}

void CTileManager::DestroyWall(Vector2 _vPos)
{
	// Destroy~~~
	Invoke(_vPos, false);
}

void CTileManager::CreateTile(Vector2 _vPos, int _iBiom, int _iDrawID)
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
	static_cast<CTile*>(pObj)->SetTile(_iDrawID, _iBiom, 0b00000000);
	m_vecTile[iIndex] = pObj;
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
		static_cast<CWall*>(m_vecTile[iIndex + 1])->OnUpdate(DIR::LEFT, _IsCreated);
		if(_IsCreated)
			static_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::RIGHT, _IsCreated);
	}

	if (TYPE::WALL == m_vecTile[iIndex + 1 - TILEX - 1]->GetType())	// Up
	{
		static_cast<CWall*>(m_vecTile[iIndex + 1 - TILEX - 1])->OnUpdate(DIR::DOWN, _IsCreated);
		if (_IsCreated)
			static_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::UP, _IsCreated);
	}
	else
	{
		if (TYPE::TILE == m_vecTile[iIndex + 1 - TILEX - 1]->GetType())
		{
			static_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX - 1])->OnUpdate(DIR::DOWN, _IsCreated);
			if (_IsCreated)
			{
				static_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX - 1])->SetRenderID(RENDERID::GAMEOBJECT);
				static_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::UP, _IsCreated);
				if (TYPE::TILE == (m_vecTile[iIndex - 1 - TILEX])->GetType())
					static_cast<CTile*>(m_vecTile[iIndex - 1 - TILEX])->OnUpdate(DIR::RIGHT, _IsCreated);
				if (TYPE::TILE == (m_vecTile[iIndex + 2 - TILEX])->GetType())
					static_cast<CTile*>(m_vecTile[iIndex + 2 - TILEX])->OnUpdate(DIR::LEFT, _IsCreated);
			}
			else
			{
				static_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX - 1])->OnUpdate(DIR::DOWN, _IsCreated);
				static_cast<CTile*>(m_vecTile[iIndex + 1 - TILEX - 1])->SetRenderID(RENDERID::BACKGROUND);
			}
		}
	}

	if (TYPE::WALL == m_vecTile[iIndex - 1]->GetType())	// Left
	{
		static_cast<CWall*>(m_vecTile[iIndex - 1])->OnUpdate(DIR::RIGHT, _IsCreated);
		if (_IsCreated)
			static_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::LEFT, _IsCreated);
	}
	if (TYPE::WALL == m_vecTile[iIndex + TILEX]->GetType())	// Down
	{
		static_cast<CWall*>(m_vecTile[iIndex + TILEX])->OnUpdate(DIR::UP, _IsCreated);
		if (_IsCreated)
			static_cast<CWall*>(m_vecTile[iIndex])->OnUpdate(DIR::DOWN, _IsCreated);
	}
}

void CTileManager::PickingTile(POINT _pt, int _iBiom, int _iDrawID, int _iOption)
{
	switch (_iOption)
	{
	case 0:
	{
		CreateTile(Vector2(_pt.x, _pt.y), _iBiom, _iDrawID);
		break;
	}
	case 1:
	{
		CreateWall(Vector2(_pt.x, _pt.y), _iBiom, _iDrawID);
		//static_cast<CWall*>(m_vecTile[iIndex])->SetTile(_iDrawIDX, _iDrawIDY, _iOption);
		break;
	}
	}
}

void CTileManager::SaveTile(void)
{
	//HANDLE	hFile = CreateFile(L"../Data/HiveTest.dat",	// Hive Mother Test
	//HANDLE	hFile = CreateFile(L"../Data/WallItemTest.dat", // Test
	HANDLE	hFile = CreateFile(L"../Data/MazeScene.dat",
	//HANDLE	hFile = CreateFile(L"../Data/MainScene.dat",	// 맵 만드는 중..
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

	TYPE	eType = TYPE::END;
	int		iDrawID = 0, iBiom = 0;
	unsigned char	chWallAround = 0;
	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		if (TYPE::TILE == iter->GetType())
		{
			eType	= TYPE::TILE;
			iDrawID = static_cast<CTile*>(iter)->GetDrawID();
			iBiom	= static_cast<CTile*>(iter)->GetBiom();
			chWallAround = static_cast<CTile*>(iter)->GetWallAround();

			//static_cast<CTile*>(iter)->GetTile(&iDrawID, &iBiom, &chWallAround);
		}
		else if(TYPE::WALL == iter->GetType())
		{
			eType	= TYPE::WALL;
			iDrawID = static_cast<CWall*>(iter)->GetDrawID();
			iBiom	= static_cast<CWall*>(iter)->GetBiom();
			chWallAround = static_cast<CWall*>(iter)->GetWallAround();

			//static_cast<CWall*>(iter)->GetTile(&iDrawID, &iBiom, &chWallAround);
		}

		WriteFile(hFile, &eType, sizeof(TYPE), &dwByte, nullptr);
		WriteFile(hFile, &(iter->GetPosition()), sizeof(Vector2), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iBiom, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &chWallAround, sizeof(unsigned char), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("Save success"), L"Success", MB_OK);
}

void CTileManager::LoadTile(void)
{
	//HANDLE	hFile = CreateFile(L"../Data/HiveTest.dat",
	//HANDLE	hFile = CreateFile(L"../Data/WallItemTest.dat",
	HANDLE	hFile = CreateFile(L"../Data/MazeScene.dat",	// 맵 만드는 중..
	//HANDLE	hFile = CreateFile(L"../Data/MainScene.dat",	// 맵 만드는 중..
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

	TYPE	eType = TYPE::END;
	int		iDrawID = 0, iBiom = 0;
	unsigned char	chWallAround = 0;
	DWORD	dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &eType, sizeof(TYPE), &dwByte, nullptr);
		ReadFile(hFile, &vPosition, sizeof(Vector2), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iBiom, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &chWallAround, sizeof(unsigned char), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		if (TYPE::TILE == eType)
		{
			CGameObject*	pObj = new CTile();
			pObj->Initialize();
			pObj->SetPosition(vPosition);
			static_cast<CTile*>(pObj)->SetTile(iDrawID, iBiom, chWallAround);

			m_vecTile.push_back(pObj);
		}
		else if (TYPE::WALL == eType)
		{
			CGameObject*	pObj = new CWall();
			pObj->Initialize();
			pObj->SetPosition(vPosition);
			static_cast<CWall*>(pObj)->SetTile(iDrawID, iBiom, chWallAround);

			m_vecTile.push_back(pObj);
		}
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("Load success"), L"Success", MB_OK);
}
