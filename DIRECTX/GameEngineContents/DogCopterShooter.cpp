#include "PreCompile.h"
#include "DogCopterShooter.h"
#include "IInGameMonsterBase.h"
#include "DogCopterBullet.h"
#include "DogCopter.h"

DogCopterShooter::DogCopterShooter()
	: PadRenderers()
	, LaserMachineRenderers()
	, PadBackRenderers()
	, LaserRenderers()
	, AttackCount(0)
{
}

DogCopterShooter::~DogCopterShooter()
{
}

void DogCopterShooter::Start()
{
	GetTransform().SetWorldPosition({ 0.0f,0.0f });
	{
		GameEngineTextureRenderer* LeftTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("TopPadOpen", 0.1f, true)); // 패드 열리기
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("TopPadOpen", 3, 3, 0.1f, false)); // 열린 상태 Idle 
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("TopPadClose", 0.1f, true)); // 패드 닫히기
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, true)); // 패드 닫히기
		LeftTopPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftTopPadRenderer->SetScaleModeImage();
		LeftTopPadRenderer->GetTransform().SetLocalPosition({ 272, -365, (int)ZOrder::NPC - 4 });
		LeftTopPadRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("MidPadOpen", 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("MidPadOpen", 2, 2, 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("MidPadClose", 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftMidPadRenderer->GetTransform().SetLocalPosition({ 208, -565, (int)ZOrder::NPC - 4 });
		LeftMidPadRenderer->SetScaleModeImage();
		LeftMidPadRenderer->Off();

		GameEngineTextureRenderer* LeftLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("LowPadOpen", 0.1f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadOPenIdle", FrameAnimation_DESC("LowPadOPen", 2, 2, 0.1f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("LowPadClose", 0.1f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftLowPadRenderer->GetTransform().SetLocalPosition({ 260, -780, (int)ZOrder::NPC - 4 });
		LeftLowPadRenderer->SetScaleModeImage();
		LeftLowPadRenderer->Off();

		GameEngineTextureRenderer* RightTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("TopPadOpen", 0.1f, true)); // 패드 열리기
		RightTopPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("TopPadOpen", 3, 3, 0.1f, false)); // 열린 상태 Idle 
		RightTopPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("TopPadClose", 0.1f, true)); // 패드 닫히기
		RightTopPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, true)); // 패드 닫히기
		RightTopPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightTopPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightTopPadRenderer->ChangeFrameAnimation("PadOpen");
		RightTopPadRenderer->SetScaleModeImage();
		RightTopPadRenderer->GetTransform().SetLocalPosition({ 1190, -347, (int)ZOrder::NPC - 4 });
		RightTopPadRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadRenderer->Off();

		GameEngineTextureRenderer* RightMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("MidPadOpen", 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("MidPadOpen", 2, 2, 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("MidPadClose", 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightMidPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightMidPadRenderer->ChangeFrameAnimation("PadOpen");
		RightMidPadRenderer->SetScaleModeImage();
		RightMidPadRenderer->GetTransform().SetLocalPosition({ 1260, -554, (int)ZOrder::NPC - 4 });
		RightMidPadRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadRenderer->Off();

		GameEngineTextureRenderer* RightLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("LowPadOpen", 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("PadOPenIdle", FrameAnimation_DESC("LowPadOPen", 2, 2, 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("LowPadClose", 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightLowPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightLowPadRenderer->ChangeFrameAnimation("PadOpen");
		RightLowPadRenderer->GetTransform().SetLocalPosition({ 1209, -765, (int)ZOrder::NPC - 4 });
		RightLowPadRenderer->SetScaleModeImage();
		RightLowPadRenderer->GetTransform().PixLocalNegativeX();
		RightLowPadRenderer->Off();

		PadRenderers.push_back(LeftTopPadRenderer);
		PadRenderers.push_back(RightTopPadRenderer);
		PadRenderers.push_back(LeftMidPadRenderer);
		PadRenderers.push_back(RightMidPadRenderer);
		PadRenderers.push_back(LeftLowPadRenderer);
		PadRenderers.push_back(RightLowPadRenderer);
	}

	{
		GameEngineTextureRenderer* LeftTopLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserTop", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserTopWarning", 0.1f, true)); // 레이저 기기 경고
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserTopShooting", 0.1f, true)); // 레이저 기기 슈팅
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserTopClose", 0.1f, false)); // 레이저 기기 제거
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftTopLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftTopLaserMachineRenderer->SetScaleModeImage();
		LeftTopLaserMachineRenderer->GetTransform().SetLocalPosition({ 410, -370, (int)ZOrder::NPC - 5 });
		LeftTopLaserMachineRenderer->Off();

		GameEngineTextureRenderer* LeftMidLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserMid", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserMidShooting", 0.1f, true)); // 레이저 기기 슈팅
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserMidShooting", 0.1f, true)); // 레이저 기기 슈팅
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserMidClose", 0.1f, false)); // 레이저 기기 제거
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftMidLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftMidLaserMachineRenderer->SetScaleModeImage();
		LeftMidLaserMachineRenderer->GetTransform().SetLocalPosition({ 270, -500, (int)ZOrder::NPC - 5 });
		LeftMidLaserMachineRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserLow", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserLowWarning", 0.1f, true)); // 레이저 기기 경고
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserLowShooting", 0.1f, true)); // 레이저 기기 슈팅
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserLowClose", 0.1f, false)); // 레이저 기기 제거
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftLowLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftLowLaserMachineRenderer->SetScaleModeImage();
		LeftLowLaserMachineRenderer->GetTransform().SetLocalPosition({ 270, -820, (int)ZOrder::NPC - 5 });
		LeftLowLaserMachineRenderer->Off();

		GameEngineTextureRenderer* RightTopLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserTop", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserTopWarning", 0.1f, true)); // 레이저 기기 경고
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserTopShooting", 0.1f, true)); // 레이저 기기 슈팅
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserTopClose", 0.1f, false)); // 레이저 기기 제거
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		RightTopLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		RightTopLaserMachineRenderer->SetScaleModeImage();
		RightTopLaserMachineRenderer->GetTransform().SetLocalPosition({ 1050, -370, (int)ZOrder::NPC - 5 });
		RightTopLaserMachineRenderer->GetTransform().PixLocalNegativeX();
		RightTopLaserMachineRenderer->Off();

		GameEngineTextureRenderer* RightMidLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserMid", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserMidShooting", 0.1f, true)); // 레이저 기기 슈팅
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserMidShooting", 0.1f, true)); // 레이저 기기 슈팅
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserMidClose", 0.1f, false)); // 레이저 기기 제거
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		RightMidLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		RightMidLaserMachineRenderer->SetScaleModeImage();
		RightMidLaserMachineRenderer->GetTransform().SetLocalPosition({ 1190, -500, (int)ZOrder::NPC - 5 });
		RightMidLaserMachineRenderer->GetTransform().PixLocalNegativeX();
		RightMidLaserMachineRenderer->Off();

		GameEngineTextureRenderer* RightLowLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserLow", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserLowWarning", 0.1f, true)); // 레이저 기기 경고
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserLowShooting", 0.1f, true)); // 레이저 기기 슈팅
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserLowClose", 0.1f, false)); // 레이저 기기 제거
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		RightLowLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		RightLowLaserMachineRenderer->SetScaleModeImage();
		RightLowLaserMachineRenderer->GetTransform().SetLocalPosition({ 1190, -820, (int)ZOrder::NPC - 5 });
		RightLowLaserMachineRenderer->GetTransform().PixLocalNegativeX();
		RightLowLaserMachineRenderer->Off();

		LaserMachineRenderers.push_back(LeftTopLaserMachineRenderer);
		LaserMachineRenderers.push_back(RightTopLaserMachineRenderer);
		LaserMachineRenderers.push_back(LeftMidLaserMachineRenderer);
		LaserMachineRenderers.push_back(RightMidLaserMachineRenderer);
		LaserMachineRenderers.push_back(LeftLowLaserMachineRenderer);
		LaserMachineRenderers.push_back(RightLowLaserMachineRenderer);
	}


	{
		GameEngineTextureRenderer* LeftTopPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTop", 0.1f, false));
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftTopPadBackRenderer->SetScaleModeImage();
		LeftTopPadBackRenderer->GetTransform().SetLocalPosition({ 273, -374, (int)ZOrder::NPC - 3 });
		LeftTopPadBackRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMid", 0.1f, false)); 
		LeftMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		LeftMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftMidPadBackRenderer->SetScaleModeImage();
		LeftMidPadBackRenderer->GetTransform().SetLocalPosition({ 299, -585, (int)ZOrder::NPC - 3 });
		LeftMidPadBackRenderer->Off();

		GameEngineTextureRenderer* LeftLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLow", 0.1f, false));
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftLowPadBackRenderer->SetScaleModeImage();
		LeftLowPadBackRenderer->GetTransform().SetLocalPosition({ 457, -827, (int)ZOrder::NPC - 3 });
		LeftLowPadBackRenderer->Off();

		GameEngineTextureRenderer* RightTopPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTop", 0.1f, false));
		RightTopPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightTopPadBackRenderer->SetScaleModeImage();
		RightTopPadBackRenderer->GetTransform().SetLocalPosition({ 1191, -355, (int)ZOrder::NPC - 3 });
		RightTopPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadBackRenderer->Off();

		GameEngineTextureRenderer* RightMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMid", 0.1f, false));
		RightMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightMidPadBackRenderer->SetScaleModeImage();
		RightMidPadBackRenderer->GetTransform().SetLocalPosition({ 1167, -567, (int)ZOrder::NPC - 3 });		
		RightMidPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadBackRenderer->Off();

		GameEngineTextureRenderer* RightLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLow", 0.1f, false));
		RightLowPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightLowPadBackRenderer->SetScaleModeImage();
		RightLowPadBackRenderer->GetTransform().SetLocalPosition({ 1007, -806, (int)ZOrder::NPC - 3 });
		RightLowPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightLowPadBackRenderer->Off();

		PadBackRenderers.push_back(LeftTopPadBackRenderer);
		PadBackRenderers.push_back(RightTopPadBackRenderer);
		PadBackRenderers.push_back(LeftMidPadBackRenderer);
		PadBackRenderers.push_back(RightMidPadBackRenderer);
		PadBackRenderers.push_back(LeftLowPadBackRenderer);
		PadBackRenderers.push_back(RightLowPadBackRenderer);
	}

	{
		GameEngineTextureRenderer* LeftTopLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningA", 0.1f, true));
		LeftTopLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamTop", 0.1f, true));
		LeftTopLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftTopLaserRenderer->SetScaleModeImage();
		LeftTopLaserRenderer->GetTransform().SetLocalPosition({ 400, -500, (int)ZOrder::NPC - 5 });
		LeftTopLaserRenderer->Off();

		GameEngineTextureRenderer* LeftMidLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningB", 0.1f, false)); 
		LeftMidLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamMid", 0.1f, false)); 
		LeftMidLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		LeftMidLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftMidLaserRenderer->SetScaleModeImage();
		LeftMidLaserRenderer->GetTransform().SetLocalPosition({ 400, -600, (int)ZOrder::NPC - 3 });
		LeftMidLaserRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningC", 0.1f, false));
		LeftLowLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamLow", 0.1f, false));
		LeftLowLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftLowLaserRenderer->SetScaleModeImage();
		LeftLowLaserRenderer->GetTransform().SetLocalPosition({ 400, -600, (int)ZOrder::NPC - 3 });
		LeftLowLaserRenderer->Off();

		GameEngineTextureRenderer* RightTopLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningA", 0.1f, true));
		RightTopLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamTop", 0.1f, true));
		RightTopLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserRenderer->ChangeFrameAnimation("LaserWarning");
		RightTopLaserRenderer->SetScaleModeImage();
		RightTopLaserRenderer->GetTransform().SetLocalPosition({ 880, -500, (int)ZOrder::NPC - 5 });
		RightTopLaserRenderer->GetTransform().PixLocalNegativeX();
		RightTopLaserRenderer->Off();

		GameEngineTextureRenderer* RightMidLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningB", 0.1f, false));
		RightMidLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamMid", 0.1f, false));
		RightMidLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserRenderer->ChangeFrameAnimation("LaserWarning");
		RightMidLaserRenderer->SetScaleModeImage();
		RightMidLaserRenderer->GetTransform().SetLocalPosition({ 880, -600, (int)ZOrder::NPC - 3 });
		RightMidLaserRenderer->GetTransform().PixLocalNegativeX();
		RightMidLaserRenderer->Off();

		GameEngineTextureRenderer* RightLowLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserRenderer->ChangeFrameAnimation("LaserWarning");
		RightLowLaserRenderer->SetScaleModeImage();
		RightLowLaserRenderer->GetTransform().SetLocalPosition({ 400, -600, (int)ZOrder::NPC - 3 });
		RightLowLaserRenderer->Off();

		LaserRenderers.push_back(LeftTopLaserRenderer);
		LaserRenderers.push_back(RightTopLaserRenderer);
		LaserRenderers.push_back(LeftMidLaserRenderer);
		LaserRenderers.push_back(RightMidLaserRenderer);
		LaserRenderers.push_back(LeftLowLaserRenderer);
		LaserRenderers.push_back(RightLowLaserRenderer);
	}

	srand(time(NULL));
}

