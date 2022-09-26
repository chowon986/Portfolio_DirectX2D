#include "PreCompile.h"
#include "ShellWeDanceDust.h"
#include "ShellWeDance.h"
#include "SaltBakerLevel.h"

ShellWeDanceDust::ShellWeDanceDust()
{
}

ShellWeDanceDust::~ShellWeDanceDust()
{
}

void ShellWeDanceDust::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ShellWeDanceLandDust", FrameAnimation_DESC("ShellWeDanceLandDust", 0.05f));
	Renderer->CreateFrameAnimationFolder("ShellWeDanceDeathDust", FrameAnimation_DESC("ShellWeDanceDeathDust", 0.05f));

	Renderer->AnimationBindFrame("ShellWeDanceLandDust", std::bind(&ShellWeDanceDust::OnShellWeDanceLandDustAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ShellWeDanceDeathDust", std::bind(&ShellWeDanceDust::OnShellWeDanceDeathDustAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetScaleModeImage();

	Renderer->ChangeFrameAnimation("ShellWeDanceLandDust");
	Renderer->Off();

	SetState(ShellWeDanceDustState::None);
}

void ShellWeDanceDust::Update(float _DeltaTime)
{
	if (nullptr != Boss)
	{
		if (Boss->GetHP() <= 0)
		{
			//	Death(); ph3 완성되면 주석 풀기
		}
	}

	if (CurState == ShellWeDanceDustState::None)
	{
		Renderer->Off();
	}

	if (CurState != BeforeState)
	{
		BeforeState = CurState;
		if (CurState == ShellWeDanceDustState::Intro)
		{
			Renderer->ChangeFrameAnimation("ShellWeDanceLandDust");
			if (nullptr != Boss)
			{
				float4 BossPos = Boss->GetTransform().GetWorldPosition();
				Renderer->GetTransform().SetWorldPosition({ BossPos.x + 200, BossPos.y - 15, BossPos.z - 0.5f });
			}
		}
		Renderer->On();
	}
}

void ShellWeDanceDust::End()
{
}

void ShellWeDanceDust::OnShellWeDanceLandDustAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 10)
	{
		SetState(ShellWeDanceDustState::None);
	}
}

void ShellWeDanceDust::OnShellWeDanceDeathDustAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 13)
	{
		Death();
		if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
		{
			Level->SetPhase(Phase::Phase4);
		}
	}
}