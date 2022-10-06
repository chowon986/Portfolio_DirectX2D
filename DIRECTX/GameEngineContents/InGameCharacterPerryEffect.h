#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class IInGameCharacterBase;
class GameEngineTextureRenderer;
class InGameCharacterPerryEffect : public GameEngineActor
{
public:
	InGameCharacterPerryEffect();
	~InGameCharacterPerryEffect();

	InGameCharacterPerryEffect(const InGameCharacterPerryEffect& _Other) = delete;
	InGameCharacterPerryEffect(InGameCharacterPerryEffect&& _Other) noexcept = delete;
	InGameCharacterPerryEffect& operator=(const InGameCharacterPerryEffect& _Other) = delete;
	InGameCharacterPerryEffect& operator=(InGameCharacterPerryEffect&& _Other) noexcept = delete;

public:
	void SetBoss(IInGameCharacterBase* _Boss) { Boss = _Boss; }
	IInGameCharacterBase* GetBoss() { return Boss; }

	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

private:
	void OnEffectAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	IInGameCharacterBase* Boss;
	GameEngineTextureRenderer* Renderer;
	float ElapsedTime;
};

