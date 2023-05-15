#pragma once
#include "Scene.h"
class CEndScene :
	public CScene
{
public:
	CEndScene();
	virtual ~CEndScene();

virtual void Initialize(void) override;
	virtual void FixedUpdate(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC m_DC) override;

private:
	TCHAR*	m_pFrameKey[2];
	TCHAR*	m_curFrameKey;
	UINT	m_iCurIndex;
	DWORD	m_dwTime;
};

