#pragma once
class ISuperIIIAttackable
{
public:
	// constrcuter destructer
	ISuperIIIAttackable();
	~ISuperIIIAttackable();

	// delete Function
	ISuperIIIAttackable(const ISuperIIIAttackable& _Other) = delete;
	ISuperIIIAttackable(ISuperIIIAttackable&& _Other) noexcept = delete;
	ISuperIIIAttackable& operator=(const ISuperIIIAttackable& _Other) = delete;
	ISuperIIIAttackable& operator=(ISuperIIIAttackable&& _Other) noexcept = delete;

private:
};

