#pragma once
class IWalkable
{
public:
	// constrcuter destructer
	IWalkable();
	~IWalkable();

	// delete Function
	IWalkable(const IWalkable& _Other) = delete;
	IWalkable(IWalkable&& _Other) noexcept = delete;
	IWalkable& operator=(const IWalkable& _Other) = delete;
	IWalkable& operator=(IWalkable&& _Other) noexcept = delete;

private:
};

