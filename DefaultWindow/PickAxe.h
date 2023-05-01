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

	// CItem��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int	Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	virtual void	SetMotion(void) override;
	virtual void	MoveFrame(void) override;

	virtual void	SetUsing(bool _isUsig) override { m_IsUsing = _isUsig; }
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

