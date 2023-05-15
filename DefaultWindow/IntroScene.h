#pragma once
#include "Scene.h"
class CIntroScene :
	public CScene
{
public:
	CIntroScene();
	virtual ~CIntroScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual void FixedUpdate(void)	override;
	virtual void Update(void)		override;
	virtual void LateUpdate(void)	override;
	virtual void Render(HDC m_DC)	override;
	virtual	void Release();

private:
	TCHAR*	m_pFrameKey[5];
	TCHAR*	m_curFrameKey;
	UINT	m_iCurIndex;
	DWORD	m_dwTime;
};

