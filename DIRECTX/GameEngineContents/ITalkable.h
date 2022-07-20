#pragma once
class ITalkable
{
public:
	// constrcuter destructer
	ITalkable();
	~ITalkable();

	// delete Function
	ITalkable(const ITalkable& _Other) = delete;
	ITalkable(ITalkable&& _Other) noexcept = delete;
	ITalkable& operator=(const ITalkable& _Other) = delete;
	ITalkable& operator=(ITalkable&& _Other) noexcept = delete;

protected:
	virtual void Talk() = 0;
private:
};

