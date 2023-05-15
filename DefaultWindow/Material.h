#pragma once
#include "Item.h"

class CGameObject;
class CMaterial :
	public CItem
{
public:
	CMaterial();
	CMaterial(const CMaterial& rhs);

	virtual ~CMaterial();

	// CItem을(를) 통해 상속됨
	virtual void Initialize()			override;
	virtual int	 Update(void)			override;
	virtual int	 LateUpdate(void)		override;
	virtual void Render(HDC hDC)		override;
	virtual void Release(void)			override;
	 
	virtual void Use()					override;

	virtual void SetUsing(bool _isUsig)	override;

	MATERIAL		GetMaterialType() { return m_eMaterialType; }
	void			SetMaterialType(MATERIAL _eMaterialType) { m_eMaterialType = _eMaterialType; }

	//virtual	CItem* clone()				override;

private:
	virtual void SetMotion(void)		override;
	virtual void MoveFrame(void)		override;

	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:
	MATERIAL		m_eMaterialType;

	// CItem을(를) 통해 상속됨
};

 