#pragma once
#include "Enum.h"

struct tagEvent
{
	EVENT_TYPE	eEvent;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class CGameObject;
class CEventManager
{
public:
	CEventManager();
	virtual ~CEventManager();

public:
	//void Initialize();
	void Update();

	void AddEvent(const tagEvent& _eve) { m_vecEvent.push_back(_eve); }

	void CreateObject(CGameObject* _pObj, TYPE _eGroup);
	void DeleteObject(CGameObject* _pObj);

private:
	void Execute(const tagEvent& _eve);

private:
	vector<tagEvent> m_vecEvent;
	vector<CGameObject*> m_vecCreate;
	vector<CGameObject*> m_vecDead;
};