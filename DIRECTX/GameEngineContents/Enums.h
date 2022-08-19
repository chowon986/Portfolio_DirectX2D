#pragma once

enum class CharacterType
{
	Cuphead,
	Mugman,
	Chalice,
};

enum class ObjectOrder
{
	PC,
	NPC,
	MONSTER,
	PC_BULLET,
	MONSTER_BULLET,
	MOVEPLANELEFT,
	MOVEPLANERIGHT,
	GROUND,
};

enum class GameObjectGroup 
{
	UI,
	Player,
	Monster,
	CharacterState,
};

enum class ZOrder : int
{
	Background = 1000,
	Foreground = 900,
	Monster = 800,
	NPC = 700,
	Player = 600,
	NPCB = 500,
	UI = 400,
};