#pragma once
class IDamageable
{
public:
	// constrcuter destructer
	IDamageable();
	~IDamageable();

	// delete Function
	IDamageable(const IDamageable& _Other) = delete;
	IDamageable(IDamageable&& _Other) noexcept = delete;
	IDamageable& operator=(const IDamageable& _Other) = delete;
	IDamageable& operator=(IDamageable&& _Other) noexcept = delete;

private:
};

