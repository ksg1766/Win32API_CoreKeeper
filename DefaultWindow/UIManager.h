#pragma once

class CGameObject;
class CUI;
class CUIManager
{
public:
	CUIManager();
	virtual ~CUIManager();

	void	Initialize();
	void	Release();

	void	InitializeSceneUI();
	void	InitializePopUpUI();

	void	AddSceneUI(CGameObject* _pUI);
	void	SubSceneUI(CGameObject* _pUI);

	void	PickingIcon(POINT _pt, bool _isPressing);

	void	OpenPopUpUI(CGameObject* _pUI);
	void	ClosePopUpUI(CGameObject* _pUI);


private:
	vector<CGameObject*>	vecGroupSceneUI;
	vector<CGameObject*>	vecGroupPopUpUI;
};

