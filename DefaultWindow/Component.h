#pragma once
#include "Define.h"

class CGameObject;
class CComponent
{
public:
	CComponent() = default;
	CComponent(CGameObject* _pHost) :m_pHost(_pHost) {}

	virtual void Initialize(CGameObject* _pHost) PURE;

	CGameObject*	GetHost() { return m_pHost; }
	void			SetHost(CGameObject* _pHost) { m_pHost = _pHost; }

	virtual ~CComponent();

protected:
	CGameObject*	m_pHost;
};

