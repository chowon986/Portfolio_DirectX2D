#pragma once
class IDiable
{
public:
	// constrcuter destructer
	IDiable();
	~IDiable();

	// delete Function
	IDiable(const IDiable& _Other) = delete;
	IDiable(IDiable&& _Other) noexcept = delete;
	IDiable& operator=(const IDiable& _Other) = delete;
	IDiable& operator=(IDiable&& _Other) noexcept = delete;

private:
};

