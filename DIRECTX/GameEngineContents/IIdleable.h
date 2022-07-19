#pragma once
class IIdleable
{
public:
	// constrcuter destructer
	IIdleable();
	~IIdleable();

	// delete Function
	IIdleable(const IIdleable& _Other) = delete;
	IIdleable(IIdleable&& _Other) noexcept = delete;
	IIdleable& operator=(const IIdleable& _Other) = delete;
	IIdleable& operator=(IIdleable&& _Other) noexcept = delete;

private:
};

