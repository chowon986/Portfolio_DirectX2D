#pragma once
class IParriable
{
public:
	// constrcuter destructer
	IParriable();
	~IParriable();

	// delete Function
	IParriable(const IParriable& _Other) = delete;
	IParriable(IParriable&& _Other) noexcept = delete;
	IParriable& operator=(const IParriable& _Other) = delete;
	IParriable& operator=(IParriable&& _Other) noexcept = delete;

protected:
	virtual void Parry() = 0;

private:
};

