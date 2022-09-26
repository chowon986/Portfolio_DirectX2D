#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ShellWeDanceDustState
{
	None,
	Intro,
	Die,
};

class ShellWeDance;
class GameEngineTextureRenderer;
class ShellWeDanceDust : public GameEngineActor
{
public:
	ShellWeDanceDust();
	~ShellWeDanceDust();

	ShellWeDanceDust(const ShellWeDanceDust& _Other) = delete;
	ShellWeDanceDust(ShellWeDanceDust&& _Other) noexcept = delete;
	ShellWeDanceDust& operator=(const ShellWeDanceDust& _Other) = delete;
	ShellWeDanceDust& operator=(ShellWeDanceDust&& _Other) noexcept = delete;

public:
	void SetBoss(ShellWeDance* _Boss) { Boss = _Boss; }
	ShellWeDance* GetBoss() { return Boss; }
	void SetState(ShellWeDanceDustState _State) { CurState = _State; }
	ShellWeDanceDustState GetState() { return CurState; }

	GameEngineTextureRenderer* GetRenderer() {return Renderer;}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void OnShellWeDanceLandDustAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnShellWeDanceDeathDustAnimationFrameChanged(const FrameAnimation_DESC& _Info);

private:
	ShellWeDance* Boss;
	GameEngineTextureRenderer* Renderer;
	ShellWeDanceDustState CurState;
	ShellWeDanceDustState BeforeState;
};