void DogCopterShooter::End()
{
}

void DogCopterShooter::OnMonsterStateChanged(InGameMonsterState _State)
{
	MonsterWeaponBase::OnMonsterStateChanged(_State);

	if (_State == InGameMonsterState::Attack1)
	{

		if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
		{
			Parent->SetAttackState(InGameMonsterAttackState::LaserPattern1);
		}
	}
}

void DogCopterShooter::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	MonsterWeaponBase::OnMonsterAttackStateChanged(_AttackState);

	if (_AttackState == InGameMonsterAttackState::LaserPattern1)
	{
		int RandomAttackPattern = rand() % 4;
		int RandomAttackCount = rand() % 2;
		
		//if (RandomAttackCount == 1)
		//{
			PadRenderers[RandomAttackPattern]->On();
			PadRenderers[RandomAttackPattern]->ChangeFrameAnimation("PadOpen");
			LaserMachineRenderers[RandomAttackPattern]->On();
			LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserPrepare");
			PadBackRenderers[RandomAttackPattern]->On();
		//}
		//else
		//{

		//	PadRenderers[RandomAttackPattern]->On();
		//	PadRenderers[RandomAttackPattern]->ChangeFrameAnimation("PadOpen");
		//	LaserMachineRenderers[RandomAttackPattern]->On();
		//	LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserPrepare");
		//	PadBackRenderers[RandomAttackPattern]->On();

		//	PadRenderers[RandomAttackPattern]->On();
		//	PadRenderers[RandomAttackPattern]->ChangeFrameAnimation("PadOpen");
		//	LaserMachineRenderers[RandomAttackPattern]->On();
		//	LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserPrepare");
		//	PadBackRenderers[RandomAttackPattern]->On();
		//}
	}
	else if (_AttackState == InGameMonsterAttackState::LaserPattern2)
	{
		RandomAttackPattern = rand() % 4;
		int RandomAttackCount = rand() % 2;

		//if (RandomAttackCount == 1)
		//{
			PadRenderers[RandomAttackPattern]->On();
			PadRenderers[RandomAttackPattern]->ChangeFrameAnimation("PadOpen");
			LaserMachineRenderers[RandomAttackPattern]->On();
			LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserPrepare");
			PadBackRenderers[RandomAttackPattern]->On();
		//}
	}
	else if (_AttackState == InGameMonsterAttackState::LaserPattern3)
	{
		PadRenderers[4]->On();
		PadRenderers[4]->ChangeFrameAnimation("PadOpen");
		LaserMachineRenderers[4]->On();
		LaserMachineRenderers[4]->ChangeFrameAnimation("LaserPrepare");
		PadBackRenderers[4]->On();

		PadRenderers[5]->On();
		PadRenderers[5]->ChangeFrameAnimation("PadOpen");
		LaserMachineRenderers[5]->On();
		LaserMachineRenderers[5]->ChangeFrameAnimation("LaserPrepare");
		PadBackRenderers[5]->On();
	}
}


