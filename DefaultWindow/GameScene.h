#pragma once
#include "Scene.h"

class CGameScene :
	public CScene
{
public:
	CGameScene();
	virtual ~CGameScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual void FixedUpdate(void)	override;
	virtual void Update(void)		override;
	virtual void LateUpdate(void)	override;
	virtual void Render(HDC m_DC)	override;
};