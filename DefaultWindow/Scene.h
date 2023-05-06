#pragma once
#include "Define.h"
#include "Enum.h"

class CGameObject;
class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void		Initialize(void)	PURE;
	virtual void		FixedUpdate(void)	PURE;
	virtual void		Update(void)		PURE;
	virtual void		LateUpdate(void)	PURE;
	virtual void		Render(HDC m_DC)	PURE;
	
	virtual void		Release(void);

	vector<CGameObject*>&	GetObjList(TYPE _eType) { return m_vecObjList[(int)_eType]; }

protected:
	vector<CGameObject*> m_vecObjList[int(TYPE::UI) + 1];
	vector<CGameObject*> m_RenderSort[(int)RENDERID::RENDER_END];
};

