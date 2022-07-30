#pragma once
class ISuperAttackable
{
public:
	// constrcuter destructer
	ISuperAttackable();
	~ISuperAttackable();

	// delete Function
	ISuperAttackable(const ISuperAttackable& _Other) = delete;
	ISuperAttackable(ISuperAttackable&& _Other) noexcept = delete;
	ISuperAttackable& operator=(const ISuperAttackable& _Other) = delete;
	ISuperAttackable& operator=(ISuperAttackable&& _Other) noexcept = delete;

protected:
	virtual void SuperAttack() = 0;

private:
};

