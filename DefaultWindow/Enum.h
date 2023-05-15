#pragma once

enum class TYPE
{
	PLAYER	= 0,
	RAY		= 1,
	MONSTER	= 2,
	BOSS	= 3,
	ITEM	= 4,
	TILE	= 5,
	END		= 6,

	WALL	= 7,
	EFFECT  = 8,

	UI		= 9,
	PROJECTILE = 10,
};

enum class RENDERID
{
	BACKGROUND = 0,
	GAMEOBJECT = 1,
	EFFECT = 2,
	UI = 3,
	RENDER_END = 4,
};

enum class ITEM
{
	WEAPON		= 0,
	HELMET		= 1,
	CHEST		= 2,
	PANTS		= 3,
	MATERIAL	= 4,
	CONSUM		= 5,
	END			= 6,
};

//enum class WEAPON
//{
//	SWORD	= 0,
//	PICKAXE	= 1,
////	SHOVEL	= 2,
//	END		= 2,
//};

enum class MONSTER
{

};

enum class BOSS
{
	GLURCH		= 0,
	HIVEMOTHER	= 1,
	END			= 2,
};

enum class MATERIAL
{
	STONE_COPPER	= 0,
	STONE_IRON		= 1,
	INGOT_COPPER	= 2,
	INGOT_IRON		= 3,
	END				= 4,
};

enum class EFFECT_TYPE
{
	HIT = 0,
	GLOW = 1,
	END = 2,
};

enum class STATE
{
	IDLE	= 0,
	MOVE	= 1,
	ATTACK	= 2,
	DEAD	= 3,
	END		= 4,
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

enum class EVENT_TYPE
{
	CREATE_OBJECT	= 0,
	DELETE_OBJECT	= 1,
	SCENE_CHANGE	= 2,
	END				= 3,
};

enum class SCENEUI
{
	HPBAR = 0,
	HUNGERBAR = 1,
	QUICKSLOT = 2,
	BOSSHP = 3,
	END = 4,
};

enum class CHANNELID
{
	SOUND_EFFECT1	= 0,
	SOUND_EFFECT2	= 1,
	SOUND_EFFECT3	= 2,
	SOUND_EFFECT4	= 3,
	SOUND_EFFECT5	= 4,
	SOUND_EFFECT6	= 5,
	SOUND_EFFECT7	= 6,
	SOUND_EFFECT8	= 7,
	SOUND_EFFECT9	= 8,
	SOUND_EFFECT10	= 9,
	SOUND_EFFECT11	= 10,
	SOUND_EFFECT12	= 11,
	SOUND_BGM1		= 12,
	SOUND_BGM2		= 13,
	MAXCHANNEL		= 14,
	END				= 15,
};

enum class BRUSH_TYPE
{
	HOLLOW		= 0,
	SOLID			= 1,
	END			= 2
};

enum class PEN_TYPE
{
	RED			= 0,
	GREEN		= 1,
	BLUE		= 2,
	END			= 3,
};