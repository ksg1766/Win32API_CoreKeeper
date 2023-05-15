#pragma once
#include "GameObject.h"
#include "Managers.h"

class CCollider;
class CTileGraphics;
class CWall :
	public CGameObject
{
public:
	CWall();
	virtual ~CWall();

	// CGameObject을(를) 통해 상속됨
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual int		LateUpdate(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	int				GetDrawID()			{ return m_iDrawID; }
	int				GetOption()			{ return m_iOption; }
	int				GetBiom()			{ return m_iBiom; }
	unsigned char	GetWallAround()		{ return m_chWallAround; }
	MATERIAL		GetMaterial()		{ return m_eMaterial; }

	void			GetTile(int* _iDrawID, int* _iBiom, unsigned char* _chWallAround, MATERIAL* _eMaterial)
	{
		_iDrawID = &m_iDrawID;
		_iBiom = &m_iBiom;
		_chWallAround = &m_chWallAround;
		_eMaterial = &m_eMaterial;
	}

	void			SetTile(int _iDrawID, int _iBiom, unsigned char _chWallAround)
	{
		m_iDrawID = _iDrawID;
		m_iBiom = _iBiom;
		if (m_iBiom == 2)
		{
			m_iHp = INT32_MAX;
		}
		m_iOption = 1;
		m_chWallAround = _chWallAround;
		if (rand() % 5 == 0)
		{
			switch (m_iBiom)
			{
			case 0:
				m_eMaterial = MATERIAL::STONE_COPPER;
				//m_iDrawID = 17;
				//CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::GLOW, m_vPosition);
				break;
			case 3:
				m_eMaterial = MATERIAL::STONE_IRON;
				//m_iDrawID = 17;
				//CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::GLOW, m_vPosition);
				break;
			default:
				m_eMaterial = MATERIAL::END;
				break;
			}
		}
		else
			m_eMaterial = MATERIAL::END;
	}

	int				GetHp()					{ return m_iHp; }
	void			SetHp(int _iHp)			{ m_iHp = _iHp; }

	void			SetCreateAround(DIR _eDir) { m_chWallAround |= (1 << (UINT)_eDir); }
	void			SetDestroyAround(DIR _eDir) { m_chWallAround &= ~(1 << (UINT)_eDir); }

	void			DropMaterial();

public:
	void			OnUpdate(DIR _eDir, bool _isCreated);

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

protected:
	int			m_iHp;

private:
	int			m_iDrawID;
	int			m_iOption;	// 지금은 Dummy지만 나중에 타일에 상태부여하거나 할때 쓸 수 있음.
	unsigned char	m_chWallAround;
	int			m_iBiom;

	MATERIAL	m_eMaterial;
};