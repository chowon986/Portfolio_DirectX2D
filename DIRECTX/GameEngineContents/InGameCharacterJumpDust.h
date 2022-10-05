#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class InGameCuphead;
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
	void SetBoss(InGameCuphead* _Boss) { Boss = _Boss; }
	InGameCuphead* GetBoss() { return Boss; }

	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

private:
	void OnDustAnimationFrameFinished(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	InGameCuphead* Boss;
	GameEngineTextureRenderer* Renderer;
	float ElapsedTime;
};

