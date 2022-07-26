#pragma once
class ISpecialAttackable
{
public:
	// constrcuter destructer
	ISpecialAttackable();
	~ISpecialAttackable();

	// delete Function
	ISpecialAttackable(const ISpecialAttackable& _Other) = delete;
	ISpecialAttackable(ISpecialAttackable&& _Other) noexcept = delete;
	ISpecialAttackable& operator=(const ISpecialAttackable& _Other) = delete;
	ISpecialAttackable& operator=(ISpecialAttackable&& _Other) noexcept = delete;

protected:
	virtual void SpecialAttack() = 0;

private:
};

