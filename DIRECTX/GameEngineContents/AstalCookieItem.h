#pragma once
#include "WeaponItemBase.h"

class AstalCookieItem : public WeaponItemBase
{
public:
	AstalCookieItem();
	~AstalCookieItem();
	AstalCookieItem(const AstalCookieItem& _Other) = delete;
	AstalCookieItem(AstalCookieItem&& _Other) noexcept = delete;
	AstalCookieItem& operator=(const AstalCookieItem& _Other) = delete;
	AstalCookieItem& operator=(AstalCookieItem&& _Other) noexcept = delete;

};

