#pragma once

//enum class CharmType
//{
//	SmokeBomb,
//	TwinHeart,
//	CursedRelic,
//	AstalCookie,
//};
//
//enum class WeaponType
//{
//	PeaShooter,
//	SpreadShooter,
//	ConvergeShooter,
//	BoomerangShooter
//};

enum class ItemType
{
	None,
	Shoot,
	Super,
	Charm,
};

enum class InventoryType
{
	None,
	ShotA,
	ShotB,
	Super,
	Charm,
};


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
	DOGFIGHT,
	MONSTER,
	PC_BULLET,
	MONSTER_BULLET,
	MONSTER_BULLET2,
	MONSTER_DAMAGEABLE_BULLET,
	MOVEPLANELEFT,
	MOVEPLANERIGHT,
	GROUND,
	TRACKING1,
	TRACKING2,
	PARRIABLEOBJECT,
	ONLYPARRIABLEOBJECT,
	ITEM,
	RETURN,
	POSINDEX,
};

enum class GameObjectGroup 
{
	UI,
	Player,
	Monster,
	CharacterState,
	CharacterScore,
	INVENTORY,
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