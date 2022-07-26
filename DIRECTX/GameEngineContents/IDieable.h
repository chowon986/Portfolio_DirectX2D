#pragma once
class IDieable
{
public:
	// constrcuter destructer
	IDieable();
	~IDieable();

	// delete Function
	IDieable(const IDieable& _Other) = delete;
	IDieable(IDieable&& _Other) noexcept = delete;
	IDieable& operator=(const IDieable& _Other) = delete;
	IDieable& operator=(IDieable&& _Other) noexcept = delete;

protected:
	virtual void Die() = 0;

private:
};

