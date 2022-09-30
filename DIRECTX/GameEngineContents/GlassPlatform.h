#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class GlassPlatform : public GameEngineActor
{
public:
	// constrcuter destructer
	GlassPlatform();
	~GlassPlatform();

	// delete Function
	GlassPlatform(const GlassPlatform& _Other) = delete;
	GlassPlatform(GlassPlatform&& _Other) noexcept = delete;
	GlassPlatform& operator=(const GlassPlatform& _Other) = delete;
	GlassPlatform& operator=(GlassPlatform&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetPositionNum(int _Num) { PositionNum = _Num; }
	int GetPositionNum() { return PositionNum; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;
	bool IsOnGround;
	GameEngineCollision* Collision;

public:
	std::vector<float4> StartPos;
	int PositionNum;
};

