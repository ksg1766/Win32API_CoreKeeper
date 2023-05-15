#pragma once
#include "Material.h"
class CCopper :
	public CMaterial
{
public:
	CCopper();
	virtual ~CCopper();

	virtual void Initialize()			override;
	virtual int	 Update(void)			override;
	virtual int	 LateUpdate(void)		override;
	virtual void Render(HDC hDC)		override;
	virtual void Release(void)			override;
	virtual void SetUsing(bool _isUsig)	override;
	virtual void SetMotion(void)		override;
	virtual void MoveFrame(void)		override;

private:

};

