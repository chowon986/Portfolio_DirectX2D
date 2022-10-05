#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BulldogPlane;
class GameEngineTextureRenderer;
class BulldogPlanePuff : public GameEngineActor
{
public:
	BulldogPlanePuff();
	~BulldogPlanePuff();

	BulldogPlanePuff(const BulldogPlanePuff& _Other) = delete;
	BulldogPlanePuff(BulldogPlanePuff&& _Other) noexcept = delete;
	BulldogPlanePuff& operator=(const BulldogPlanePuff& _Other) = delete;
	BulldogPlanePuff& operator=(BulldogPlanePuff&& _Other) noexcept = delete;

public:
	void SetBoss(BulldogPlane* _Boss) { Boss = _Boss; }
	BulldogPlane* GetBoss() { return Boss; }

	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetSpeed(float _Speed) { Speed = _Speed; }
	void SetDirection(float4 _Direction) { Direction = _Direction; }

private:
	void OnPuffAnimationFrameFinished(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	BulldogPlane* Boss;
	GameEngineTextureRenderer* Renderer;
	float4 Direction;
	float Speed;
};

