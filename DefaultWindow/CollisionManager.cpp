#include "stdafx.h"
#include "Managers.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"


CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::LateUpdate()
{
	for (UINT iRow = 0; iRow < (UINT)TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)TYPE::END; ++iCol)
		{
			if ((UINT)TYPE::TILE == iRow && (UINT)TYPE::TILE == iCol)	// ���߿� enum���� �ٲٰ� ���� �� ��...
				continue;
			//if ((UINT)TYPE::PLAYER == iRow && (UINT)TYPE::PLAYER == iCol)	// ���߿� enum���� �ٲٰ� ���� �� ��...
			//	continue;

			if (m_arrCheck[iRow] & (1 << iCol))		// �� ������ �浹 �ȳ���?
			{
				CheckCollisionByType((TYPE)iRow, (TYPE)iCol);
			}
		}
	}
}

void CCollisionManager::CheckCollisionByType(TYPE _eTypeLeft, TYPE _eTypeRight)
{
	CScene* pCurScene = CManagers::instance().Scene()->CurrentScene();

	const vector<CGameObject*>& vecLeft = pCurScene->GetObjList(_eTypeLeft);
	const vector<CGameObject*>& vecRight = pCurScene->GetObjList(_eTypeRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			if (abs(pLeftCol->GetPosition().x - pRightCol->GetPosition().x) > 300
				&& abs(pLeftCol->GetPosition().y - pRightCol->GetPosition().y) > 200)
				continue;

			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			
			iter = m_mapColInfo.find(ID.ID);

			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))
			{	// ���� �浹 ��
				if (iter->second)
				{	// �������� �浹
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{	// �� �� �ϳ� ���� �����̸� �浹 ����
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollisionStay(pRightCol);
						pRightCol->OnCollisionStay(pLeftCol);
					}
				}
				else
				{	// �������� �浹 x	// �ٵ� �� �� �ϳ� ���� �����̸� �浹���� ���� ������ ���
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{		// ���� �浹 x��
				if (iter->second)
				{	//�������� �浹�ϰ� �־���.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider * _pLeft, CCollider * _pRight)
{
	Vector2 vLeftPos = _pLeft->GetPosition();
	Vector2 vLeftScale = _pLeft->GetScale();

	Vector2 vRightPos =	_pRight->GetPosition();
	Vector2 vRightScale = _pRight->GetScale();

	if ((abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& (abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)))
	{
		return true;
	}
	return false;
}

void CCollisionManager::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)TYPE::TILE);
}

void CCollisionManager::CheckGroup(TYPE _eLeft, TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if(iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}
