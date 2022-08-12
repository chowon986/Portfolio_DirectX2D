#include "PreCompile.h"
#include "InGameMovementComponent.h"
#include "Bulldog.h"
#include "BulldogPlane.h"

InGameMovementComponent::InGameMovementComponent()
	//:Speed(100.0f)
	//, Direction(float4::ZERO)
	//, ImageDir(float4::ZERO)
{
}

InGameMovementComponent::~InGameMovementComponent()
{
}

//
//void InGameMovementComponent::OnStateChanged(InGameMonsterState _State)
//{
//	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
//	if (InGameMonster == nullptr)
//	{
//		return;
//	}
//
//	State = _State;
//
//	switch (_State)
//	{
//	case InGameMonsterState::Unmount:
//	{
//		if (nullptr != GetParent<Bulldog>())
//		{
//			Bulldog* BulldogMonster = GetParent<Bulldog>();
//
//			if (nullptr != GetParent<BulldogPlane>())
//			{
//				BulldogPlane* Plane = GetParent<BulldogPlane>();
//
//				//Move(BulldogMonster->GetTransform().GetWorldPosition(), { BulldogMonster->GetTransform().GetWorldPosition().x, BulldogMonster->GetTransform().GetWorldPosition().y + 300 });
//				Move(Plane->GetTransform().GetWorldPosition(), { Plane->GetTransform().GetWorldPosition().x, Plane->GetTransform().GetWorldPosition().y + 300 });
//				SetSpeed(100.0f);
//			}
//		}
//		break;
//	}
//
//	case InGameMonsterState::Mount:
//	{
//		if (nullptr != GetParent<Bulldog>())
//		{
//			Bulldog* BulldogMonster = GetParent<Bulldog>();
//
//			if (nullptr != BulldogMonster->GetParent<BulldogPlane>())
//			{
//				BulldogPlane* Plane = BulldogMonster->GetParent<BulldogPlane>();
//				Direction = float4::DOWN;
//				
//				//Move(BulldogMonster->GetTransform().GetWorldPosition(), { BulldogMonster->GetTransform().GetWorldPosition().x, BulldogMonster->GetTransform().GetWorldPosition().y - 300 });
//				//Plane->GetTransform().SetWorldMove({ Plane->GetTransform().GetLocalPosition().x, Plane->GetTransform().GetLocalPosition().y - 300 });
//				//Move(Plane->GetTransform().GetLocalPosition(), { Plane->GetTransform().GetLocalPosition().x, Plane->GetTransform().GetLocalPosition().y - 300 });
//				SetSpeed(100.0f);
//			}
//		}
//		break;
//	}
//
//	case InGameMonsterState::PrepareAttack1:
//	{
//		if (nullptr != GetParent<Bulldog>())
//		{
//			Bulldog* BulldogMonster = GetParent<Bulldog>();
//				ImageDir = BulldogMonster->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? BulldogMonster->GetTransform().GetWorldPosition().x + 150 : BulldogMonster->GetTransform().GetWorldPosition().x - 150;
//				Move(BulldogMonster->GetTransform().GetWorldPosition(), { ImageDir.x, BulldogMonster->GetTransform().GetWorldPosition().y });
//				SetSpeed(100.0f);
//		}
//		break;
//	}
//
//	case InGameMonsterState::PrepareAttack2:
//	{
//		if (nullptr != GetParent<Bulldog>())
//		{
//			Bulldog* BulldogMonster = GetParent<Bulldog>();
//				Move(BulldogMonster->GetTransform().GetWorldPosition(), { BulldogMonster->GetTransform().GetWorldPosition().x, BulldogMonster->GetTransform().GetWorldPosition().y - 450 });
//				SetSpeed(110.0f);
//		}
//		break;
//	}
//
//	case InGameMonsterState::Attack2:
//	{
//		if (nullptr != GetParent<Bulldog>())
//		{
//			Bulldog* BulldogMonster = GetParent<Bulldog>();
//				Move(BulldogMonster->GetTransform().GetWorldPosition(), { BulldogMonster->GetTransform().GetWorldPosition().x, BulldogMonster->GetTransform().GetWorldPosition().y - 300 });
//				SetSpeed(150.0f);
//		}
//		break;
//	}
//
//	case InGameMonsterState::AttackFinish2:
//	{
//		if (nullptr != GetParent<Bulldog>())
//		{
//			Bulldog* BulldogMonster = GetParent<Bulldog>();
//				Move(BulldogMonster->GetTransform().GetWorldPosition(), { BulldogMonster->GetTransform().GetWorldPosition().x, BulldogMonster->GetTransform().GetWorldPosition().y + 100 });
//				SetSpeed(100.0f);
//		}
//		break;
//	}
//	}
//}



void InGameMovementComponent::Start()
{
}

void InGameMovementComponent::Update(float _DeltaTime)
{
	//GameEngineActor* Actor = GetParent<GameEngineActor>();
	//if (Actor == nullptr)
	//{
	//	return;
	//}


	//if (State == InGameMonsterState::AttackFinish2)
	//{
	//	Actor->GetTransform().SetWorldMove(Direction * 4 * Speed * _DeltaTime);

	//}
	//else
	//{
	//	Actor->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
	//}
}

void InGameMovementComponent::End()
{
}
