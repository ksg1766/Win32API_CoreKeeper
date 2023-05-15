#pragma once
#include "HP_Bar.h"
class CHP_Bar_Boss :
	public CHP_Bar
{
public:
	CHP_Bar_Boss();
	virtual ~CHP_Bar_Boss();

	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual int		LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

private:
	CUI*			m_pHPfront;
};

