#pragma once
#include "IInGameMonsterBase.h"

class SaltBakerHand : public IInGameMonsterBase
{
public:
	SaltBakerHand();
	~SaltBakerHand();

	// delete Function
	SaltBakerHand(const SaltBakerHand& _Other) = delete;
	SaltBakerHand(SaltBakerHand&& _Other) noexcept = delete;
	SaltBakerHand& operator=(const SaltBakerHand& _Other) = delete;
	SaltBakerHand& operator=(SaltBakerHand&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

private:
	void OnSaltBakerHandDeathAnimationFrameChanged(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* TopperRenderer;
};							  