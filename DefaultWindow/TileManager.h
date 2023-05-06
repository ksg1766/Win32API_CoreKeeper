#pragma once
#include "Vector2.h"

class CGameObject;
class CTileManager
{
public:
	CTileManager();
	~CTileManager();

	void Initialize(void);
	void Update(void);
	void LateUpdate(void);
	void Render(HDC hDC);
	void Release(void);

public:
	vector<CGameObject*>& GetTile() { return m_vecTile;	}

	void CreateWall(Vector2 _vPos, int _iBiom, int _iDrawID);
	void DestroyWall(Vector2 _vPos);

	void CreateTile(Vector2 _vPos, int _iBiom, int _iDrawID);
	void DestroyTile(Vector2 _vPos);

	void Invoke(Vector2 _pPos, bool _IsCreated);
	 
public:
	void	PickingTile(POINT _pt, int _iBiom, int _iDrawID, int _iOption);
	void	SaveTile(void);
	void	LoadTile(void);

private:
	vector<CGameObject*>	m_vecTile;
	vector<CGameObject*>	m_vecWall;
};

