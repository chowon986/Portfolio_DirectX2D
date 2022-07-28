#pragma once
#include "Iwalkable.h"
#include "IIdleable.h"

class GameEngineTextureRenderer;

enum class WorldMapCharacterState
{
	Idle,
	Walk,
	// talk, enter
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
	void SetState(WorldMapCharacterState _State);
	WorldMapCharacterState GetState();

	void SetDirection(std::string _Dir);
	std::string GetDirection() { return Dir; }

	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage) { ColMapImage = _ColMapImage; }
	GameEngineTextureRenderer* GetColMapImage() { return ColMapImage; }

	MulticastDelegate<WorldMapCharacterState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<std::string>& GetDirectionChangedDelegate() { return DirectionChangedDelegate; }

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* ColMapImage;
	WorldMapCharacterState State;
	std::string Dir;
	MulticastDelegate<WorldMapCharacterState> StateChangedDelegate;
	MulticastDelegate<std::string> DirectionChangedDelegate;
};

