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
	void		SetTile(int _iDrawIDX, int _iDrawIDY, int _iOption)
	{
		m_iDrawIDX = _iDrawIDX;
		m_iDrawIDY = _iDrawIDY;
		m_iOption = _iOption;
	}

	int			GetDrawIDX() { return m_iDrawIDX; }
	int			GetDrawIDY() { return m_iDrawIDY; }
	int			GetOption() { return m_iOption; }

	void		OnUpdate(DIR _eDir, bool _isCreated);

protected:
	int			m_iDrawIDX;
	int			m_iDrawIDY;
	int			m_iOption;	// ������ Dummy���� ���߿� Ÿ�Ͽ� ���ºο��ϰų� �Ҷ� �� �� ����.

private:
	CTileGraphics*	m_pGraphics;
	unsigned char	m_chWallAround;
};

