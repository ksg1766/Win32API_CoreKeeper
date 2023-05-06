#pragma once
#include "GameObject.h"
struct Pos;
class CMonster :
	public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void)	PURE;
	virtual int	 Update(void)		PURE;
	virtual int	 LateUpdate(void)	PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release(void)		PURE;

	UINT	GetBiom() { return m_iBiom; }
	int		GetDamage() { return m_iDamage; }
	int		GetHp() { return m_iHp; }
	void	SetHp(int _iHp) { m_iHp = _iHp; }

	bool CanGo(Pos _pos);
	void AStar();

protected:
	int				m_iRange;
	CGameObject*	m_pTarget;

	Vector2			m_vTargetPoint;

	UINT			m_iBiom;

	CShadow*		m_pShadow;

	STATE			m_eCurState;
	STATE			m_ePreState;

	int				m_iHp;
	int				m_iDamage;

	vector<Pos>		m_path;
	UINT			m_pathIndex;
	bool			m_isTracking;


	vector<CGameObject*> vecTileMap;

	virtual void	Action()		PURE;
	virtual void	Attack()		PURE;
	virtual void	SetMotion(void)	PURE;
	virtual void	MoveFrame(void)	PURE;

//protected:
//	void		Update_Rect(void);
//	void		SetDead(bool _IsDead) { m_IsDead = _IsDead; }
//
//protected:
//	bool		m_IsDead;
//
//	INFO		m_tInfo;
//	RECT		m_tRect;
//
//	Vector2		m_tVelocity;
//	float		m_fSpeed;
};

