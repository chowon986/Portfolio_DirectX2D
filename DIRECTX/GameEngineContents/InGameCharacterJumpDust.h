#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class IInGameCharacterBase;
class GameEngineTextureRenderer;
class InGameCharacterJumpDust : public GameEngineActor
{
public:
	InGameCharacterJumpDust();
	~InGameCharacterJumpDust();

	InGameCharacterJumpDust(const InGameCharacterJumpDust& _Other) = delete;
	InGameCharacterJumpDust(InGameCharacterJumpDust&& _Other) noexcept = delete;
	InGameCharacterJumpDust& operator=(const InGameCharacterJumpDust& _Other) = delete;
	InGameCharacterJumpDust& operator=(InGameCharacterJumpDust&& _Other) noexcept = delete;

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