void DogCopterShooter::Update(float _DeltaTime)
{

}

void DogCopterShooter::OnPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	PadRenderers[RandomAttackPattern]->ChangeFrameAnimation("PadOpenIdle");
}

void DogCopterShooter::OnPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	PadRenderers[RandomAttackPattern]->ChangeFrameAnimation("PadRendererNothing");
	PadBackRenderers[RandomAttackPattern]->Off();
}

void DogCopterShooter::OnLaserAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserWarning");
	LaserRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserWarning");
	LaserRenderers[RandomAttackPattern]->On();
}

void DogCopterShooter::OnLaserWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserShooting");
	LaserRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserBeam");
}

void DogCopterShooter::OnLaserShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserClose");
	LaserRenderers[RandomAttackPattern]->ChangeFrameAnimation("Nothing");
	LaserRenderers[RandomAttackPattern]->Off();
	PadRenderers[RandomAttackPattern]->ChangeFrameAnimation("PadClose");
}

void DogCopterShooter::OnLaserCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	//LaserMachineRenderers[0]->ChangeFrameAnimation("LaserNothing");
	//LaserMachineRenderers[0]->Off();
	//PadBackRenderers[0]->Off();
	LaserMachineRenderers[RandomAttackPattern]->ChangeFrameAnimation("LaserNothing");
	LaserMachineRenderers[RandomAttackPattern]->Off();
	PadBackRenderers[RandomAttackPattern]->Off();

	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			Parent->SetState(InGameMonsterState::BeforeRotateCameraIn);
		}
		else
		{
			if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern1)
			{
				Parent->SetAttackState(InGameMonsterAttackState::LaserPattern2);
			}
			else if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern2)
			{
				Parent->SetAttackState(InGameMonsterAttackState::LaserPattern3);
			}
		}
	}
}