#pragma once
class CScrollManager
{
public:
	CScrollManager();
	~CScrollManager();

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	float		Get_ScrollY(void) { return m_fScrollY; }

	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	void		ScrollShaking();
	void		StartScrollShaking(int _iCount);

public:
	void Initialize();
	void Release();

private:
	float					m_fScrollX;
	float					m_fScrollY;
	DWORD					m_dwTime;
};

