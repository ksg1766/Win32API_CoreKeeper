#pragma once
#include "GameObject.h"

class CCollider;
class CTileGraphics;
class CWall :
	public CGameObject
{
public:
	CWall();
	virtual ~CWall();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	int			GetDrawID() { return m_iDrawID; }
	int			GetOption() { return m_iOption; }
	int			GetBiom() { return m_iBiom; }
	unsigned char GetWallAround() { return m_chWallAround; }

	void		GetTile(int* _iDrawID, int* _iBiom, unsigned char* _chWallAround)
	{
		_iDrawID = &m_iDrawID;
		_iBiom = &m_iBiom;
		_chWallAround = &m_chWallAround;
	}

	void		SetTile(int _iDrawID, int _iBiom, unsigned char _chWallAround)
	{
		m_iDrawID = _iDrawID;
		m_iBiom = _iBiom;
		m_iOption = 1;
		m_chWallAround = _chWallAround;
	}
	void		SetCreateAround(DIR _eDir) { m_chWallAround |= (1 << (UINT)_eDir); }
	void		SetDestroyAround(DIR _eDir) { m_chWallAround &= ~(1 << (UINT)_eDir); }

public:
	void		OnUpdate(DIR _eDir, bool _isCreated);

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	int			m_iDrawID;
	int			m_iOption;	// 지금은 Dummy지만 나중에 타일에 상태부여하거나 할때 쓸 수 있음.
	int			m_iBiom;
	unsigned char	m_chWallAround;
};

