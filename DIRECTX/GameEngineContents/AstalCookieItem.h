#pragma once
#include "CharmItemBase.h"

class AstalCookieItem : public CharmItemBase
{
public:
	AstalCookieItem();
	~AstalCookieItem();
	AstalCookieItem(const AstalCookieItem& _Other) = delete;
	AstalCookieItem(AstalCookieItem&& _Other) noexcept = delete;
	AstalCookieItem& operator=(const AstalCookieItem& _Other) = delete;
	AstalCookieItem& operator=(AstalCookieItem&& _Other) noexcept = delete;

};

