#pragma once

enum class ObjectOrder
{
	PC,
	NPC,
	MONSTER,
	PC_BULLET,
	MONSTER_BULLET,
};

enum class GameObjectGroup 
{
	UI,
	Player,
	Monster,
};

enum class ZOrder :int
{
	Background = 1000,
	Foreground = 900,
	Monster = 800,
	NPC = 700,
	Player = 600,
	NPCB = 500,
	UI = 400,
	TEST = 100
};