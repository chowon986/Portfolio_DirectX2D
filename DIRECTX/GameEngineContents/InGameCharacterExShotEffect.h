#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class IInGameCharacterBase;
class GameEngineTextureRenderer;
class InGameCharacterExShotEffect : public GameEngineActor
{
public:
	InGameCharacterExShotEffect();
	~InGameCharacterExShotEffect();

	InGameCharacterExShotEffect(const InGameCharacterExShotEffect& _Other) = delete;
	InGameCharacterExShotEffect(InGameCharacterExShotEffect&& _Other) noexcept = delete;
	InGameCharacterExShotEffect& operator=(const InGameCharacterExShotEffect& _Other) = delete;
	InGameCharacterExShotEffect& operator=(InGameCharacterExShotEffect&& _Other) noexcept = delete;

public:
	void SetBoss(IInGameCharacterBase* _Boss) { Boss = _Boss; }
	IInGameCharacterBase* GetBoss() { return Boss; }

	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

private:
	void OnDustAnimationFrameFinished(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	IInGameCharacterBase* Boss;
	GameEngineTextureRenderer* Renderer;
	float ElapsedTime;
};

