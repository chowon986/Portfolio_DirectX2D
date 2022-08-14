#include "PreCompile.h"
#include "Canteen.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "IInGameCharacterBase.h"
#include "BowWowShooter.h"

Canteen::Canteen()
	: Renderer(nullptr)
	, AttackState(InGameMonsterAttackState::None)
	, Animation(nullptr)
	, Collision(nullptr)
	, RotationAngle(0.0f)
{
}

Canteen::~Canteen()
{
}

void Canteen::Start()
{
	// 애니메이션 생성
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenIntro", FrameAnimation_DESC("CanteenIntro", 0.1f)); // Prepare
		Renderer->CreateFrameAnimationFolder("CanteenIdle", FrameAnimation_DESC("CanteenIdle", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenBlink", FrameAnimation_DESC("CanteenBlink", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenCheer", FrameAnimation_DESC("CanteenCheer", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookAround", FrameAnimation_DESC("CanteenLookAround", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookDown", FrameAnimation_DESC("CanteenLookDown", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookDownLeft", FrameAnimation_DESC("CanteenLookDownLeft", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookDownRight", FrameAnimation_DESC("CanteenLookDownRight", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookUp", FrameAnimation_DESC("CanteenLookUp", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookUpLeft", FrameAnimation_DESC("CanteenLookUpLeft", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookUpLeftArchUp", FrameAnimation_DESC("CanteenLookUpLeftArchUp", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookUpRight", FrameAnimation_DESC("CanteenLookUpRight", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenLookUpRightArchUp", FrameAnimation_DESC("CanteenLookUpRightArchUp", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenPlane", FrameAnimation_DESC("CanteenPlane", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenTakeDamage", FrameAnimation_DESC("CanteenTakeDamage", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenWin", FrameAnimation_DESC("CanteenWin", 0.1f)); // Idle

		Renderer->ChangeFrameAnimation("CanteenIntro");

		//Renderer->SetPivot(PIVOTMODE::BOT);

		//Renderer->GetTransform().SetLocalPosition({ 300, 0, (int)ZOrder::NPC });

		//SetRenderer(Renderer);
	}


	// 컴포넌트 생성
	{
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("Canteen");
	}


	// 총 생성
	{
		BowWowShooter* BowWowGun = GetLevel()->CreateActor<BowWowShooter>();
		BowWowGun->SetParent(this);
	}

	srand(time(NULL));
	SetHP(5);
	SetState(InGameMonsterState::Idle);
	SetAttackState(InGameMonsterAttackState::None);
}

void Canteen::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void Canteen::TakeDamage()
{
}

void Canteen::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Canteen::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void Canteen::Shoot()
{
	float4 PlayerPos = Player->GetTransform().GetLocalPosition();
	if (GetTransform().GetLocalPosition().x > PlayerPos.x) // 몬스터가 플레이어보다 오른쪽
	{
		if (GetTransform().GetLocalPosition().y > PlayerPos.y) // 몬스터가 플레이어보다 위쪽
		{
			SetBowWowDirection(float4::LEFT + float4::DOWN);
		}
		else
		{
			SetBowWowDirection(float4::LEFT + float4::UP);
		}
	}

	else // 몬스터가 플레이어보다 왼쪽
	{
		if (GetTransform().GetLocalPosition().y > PlayerPos.y) // 몬스터가 플레이어보다 위쪽
		{
			SetBowWowDirection(float4::RIGHT + float4::DOWN);
		}
		else
		{
			SetBowWowDirection(float4::RIGHT + float4::UP);
		}
	}
	SetState(InGameMonsterState::Attack5);
}

void Canteen::Die()
{
	SetState(InGameMonsterState::Die);
}



void Canteen::OnEnterAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	//if (_Info.CurFrame == 1)
	//{
	//	StartPos = GetTransform().GetLocalPosition();
	//	EndPos = float4(640, 360); // 고민 해 보기
	//	MoveSpeed = 100.0f;
	//	MoveToEndPos(StartPos, EndPos);
	//}
}

void Canteen::OnPreapareAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	//if (_Info.CurFrame == 1)
	//{
	//	StartPos = float4(640, 360);  // 고민 해 보기
	//	EndPos = GetTransform().GetLocalPosition();
	//	MoveSpeed = 100.0f;
	//	MoveToEndPos(StartPos, EndPos);
	//}
}

void Canteen::OnAttackAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 2)
	{
		SetAttackState(InGameMonsterAttackState::BowWow);
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Canteen::OnEnterAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Prepare();
}

void Canteen::OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}

void Canteen::OnIdleAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Shoot();
}

void Canteen::OnAttackAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}


