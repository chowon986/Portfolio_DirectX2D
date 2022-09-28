#pragma once
#include "InGameLevelBase.h"

class Ph2Dog;
class BulldogPlane;
class GameEngineTextureRenderer;
class BackgroundHills;
class BackgroundObject;
class Bulldog;
class CanteenPlane;
class DogCopter;
class InGameCuphead;
class CharacterScore;
class IInGameCharacterBase;
enum class InGameMonsterState;
class CharacterState;
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
	void PushToRotateCamera2(GameEngineUpdateObject* _Object) override;
	void PushToBackgroundCamera(GameEngineUpdateObject* _Object) override;
	void LightOnAnimaitonFrameFinished(const FrameAnimation_DESC& _Info);
	void BulldogIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void DogCopterIntroPhase1IntroAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void DogCopterIntroPhase1IntroAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void KnockOutAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void ReadyWallopAnimationFrameFinished(const FrameAnimation_DESC& _Info);

	CharacterState* GetCharacterState() { return State;}

protected:
	void LevelStartEvent() override;
	void LevelEndEvent() override;
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
	GameEngineTextureRenderer* BulldogIntroRenderer;
	GameEngineTextureRenderer* DogCopterIntroRenderer;
	// 
	BackgroundObject* PatchLeftA;

	Bulldog* PH1BullDog;
	BulldogPlane* PH1BulldogPlane;
	CanteenPlane* CaptainCanteenPlane;
	DogCopter* LeaderCopter;
	InGameCuphead* Cuphead;
	bool OnceCheck;
	GameEngineTextureRenderer* ScreenLightRenderer;
	bool IrisOnceCheck;
	float ElapsedTime;
	float PlayElapsedTime;

	Ph2Dog* DogFightPh2DogB;
	Ph2Dog* DogFightPh2DogD;
	Ph2Dog* DogFightPh2DogA;
	Ph2Dog* DogFightPh2DogC;
	InGameMonsterState OldState;

	float RotateElapsedTime;
	bool IsRotateCompleted;
	float ZAngle;

	GameEngineTextureRenderer* ReadyWallopRenderer;
	GameEngineTextureRenderer* HPRenderer;
	int HPCount;
	GameEngineTextureRenderer* SuperMeter;
	CharacterState* State;
	CharacterScore* Score;
	float RotateTime;

};

