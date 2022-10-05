#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Ph2DogZetPuff;
class GameEngineTextureRenderer;
class Ph2Dog;
class Ph2DogZetPuff : public GameEngineActor
{
public:
	Ph2DogZetPuff();
	~Ph2DogZetPuff();

	Ph2DogZetPuff(const Ph2DogZetPuff& _Other) = delete;
	Ph2DogZetPuff(Ph2DogZetPuff&& _Other) noexcept = delete;
	Ph2DogZetPuff& operator=(const Ph2DogZetPuff& _Other) = delete;
	Ph2DogZetPuff& operator=(Ph2DogZetPuff&& _Other) noexcept = delete;

public:
	void SetBoss(Ph2Dog* _Boss) { Boss = _Boss; }
	Ph2Dog* GetBoss() { return Boss; }

	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

private:
	void OnZetPuffAnimationFrameFinished(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	Ph2Dog* Boss;
	GameEngineTextureRenderer* Renderer;
};

