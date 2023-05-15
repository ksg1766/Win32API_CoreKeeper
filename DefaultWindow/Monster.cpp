#include "stdafx.h"
#include "Monster.h"
#include "Managers.h"
#include "Struct.h"
#include "Collider.h"

CMonster::CMonster()
{
	m_IsDead = false;
	m_eRender = RENDERID::GAMEOBJECT;
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	//vecTileMap = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::TILE);
}

int CMonster::Update(void)
{
	return 0;
}

int CMonster::LateUpdate(void)
{
	return 0;
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release(void)
{
}

bool CMonster::CanGo(Pos _vPos)
{

	TYPE tileType;
	if (_vPos.x < 0)
		_vPos.x = 0;
	if (_vPos.x >= TILEX)
		_vPos.x = TILEX - 1;

	if (_vPos.y < 0)
		_vPos.y = 0;
	if (_vPos.y >= TILEY)
		_vPos.y = TILEY - 1;
	
	if(vecTileMap[_vPos.x + TILEX * _vPos.y])
		tileType = vecTileMap[_vPos.x + TILEX * _vPos.y]->GetType();
	else
		tileType = TYPE::WALL;

	return (tileType == TYPE::TILE);
}

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int	f; // f = g + h
	int	g;
	Pos		pos;
};

void CMonster::AStar()
{
	vecTileMap = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::TILE);
	// F = G + H
	// F = ���� ���� (���� ���� ����, ��ο� ���� �޶���)
	// G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ��� (���� ���� ����, ��ο� ���� �޶���)
	// H = ���������� �󸶳� ������� (���� ���� ����, ����)

	int	i = (m_pCollider->GetPosition().x - (TILECX >> 1)) / TILECX;
	int	j = (m_pCollider->GetPosition().y - (TILECY >> 1)) / TILECY;
	Pos start = Pos(i, j);
	

	i = (m_pTarget->GetCollider()->GetPosition().x - (TILECX >> 1)) / TILECX;
	j = (m_pTarget->GetCollider()->GetPosition().y - (TILECY >> 1)) / TILECY;
	

	Pos dest = Pos(i, j);

	enum
	{
		DIR_COUNT = 4
	};

	Pos front[] =
	{
		Pos{ 1, 0 },	// RIGHT
		Pos{ 0, -1 },	// UP
		Pos{ -1, 0 },	// LEFT
		Pos{ 0, 1 },	// DOWN
		Pos{ 1, -1 },	// UP_RIGHT
		Pos{ -1, -1 },	// UP_LEFT
		Pos{ -1, 1 },	// DOWN_LEFT
		Pos{ 1, 1 },	// DOWN_RIGHT
	};

	int cost[] =
	{
		10, // UP
		10, // LEFT
		10, // DOWN
		10, // RIGHT
		14,
		14,
		14,
		14
	};

	const int size = vecTileMap.size();

	// ClosedList
	// close[y][x] -> (y, x)�� �湮�� �ߴ��� ����
	vector<vector<bool>> closed(TILEY, vector<bool>(TILEX, false));

	// best[y][x] -> ���ݱ��� (y, x)�� ���� ���� ���� ��� (���� ���� ����)
	vector<vector<int>> best(TILEY, vector<int>(TILEX, INT32_MAX));

	// �θ� ���� �뵵
	map<Pos, Pos> parent;

	// OpenList
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 1) ����(�߰�) �ý��� ����
	// - �̹� �� ���� ��θ� ã�Ҵٸ� ��ŵ
	// 2) �ڴʰ� �� ���� ��ΰ� �߰ߵ� �� ���� -> ���� ó�� �ʼ�
	// - openList���� ã�Ƽ� �����Ѵٰų�.
	// - pq���� pop�� ������ �����Ѵٰų�.

	// �ʱⰪ
	{
		int g = 0;
		int h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�
		PQNode node = pq.top();
		pq.pop();

		// ������ ��ǥ�� ���� ��η� ã�Ƽ�\
		// �� ���� ��η� ���ؼ� �̹� �湮(closed)�� ��� ��ŵ
// [����]

		if (closed[node.pos.y][node.pos.x])
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// �湮
		closed[node.pos.y][node.pos.x] = true;

		// �������� ���������� �ٷ� ����
		if (node.pos == dest)
			break;

		for (int dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			
			if (nextPos.x < 0)
				nextPos.x = 0;
			if (nextPos.x >= TILEX)
				nextPos.x = TILEX-1;

			if (nextPos.y < 0)
				nextPos.y = 0;
			if (nextPos.y >= TILEY)
				nextPos.y = TILEY-1;

			if (nextPos == dest)
				if (CanGo(dest) == false)
					dest = node.pos;
					//m_path.clear();

			// �� �� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false)
				continue;
			// [����] �̹� �湮�� ���̸� ��ŵ

			if (closed[nextPos.y][nextPos.x])
				continue;

			// ��� ���
			int g = node.g + cost[dir];
			int h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// �ٸ� ��ο��� �� ���� ���� ã������ ��ŵ
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// ���� ����
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}

	// �Ųٷ� �Ž��� �ö󰣴�
	Pos pos = dest;

	m_path.clear();
	m_pathIndex = 0;

	while (true)
	{
		m_path.push_back(pos);

		// �������� �ڽ��� �� �θ��̴�
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(m_path.begin(), m_path.end());
}