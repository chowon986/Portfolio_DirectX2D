#include "PreCompile.h"
#include "BreakObject.h"
#include "SaltBakerHeart.h"

BreakObject::BreakObject()
	: StartPos(float4::ZERO)
	, Renderer(nullptr)
	, AnimationName("")
	, IsOnGround(false)
	, CanMove(true)
{
}

BreakObject::~BreakObject()
{
}

void BreakObject::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Ph2DeribsA", FrameAnimation_DESC("Ph2DeribsA", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2DeribsB", FrameAnimation_DESC("Ph2DeribsB", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2DeribsC", FrameAnimation_DESC("Ph2DeribsC", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2DeribsD", FrameAnimation_DESC("Ph2DeribsD", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakMidLeftFall", FrameAnimation_DESC("Ph2BreakMidLeftFall", 0.07f, false));
	Renderer->CreateFrameAnimationFolder("Ph2BreakMidLeftFallLoop", FrameAnimation_DESC("Ph2BreakMidLeftFallLoop", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakMidRightFall", FrameAnimation_DESC("Ph2BreakMidRightFall", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakMidRightFallLoop", FrameAnimation_DESC("Ph2BreakMidRightFallLoop", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakLeft", FrameAnimation_DESC("Ph2BreakLeft", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakLeftLoop", FrameAnimation_DESC("Ph2BreakLeftLoop", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakRight", FrameAnimation_DESC("Ph2BreakRight", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakRightLoop", FrameAnimation_DESC("Ph2BreakRightLoop", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakFrontFallLeft", FrameAnimation_DESC("Ph2BreakFrontFallLeft", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("Ph2BreakFrontFallLeftLoop", FrameAnimation_DESC("Ph2BreakFrontFallLeftLoop", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("LittleTornadoA", FrameAnimation_DESC("LittleTornadoA", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("LittleTornadoALoop", FrameAnimation_DESC("LittleTornadoALoop", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("LittleTornadoB", FrameAnimation_DESC("LittleTornadoB", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("LittleTornadoBLoop", FrameAnimation_DESC("LittleTornadoBLoop", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("SaltManIntro", FrameAnimation_DESC("SaltManIntro", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("SaltManIntroLoop", FrameAnimation_DESC("SaltManIntroLoop", 0.07f, true));

	Renderer->AnimationBindFrame("Ph2DeribsA", std::bind(&BreakObject::OnGround, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2DeribsB", std::bind(&BreakObject::OnGround, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2DeribsC", std::bind(&BreakObject::OnGround, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2DeribsD", std::bind(&BreakObject::OnGround, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2BreakMidLeftFall", std::bind(&BreakObject::OnBreakObjectsAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2BreakMidRightFall", std::bind(&BreakObject::OnBreakObjectsAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2BreakLeft", std::bind(&BreakObject::OnBreakObjectsAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2BreakRight", std::bind(&BreakObject::OnBreakObjectsAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("Ph2BreakFrontFallLeft", std::bind(&BreakObject::OnBreakObjectsAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("LittleTornadoA", std::bind(&BreakObject::OnBreakObjectsAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("LittleTornadoB", std::bind(&BreakObject::OnBreakObjectsAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltManIntro", std::bind(&BreakObject::OnSaltManIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltManIntroLoop", std::bind(&BreakObject::OnSaltManIntroAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetScaleModeImage();
}

void BreakObject::Update(float _DeltaTime)
{
	if (AnimationName == "Ph2DeribsA")
	{
		Renderer->SetPivot(PIVOTMODE::RIGHTBOT);
	}
	if (AnimationName == "Ph2DeribsB" || AnimationName == "Ph2DeribsC" || AnimationName == "Ph2DeribsD")
	{
		Renderer->SetPivot(PIVOTMODE::BOT);
	}

	if (AnimationName == "Ph2BreakMidLeftFall" || AnimationName == "Ph2BreakMidRightFall" || AnimationName == "Ph2BreakLeft"
		|| AnimationName == "Ph2BreakRight" || AnimationName == "Ph2BreakFrontFallLeft")
	{
		Renderer->SetPivot(PIVOTMODE::TOP);
		IsOnGround = false;
		CanMove = false;
	}

	if  (AnimationName == "LittleTornadoA" || AnimationName == "LittleTornadoB" || AnimationName == "SaltManIntro")
	{
		Renderer->SetPivot(PIVOTMODE::BOT);
		IsOnGround = false;
		CanMove = false;
	}

	if (false == IsOnGround && true == CanMove)
	{
		GetTransform().SetWorldMove(float4::DOWN * _DeltaTime * 500);
	}

	if (GetTransform().GetWorldPosition().y < -650 && CanMove == true)
	{
		IsOnGround = true;
		if (true == Renderer->IsCurAnimationPause())
		{
			Renderer->CurAnimationPauseOff();
		}
	}
}

void BreakObject::End()
{
}

void BreakObject::OnBreakObjectsAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (AnimationName == "Ph2BreakMidLeftFall")
	{
		if (_Info.CurFrame == 9)
		{
			Renderer->ChangeFrameAnimation(AnimationName + "Loop");

		}
	}

	if (AnimationName == "Ph2BreakMidRightFall")
	{
		if (_Info.CurFrame == 9)
		{
			Renderer->ChangeFrameAnimation(AnimationName + "Loop");

		}
	}

	if (AnimationName == "Ph2BreakLeft")
	{
		if (_Info.CurFrame == 12)
		{
			Renderer->ChangeFrameAnimation(AnimationName + "Loop");

		}
	}

	if (AnimationName == "Ph2BreakRight")
	{
		if (_Info.CurFrame == 13)
		{
			Renderer->ChangeFrameAnimation(AnimationName + "Loop");

		}
	}

	if (AnimationName == "Ph2BreakFrontFallLeft")
	{
		if (_Info.CurFrame == 30)
		{
			Renderer->ChangeFrameAnimation(AnimationName + "Loop");

		}
	}

	if (AnimationName == "LittleTornadoA" || AnimationName == "LittleTornadoB")
	{
		if (_Info.CurFrame == 9)
		{
			Renderer->ChangeFrameAnimation(AnimationName + "Loop");

		}
	}
}

void BreakObject::OnSaltManIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 40)
	{
		SaltBakerHeart* Ph4Boss = GetLevel()->CreateActor<SaltBakerHeart>();
		Ph4Boss->GetTransform().SetWorldPosition({ 640.0f,-400.0f });
	}

	if (_Info.CurFrame == 52)
	{
		Renderer->ChangeFrameAnimation("SaltManIntroLoop");
	}
}

void BreakObject::OnGround(const FrameAnimation_DESC& _Info)
{
	if (AnimationName == "Ph2DeribsA")
	{
		if (_Info.CurFrame == 2)
		{
			if (true != IsOnGround)
			{
				Renderer->CurAnimationPauseOn();
			}

		}
		if (_Info.CurFrame == 16)
		{
			// 아래는 테스트용 코드
			GetTransform().SetWorldPosition({ StartPos });
			IsOnGround = false;
		}
	}

	if (AnimationName == "Ph2DeribsB")
	{
		if (_Info.CurFrame == 3)
		{
			if (true != IsOnGround)
			{
				Renderer->CurAnimationPauseOn();
			}

		}
		if (_Info.CurFrame == 15)
		{
			// 아래는 테스트용 코드
			GetTransform().SetWorldPosition({ StartPos });
			IsOnGround = false;
		}
	}

	if (AnimationName == "Ph2DeribsC")
	{
		if (_Info.CurFrame == 5)
		{
			if (true != IsOnGround)
			{
				Renderer->CurAnimationPauseOn();
			}

		}
		if (_Info.CurFrame == 17)
		{
			// 아래는 테스트용 코드
			GetTransform().SetWorldPosition({ StartPos });
			IsOnGround = false;
		}
	}

	if (AnimationName == "Ph2DeribsD")
	{
		if (_Info.CurFrame == 4)
		{
			if (true != IsOnGround)
			{
				Renderer->CurAnimationPauseOn();
			}

		}
		if (_Info.CurFrame == 20)
		{
			// 아래는 테스트용 코드
			GetTransform().SetWorldPosition({ StartPos });
			IsOnGround = false;
		}
	}
}
