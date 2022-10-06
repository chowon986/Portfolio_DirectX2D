#include "PreCompile.h"
#include "AstalCookieItem.h"

AstalCookieItem::AstalCookieItem()
{
	ItemName = "AstalCookie";
	MaxHP = 4;
	OnDashInvisible = false;
	PlayerCharacterType = CharacterType::Chalice;
}

AstalCookieItem::~AstalCookieItem()
{
}
