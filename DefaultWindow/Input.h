#pragma once
#include "Component.h"
#include "Managers.h"
//class CManagers;
class CInput :
	public CComponent
{
public:
	CInput() = default;
	CInput(CGameObject* _pHost) :CComponent(_pHost) 
	{
		Key = CManagers::instance().Key();
	}

	void Update();

	virtual ~CInput();

private:
	CKeyManager* Key;
};

