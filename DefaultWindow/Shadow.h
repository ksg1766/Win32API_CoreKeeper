#pragma once
#include "GameObject.h"

class CShadow :
	public CGameObject
{
public:
	CShadow();
	virtual ~CShadow();

	// CGameObject��(��) ���� ��ӵ�
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual int		LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

	void			SetHost(CGameObject* _pHost) { m_pHost = _pHost; }
	void			SetFrameKey(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }

private:
	CGameObject*	m_pHost;
	friend class	CGameObject;	// �̰� ���̷��� �������� �־� ���ް�
};

