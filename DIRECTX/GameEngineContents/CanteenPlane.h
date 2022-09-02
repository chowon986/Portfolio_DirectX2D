#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
enum class InGameDogCopterState;
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class Canteen;
class DogCopter;
class CanteenPlane : public GameEngineActor
{
public:
	// constrcuter destructer
	CanteenPlane();
	~CanteenPlane();

	// delete Function
	CanteenPlane(const CanteenPlane& _Other) = delete;
	CanteenPlane(CanteenPlane&& _Other) noexcept = delete;
	CanteenPlane& operator=(const CanteenPlane& _Other) = delete;
	CanteenPlane& operator=(CanteenPlane&& _Other) noexcept = delete;

public:
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }

	void SetDogCopter(DogCopter* _LeaderCopter) { LeaderCopter = _LeaderCopter; }
	DogCopter* GetDogCopter() { return LeaderCopter; }

	bool CanMove(GameEngineCollision* _This, GameEngineCollision* _Other);

	bool RotateLeaderCopter();

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage) { ColMapImage = _ColMapImage; }
	GameEngineTextureRenderer* GetColMapImage() { return ColMapImage; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	
private:
	GameEngineCollision* LeftCollision;
	GameEngineCollision* RightCollision;
	GameEngineCollision* GroundCollision;

	GameEngineTextureRenderer* ColMapImage;
	GameEngineTexture* ColMapTexture;
	float4 MoveDirection;

	InGameDogCopterState LeaderState;
	IInGameCharacterBase* Player;
	Canteen* CaptainCanteen;
	DogCopter* LeaderCopter;

	float ElapsedTime;
	bool IsPhase2MoveCompleted;
};

