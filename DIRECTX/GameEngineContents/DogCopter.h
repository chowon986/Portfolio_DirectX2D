#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class Bulldog;
class DogCopter : public GameEngineActor
{
public:
	// constrcuter destructer
	DogCopter();
	~DogCopter();

	// delete Function
	DogCopter(const DogCopter& _Other) = delete;
	DogCopter(DogCopter&& _Other) noexcept = delete;
	DogCopter& operator=(const DogCopter& _Other) = delete;
	DogCopter& operator=(DogCopter&& _Other) noexcept = delete;

public:
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	IInGameCharacterBase* Player;
	Bulldog* BossBulldog;
};

