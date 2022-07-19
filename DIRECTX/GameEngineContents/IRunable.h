#pragma once
class IRunable
{
public:
	// constrcuter destructer
	IRunable();
	~IRunable();

	// delete Function
	IRunable(const IRunable& _Other) = delete;
	IRunable(IRunable&& _Other) noexcept = delete;
	IRunable& operator=(const IRunable& _Other) = delete;
	IRunable& operator=(IRunable&& _Other) noexcept = delete;

private:
};

