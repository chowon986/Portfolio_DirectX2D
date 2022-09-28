#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class BreakObject : public GameEngineActor
{
public:
	// constrcuter destructer
	BreakObject();
	~BreakObject();

	// delete Function
	BreakObject(const BreakObject& _Other) = delete;
	BreakObject(BreakObject&& _Other) noexcept = delete;
	BreakObject& operator=(const BreakObject& _Other) = delete;
	BreakObject& operator=(BreakObject&& _Other) noexcept = delete;

public:
	void SetAnimationName(std::string _Name) { AnimationName = _Name; }
	void SetStartPos(float4 _Pos) { StartPos = _Pos; }
	float4 GetStartPos() { return StartPos; }
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void OnGround(const FrameAnimation_DESC& _Info);
	void OnBreakObjectsAnimationFrameChanged(const FrameAnimation_DESC& _Info);

private:
	float4 StartPos;
	GameEngineTextureRenderer* Renderer;
	std::string AnimationName;
	bool IsOnGround;
	bool CanMove;
};

