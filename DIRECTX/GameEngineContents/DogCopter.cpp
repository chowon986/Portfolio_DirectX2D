#include "PreCompile.h"
#include "DogCopter.h"
#include "DogCopterArms.h"
#include "InGameDogCopterAnimationControllerComponent.h"

DogCopter::DogCopter()
	: Renderer(nullptr)
	, CopterArms(nullptr)
	, Animation(nullptr)
{
}

DogCopter::~DogCopter()
{
}

void DogCopter::Start()
{
	IInGameMonsterBase::Start();
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("DogCopterIntro", FrameAnimation_DESC("DogCopterIntro",0,29, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("DogCopterIdle", FrameAnimation_DESC("DogCopterIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterAttack1", FrameAnimation_DESC("DogCopterIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCamera", FrameAnimation_DESC("DogCopterRotateCamera", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotatedIdle", FrameAnimation_DESC("DogCopterRotatedIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterAttack2", FrameAnimation_DESC("DogCopterRotatedIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCameraOut", FrameAnimation_DESC("DogCopterRotateCameraOut", 0.1f));

		Renderer->AnimationBindEnd("DogCopterIntro", std::bind(&DogCopter::OnIntroAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterIdle", std::bind(&DogCopter::OnIdleAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterAttack1", std::bind(&DogCopter::OnAttack1AnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotateCamera", std::bind(&DogCopter::OnRotateCameraAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotatedIdle", std::bind(&DogCopter::OnRotatedIdleAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterAttack2", std::bind(&DogCopter::OnAttack2AnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotateCameraOut", std::bind(&DogCopter::OnRotateCameraOutAnimationFrameFinished, this, std::placeholders::_1));
	
		Renderer->AnimationBindFrame("DogCopterRotateCameraOut", std::bind(&DogCopter::OnRotateCameraOutAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterRotateCamera", std::bind(&DogCopter::OnRotateCameraAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterAttack1", std::bind(&DogCopter::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("DogCopterIntro");
		Renderer->SetScaleModeImage();
		Renderer->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC - 1 });

		SetState(InGameMonsterState::Prepare);
		SetRenderer(Renderer);
	}

	{
		ArmsRenderer = CreateComponent<GameEngineTextureRenderer>();
		ArmsRenderer->CreateFrameAnimationFolder("DogCopterIdleArms", FrameAnimation_DESC("DogCopterIdleArms", 0.1f));
		ArmsRenderer->ChangeFrameAnimation("DogCopterIdleArms");
		ArmsRenderer->SetScaleModeImage();
		ArmsRenderer->GetTransform().SetLocalPosition({ 650, -360, (int)ZOrder::NPC });
		ArmsRenderer->Off();
	}

	{
		WristRenderer = CreateComponent<GameEngineTextureRenderer>();
		WristRenderer->CreateFrameAnimationFolder("DogCopterIdleWrist", FrameAnimation_DESC("DogCopterIdleWrist", 0.1f)); // Idle Wrist
		WristRenderer->ChangeFrameAnimation("DogCopterIdleWrist");
		WristRenderer->SetScaleModeImage();
		WristRenderer->GetTransform().SetLocalPosition({ 650, -360, (int)ZOrder::NPC - 1 });
		WristRenderer->Off();
	}

	{
		LeftHandRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftHandRenderer->CreateFrameAnimationFolder("PawMerge", FrameAnimation_DESC("PawMerge", 0.1f));
		LeftHandRenderer->ChangeFrameAnimation("PawMerge");
		LeftHandRenderer->SetScaleModeImage();
		LeftHandRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 2 });
		LeftHandRenderer->Off();

		RightHandRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightHandRenderer->CreateFrameAnimationFolder("PawMerge", FrameAnimation_DESC("PawMerge", 0.1f));
		RightHandRenderer->ChangeFrameAnimation("PawMerge");
		RightHandRenderer->SetScaleModeImage();
		RightHandRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 2 });
		RightHandRenderer->GetTransform().PixLocalNegativeX();
		RightHandRenderer->Off();
	}

	{
		LeftTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadRenderer->CreateFrameAnimationFolder("TopPadOpen", FrameAnimation_DESC("TopPadOpen", 0.1f, true)); // 패드 열리기
		LeftTopPadRenderer->CreateFrameAnimationFolder("TopPadOpenIdle", FrameAnimation_DESC("TopPadOpen", 3, 3, 0.1f, false)); // 열린 상태 Idle 
		LeftTopPadRenderer->CreateFrameAnimationFolder("TopPadClose", FrameAnimation_DESC("TopPadClose", 0.1f, true)); // 패드 닫히기
		LeftTopPadRenderer->CreateFrameAnimationFolder("LeftTopPadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, true)); // 패드 닫히기
		LeftTopPadRenderer->AnimationBindEnd("TopPadOpen", std::bind(&DogCopter::OnTopPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopPadRenderer->AnimationBindEnd("TopPadClose", std::bind(&DogCopter::OnTopPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopPadRenderer->ChangeFrameAnimation("TopPadOpen");
		LeftTopPadRenderer->SetScaleModeImage();
		LeftTopPadRenderer->GetTransform().SetLocalPosition({ 193, -147, (int)ZOrder::NPC - 4 });
		LeftTopPadRenderer->Off();

		LeftMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadRenderer->CreateFrameAnimationFolder("MidPadOpen", FrameAnimation_DESC("MidPadOpen", 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("MidPadOpenIdle", FrameAnimation_DESC("MidPadOpen", 2, 2, 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("MidPadClose", FrameAnimation_DESC("MidPadClose", 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("LeftMidPadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadRenderer->AnimationBindEnd("MidPadOPen", std::bind(&DogCopter::OnMidPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidPadRenderer->AnimationBindEnd("MidPadClose", std::bind(&DogCopter::OnMidPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidPadRenderer->ChangeFrameAnimation("MidPadOpen");
		LeftMidPadRenderer->GetTransform().SetLocalPosition({ 125, -350, (int)ZOrder::NPC - 3 });
		LeftMidPadRenderer->SetScaleModeImage();
		LeftMidPadRenderer->Off();

		LeftLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadRenderer->CreateFrameAnimationFolder("LowPadOpen", FrameAnimation_DESC("LowPadOpen", 0.1f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("LowPadOPenIdle", FrameAnimation_DESC("LowPadOPenIdle", 2, 2, 0.1f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("LowPadClose", FrameAnimation_DESC("LowPadClose", 0.1f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("LeftLowPadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadRenderer->AnimationBindEnd("LowPadOpen", std::bind(&DogCopter::OnLowPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowPadRenderer->AnimationBindEnd("LowPadClose", std::bind(&DogCopter::OnLowPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowPadRenderer->ChangeFrameAnimation("LowPadOpen");
		LeftLowPadRenderer->GetTransform().SetLocalPosition({ 176, -559, (int)ZOrder::NPC - 3 });
		LeftLowPadRenderer->SetScaleModeImage();
		LeftLowPadRenderer->Off();
	}

	{
		RightTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadRenderer->CreateFrameAnimationFolder("TopPadOpen", FrameAnimation_DESC("TopPadOpen", 0.1f, true)); // 패드 열리기
		RightTopPadRenderer->CreateFrameAnimationFolder("TopPadOpenIdle", FrameAnimation_DESC("TopPadOpen", 3, 3, 0.1f, false)); // 열린 상태 Idle 
		RightTopPadRenderer->CreateFrameAnimationFolder("TopPadClose", FrameAnimation_DESC("TopPadClose", 0.1f, true)); // 패드 닫히기
		RightTopPadRenderer->CreateFrameAnimationFolder("LeftTopPadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, true)); // 패드 닫히기
		RightTopPadRenderer->AnimationBindEnd("TopPadOpen", std::bind(&DogCopter::OnTopPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightTopPadRenderer->AnimationBindEnd("TopPadClose", std::bind(&DogCopter::OnTopPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightTopPadRenderer->ChangeFrameAnimation("TopPadOpen");
		RightTopPadRenderer->GetTransform().SetLocalPosition({ 1110, -129, (int)ZOrder::NPC - 4 });
		RightTopPadRenderer->SetScaleModeImage();
		RightTopPadRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadRenderer->Off();

		RightMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadRenderer->CreateFrameAnimationFolder("MidPadOPen", FrameAnimation_DESC("MidPadOpen", 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("MidPadOPenIdle", FrameAnimation_DESC("MidPadOPenIdle", 2, 2, 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("MidPadClose", FrameAnimation_DESC("MidPadClose", 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("RightMidPadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadRenderer->AnimationBindEnd("MidPadOPen", std::bind(&DogCopter::OnMidPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightMidPadRenderer->AnimationBindEnd("MidPadClose", std::bind(&DogCopter::OnMidPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightMidPadRenderer->ChangeFrameAnimation("MidPadOpen");
		RightMidPadRenderer->GetTransform().SetLocalPosition({ 1180, -338, (int)ZOrder::NPC - 4 });
		RightMidPadRenderer->SetScaleModeImage();
		RightMidPadRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadRenderer->Off();

		RightLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadRenderer->CreateFrameAnimationFolder("LowPadOpen", FrameAnimation_DESC("LowPadOpen", 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("LowPadOPenIdle", FrameAnimation_DESC("LowPadOPenIdle", 2, 2, 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("LowPadClose", FrameAnimation_DESC("LowPadClose", 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("RightLowPadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowPadRenderer->AnimationBindEnd("LowPadOpen", std::bind(&DogCopter::OnLowPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightLowPadRenderer->AnimationBindEnd("LowPadClose", std::bind(&DogCopter::OnLowPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightLowPadRenderer->ChangeFrameAnimation("LowPadOpen");
		RightLowPadRenderer->GetTransform().SetLocalPosition({ 1125, -540, (int)ZOrder::NPC - 4 });
		RightLowPadRenderer->GetTransform().PixLocalNegativeX();
		RightLowPadRenderer->SetScaleModeImage();
		RightLowPadRenderer->Off();
	}

	{
		LaserBeamTopRenderer = CreateComponent<GameEngineTextureRenderer>();
		LaserBeamTopRenderer->CreateFrameAnimationFolder("LaserTop", FrameAnimation_DESC("LaserTop", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LaserBeamTopRenderer->CreateFrameAnimationFolder("LaserTopWarning", FrameAnimation_DESC("LaserTopWarning", 0.1f, true)); // 레이저 기기 경고
		LaserBeamTopRenderer->CreateFrameAnimationFolder("LaserTopShooting", FrameAnimation_DESC("LaserTopShooting", 0.1f, true)); // 레이저 기기 슈팅
		LaserBeamTopRenderer->CreateFrameAnimationFolder("LaserTopClose", FrameAnimation_DESC("LaserTopClose", 0.1f, false)); // 레이저 기기 제거
		LaserBeamTopRenderer->CreateFrameAnimationFolder("LaserBeamTopRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LaserBeamTopRenderer->AnimationBindEnd("LaserTop", std::bind(&DogCopter::OnLaserTopAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamTopRenderer->AnimationBindEnd("LaserTopWarning", std::bind(&DogCopter::OnLaserTopWarningAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamTopRenderer->AnimationBindEnd("LaserTopShooting", std::bind(&DogCopter::OnLaserTopShootingAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamTopRenderer->AnimationBindFrame("LaserTopClose", std::bind(&DogCopter::OnLaserToCloseAnimationFrameChanged, this, std::placeholders::_1));
		LaserBeamTopRenderer->AnimationBindEnd("LaserTopClose", std::bind(&DogCopter::OnLaserToCloseAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamTopRenderer->ChangeFrameAnimation("LaserTop");
		LaserBeamTopRenderer->SetScaleModeImage();
		LaserBeamTopRenderer->GetTransform().SetLocalPosition({ 330, -164, (int)ZOrder::NPC - 5 });
		LaserBeamTopRenderer->Off();

		LaserBeamMidRenderer = CreateComponent<GameEngineTextureRenderer>();
		LaserBeamMidRenderer->CreateFrameAnimationFolder("LaserMid", FrameAnimation_DESC("LaserMid", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LaserBeamMidRenderer->CreateFrameAnimationFolder("LaserMidShooting", FrameAnimation_DESC("LaserMidShooting", 0.1f, true)); // 레이저 기기 슈팅
		LaserBeamMidRenderer->CreateFrameAnimationFolder("LaserMidClose", FrameAnimation_DESC("LaserMidClose", 0.1f, false)); // 레이저 기기 제거
		LaserBeamMidRenderer->CreateFrameAnimationFolder("LaserBeamMidRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LaserBeamMidRenderer->AnimationBindEnd("LaserMid", std::bind(&DogCopter::OnLaserMidAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamMidRenderer->AnimationBindEnd("LaserMidShooting", std::bind(&DogCopter::OnLaserMidShootingAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamMidRenderer->AnimationBindFrame("LaserMidClose", std::bind(&DogCopter::OnLaserToCloseAnimationFrameChanged, this, std::placeholders::_1));
		LaserBeamMidRenderer->AnimationBindEnd("LaserMidClose", std::bind(&DogCopter::OnLaserToCloseAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamMidRenderer->ChangeFrameAnimation("LaserMid");
		LaserBeamMidRenderer->SetScaleModeImage();
		// LaserBeamMidRenderer->GetTransform().SetLocalPosition({ 330, -164, (int)ZOrder::NPC - 5 });
		LaserBeamMidRenderer->Off();

		LaserBeamLowRenderer = CreateComponent<GameEngineTextureRenderer>();
		LaserBeamLowRenderer->CreateFrameAnimationFolder("LaserLow", FrameAnimation_DESC("LaserLow", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LaserBeamLowRenderer->CreateFrameAnimationFolder("LaserLowWarning", FrameAnimation_DESC("LaserLowWarning", 0.1f, true)); // 레이저 기기 경고
		LaserBeamLowRenderer->CreateFrameAnimationFolder("LaserLowShooting", FrameAnimation_DESC("LaserLowShooting", 0.1f, true)); // 레이저 기기 슈팅
		LaserBeamLowRenderer->CreateFrameAnimationFolder("LaserLowClose", FrameAnimation_DESC("LaserLowClose", 0.1f, false)); // 레이저 기기 제거
		LaserBeamLowRenderer->CreateFrameAnimationFolder("LaserBeamLowRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LaserBeamLowRenderer->AnimationBindEnd("LaserLow", std::bind(&DogCopter::OnLaserLowAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamLowRenderer->AnimationBindEnd("LaserLowWarning", std::bind(&DogCopter::OnLaserLowWarningAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamLowRenderer->AnimationBindEnd("LaserLowShooting", std::bind(&DogCopter::OnLaserLowShootingAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamLowRenderer->AnimationBindFrame("LaserLowClose", std::bind(&DogCopter::OnLaserToCloseAnimationFrameChanged, this, std::placeholders::_1));
		LaserBeamLowRenderer->AnimationBindEnd("LaserLowClose", std::bind(&DogCopter::OnLaserToCloseAnimationFrameFinished, this, std::placeholders::_1));
		LaserBeamLowRenderer->ChangeFrameAnimation("LaserLow");
		LaserBeamLowRenderer->SetScaleModeImage();
		// LaserBeamLowRenderer->GetTransform().SetLocalPosition({ 330, -164, (int)ZOrder::NPC - 5 });
		LaserBeamLowRenderer->Off();
	}


	{
		LeftTopPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("LeftPawHoleTop", FrameAnimation_DESC("LeftPawHoleTop", 0.1f, false)); 
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("LeftTopPadBackRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		LeftTopPadBackRenderer->ChangeFrameAnimation("LeftPawHoleTop");
		LeftTopPadBackRenderer->SetScaleModeImage();
		LeftTopPadBackRenderer->GetTransform().SetLocalPosition({ 196, -155, (int)ZOrder::NPC - 3 });
		LeftTopPadBackRenderer->Off();

		//LeftMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		//LeftMidPadBackRenderer->CreateFrameAnimationFolder("LeftPawHoleMid", FrameAnimation_DESC("LeftPawHoleMid", 0.1f, false)); 
		//LeftMidPadBackRenderer->CreateFrameAnimationFolder("LeftMidPadBackRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		//LeftMidPadBackRenderer->ChangeFrameAnimation("LeftPawHoleMid");
		//LeftMidPadBackRenderer->SetScaleModeImage();
		////LeftMidPadBackRenderer->GetTransform().SetLocalPosition({ 196, -155, (int)ZOrder::NPC - 3 });
		//LeftMidPadBackRenderer->Off();

		LeftLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("LeftPawHoleLow", FrameAnimation_DESC("LeftPawHoleLow", 0.1f, false)); 
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("LeftLowPadBackRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		LeftLowPadBackRenderer->ChangeFrameAnimation("LeftPawHoleLow");
		LeftLowPadBackRenderer->SetScaleModeImage();
		//LeftLowPadBackRenderer->GetTransform().SetLocalPosition({ 196, -155, (int)ZOrder::NPC - 3 });
		LeftLowPadBackRenderer->Off();

		RightTopPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadBackRenderer->CreateFrameAnimationFolder("LeftPawHoleTop", FrameAnimation_DESC("LeftPawHoleTop", 0.1f, false)); 
		RightTopPadBackRenderer->CreateFrameAnimationFolder("LeftTopPadBackRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		RightTopPadBackRenderer->ChangeFrameAnimation("LeftPawHoleTop");
		RightTopPadBackRenderer->SetScaleModeImage();
		//RightTopPadBackRenderer->GetTransform().SetLocalPosition({ 196, -155, (int)ZOrder::NPC - 3 });
		RightTopPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadBackRenderer->Off();

		//RightMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		//RightMidPadBackRenderer->CreateFrameAnimationFolder("RightPawHoleMid", FrameAnimation_DESC("RightPawHoleMid", 0.1f, false)); 
		//RightMidPadBackRenderer->CreateFrameAnimationFolder("RightMidPadBackRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		//RightMidPadBackRenderer->ChangeFrameAnimation("RightPawHoleMid");
		//RightMidPadBackRenderer->SetScaleModeImage();
		////RightMidPadBackRenderer->GetTransform().SetLocalPosition({ 196, -155, (int)ZOrder::NPC - 3 });
		//RightMidPadBackRenderer->GetTransform().PixLocalNegativeX();
		//RightMidPadBackRenderer->Off();

		RightLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadBackRenderer->CreateFrameAnimationFolder("LeftPawHoleLow", FrameAnimation_DESC("LeftPawHoleLow", 0.1f, false)); 
		RightLowPadBackRenderer->CreateFrameAnimationFolder("LeftLowPadBackRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		RightLowPadBackRenderer->ChangeFrameAnimation("LeftPawHoleLow");
		RightLowPadBackRenderer->SetScaleModeImage();
		//RightLowPadBackRenderer->GetTransform().SetLocalPosition({ 196, -155, (int)ZOrder::NPC - 3 });
		//RightLowPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightLowPadBackRenderer->Off();
	}

	Animation = CreateComponent<InGameDogCopterAnimationControllerComponent>();
	Animation->SetMonsterName("DogCopter");

	srand(time(NULL));

}

void DogCopter::Update(float _DeltaTime)
{

}

void DogCopter::End()
{
}

void DogCopter::Prepare()
{
	int a = 0;
}

void DogCopter::Idle()
{
	SetDogCopterState(InGameDogCopterState::Idle);
}

void DogCopter::TakeDamage()
{
}

void DogCopter::Shoot()
{
}

void DogCopter::Die()
{
}

void DogCopter::Attack1()
{
	SetDogCopterState(InGameDogCopterState::Attack1);
}

void DogCopter::Attack2()
{
	SetDogCopterState(InGameDogCopterState::Attack2);
}

void DogCopter::RotateCameraIn()
{
	SetDogCopterState(InGameDogCopterState::RotateCameraIn);
}

void DogCopter::RotateCameraOut()
{
	SetDogCopterState(InGameDogCopterState::RotateCameraOut);
}

void DogCopter::RotateCameraIdle()
{
	SetDogCopterState(InGameDogCopterState::RotateCameraIdle);
}


void DogCopter::OnIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	//if (CopterArms == nullptr)
	//{
	//	CopterArms = GetLevel()->CreateActor<DogCopterArms>();
	//}
	ArmsRenderer->On();
	WristRenderer->On();
	LeftHandRenderer->On();
	RightHandRenderer->On();
	Idle();
}

void DogCopter::OnIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Attack1();
}

void DogCopter::OnAttack1AnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	ArmsRenderer->Off();
	WristRenderer->Off();
	//RotateCameraIn();
}

void DogCopter::OnRotateCameraAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	RotateCameraIdle();
}

void DogCopter::OnRotatedIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Attack2();
}

void DogCopter::OnAttack2AnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	RotateCameraOut();
}

void DogCopter::OnRotateCameraOutAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->GetTransform().SetLocalRotate({ 0,0,180 });
	ArmsRenderer->On();
	WristRenderer->On();
	Idle();
}

void DogCopter::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 6)
	{
		//int RandomAttack = rand() % 3;
		//++RandomAttack;
		//if (RandomAttack == 1)
		//{
			LeftTopPadBackRenderer->On();
			LeftTopPadRenderer->On();
			LaserBeamTopRenderer->On();
		//}
		//else if(RandomAttack == 2)
		//{

		//}
	}
}

void DogCopter::OnRotateCameraAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 11)
	{
		LeftHandRenderer->Off();
		RightHandRenderer->Off();
	}
}

void DogCopter::OnRotateCameraOutAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 8)
	{
		LeftHandRenderer->On();
		RightHandRenderer->On();
	}
}

void DogCopter::OnTopPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LeftTopPadRenderer->ChangeFrameAnimation("TopPadOpenIdle");
}

void DogCopter::OnTopPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LeftTopPadRenderer->ChangeFrameAnimation("LeftTopPadRendererNothing");
	LeftTopPadRenderer->Off();
	LeftTopPadBackRenderer->ChangeFrameAnimation("LeftTopPadBackRendererNothing");
	LeftTopPadBackRenderer->Off();
}

void DogCopter::OnMidPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	//LeftMidPadRenderer->ChangeFrameAnimation("MidPadOpenIdle");
}

void DogCopter::OnMidPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LeftMidPadRenderer->ChangeFrameAnimation("LeftMidPadRendererNothing");
	LeftMidPadRenderer->Off();
	//LeftMidPadBackRenderer->ChangeFrameAnimation("LeftMidPadBackRendererNothing");
	//LeftMidPadBackRenderer->Off();
}

void DogCopter::OnLowPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LeftLowPadRenderer->ChangeFrameAnimation("LowPadOpenIdle");
}

void DogCopter::OnLowPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LeftLowPadRenderer->ChangeFrameAnimation("LeftLowPadRendererNothing");
	LeftLowPadRenderer->Off();
	//LeftLowPadBackRenderer->ChangeFrameAnimation("LeftLowPadBackRendererNothing");
	//LeftLowPadBackRenderer->Off();
}

void DogCopter::OnLaserTopAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserBeamTopRenderer->ChangeFrameAnimation("LaserTopWarning");
}

void DogCopter::OnLaserTopWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserBeamTopRenderer->ChangeFrameAnimation("LaserTopShooting");
}

void DogCopter::OnLaserTopShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserBeamTopRenderer->ChangeFrameAnimation("LaserTopClose");
}

void DogCopter::OnLaserToCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserBeamTopRenderer->ChangeFrameAnimation("LaserBeamTopRendererNothing");
	LaserBeamTopRenderer->Off();
}

void DogCopter::OnLaserMidAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
}

void DogCopter::OnLaserMidWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
}

void DogCopter::OnLaserMidShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
}

void DogCopter::OnLaserLowAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
}

void DogCopter::OnLaserLowWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
}

void DogCopter::OnLaserLowShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
}

void DogCopter::OnLaserToCloseAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 10)
	{
		// 다음 공격 생성
		//LeftMidPadBackRenderer->On();
		LeftMidPadRenderer->On();
		//LaserBeamMidRenderer->On();
	}

	if (_Info.CurFrame == 13)
	{
		LeftTopPadRenderer->ChangeFrameAnimation("TopPadClose");
	}
}
