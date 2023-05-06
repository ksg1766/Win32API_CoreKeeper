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
		m_iOption = 0;
		m_chWallAround = _chWallAround;
	}

	int			GetDrawID() { return m_iDrawID; }
	int			GetOption() { return m_iOption; }
	int			GetBiom() { return m_iBiom; }
	unsigned char GetWallAround() { return m_chWallAround; }

	void		OnUpdate(DIR _eDir, bool _isCreated);

private:

	int			m_iDrawID;
	int			m_iOption;	// ������ Dummy���� ���߿� Ÿ�Ͽ� ���ºο��ϰų� �Ҷ� �� �� ����.
	int			m_iBiom;

	unsigned char	m_chWallAround;

private:
	CTileGraphics*	m_pGraphics;
};

