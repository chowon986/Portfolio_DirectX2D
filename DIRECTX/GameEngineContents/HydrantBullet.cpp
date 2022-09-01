#include "PreCompile.h"
#include "HydrantBullet.h"
#include "DogCopterPhase1.h"
#include "IInGameCharacterBase.h"

HydrantBullet::HydrantBullet()
	: Collision(nullptr)
	, Parent(nullptr)
{
}

HydrantBullet::~HydrantBullet()
{
}

void HydrantBullet::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("PeashotIntro", 0.1f, true));
	Renderer->ChangeFrameAnimation("PeashotIntro");
	Renderer->SetScaleModeImage();

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);
}

void HydrantBullet::Update(float _DeltaTime)
{
	if (nullptr != dynamic_cast<DogCopterPhase1*>(GetParent()))
	{
		if (Parent == nullptr)
		{
			Parent = dynamic_cast<DogCopterPhase1*>(GetParent());
		}
	}
	float4 PlayerPos = Parent->GetPlayer()->GetTransform().GetWorldPosition();
	//if (false == PlayerPos.CompareInt2D(float4::ZERO))
	//{
	//	DetachObject();
	//}
	float4 Pos = PlayerPos - GetTransform().GetWorldPosition();
	MovePosition.x = Pos.x > 0 ? float4::RIGHT.x : float4::LEFT.x;
	MovePosition.y = Pos.y > 0 ? float4::UP.y : float4::DOWN.y;
	GetTransform().SetWorldMove(MovePosition * _DeltaTime * 10);
}

void HydrantBullet::End()
{
}
