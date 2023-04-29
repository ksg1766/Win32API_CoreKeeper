#pragma once
#include "GameObject.h"

class CTileGraphics;
class CTile :
	public CGameObject
{
public:
	CTile();
	virtual ~CTile();

	virtual void Initialize() override;
	virtual int  Update(void) override;
	virtual int  LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	void		SetTile(int _iDrawIDX, int _iDrawIDY, int _iOption, unsigned char _chWallAround)
	{
		m_iDrawIDX = _iDrawIDX;
		m_iDrawIDY = _iDrawIDY;
		m_iOption = _iOption;
		m_chWallAround = _chWallAround;
	}

	int			GetDrawIDX() { return m_iDrawIDX; }
	int			GetDrawIDY() { return m_iDrawIDY; }
	int			GetOption() { return m_iOption; }
	unsigned char GetWallAround() { return m_chWallAround; }

	void		OnUpdate(DIR _eDir, bool _isCreated);

protected:
	int			m_iDrawIDX;
	int			m_iDrawIDY;
	int			m_iOption;	// 지금은 Dummy지만 나중에 타일에 상태부여하거나 할때 쓸 수 있음.
	unsigned char	m_chWallAround;

private:
	CTileGraphics*	m_pGraphics;
};

