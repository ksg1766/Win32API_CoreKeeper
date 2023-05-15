#pragma once
#include "GameObject.h"
class CHartCoreTile :
	public CGameObject
{
public:
	CHartCoreTile();
	virtual ~CHartCoreTile();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

