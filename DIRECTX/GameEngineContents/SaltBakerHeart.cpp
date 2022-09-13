#include "PreCompile.h"
#include "SaltBakerHeart.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "SaltBakerHeartPhysicsComponent.h"

SaltBakerHeart::SaltBakerHeart()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
{
}

SaltBakerHeart::~SaltBakerHeart()
{
}

void SaltBakerHeart::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Bow1", FrameAnimation_DESC("Bow1", 0.1f));
	Renderer->CreateFrameAnimationFolder("Bow2", FrameAnimation_DESC("Bow2", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("Wow1", FrameAnimation_DESC("Wow1", 0.1f));
	Renderer->CreateFrameAnimationFolder("Wow2", FrameAnimation_DESC("Wow2", 0.1f)); // Pink
	Renderer->ChangeFrameAnimation("Bow1");
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 60.0f, 60.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

	//SetPhysicsComponent(CreateComponent<SaltBakerHeartPhysicsComponent>());

	StartPosX.insert(std::make_pair<int, float>(0, 400.0f));
	DestPosX.insert(std::make_pair<int, float>(0, 700.0f));

	SetUpDownDirection(float4::DOWN);
}

void SaltBakerHeart::Update(float _DeltaTime)
{
	GameEngineTextureRenderer* CollisionMap = GetLevel()->GetMainColMapImage();
	if (CollisionMap == nullptr)
	{
		return;
	}

	GameEngineTexture* ColMapTexture = CollisionMap->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}

	ElapsedTime += _DeltaTime;
	LerpTime = ElapsedTime / 1.0f;
	float4 CurPos = GetTransform().GetWorldPosition();

	if (IsHeartPosRightEnd == false)
	{
		if (DestPosX[0] == CurPos.x)
		{
			IsHeartPosRightEnd = true;
			ElapsedTime = 0.0f;
			return;
		}

		LerpPos = float4::LerpLimit(StartPosX[0], DestPosX[0], LerpTime);
	}
	else
	{
		if (StartPosX[0] == CurPos.x)
		{
			IsHeartPosRightEnd = false;
			ElapsedTime = 0.0f;
			return;
		}
		LerpPos = float4::LerpLimit(DestPosX[0], StartPosX[0], LerpTime);
	}

	GetTransform().SetLocalPosition({ LerpPos.x, CurPos.y, (int)ZOrder::Background - 2 });

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 15)).CompareInt4D(float4::BLACK))
	{
		SetUpDownDirection(float4::UP);
	}
	else if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 15)).CompareInt4D(float4::BLACK))
	{
		SetUpDownDirection(float4::DOWN);
	}
	GetTransform().SetLocalMove(GetUpDownDirection() * _DeltaTime * 200);

}

void SaltBakerHeart::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void SaltBakerHeart::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void SaltBakerHeart::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void SaltBakerHeart::Shoot()
{
	//SetState(InGameMonsterState::Attack5);
	//SetAttackState(InGameMonsterAttackState::Attack5);
	SetState(InGameMonsterState::Attack1);
	SetAttackState(InGameMonsterAttackState::Attack1);
}

void SaltBakerHeart::Die()
{
	SetState(InGameMonsterState::Die);
}

void SaltBakerHeart::Test(const FrameAnimation_DESC& _Info)
{
}
