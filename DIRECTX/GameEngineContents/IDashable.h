#pragma once
class IDashable
{
public:
	// constrcuter destructer
	IDashable();
	~IDashable();

	// delete Function
	IDashable(const IDashable& _Other) = delete;
	IDashable(IDashable&& _Other) noexcept = delete;
	IDashable& operator=(const IDashable& _Other) = delete;
	IDashable& operator=(IDashable&& _Other) noexcept = delete;

protected:
	virtual void Dash() = 0;

private:
};

