#pragma once
class IDuckable
{
public:
	// constrcuter destructer
	IDuckable();
	~IDuckable();

	// delete Function
	IDuckable(const IDuckable& _Other) = delete;
	IDuckable(IDuckable&& _Other) noexcept = delete;
	IDuckable& operator=(const IDuckable& _Other) = delete;
	IDuckable& operator=(IDuckable&& _Other) noexcept = delete;

protected:
	virtual void Duck() = 0;

private:
};

