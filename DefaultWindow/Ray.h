#pragma once
#include "GameObject.h"

class CPlayer;
class CRay :
	public CGameObject
{
public:
	CRay();
	virtual ~CRay();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void	SetHost(CGameObject* _pHost);

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	CGameObject*	m_pHost;
	Vector2			m_vOffset;
};

