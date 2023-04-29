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

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	int			GetDrawIDX() { return m_iDrawIDX; }
	int			GetDrawIDY() { return m_iDrawIDY; }
	int			GetOption() { return m_iOption; }
	unsigned char GetWallAround() { return m_chWallAround; }

	void		SetTile(int _iDrawIDX, int _iDrawIDY, int _iOption, unsigned char _chWallAround)
	{
		m_iDrawIDX = _iDrawIDX;
		m_iDrawIDY = _iDrawIDY;
		m_iOption = _iOption;
		m_chWallAround = _chWallAround;
	}
	void		SetCreateAround(DIR _eDir) { m_chWallAround |= (1 << (UINT)_eDir); }
	void		SetDestroyAround(DIR _eDir) { m_chWallAround &= ~(1 << (UINT)_eDir); }

public:
	void		OnUpdate(DIR _eDir, bool _isCreated);

private:
	int			m_iDrawIDX;
	int			m_iDrawIDY;
	int			m_iOption;	// ������ Dummy���� ���߿� Ÿ�Ͽ� ���ºο��ϰų� �Ҷ� �� �� ����.
	unsigned char	m_chWallAround;

private:
	CCollider*		m_pCollider;
	CTileGraphics*	m_pGraphics;
};

