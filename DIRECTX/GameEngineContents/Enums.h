#pragma once

enum class GameObjectGroup 
{
	UI,
	Player,
	Monster,
};

enum class ZOrder:int
{
	Background = 1000,
	Foreground = 900,
	Monster = 500,
	NPC = 400,
	Player = 300,
	NPCB = 200,
	UI = 0,	
};