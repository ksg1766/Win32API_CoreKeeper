#pragma once
#include "Scene.h"
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
	int			m_iDrawIDX;
	int			m_iDrawIDY;
	int			m_iOption;
};

