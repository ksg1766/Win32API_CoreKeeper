#pragma once
#include "Component.h"
#include "Vector2.h"

class CRigidBody :
	public CComponent
{
public:
	CRigidBody();
	virtual ~CRigidBody();

	void Initialize(CGameObject* _pHost);
	void Update();

	void SetVelocity(Vector2 _vVelocity)
	{
		m_vVelocity = _vVelocity;
	}

	void Move();

private:
	Vector2		m_vVelocity;
};

