#pragma once
#include "Scene.h"
#include "Struct.h"

class CEditScene :
	public CScene
{
public:
	CEditScene();
	virtual ~CEditScene();

	virtual void Initialize(void)	override;
	virtual void FixedUpdate(void)	override;
	virtual void Update(void)		override;
	virtual void LateUpdate(void)	override;
	virtual void Render(HDC m_DC)	override;

private:
	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;

	int			m_iBiom;
	int			m_iDrawID;
	int			m_iOption;	//  0 = ¹Ù´Ú, 1 = º®
};

