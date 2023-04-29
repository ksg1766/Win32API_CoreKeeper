#pragma once

enum class TYPE
{
	PLAYER	= 0,
	MONSTER	= 1,
	BOSS	= 2,
	WALL	= 3,
	ITEM	= 4,
	TILE	= 5,

	END		= 6,
};

enum class ITEM
{
	WEAPON	= 0,
	HELMET	= 1,
	CHEST	= 2,
	PANTS	= 3,
	END		= 4,
};

//enum class WEAPON
//{
//	SWORD	= 0,
//	PICKAXE	= 1,
////	SHOVEL	= 2,
//	END		= 2,
//};

enum class RENDERID
{
	BACKGROUND,
	GAMEOBJECT,
	EFFECT,
	UI,
	END,
};

enum class STATE
{
	IDLE	= 0,
	MOVE	= 1,
	ATTACK	= 2,
	END		= 3,
};

enum class DIR
{
	RIGHT		= 0,
	RIGHTUP		= 1,
	UP			= 2,
	LEFTUP		= 3,
	LEFT		= 4,
	LEFTDOWN	= 5,
	DOWN		= 6,
	RIGHTDOWN	= 7,
	END			= 8,
};

enum class BRUSH_TYPE
{
	HOLLOW		= 0,
	END			= 1,
};

enum class PEN_TYPE
{
	RED			= 0,
	GREEN		= 1,
	BLUE		= 2,
	END			= 3,
};