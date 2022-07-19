#pragma once
class ISpeacialAttackable
{
public:
	// constrcuter destructer
	ISpeacialAttackable();
	~ISpeacialAttackable();

	// delete Function
	ISpeacialAttackable(const ISpeacialAttackable& _Other) = delete;
	ISpeacialAttackable(ISpeacialAttackable&& _Other) noexcept = delete;
	ISpeacialAttackable& operator=(const ISpeacialAttackable& _Other) = delete;
	ISpeacialAttackable& operator=(ISpeacialAttackable&& _Other) noexcept = delete;

private:
};

