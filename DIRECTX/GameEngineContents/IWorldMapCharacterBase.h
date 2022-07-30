#pragma once
#include "Delegates.h"
#include "IWalkable.h"
#include "IIdleable.h"

class GameEngineTextureRenderer;
enum class WorldMapCharacterState
{
	Idle,
	Walk,
	// talk, enter
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

