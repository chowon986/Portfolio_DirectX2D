#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class Ph1Dog;
class Bulldog;
class GameEngineTexture;
class BulldogPlane : public GameEngineActor
{
public:
	// constrcuter destructer
	BulldogPlane();
	~BulldogPlane();

	// delete Function
	BulldogPlane(const BulldogPlane& _Other) = delete;
	BulldogPlane(BulldogPlane&& _Other) noexcept = delete;
	BulldogPlane& operator=(const BulldogPlane& _Other) = delete;
	BulldogPlane& operator=(BulldogPlane&& _Other) noexcept = delete;

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
	Ph1Dog* DogFightPh1Dog;

	std::vector<GameEngineTextureRenderer*> AllBulldogPlaneRenderer;
	std::vector<GameEngineTextureRenderer*> WingRenderers;
	GameEngineTexture* ColMapTexture;
	GameEngineTextureRenderer* ColMapImage;
	float4 Direction;

	float PuffDeltaTime;
	bool OnDeath;

public:
	bool CanMoveLeftRight;
};

