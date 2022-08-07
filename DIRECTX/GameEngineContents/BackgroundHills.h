#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class BackgroundHills : public GameEngineActor
{
public:
	// constrcuter destructer
	BackgroundHills();
	~BackgroundHills();

	// delete Function
	BackgroundHills(const BackgroundHills& _Other) = delete;
	BackgroundHills(BackgroundHills&& _Other) noexcept = delete;
	BackgroundHills& operator=(const BackgroundHills& _Other) = delete;
	BackgroundHills& operator=(BackgroundHills&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;


private:
	GameEngineTextureRenderer* Renderer;
};

