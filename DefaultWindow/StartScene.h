#pragma once
#include "Scene.h"

class CStartScene :
	public CScene
{
public:
	CStartScene();
	virtual ~CStartScene();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual void FixedUpdate(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC m_DC) override;
};

