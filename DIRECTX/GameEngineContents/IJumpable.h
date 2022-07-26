#pragma once
class IJumpable
{
public:
	// constrcuter destructer
	IJumpable();
	~IJumpable();

	// delete Function
	IJumpable(const IJumpable& _Other) = delete;
	IJumpable(IJumpable&& _Other) noexcept = delete;
	IJumpable& operator=(const IJumpable& _Other) = delete;
	IJumpable& operator=(IJumpable&& _Other) noexcept = delete;

protected:
	virtual void Jump() = 0;

private:
};

