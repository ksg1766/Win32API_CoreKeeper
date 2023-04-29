#pragma once
#include "Component.h"
#include "Vector2.h"

class CCollider :
	public CComponent
{
public:
	CCollider();
	virtual ~CCollider();
	virtual void Initialize(CGameObject* _pHost) override;
	void LateUpdate();
	void Render(HDC _hDC);

public:
	Vector2	GetOffset()		{ return m_vOffeset; }
	Vector2 GetPosition()	{ return m_vPosition; }
	Vector2 GetScale()		{ return m_vScale; }

	void SetOffset(Vector2 _vOffset)		{ m_vOffeset = _vOffset; }
	void SetPosition(Vector2 _vPosition)	{ m_vPosition = _vPosition; }
	void SetScale(Vector2 _vScale)			{ m_vScale = _vScale; }

public:
	virtual void	OnCollisionEnter();
	virtual void	OnCollisionStay();
	virtual void	OnCollisionExit();

private:
	Vector2		m_vOffeset;
	Vector2		m_vPosition;
	Vector2		m_vScale;

	int			m_iCol;

//	CGameObject*	m_pHost;
};

