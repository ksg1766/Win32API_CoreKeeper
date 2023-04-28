#pragma once

class CGameObject;
class CComponent
{
public:
	CComponent() = default;
	CComponent(CGameObject* _pHost) :m_pHost(_pHost) {}

	CGameObject*	GetHost() { return m_pHost; }
	void			SetHost(CGameObject* _pHost) { m_pHost = _pHost; }

	virtual ~CComponent();

protected:
	CGameObject*	m_pHost;
};

