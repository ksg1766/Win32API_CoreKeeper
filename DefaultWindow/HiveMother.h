#pragma once
#include "GameObject.h"

class CUI;
class CSpawner;
class CHiveMother :
	public CGameObject
{
public:
	CHiveMother();
	virtual ~CHiveMother();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	UINT		GetBiom() { return m_iBiom; }
	int			GetHp() { return m_iHp; }
	int			GetMaxHp() { return m_iMaxHp; }
	int			GetDamage() { return m_iDamage; }
	void		SetHp(int _iHp) { m_iHp = _iHp; }

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	void			Action();
	void			SetMotion(void);
	void			MoveFrame(void);
	void			LaunchAcid();


	UINT			m_iBiom;

	int				m_iMaxHp;
	int				m_iHp;
	int				m_iDamage;

	int				m_iRange;
	CGameObject*	m_pTarget;
	Vector2			m_vTargetPoint;
	bool			m_LaunchOnlyOnce;

	CShadow*		m_pShadow;

	CSpawner*		m_pSpawners[5];

	STATE			m_eCurState;
	STATE			m_ePreState;

	FRAME			m_tFrame2;
	TCHAR*			m_pFrameKey2;

	CGraphics*		m_pGraphics2;	// 삭제해도될듯

	CUI*			m_pHPBar;

	friend class	CShadow;

//private:
//	TYPE		m_eType;
//	bool		m_IsDead;
//
//	DIR			m_eDir;
//
//	Vector2		m_vPosition;
//	Vector2		m_vScale;
//
//	FRAME		m_tFrame;
//	TCHAR*		m_pFrameKey;
//	DWORD		m_dwTime;
//
//	float		m_fSpeed;
//
//protected:
//	CCollider*		m_pCollider;
//	CRigidBody*		m_pRigidBody;
//	CGraphics*		m_pGraphics;
};

