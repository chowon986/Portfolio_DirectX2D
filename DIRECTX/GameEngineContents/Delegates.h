#pragma once
template<typename T>
class MulticastDelegate
{
public:
	void Add(std::function<void(T)> func)
	{
		Delegates.push_back(func);
	}

	void Invoke(T Value)
	{
		for (auto Delegate : Delegates)
		{
			Delegate(Value);
		}
	}

	std::vector<std::function<void(T)>> Delegates;
};