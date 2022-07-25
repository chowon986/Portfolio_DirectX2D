#pragma once
#include "Iwalkable.h"
#include "IIdleable.h"

class GameEngineTextureRenderer;

enum class WorldMapCupheadState
{
	Idle,
	Walk,
};

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

class IWorldMapCharacterBase : public GameEngineActor, public IWalkable, public IIdleable
{
public:
	// constrcuter destructer
	IWorldMapCharacterBase();
	~IWorldMapCharacterBase();

	// delete Function
	IWorldMapCharacterBase(const IWorldMapCharacterBase& _Other) = delete;
	IWorldMapCharacterBase(IWorldMapCharacterBase&& _Other) noexcept = delete;
	IWorldMapCharacterBase& operator=(const IWorldMapCharacterBase& _Other) = delete;
	IWorldMapCharacterBase& operator=(IWorldMapCharacterBase&& _Other) noexcept = delete;

public:
	void SetState(WorldMapCupheadState _State);
	WorldMapCupheadState GetState();

	void SetDirection(std::string _Dir);
	std::string GetDirection() { return Dir; }

	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	MulticastDelegate<WorldMapCupheadState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<std::string>& GetDirectionChangedDelegate() { return DirectionChangedDelegate; }

private:
	GameEngineTextureRenderer* Renderer;
	WorldMapCupheadState State;
	std::string Dir;
	MulticastDelegate<WorldMapCupheadState> StateChangedDelegate;
	MulticastDelegate<std::string> DirectionChangedDelegate;
};

