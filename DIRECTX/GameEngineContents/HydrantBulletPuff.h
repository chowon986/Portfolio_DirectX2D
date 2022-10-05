#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HydrantBullet;
class GameEngineTextureRenderer;
class HydrantBulletPuff : public GameEngineActor
{
public:
	HydrantBulletPuff();
	~HydrantBulletPuff();

	HydrantBulletPuff(const HydrantBulletPuff& _Other) = delete;
	HydrantBulletPuff(HydrantBulletPuff&& _Other) noexcept = delete;
	HydrantBulletPuff& operator=(const HydrantBulletPuff& _Other) = delete;
	HydrantBulletPuff& operator=(HydrantBulletPuff&& _Other) noexcept = delete;

public:
	void SetBoss(HydrantBullet* _Boss) { Boss = _Boss; }
	HydrantBullet* GetBoss() { return Boss; }

	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

private:
	void OnHydrantPuffAnimationFrameFinished(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	HydrantBullet* Boss;
	GameEngineTextureRenderer* Renderer;
};

