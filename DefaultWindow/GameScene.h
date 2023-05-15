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
	virtual void Release()			override;

	void	SetHiveMotherDead(bool _bDead) { m_IsHiveMotherDead = _bDead; }
	void	SetGlurchDead(bool _bDead) { m_IsGlurchDead = _bDead; }

	bool	GetGlurchDead() { return m_IsGlurchDead; }
	bool	GetHiveMotherDead() { return m_IsHiveMotherDead; }

private:
	bool	m_IsGlurchDead;
	bool	m_IsHiveMotherDead;
};