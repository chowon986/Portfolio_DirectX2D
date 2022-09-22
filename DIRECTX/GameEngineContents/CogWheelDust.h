#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class CogWheelDustState
{
	None,
	Intro,
};

class CogWheel;
class ShellWeDance;
class GameEngineTextureRenderer;
class CogWheelDust : public GameEngineActor
{
public:
	CogWheelDust();
	~CogWheelDust();

	CogWheelDust(const CogWheelDust& _Other) = delete;
	CogWheelDust(CogWheelDust&& _Other) noexcept = delete;
	CogWheelDust& operator=(const CogWheelDust& _Other) = delete;
	CogWheelDust& operator=(CogWheelDust&& _Other) noexcept = delete;

public:
	void SetBoss(CogWheel* _Boss) { Boss = _Boss; }
	CogWheel* GetBoss() { return Boss; }
	void SetState(CogWheelDustState _State) { CurState = _State; }
	CogWheelDustState GetState() { return CurState; }
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void OnCogWheelIntroDustAnimationFrameChanged(const FrameAnimation_DESC& _Info);

private:
	CogWheel* Boss;
	GameEngineTextureRenderer* Renderer;
	CogWheelDustState CurState;
	CogWheelDustState BeforeState;
	ShellWeDance* Ph3Boss;
};

