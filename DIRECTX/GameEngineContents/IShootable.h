#pragma once
class IShootable
{
public:
	// constrcuter destructer
	IShootable();
	~IShootable();

	// delete Function
	IShootable(const IShootable& _Other) = delete;
	IShootable(IShootable&& _Other) noexcept = delete;
	IShootable& operator=(const IShootable& _Other) = delete;
	IShootable& operator=(IShootable&& _Other) noexcept = delete;

private:
};

