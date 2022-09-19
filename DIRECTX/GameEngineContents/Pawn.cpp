#include "PreCompile.h"
#include "Pawn.h"
#include "PawnPhysicsComponent.h"
#include "IInGameCharacterBase.h"
#include "InGameCuphead.h"
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
	, RollCount(0)
{
}

Pawn::~Pawn()
{
}

void Pawn::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PawnIntro", FrameAnimation_DESC("PawnPrepare", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnPrepareToIntro", FrameAnimation_DESC("PawnPrepareToIntro", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnIntroAStart", FrameAnimation_DESC("PawnIntroAStart", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnIntroBStart", FrameAnimation_DESC("PawnIntroBStart", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnIdleAStart", FrameAnimation_DESC("PawnIdleAStart", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnIdleBStart", FrameAnimation_DESC("PawnIdleBStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("PawnJump", FrameAnimation_DESC("PawnJump", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnFall", FrameAnimation_DESC("PawnFall", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnLand", FrameAnimation_DESC("PawnLand", 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("PawnRun", FrameAnimation_DESC("PawnRun", 0.1f, true));
	Renderer->ChangeFrameAnimation("PawnIntro");

	//Renderer->AnimationBindFrame("PawnIntro", std::bind(&Pawn::PawnPrepareAnimationFrameChanged, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("PawnPrepareToIntro", std::bind(&Pawn::PawnPrepareToIntroAnimationFrameChanged, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("PawnIntroAStart", std::bind(&Pawn::PawnIntroAnimationFrameChanged, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("PawnIntroBStart", std::bind(&Pawn::PawnIntroAnimationFrameChanged, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("PawnIdleAStart", std::bind(&Pawn::PawnIdleAnimationFrameChanged, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("PawnIdleBStart", std::bind(&Pawn::PawnIdleAnimationFrameChanged, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("PawnJump", std::bind(&Pawn::PawnJumpAnimationFrameChanged, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("PawnLand", std::bind(&Pawn::PawnLandAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetScaleModeImage();
	Renderer->SetPivot(PIVOTMODE::BOT);

	Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Pawn");

	SetPawnPhysicsComponent(CreateComponent<PawnPhysicsComponent>());

	Collision = CreateComponent<GameEngineCollision>();
	Collision->ChangeOrder((int)ObjectOrder::PARRIABLEOBJECT);
	Collision->GetTransform().SetLocalScale({ 40.0f,60.0f,1.0f });

	//GameEngineCollision* PosIndexCollision = CreateComponent<GameEngineCollision>();
	//PosIndexCollision->ChangeOrder((int)ObjectOrder::POSINDEX);
	//PosIndexCollision->GetTransform().SetLocalScale({ 50.0f,100.0f,1.0f });
	//PosIndexCollision->GetTransform().SetLocalPosition({ 0.0f,300.0f,1.0f });

	srand(static_cast<unsigned int>(time(NULL)));

	SetRenderer(Renderer);

	SetState(InGameMonsterState::Prepare);

	PawnPosX = { 150.0f, 290.0f, 430.0f, 570.0f, 710.0f, 850.0f, 990.0f, 1130.0f };
}

void Pawn::SetPawnPhysicsComponent(PawnPhysicsComponent* _Physics)
{
	Physics = _Physics;
}

void Pawn::CheckJumpDirection()
{
	int RandomDiretionNum = (rand() % 2) + 1;
	Direction.x = RandomDiretionNum == 1 ? 1.0f : -1.0f;
}

CollisionReturn Pawn::OnReturnCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	RandomPosIndex = rand() % 8; // 한 위치를 랜덤으로 정한다.
	GetTransform().SetWorldPosition({ PawnPosX[RandomPosIndex] , 50.0f }); // 그 위치로 이동시킨다.
	// 해당 위치에 콜리전이 없으면 다시 위치를 구한다.
	while (false == Collision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::POSINDEX, CollisionType::CT_AABB2D, std::bind(&Pawn::OnPawnCollision, this, std::placeholders::_1, std::placeholders::_2)))
	{
		RandomPosIndex = rand() % 8;
		GetTransform().SetWorldPosition({ PawnPosX[RandomPosIndex] , 50.0f }); // 새로 구한 위치로 이동시킨다.
	}

	Prepare();

	return CollisionReturn::ContinueCheck;
}

CollisionReturn Pawn::OnPawnCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionReturn::ContinueCheck;
}

void Pawn::CheckMoveDirection()
{
	if (GetPlayer() != nullptr)
	{
		float4 PlayerPos = GetPlayer()->GetTransform().GetWorldPosition();
		float4 MyPos = GetTransform().GetWorldPosition();
		Direction.x = PlayerPos.ix() - MyPos.ix() > 0 ? 1.0f : -1.0f;
	}
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
		Run();
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
	if (ColMapRenderer == nullptr)
	{
		ColMapRenderer = GetLevel()->GetMainColMapImage();
	}

	if (ColMapTexture == nullptr)
	{
		ColMapTexture = ColMapRenderer->GetCurTexture();
	}

	if (GetState() == InGameMonsterState::Prepare)
	{
		ElapsedTime += _DeltaTime;
		if (ElapsedTime > GetAttackIntervalTime())
		{
			Jump();
			ElapsedTime = 0.0f;
		}
	}

	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::RETURN, CollisionType::CT_AABB2D, std::bind(&Pawn::OnReturnCollision, this, std::placeholders::_1, std::placeholders::_2));

	if (GetState() != InGameMonsterState::Prepare)
	{
		GetTransform().SetWorldMove(Direction * 300 * _DeltaTime);
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
	CheckJumpDirection();
}

void Pawn::Run()
{
	SetState(InGameMonsterState::Run);
	CheckMoveDirection();
}
