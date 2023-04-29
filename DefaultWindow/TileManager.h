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
	void CreateWall(Vector2 _vPos);
	void DestroyWall(Vector2 _vPos);

	void CreateTile(Vector2 _vPos);
	void DestroyTile(Vector2 _vPos);

	void Invoke(Vector2 _pPos, bool _IsCreated);

public:
	void	PickingTile(POINT _pt, int _iDrawIDX, int _iDrawIDY, int _iOption);
	void	SaveTile(void);
	void	LoadTile(void);

private:
	vector<CGameObject*>	m_vecTile;
};

