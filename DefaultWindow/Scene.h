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

	list<CGameObject*>&	GetObjList(TYPE _eType) { return m_cObjList[(int)_eType]; }

protected:
	list<CGameObject*> m_cObjList[int(TYPE::END)];
};

