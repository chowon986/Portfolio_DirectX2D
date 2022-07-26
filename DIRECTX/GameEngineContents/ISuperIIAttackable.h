#pragma once
class ISuperIIAttackable
{
public:
	// constrcuter destructer
	ISuperIIAttackable();
	~ISuperIIAttackable();

	// delete Function
	ISuperIIAttackable(const ISuperIIAttackable& _Other) = delete;
	ISuperIIAttackable(ISuperIIAttackable&& _Other) noexcept = delete;
	ISuperIIAttackable& operator=(const ISuperIIAttackable& _Other) = delete;
	ISuperIIAttackable& operator=(ISuperIIAttackable&& _Other) noexcept = delete;

protected:
	virtual void SuperIIAttack() = 0;

private:
};

