#pragma once
class IDoubleJumpable
{
public:
	// constrcuter destructer
	IDoubleJumpable();
	~IDoubleJumpable();

	// delete Function
	IDoubleJumpable(const IDoubleJumpable& _Other) = delete;
	IDoubleJumpable(IDoubleJumpable&& _Other) noexcept = delete;
	IDoubleJumpable& operator=(const IDoubleJumpable& _Other) = delete;
	IDoubleJumpable& operator=(IDoubleJumpable&& _Other) noexcept = delete;

private:
};

