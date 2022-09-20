#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class InGameCharacter;
class BulldogPlane;
class GameEngineCollision;
class GameEngineTextureRenderer;
class InGameMovementComponent;
class InGameLevelBase;
class InGameMonsterAnimationControllerComponent;
class SaltBaker : public IInGameMonsterBase
{
public:
	SaltBaker();
	~SaltBaker();

	// delete Function
	SaltBaker(const SaltBaker& _Other) = delete;
	SaltBaker(SaltBaker&& _Other) noexcept = delete;
	SaltBaker& operator=(const SaltBaker& _Other) = delete;
	SaltBaker& operator=(SaltBaker&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

	void OnIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack3AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnAttack4AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltBakerPhase2IntroFrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltBakerPhase2FrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltBakerAttack5FrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltBakerAttack6FrameChanged(const FrameAnimation_DESC& _Info);

public:
	void SetBackgroundRenderer(GameEngineTextureRenderer* _Renderer) { BackgroundRenderer = _Renderer; }
	GameEngineTextureRenderer* GetBackgroundRenderer() { return BackgroundRenderer; }

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* HandRenderer;
	InGameMonsterState State;
	InGameMonsterAttackState AttackState;
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* BackgroundRenderer;
	InGameLevelBase* Level;
	bool TimeCountOn;
	float CanAttackIntervalTime;
	float ElapsedTime;
};