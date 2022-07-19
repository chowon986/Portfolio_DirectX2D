#pragma once
class IPreparable
{
public:
	// constrcuter destructer
	IPreparable();
	~IPreparable();

	// delete Function
	IPreparable(const IPreparable& _Other) = delete;
	IPreparable(IPreparable&& _Other) noexcept = delete;
	IPreparable& operator=(const IPreparable& _Other) = delete;
	IPreparable& operator=(IPreparable&& _Other) noexcept = delete;

private:
};

