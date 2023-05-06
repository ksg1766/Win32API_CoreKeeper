#pragma once
#include "Component.h"

class CGameObject;
class CStorage :
	public CComponent
{
public:
	CStorage();
	virtual ~CStorage();

	// CComponent을(를) 통해 상속됨
	virtual void Initialize(CGameObject * _pHost) override;
	void	AddObject(CGameObject* _pObject);
	void	SubObject(UINT _iIndex);
	
	vector<CGameObject*>&	GetStorage() { return m_vecStorage; }
	UINT	GetSize() { return m_vecStorage.size(); }
	void	SetSize(UINT _iSize) { m_vecStorage.reserve(_iSize); }
	
private:
	vector<CGameObject*>	m_vecStorage;
};