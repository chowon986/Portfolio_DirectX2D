#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// ���� :
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class Ph1Dog;
class Bulldog;
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
	GameEngineTextureRenderer* BulldogPlaneFront;
	GameEngineTextureRenderer* BulldogPlaneWingLeft;
	GameEngineTextureRenderer* BulldogPlaneWingRight;
	GameEngineTextureRenderer* BulldogPlaneBack;
	GameEngineTextureRenderer* BulldogPlaneTail;
	GameEngineTextureRenderer* BulldogPropellorRingCenter;
	GameEngineTextureRenderer* BulldogPropellorTipCenter;
	GameEngineTextureRenderer* BulldogPropellorSpinCenter;
	GameEngineTextureRenderer* BulldogPropelloRingLeft;
	GameEngineTextureRenderer* BulldogPropelloRingRight;
	GameEngineTextureRenderer* BulldogPropellorTipLeft;
	GameEngineTextureRenderer* BulldogPropellorSpinLeft;
	GameEngineTextureRenderer* BulldogPropellorTipRight;
	GameEngineTextureRenderer* BulldogPropellorSpinRight;
	GameEngineTextureRenderer* BulldogPlaneFlapLeftA;
	GameEngineTextureRenderer* BulldogPlaneFlapLeftB;
	GameEngineTextureRenderer* BulldogPlaneFlapRightA;
	GameEngineTextureRenderer* BulldogPlaneFlapRightB;

	std::vector<GameEngineTextureRenderer*> AllBulldogPlaneRenderer;
};

