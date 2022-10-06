#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class PigState
{
	Idle,
	Welcome,
	Goodbye,
};

class GameEngineTextureRenderer;
class Pig : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	Pig();
	~Pig();

	// delete Function
	Pig(const Pig& _Other) = delete;
	Pig(Pig&& _Other) noexcept = delete;
	Pig& operator=(const Pig& _Other) = delete;
	Pig& operator=(Pig&& _Other) noexcept = delete;

public:
	void SetState(PigState _State);
	PigState GetState();
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

protected:
	void Start() override;
	void LevelEndEvent() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;

private:
	void OnByeAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnWelcomeAnimationFrameChanged(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	PigState State;
	std::string Dir;
};
