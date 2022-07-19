#pragma once
class IEvatiable
{
public:
	// constrcuter destructer
	IEvatiable();
	~IEvatiable();

	// delete Function
	IEvatiable(const IEvatiable& _Other) = delete;
	IEvatiable(IEvatiable&& _Other) noexcept = delete;
	IEvatiable& operator=(const IEvatiable& _Other) = delete;
	IEvatiable& operator=(IEvatiable&& _Other) noexcept = delete;

private:
};

