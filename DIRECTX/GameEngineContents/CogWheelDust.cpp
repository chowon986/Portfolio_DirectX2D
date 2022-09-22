#include "PreCompile.h"
#include "CogWheelDust.h"
#include "CogWheel.h"
#include "ShellWeDance.h"

CogWheelDust::CogWheelDust()
	: Boss(nullptr)
	, Renderer(nullptr)
	, CurState(CogWheelDustState::None)
	, BeforeState(CogWheelDustState::None)
{
}

CogWheelDust::~CogWheelDust()
{
}

void CogWheelDust::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("CogWheelIntroDust", FrameAnimation_DESC("CogWheelIntroDust", 0.05f, true));

	Renderer->AnimationBindFrame("CogWheelIntroDust", std::bind(&CogWheelDust::OnCogWheelIntroDustAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetScaleModeImage();

	Renderer->ChangeFrameAnimation("CogWheelIntroDust");
}

void CogWheelDust::Update(float _DeltaTime)
{
	if (CurState != BeforeState)
	{
		BeforeState = CurState;
		if (CurState == CogWheelDustState::None)
		{
			Renderer->Off();
		}
		else
		{
			if (CurState == CogWheelDustState::Intro)
			{
				Renderer->ChangeFrameAnimation("CogWheelIntroDust");
				if (nullptr != Boss)
				{
					float4 BossPos = Boss->GetTransform().GetWorldPosition();
					Renderer->GetTransform().SetWorldPosition({ BossPos.x, BossPos.y + 15, BossPos.z-1});
				}
			}
			Renderer->On();
		}
	}
}

void CogWheelDust::End()
{
}

void CogWheelDust::OnCogWheelIntroDustAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 7)
	{
		SetState(CogWheelDustState::None);
		GetLevel()->CreateActor<ShellWeDance>();
	}
}
