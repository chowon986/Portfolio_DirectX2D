#pragma once
class IEvadable
{
public:
	// constrcuter destructer
	IEvadable();
	~IEvadable();

	// delete Function
	IEvadable(const IEvadable& _Other) = delete;
	IEvadable(IEvadable&& _Other) noexcept = delete;
	IEvadable& operator=(const IEvadable& _Other) = delete;
	IEvadable& operator=(IEvadable&& _Other) noexcept = delete;

protected:
	virtual void Evade() = 0;

private:
};

