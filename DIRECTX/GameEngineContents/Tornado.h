#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class TornadoState
{
	Intro,
	Move
};

class GameEngineTextureRenderer;
class Tornado : public GameEngineActor
{
public:
	Tornado();
	~Tornado();

	Tornado(const Tornado& _Other) = delete;
	Tornado(Tornado&& _Other) noexcept = delete;
	Tornado& operator=(const Tornado& _Other) = delete;
	Tornado& operator=(Tornado&& _Other) noexcept = delete;

public:
	void SetCollision(GameEngineCollision* _Collision) { Collision = _Collision; }
	GameEngineCollision* GetCollision() { return Collision;}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void SetState(TornadoState _State) { CurState = _State; }
	TornadoState GetState() { return CurState; }

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* IntroRenderer;
	TornadoState CurState;
	GameEngineCollision* Collision;
};

