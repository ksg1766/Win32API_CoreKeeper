#pragma once
#include "Scene.h"

class CGameScene :
	public CScene
{
public:
	CGameScene();
	virtual ~CGameScene();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void)	override;
	virtual void FixedUpdate(void)	override;
	virtual void Update(void)		override;
	virtual void LateUpdate(void)	override;
	virtual void Render(HDC m_DC)	override;
};