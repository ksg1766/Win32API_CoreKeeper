#pragma once
#include "Component.h"
#include "Vector2.h"

class CGameObject;
class CCollider :
	public CComponent
{
public:
	CCollider();
	CCollider(const CCollider& rhs);
	CCollider& operator= (CCollider& _origin) = delete;
	virtual ~CCollider();

	virtual void	Initialize(CGameObject* _pHost) override;

	void			LateUpdate();
	void			Render(HDC _hDC);

public:
	Vector2	GetOffset()		{ return m_vOffset; }
	Vector2 GetPosition()	{ return m_vPosition; }
	Vector2 GetScale()		{ return m_vScale; }
	UINT	GetID()			{ return m_iID; }

	void SetOffset(Vector2 _vOffset)		{ m_vOffset = _vOffset; }
	void SetPosition(Vector2 _vPosition)	{ m_vPosition = _vPosition; }
	void SetScale(Vector2 _vScale)			{ m_vScale = _vScale; }

public:
	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	Vector2		m_vOffset;
	Vector2		m_vPosition;
	Vector2		m_vScale;

	UINT		m_iID;
	static UINT g_iNextID;

	int			m_iCol;

	friend class CGameObject;
};

