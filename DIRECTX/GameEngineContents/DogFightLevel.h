#pragma once
#include "InGameLevelBase.h"

// Ό³Έν :
class BulldogPlane;
class GameEngineTextureRenderer;
class BackgroundHills;
class BackgroundObject;
class Bulldog;
class CanteenPlane;
class DogCopter;
class InGameCuphead;
class DogFightLevel : public InGameLevelBase
{
public:
	// constrcuter destructer
	DogFightLevel();
	~DogFightLevel();

	// delete Function
	DogFightLevel(const DogFightLevel& _Other) = delete;
	DogFightLevel(DogFightLevel&& _Other) noexcept = delete;
	DogFightLevel& operator=(const DogFightLevel& _Other) = delete;
	DogFightLevel& operator=(DogFightLevel&& _Other) noexcept = delete;

public:
	void ColMapOnOffSwitch();
	void ResetPositionCloudLeftA(const FrameAnimation_DESC& _Info);
	void ResetPositionCloudLeftA2(const FrameAnimation_DESC& _Info);
	void ResetPositionCloudLeftB(const FrameAnimation_DESC& _Info);
	void ResetPositionCloudLeftC(const FrameAnimation_DESC& _Info);
	void ResetPositionCloudLeftC2(const FrameAnimation_DESC& _Info);
	void ResetPositionCloudLeftD(const FrameAnimation_DESC& _Info);
	void ResetPositionCloudLeftD2(const FrameAnimation_DESC& _Info);
	void ResetPositionPatchMiddleA(const FrameAnimation_DESC& _Info);
	void ResetPositionPlanePuffRight(const FrameAnimation_DESC& _Info);
	void ResetPositionPlanePuffLeft(const FrameAnimation_DESC& _Info);
	void PushToRotateCamera(GameEngineUpdateObject* _Object) override;
	void PushToBackgroundCamera(GameEngineUpdateObject* _Object) override;
	void LightUpAnimaitonFrameFinished(const FrameAnimation_DESC& _Info);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	BackgroundHills* Hills;
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* BackgroundSkyRenderer;
	// Cloud
	BackgroundObject* CloudA1;
	BackgroundObject* CloudA2;
	BackgroundObject* CloudB2;
	BackgroundObject* CloudC1;
	BackgroundObject* CloudC2;
	BackgroundObject* CloudD1;
	BackgroundObject* CloudD2;
	BackgroundObject* PlanePuffRight;
	BackgroundObject* PlanePuffLeft;
	// 
	BackgroundObject* PatchLeftA;

	Bulldog* PH1BullDog;
	BulldogPlane* PH1BulldogPlane;
	CanteenPlane* CaptainCanteenPlane;
	DogCopter* LeaderCopter;
	InGameCuphead* Cuphead;
	bool OnceCheck;
	GameEngineTextureRenderer* ScreenLightRenderer;
};

