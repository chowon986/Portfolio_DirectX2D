#include "PreCompile.h"
#include "Pawn.h"
#include "PawnPhysicsComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

Pawn::Pawn()
	:State(InGameMonsterState::Prepare)
	, OnceCheck(false)
	, ColMapRenderer(nullptr)
	, ColMapTexture(nullptr)
	, IntroName("")
	, AttackIntervalTime(10.0f)
	, LandOnceCheck(false)
	, IsOnGround(false)
{
}

Pawn::~Pawn()
{
}

void Pawn::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PawnIntro", FrameAnimation_DESC("PawnPrepare", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnPrepareToIntro", FrameAnimation_DESC("PawnPrepareToIntro", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnIntroAStart", FrameAnimation_DESC("PawnIntroAStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnIntroBStart", FrameAnimation_DESC("PawnIntroBStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnIdleAStart", FrameAnimation_DESC("PawnIdleAStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnIdleBStart", FrameAnimation_DESC("PawnIdleBStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnJump", FrameAnimation_DESC("PawnJump", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnFall", FrameAnimation_DESC("PawnFall", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnLand", FrameAnimation_DESC("PawnLand", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnRun", FrameAnimation_DESC("PawnRun", 0.1f, true));
	Renderer->ChangeFrameAnimation("PawnIntro");

	Renderer->AnimationBindFrame("PawnIntro", std::bind(&Pawn::PawnPrepareAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PawnPrepareToIntro", std::bind(&Pawn::PawnPrepareToIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PawnIntroAStart", std::bind(&Pawn::PawnIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PawnIntroBStart", std::bind(&Pawn::PawnIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PawnIdleAStart", std::bind(&Pawn::PawnIdleAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PawnIdleBStart", std::bind(&Pawn::PawnIdleAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PawnJump", std::bind(&Pawn::PawnJumpAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PawnLand", std::bind(&Pawn::PawnLandAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetScaleModeImage();
	Renderer->SetPivot(PIVOTMODE::BOT);

	Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Pawn");

	SetPawnPhysicsComponent(CreateComponent<PawnPhysicsComponent>());

	Collision = CreateComponent<GameEngineCollision>();
	Collision->ChangeOrder((int)ObjectOrder::PARRIABLEOBJECT);
	Collision->GetTransform().SetLocalScale({ 40.0f,60.0f,1.0f });

	srand(time(NULL));

	SetRenderer(Renderer);

	SetState(InGameMonsterState::Prepare);
}

void Pawn::SetPawnPhysicsComponent(PawnPhysicsComponent* _Physics)
{
	Physics = _Physics;
}

void Pawn::PawnPrepareAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("PawnPrepareToIntro");
}

void Pawn::PawnPrepareToIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 12)
	{
		Renderer->ChangeFrameAnimation("PawnIntro" + IntroName);
	}
}

void Pawn::PawnIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 32)
	{
		Renderer->ChangeFrameAnimation("PawnIdle" + IntroName);
	}
}

void Pawn::PawnJumpAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 13)
	{
		Renderer->ChangeFrameAnimation("PawnFall");
	}
}

void Pawn::PawnLandAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 4)
	{
		Renderer->ChangeFrameAnimation("PawnRun");
	}
}

void Pawn::PawnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 12)
	{
		Jump();
	}
}

void Pawn::PawnPrepareAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("PawnPrepareToIntro");
}

void Pawn::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;

	if (ColMapRenderer == nullptr)
	{
		ColMapRenderer = GetLevel()->GetMainColMapImage();
	}

	if (ColMapTexture == nullptr)
	{
		ColMapTexture = ColMapRenderer->GetCurTexture();
	}

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 15)).CompareInt4D(float4::RED) &&
		false == OnceCheck)
	{
		Direciton = float4::ZERO;
		OnceCheck = true;
		LandOnceCheck = false;
	}

	if (GetState() != InGameMonsterState::Prepare)
	{
		GetTransform().SetWorldMove(Direciton * 200 * _DeltaTime);
	}
}

void Pawn::TakeDamage()
{
}

void Pawn::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Pawn::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void Pawn::Shoot()
{
	SetState(InGameMonsterState::Attack1);
}

void Pawn::Die()
{
	SetState(InGameMonsterState::Die);
}

void Pawn::Jump()
{
	SetState(InGameMonsterState::Jump);
	GetPawnPhysicsComponent()->Reset();
	GetPawnPhysicsComponent()->AddForce(40);
}