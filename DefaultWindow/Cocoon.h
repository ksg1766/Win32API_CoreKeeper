#pragma once
#include "GameObject.h"
class CCocoon :
	public CGameObject
{
public:
	CCocoon();
	virtual ~CCocoon();

	// CGameObject을(를) 통해 상속됨
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual int		LateUpdate(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

	int				GetHp() { return m_iHp; }
	void			SetHp(int _iHp) { m_iHp = _iHp; }
	void			SetState(STATE _eState) { m_ePreState = m_eCurState; m_eCurState = _eState; }

private:
	void			Action();
	void			SetMotion(void);
	void			MoveFrame(void);

	STATE			m_eCurState;
	STATE			m_ePreState;

	UINT			m_iBiom;

	int				m_iMaxHp;
	int				m_iHp;
};

