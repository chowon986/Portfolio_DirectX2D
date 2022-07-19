#pragma once
class IAimable
{
public:
	// constrcuter destructer
	IAimable();
	~IAimable();

	// delete Function
	IAimable(const IAimable& _Other) = delete;
	IAimable(IAimable&& _Other) noexcept = delete;
	IAimable& operator=(const IAimable& _Other) = delete;
	IAimable& operator=(IAimable&& _Other) noexcept = delete;

private:
};

