#pragma once
#include "GameObject.h"

class CUIGraphics;
class CUI :
	public CGameObject
{
public:
	CUI();
	virtual ~CUI();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int Update(void)		override;
	virtual int LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

	UINT		GetLayer() { return m_iLayer; }
	void		SetFrameKey(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void		SetLayer(UINT _iLayer) { m_iLayer = _iLayer; };

protected:
	UINT			m_iLayer;
	CUI*			m_pIcon;
};

