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
	Player = 300,
	NPC = 400,
	UI = 0,	
};