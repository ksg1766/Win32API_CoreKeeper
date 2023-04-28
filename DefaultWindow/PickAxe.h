#pragma once
#include "Item.h"

class CCollider;
class CGraphics;
class CPickAxe :
	public CItem
{
public:
	CPickAxe();
	virtual ~CPickAxe();

	// CItem을(를) 통해 상속됨
	virtual void Initialize(CPlayer* _pOwner) override;
	virtual int	Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:

public:
	virtual void OnCollisionEnter() override;
	virtual void OnCollisionStay() override;
	virtual void OnCollisionExit() override;


private:
	virtual void	SetMotion(void) override;
	virtual void	MoveFrame(void) override;


private:
	CCollider*	m_pCollider;
	CGraphics*	m_pGraphics;
//private:
	//bool		m_IsDead;

	//DIR			m_eDir;

	//Vector2		m_vPosition;
	//Vector2		m_vScale;

	//FRAME		m_tFrame;
	//TCHAR*		m_pFrameKey;
	//float		m_fTime;

	//float		m_fSpeed;
};

