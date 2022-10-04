#include "PreCompile.h"
#include "NewsCat.h"

NewsCat::NewsCat()
	: Collision(nullptr)
	, Renderer(nullptr)
	, State(NewsCatState::Idle)
	, BeforeState(NewsCatState::Idle)
	, CurAnimationNum(0)
	, OnceCheck(false)
	, BackgroundRenderer(nullptr)
	, ElapsedTime(0.0f)
{
}

NewsCat::~NewsCat()
{
}

void NewsCat::SetState(NewsCatState _State)
{
}

NewsCatState NewsCat::GetState()
{
	return NewsCatState();
}

void NewsCat::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Newscat", FrameAnimation_DESC("NPCNewscat", 0.1f));
	Renderer->ChangeFrameAnimation("Newscat");
	Renderer->GetTransform().SetLocalScale({ 110, 113, 100 });
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f,1.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, 0.0f, (int)ZOrder::Foreground });
	Collision->ChangeOrder(ObjectOrder::NPC);

	TalkBubbleRenderer = CreateComponent<GameEngineTextureRenderer>();
	TalkBubbleRenderer->SetTexture("SpeechBubble0.png");
	TalkBubbleRenderer->ScaleToTexture();
	TalkBubbleRenderer->GetTransform().SetLocalPosition({ -310.0f, 300.0f, -1000.0f});
	TalkBubbleRenderer->Off();

	BackgroundRenderer = CreateComponent<GameEngineTextureRenderer>();
	BackgroundRenderer->SetTexture("GetCoin.png");
	BackgroundRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
	BackgroundRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -1100.0f });
	BackgroundRenderer->Off();

	{
		GameEngineTextureRenderer* CoinRenderer = CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->CreateFrameAnimationFolder("EventCoin", FrameAnimation_DESC("EventCoin", 0.1f));
		CoinRenderer->ChangeFrameAnimation("EventCoin");
		CoinRenderer->SetScaleModeImage();
		CoinRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, GetTransform().GetWorldPosition().z });
		CoinRenderer->Off();

		CoinRenderers.push_back(CoinRenderer);
	}

	{
		GameEngineTextureRenderer* CoinRenderer = CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->CreateFrameAnimationFolder("EventCoin", FrameAnimation_DESC("EventCoin", 0.1f));
		CoinRenderer->ChangeFrameAnimation("EventCoin");
		CoinRenderer->SetScaleModeImage();
		CoinRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -2000.0f });
		CoinRenderer->Off();

		CoinRenderers.push_back(CoinRenderer);
	}

	{
		GameEngineTextureRenderer* CoinRenderer = CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->CreateFrameAnimationFolder("EventCoin", FrameAnimation_DESC("EventCoin", 0.1f));
		CoinRenderer->ChangeFrameAnimation("EventCoin");
		CoinRenderer->SetScaleModeImage();
		CoinRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -2000.0f });
		CoinRenderer->Off();

		CoinRenderers.push_back(CoinRenderer);
	}
}

void NewsCat::Update(float _DeltaTime)
{
	Collision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&NewsCat::OnPortalCollision, this, std::placeholders::_1, std::placeholders::_2));

	if (BeforeState != State)
	{
		BeforeState = State;

		if (BeforeState == NewsCatState::Talk)
		{
			TalkBubbleRenderer->On();
			CurAnimationNum = 0;
			TalkBubbleRenderer->SetTexture("SpeechBubble" + std::to_string(CurAnimationNum) + ".png");
		}
	}

	if (State == NewsCatState::Talk)
	{
		ElapsedTime += _DeltaTime;
		if (true == GameEngineInput::GetInst()->IsDown("Select") && ElapsedTime > 0.05)
		{
			ElapsedTime = 0.0f;
			++CurAnimationNum;
			if (OnceCheck == false)
			{
				if (CurAnimationNum >= 5)
				{
					GiveCoin();
					OnceCheck = true;
				}
				else
				{
					TalkBubbleRenderer->SetTexture("SpeechBubble" + std::to_string(CurAnimationNum) + ".png");
				}
			}
		}
	}
}

void NewsCat::Talk()
{
}

void NewsCat::Idle()
{
}

CollisionReturn NewsCat::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
	{
		State = NewsCatState::Talk;
		_This->Off();
	}
	return CollisionReturn::Break;
}

void NewsCat::GiveCoin()
{
	BackgroundRenderer->On();
	for (int i = 0; i < 3; i++)
	{
		CoinRenderers[i]->On();
	}
}
