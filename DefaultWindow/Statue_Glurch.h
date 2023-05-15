#pragma once
#include "Wall.h"
class CStatue_Glurch :
	public CWall
{
public:
	CStatue_Glurch();
	virtual ~CStatue_Glurch();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual int	 LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void	OnCollisionStay(CCollider* _pOther) override;

private:
	void		SetMotion(void);
	void		MoveFrame(void);
};

