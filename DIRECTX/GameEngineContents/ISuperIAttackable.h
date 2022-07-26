#pragma once
class ISuperIAttackable
{
public:
	// constrcuter destructer
	ISuperIAttackable();
	~ISuperIAttackable();

	// delete Function
	ISuperIAttackable(const ISuperIAttackable& _Other) = delete;
	ISuperIAttackable(ISuperIAttackable&& _Other) noexcept = delete;
	ISuperIAttackable& operator=(const ISuperIAttackable& _Other) = delete;
	ISuperIAttackable& operator=(ISuperIAttackable&& _Other) noexcept = delete;

protected:
	virtual void SuperIAttack() = 0;

private:
};

