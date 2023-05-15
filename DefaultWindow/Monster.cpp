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
	// F = 최종 점수 (작을 수록 좋음, 경로에 따라 달라짐)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐)
	// H = 목적지에서 얼마나 가까운지 (작을 수록 좋음, 고정)

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
	// close[y][x] -> (y, x)에 방문을 했는지 여부
	vector<vector<bool>> closed(TILEY, vector<bool>(TILEX, false));

	// best[y][x] -> 지금까지 (y, x)에 대한 가장 좋은 비용 (작을 수록 좋음)
	vector<vector<int>> best(TILEY, vector<int>(TILEX, INT32_MAX));

	// 부모 추적 용도
	map<Pos, Pos> parent;

	// OpenList
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 1) 예약(발견) 시스템 구현
	// - 이미 더 좋은 경로를 찾았다면 스킵
	// 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수
	// - openList에서 찾아서 제거한다거나.
	// - pq에서 pop한 다음에 무시한다거나.

	// 초기값
	{
		int g = 0;
		int h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로로 찾아서\
		// 더 빠른 경로로 인해서 이미 방문(closed)된 경우 스킵
// [선택]

		if (closed[node.pos.y][node.pos.x])
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에 도착했으면 바로 종료
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

			// 갈 수 있는 지역은 맞는지 확인
			if (CanGo(nextPos) == false)
				continue;
			// [선택] 이미 방문한 곳이면 스킵

			if (closed[nextPos.y][nextPos.x])
				continue;

			// 비용 계산
			int g = node.g + cost[dir];
			int h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// 다른 경로에서 더 빠른 길을 찾았으면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}

	// 거꾸로 거슬러 올라간다
	Pos pos = dest;

	m_path.clear();
	m_pathIndex = 0;

	while (true)
	{
		m_path.push_back(pos);

		// 시작점은 자신이 곧 부모이다
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(m_path.begin(), m_path.end());
}