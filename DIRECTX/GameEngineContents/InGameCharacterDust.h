#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class InGameCuphead;
enum class InGameCharacterState;
class GameEngineTextureRenderer;
class InGameCharacterDust : public GameEngineActor
{
public:
	InGameCharacterDust();
	~InGameCharacterDust();

	InGameCharacterDust(const InGameCharacterDust& _Other) = delete;
	InGameCharacterDust(InGameCharacterDust&& _Other) noexcept = delete;
	InGameCharacterDust& operator=(const InGameCharacterDust& _Other) = delete;
	InGameCharacterDust& operator=(InGameCharacterDust&& _Other) noexcept = delete;

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
	InGameCharacterState BeforeState;
};

