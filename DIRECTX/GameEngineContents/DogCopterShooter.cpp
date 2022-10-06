#include "PreCompile.h"
#include "DogCopterShooter.h"
#include "IInGameMonsterBase.h"
#include "DogCopter.h"
#include "DogBowlBullet.h"

DogCopterShooter::DogCopterShooter()
	: PadRenderers()
	, LaserMachineRenderers()
	, PadBackRenderers()
	, LaserRenderers()
	, HP(10)
	, CanTakeDamgageTime(0.0f)
{
}

DogCopterShooter::~DogCopterShooter()
{
}

void DogCopterShooter::Start()
{
	GetTransform().SetWorldPosition({ 0.0f,0.0f });

	{
		GameEngineTextureRenderer* LeftTopTeethRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopTeethRenderer->CreateFrameAnimationFolder("LaserTeeth", FrameAnimation_DESC("LaserTopShootingTeeth", 0.05f, true));
		LeftTopTeethRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopTeethRenderer->ChangeFrameAnimation("LaserTeeth");
		LeftTopTeethRenderer->SetScaleModeImage();
		LeftTopTeethRenderer->GetTransform().SetLocalPosition({ 395, -135, (int)ZOrder::NPC - 9 });
		LeftTopTeethRenderer->Off();

		GameEngineTextureRenderer* RightTopTeethRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopTeethRenderer->CreateFrameAnimationFolder("LaserTeeth", FrameAnimation_DESC("LaserTopShootingTeeth", 0.05f, true));
		RightTopTeethRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopTeethRenderer->ChangeFrameAnimation("LaserTeeth");
		RightTopTeethRenderer->SetScaleModeImage();
		RightTopTeethRenderer->GetTransform().SetLocalPosition({ 907, -136, (int)ZOrder::NPC - 9 });
		RightTopTeethRenderer->GetTransform().PixLocalNegativeX();
		RightTopTeethRenderer->Off();

		MachineTeethRenderers.push_back(LeftTopTeethRenderer);
		MachineTeethRenderers.push_back(RightTopTeethRenderer);
	}

	{
		GameEngineTextureRenderer* LeftTopAuraRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopAuraRenderer->CreateFrameAnimationFolder("LaserAura", FrameAnimation_DESC("LaserWarningAuraA", 0.05f, true));
		LeftTopAuraRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopAuraRenderer->ChangeFrameAnimation("LaserAura");
		LeftTopAuraRenderer->SetScaleModeImage();
		LeftTopAuraRenderer->GetTransform().SetLocalPosition({ 395, -140, (int)ZOrder::NPC - 8 });
		LeftTopAuraRenderer->Off();


		GameEngineTextureRenderer* RightTopAuraRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopAuraRenderer->CreateFrameAnimationFolder("LaserAura", FrameAnimation_DESC("LaserWarningAuraA", 0.05f, true));
		RightTopAuraRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopAuraRenderer->ChangeFrameAnimation("LaserAura");
		RightTopAuraRenderer->SetScaleModeImage();
		RightTopAuraRenderer->GetTransform().SetLocalPosition({ 900, -140, (int)ZOrder::NPC - 8 });
		RightTopAuraRenderer->GetTransform().PixLocalNegativeX();
		RightTopAuraRenderer->Off();

		GameEngineTextureRenderer* BotAuraRenderer = CreateComponent<GameEngineTextureRenderer>();
		BotAuraRenderer->CreateFrameAnimationFolder("LaserAura", FrameAnimation_DESC("LaserWarningAuraC", 0.05f, true));
		BotAuraRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		BotAuraRenderer->ChangeFrameAnimation("LaserAura");
		BotAuraRenderer->SetScaleModeImage();
		BotAuraRenderer->GetTransform().SetLocalPosition({ 310, -540, (int)ZOrder::NPC - 8 });
		BotAuraRenderer->Off();

		AuraRenderers.push_back(LeftTopAuraRenderer);
		AuraRenderers.push_back(RightTopAuraRenderer);
		AuraRenderers.push_back(BotAuraRenderer);
	}

	{
		GameEngineTextureRenderer* LeftTopPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTopBacker", 0.05f, false));
		LeftTopPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		LeftTopPadBackBackerRenderer->SetScaleModeImage();
		LeftTopPadBackBackerRenderer->GetTransform().SetLocalPosition({ 194, -154, (int)ZOrder::NPC - 3 });
		LeftTopPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMidBacker", 0.05f, false));
		LeftMidPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		LeftMidPadBackBackerRenderer->SetScaleModeImage();
		LeftMidPadBackBackerRenderer->GetTransform().SetLocalPosition({ 223, -363, (int)ZOrder::NPC - 3 });
		LeftMidPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* LeftLowPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLowBacker", 0.05f, false));
		LeftLowPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		LeftLowPadBackBackerRenderer->SetScaleModeImage();
		LeftLowPadBackBackerRenderer->GetTransform().SetLocalPosition({ 378, -608, (int)ZOrder::NPC - 3 });
		LeftLowPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* RightTopPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTopBacker", 0.05f, false));
		RightTopPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		RightTopPadBackBackerRenderer->SetScaleModeImage();
		RightTopPadBackBackerRenderer->GetTransform().SetLocalPosition({ 1111, -133, (int)ZOrder::NPC - 3 });
		RightTopPadBackBackerRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* RightMidPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMidBacker", 0.05f, false));
		RightMidPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		RightMidPadBackBackerRenderer->SetScaleModeImage();
		RightMidPadBackBackerRenderer->GetTransform().SetLocalPosition({ 1082, -345, (int)ZOrder::NPC - 3 });
		RightMidPadBackBackerRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* RightLowPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLowBacker", 0.05f, false));
		RightLowPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		RightLowPadBackBackerRenderer->SetScaleModeImage();
		RightLowPadBackBackerRenderer->GetTransform().SetLocalPosition({ 926, -589, (int)ZOrder::NPC - 3 });
		RightLowPadBackBackerRenderer->GetTransform().PixLocalNegativeX();
		RightLowPadBackBackerRenderer->Off();

		PadBackBackerRenderers.push_back(LeftTopPadBackBackerRenderer);
		PadBackBackerRenderers.push_back(RightTopPadBackBackerRenderer);
		PadBackBackerRenderers.push_back(LeftMidPadBackBackerRenderer);
		PadBackBackerRenderers.push_back(RightMidPadBackBackerRenderer);
		PadBackBackerRenderers.push_back(LeftLowPadBackBackerRenderer);
		PadBackBackerRenderers.push_back(RightLowPadBackBackerRenderer);
	}

	{
		GameEngineTextureRenderer* LeftTopLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserTopBackerStart", 0.05f, false));
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserTopShootingBacker", 0.05f, false));
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserTopBackerEnd", 0.05f, false));
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		LeftTopLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		LeftTopLaserMachineBackerRenderer->SetScaleModeImage();
		LeftTopLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 260, -90, (int)ZOrder::NPC - 4 });
		LeftTopLaserMachineBackerRenderer->Off();


		GameEngineTextureRenderer* LeftMidLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserMidBackerStart", 0.05f, false));
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserMidShootingBacker", 0.05f, false));
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserMidBackerEnd", 0.05f, false));
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		LeftMidLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		LeftMidLaserMachineBackerRenderer->SetScaleModeImage();
		LeftMidLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 320, -300, (int)ZOrder::NPC - 4 });
		LeftMidLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserLowBackerStart", 0.05f, false));
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserLowShootingBacker", 0.05f, false));
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserLowBackerEnd", 0.05f, false));
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		LeftLowLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		LeftLowLaserMachineBackerRenderer->SetScaleModeImage();
		LeftLowLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 200, -550, (int)ZOrder::NPC - 4 });
		LeftLowLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* RightTopLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserTopBackerStart", 0.05f, false));
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserTopShootingBacker", 0.05f, false));
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserTopBackerEnd", 0.05f, false));
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		RightTopLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		RightTopLaserMachineBackerRenderer->SetScaleModeImage();
		RightTopLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 1045, -90, (int)ZOrder::NPC - 4 });
		RightTopLaserMachineBackerRenderer->GetTransform().PixLocalNegativeX();
		RightTopLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* RightMidLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserMidBackerStart", 0.05f, false));
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserMidShootingBacker", 0.05f, false));
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserMidBackerEnd", 0.05f, false));
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		RightMidLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		RightMidLaserMachineBackerRenderer->SetScaleModeImage();
		RightMidLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 1000, -300, (int)ZOrder::NPC - 4 });
		RightMidLaserMachineBackerRenderer->GetTransform().PixLocalNegativeX();
		RightMidLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* RightLowLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserLowBackerStart", 0.05f, false));
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserLowShootingBacker", 0.05f, false));
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserLowBackerEnd", 0.05f, false));
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		RightLowLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		RightLowLaserMachineBackerRenderer->SetScaleModeImage();
		RightLowLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 1120, -560, (int)ZOrder::NPC - 4 });
		RightLowLaserMachineBackerRenderer->GetTransform().PixLocalNegativeX();
		RightLowLaserMachineBackerRenderer->Off();

		LaserMachineBackerRenderers.push_back(LeftTopLaserMachineBackerRenderer);
		LaserMachineBackerRenderers.push_back(RightTopLaserMachineBackerRenderer);
		LaserMachineBackerRenderers.push_back(LeftMidLaserMachineBackerRenderer);
		LaserMachineBackerRenderers.push_back(RightMidLaserMachineBackerRenderer);
		LaserMachineBackerRenderers.push_back(LeftLowLaserMachineBackerRenderer);
		LaserMachineBackerRenderers.push_back(RightLowLaserMachineBackerRenderer);
	}

	{
		GameEngineTextureRenderer* LeftTopPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTop", 0.05f, false));
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftTopPadBackRenderer->SetScaleModeImage();
		LeftTopPadBackRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 5 });
		LeftTopPadBackRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMid", 0.05f, false));
		LeftMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftMidPadBackRenderer->SetScaleModeImage();
		LeftMidPadBackRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 5 });
		LeftMidPadBackRenderer->Off();

		GameEngineTextureRenderer* LeftLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLow", 0.05f, false));
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftLowPadBackRenderer->SetScaleModeImage();
		LeftLowPadBackRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 5 });
		LeftLowPadBackRenderer->Off();

		GameEngineTextureRenderer* RightTopPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTop", 0.05f, false));
		RightTopPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightTopPadBackRenderer->SetScaleModeImage();
		RightTopPadBackRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 5 });
		RightTopPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadBackRenderer->Off();

		GameEngineTextureRenderer* RightMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMid", 0.05f, false));
		RightMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightMidPadBackRenderer->SetScaleModeImage();
		RightMidPadBackRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 5 });
		RightMidPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadBackRenderer->Off();

		GameEngineTextureRenderer* RightLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLow", 0.05f, false));
		RightLowPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightLowPadBackRenderer->SetScaleModeImage();
		RightLowPadBackRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 5 });
		RightLowPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightLowPadBackRenderer->Off();

		GameEngineTextureRenderer* LeftTopMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTopMid", 0.05f, false));
		LeftTopMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftTopMidPadBackRenderer->SetScaleModeImage();
		LeftTopMidPadBackRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 5 });
		LeftTopMidPadBackRenderer->Off();

		GameEngineTextureRenderer* RightTopMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTopMid", 0.05f, false));
		RightTopMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightTopMidPadBackRenderer->SetScaleModeImage();
		RightTopMidPadBackRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 5 });
		RightTopMidPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightTopMidPadBackRenderer->Off();

		PadBackRenderers.push_back(LeftTopPadBackRenderer);
		PadBackRenderers.push_back(RightTopPadBackRenderer);
		PadBackRenderers.push_back(LeftMidPadBackRenderer);
		PadBackRenderers.push_back(RightMidPadBackRenderer);
		PadBackRenderers.push_back(LeftLowPadBackRenderer);
		PadBackRenderers.push_back(RightLowPadBackRenderer);
		PadBackRenderers.push_back(LeftTopMidPadBackRenderer);
		PadBackRenderers.push_back(RightTopMidPadBackRenderer);
	}


	{
		GameEngineTextureRenderer* LeftTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("TopPadOpen", 0.05f, true)); // 패드 열리기
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("TopPadOpen", 3, 3, 0.1f, false)); // 열린 상태 Idle 
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("TopPadClose", 0.05f, true)); // 패드 닫히기
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, true)); // 패드 닫히기
		LeftTopPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopPadRenderer->AnimationBindFrame("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameChanged, this, std::placeholders::_1));
		LeftTopPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftTopPadRenderer->SetScaleModeImage();
		LeftTopPadRenderer->GetTransform().SetLocalPosition({ 194, -148, (int)ZOrder::NPC - 6 });
		LeftTopPadRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("MidPadOpen", 0.05f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("MidPadOpen", 2, 2, 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("MidPadClose", 0.05f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidPadRenderer->AnimationBindFrame("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameChanged, this, std::placeholders::_1));
		LeftMidPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftMidPadRenderer->GetTransform().SetLocalPosition({ 130, -353, (int)ZOrder::NPC - 6 });
		LeftMidPadRenderer->SetScaleModeImage();
		LeftMidPadRenderer->Off();

		GameEngineTextureRenderer* LeftLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("LowPadOpen", 0.05f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadOPenIdle", FrameAnimation_DESC("LowPadOPen", 2, 2, 0.1f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("LowPadClose", 0.05f, false));
		LeftLowPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowPadRenderer->AnimationBindFrame("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameChanged, this, std::placeholders::_1));
		LeftLowPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftLowPadRenderer->GetTransform().SetLocalPosition({ 180, -565, (int)ZOrder::NPC - 6 });
		LeftLowPadRenderer->SetScaleModeImage();
		LeftLowPadRenderer->Off();

		GameEngineTextureRenderer* RightTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("TopPadOpen", 0.05f, true)); // 패드 열리기
		RightTopPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("TopPadOpen", 3, 3, 0.1f, false)); // 열린 상태 Idle 
		RightTopPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("TopPadClose", 0.05f, true)); // 패드 닫히기
		RightTopPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, true)); // 패드 닫히기
		RightTopPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightTopPadRenderer->AnimationBindFrame("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameChanged, this, std::placeholders::_1));
		RightTopPadRenderer->ChangeFrameAnimation("PadOpen");
		RightTopPadRenderer->SetScaleModeImage();
		RightTopPadRenderer->GetTransform().SetLocalPosition({ 1109, -128, (int)ZOrder::NPC - 6 });
		RightTopPadRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadRenderer->Off();

		GameEngineTextureRenderer* RightMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("MidPadOpen", 0.05f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("MidPadOpen", 2, 2, 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("MidPadClose", 0.05f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightMidPadRenderer->AnimationBindFrame("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameChanged, this, std::placeholders::_1));
		RightMidPadRenderer->ChangeFrameAnimation("PadOpen");
		RightMidPadRenderer->SetScaleModeImage();
		RightMidPadRenderer->GetTransform().SetLocalPosition({ 1175, -330, (int)ZOrder::NPC - 6 });
		RightMidPadRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadRenderer->Off();

		GameEngineTextureRenderer* RightLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("LowPadOpen", 0.05f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("PadOPenIdle", FrameAnimation_DESC("LowPadOPen", 2, 2, 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("LowPadClose", 0.05f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		RightLowPadRenderer->AnimationBindFrame("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameChanged, this, std::placeholders::_1));
		RightLowPadRenderer->ChangeFrameAnimation("PadOpen");
		RightLowPadRenderer->GetTransform().SetLocalPosition({ 1127, -550, (int)ZOrder::NPC - 6 });
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
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserTop", 0.05f, true)); // 레이저 기기 왼쪽 위 생성
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserTopWarning", 0.05f, true)); // 레이저 기기 경고
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserTopShooting", 0.05f, true)); // 레이저 기기 슈팅
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserTopClose", 0.05f, false)); // 레이저 기기 제거
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftTopLaserMachineRenderer->AnimationBindFrame("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameChanged, this, std::placeholders::_1));
		LeftTopLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftTopLaserMachineRenderer->SetScaleModeImage();
		LeftTopLaserMachineRenderer->GetTransform().SetLocalPosition({ 260, -90, (int)ZOrder::NPC - 7 });
		LeftTopLaserMachineRenderer->Off();

		GameEngineTextureRenderer* LeftMidLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserMid", 0.05f, true)); // 레이저 기기 왼쪽 위 생성
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserMidShooting", 0.05f, true)); // 레이저 기기 슈팅
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserMidShooting", 0.05f, true)); // 레이저 기기 슈팅
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserMidClose", 0.05f, false)); // 레이저 기기 제거
		LeftMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftMidLaserMachineRenderer->AnimationBindFrame("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameChanged, this, std::placeholders::_1));
		LeftMidLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftMidLaserMachineRenderer->SetScaleModeImage();
		LeftMidLaserMachineRenderer->GetTransform().SetLocalPosition({ 320, -300, (int)ZOrder::NPC - 7 });
		LeftMidLaserMachineRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserLow", 0.05f, true)); // 레이저 기기 왼쪽 위 생성
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserLowWarning", 0.05f, true)); // 레이저 기기 경고
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserLowShooting", 0.05f, true)); // 레이저 기기 슈팅
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserLowClose", 0.05f, false)); // 레이저 기기 제거
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftLowLaserMachineRenderer->AnimationBindFrame("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameChanged, this, std::placeholders::_1));
		LeftLowLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftLowLaserMachineRenderer->SetScaleModeImage();
		LeftLowLaserMachineRenderer->GetTransform().SetLocalPosition({ 200, -550, (int)ZOrder::NPC - 7 });
		LeftLowLaserMachineRenderer->Off();

		GameEngineTextureRenderer* RightTopLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserTop", 0.05f, true)); // 레이저 기기 왼쪽 위 생성
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserTopWarning", 0.05f, true)); // 레이저 기기 경고
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserTopShooting", 0.05f, true)); // 레이저 기기 슈팅
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserTopClose", 0.05f, false)); // 레이저 기기 제거
		RightTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		RightTopLaserMachineRenderer->AnimationBindFrame("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameChanged, this, std::placeholders::_1));
		RightTopLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		RightTopLaserMachineRenderer->SetScaleModeImage();
		RightTopLaserMachineRenderer->GetTransform().SetLocalPosition({ 1044, -90, (int)ZOrder::NPC - 7 });
		RightTopLaserMachineRenderer->GetTransform().PixLocalNegativeX();
		RightTopLaserMachineRenderer->Off();

		GameEngineTextureRenderer* RightMidLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserMid", 0.05f, true)); // 레이저 기기 왼쪽 위 생성
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserMidShooting", 0.05f, true)); // 레이저 기기 슈팅
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserMidShooting", 0.05f, true)); // 레이저 기기 슈팅
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserMidClose", 0.05f, false)); // 레이저 기기 제거
		RightMidLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		RightMidLaserMachineRenderer->AnimationBindFrame("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameChanged, this, std::placeholders::_1));
		RightMidLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		RightMidLaserMachineRenderer->SetScaleModeImage();
		RightMidLaserMachineRenderer->GetTransform().SetLocalPosition({ 1000, -300, (int)ZOrder::NPC - 7 });
		RightMidLaserMachineRenderer->GetTransform().PixLocalNegativeX();
		RightMidLaserMachineRenderer->Off();

		GameEngineTextureRenderer* RightLowLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserLow", 0.05f, true)); // 레이저 기기 왼쪽 위 생성
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserLowWarning", 0.05f, true)); // 레이저 기기 경고
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserLowShooting", 0.05f, true)); // 레이저 기기 슈팅
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserLowClose", 0.05f, false)); // 레이저 기기 제거
		RightLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		RightLowLaserMachineRenderer->AnimationBindFrame("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameChanged, this, std::placeholders::_1));
		RightLowLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		RightLowLaserMachineRenderer->SetScaleModeImage();
		RightLowLaserMachineRenderer->GetTransform().SetLocalPosition({ 1120, -560, (int)ZOrder::NPC - 7 });
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
		GameEngineTextureRenderer* LeftTopLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningA", 0.05f, true));
		LeftTopLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamTop", 0.05f, true));
		LeftTopLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftTopLaserRenderer->SetScaleModeImage();
		LeftTopLaserRenderer->GetTransform().SetLocalPosition({ 390, -135, (int)ZOrder::NPC - 8 });
		LeftTopLaserRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		LeftTopLaserRenderer->Off();

		GameEngineTextureRenderer* LeftMidLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningB", 0.05f, false));
		LeftMidLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamMid", 0.05f, false));
		LeftMidLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftMidLaserRenderer->SetScaleModeImage();
		LeftMidLaserRenderer->GetTransform().SetLocalPosition({ 175, -100, (int)ZOrder::NPC - 6 });
		LeftMidLaserRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		LeftMidLaserRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningC", 0.05f, false));
		LeftLowLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamLow", 0.05f, false));
		LeftLowLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftLowLaserRenderer->SetScaleModeImage();
		LeftLowLaserRenderer->GetTransform().SetLocalPosition({ 230, -440, (int)ZOrder::NPC - 6 });
		LeftLowLaserRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		LeftLowLaserRenderer->Off();

		GameEngineTextureRenderer* RightTopLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningA", 0.05f, true));
		RightTopLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamTop", 0.05f, true));
		RightTopLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserRenderer->ChangeFrameAnimation("LaserWarning");
		RightTopLaserRenderer->SetScaleModeImage();
		RightTopLaserRenderer->GetTransform().SetLocalPosition({ 110, -130, (int)ZOrder::NPC - 8 });
		RightTopLaserRenderer->GetTransform().PixLocalNegativeX();
		RightTopLaserRenderer->SetPivot(PIVOTMODE::RIGHTTOP);
		RightTopLaserRenderer->Off();

		GameEngineTextureRenderer* RightMidLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningB", 0.05f, false));
		RightMidLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamMid", 0.05f, false));
		RightMidLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserRenderer->ChangeFrameAnimation("LaserWarning");
		RightMidLaserRenderer->SetScaleModeImage();
		RightMidLaserRenderer->GetTransform().SetLocalPosition({ 290, -110, (int)ZOrder::NPC - 6 });
		RightMidLaserRenderer->GetTransform().PixLocalNegativeX();
		RightMidLaserRenderer->SetPivot(PIVOTMODE::RIGHTTOP);
		RightMidLaserRenderer->Off();

		GameEngineTextureRenderer* RightLowLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningC", 0.05f, false));
		RightLowLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamLow", 0.05f, false));
		RightLowLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserRenderer->ChangeFrameAnimation("LaserWarning");
		RightLowLaserRenderer->SetScaleModeImage();
		RightLowLaserRenderer->GetTransform().SetLocalPosition({ 230, -440, (int)ZOrder::NPC - 6 });
		RightLowLaserRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		RightLowLaserRenderer->Off();

		LaserRenderers.push_back(LeftTopLaserRenderer);
		LaserRenderers.push_back(RightTopLaserRenderer);
		LaserRenderers.push_back(LeftMidLaserRenderer);
		LaserRenderers.push_back(RightMidLaserRenderer);
		LaserRenderers.push_back(LeftLowLaserRenderer);
		LaserRenderers.push_back(RightLowLaserRenderer);

		GameEngineCollision* LeftTopLaserRendererCollision0 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision0->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision0->GetTransform().SetLocalPosition({ 516, -250, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision0->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision0->Off();

		GameEngineCollision* LeftTopLaserRendererCollision1 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision1->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision1->GetTransform().SetLocalPosition({ 570, -300, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision1->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision1->Off();

		GameEngineCollision* LeftTopLaserRendererCollision2 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision2->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision2->GetTransform().SetLocalPosition({ 636, -350, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision2->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision2->Off();

		GameEngineCollision* LeftTopLaserRendererCollision3 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision3->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision3->GetTransform().SetLocalPosition({ 666, -400, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision3->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision3->Off();

		GameEngineCollision* LeftTopLaserRendererCollision4 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision4->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision4->GetTransform().SetLocalPosition({ 736, -450, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision4->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision4->Off();

		GameEngineCollision* LeftTopLaserRendererCollision5 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision5->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision5->GetTransform().SetLocalPosition({ 796, -500, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision5->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision5->Off();

		GameEngineCollision* LeftTopLaserRendererCollision6 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision6->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision6->GetTransform().SetLocalPosition({ 856, -550, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision6->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision6->Off();

		GameEngineCollision* LeftTopLaserRendererCollision7 = CreateComponent<GameEngineCollision>();
		LeftTopLaserRendererCollision7->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftTopLaserRendererCollision7->GetTransform().SetLocalPosition({ 906, -600, (int)ZOrder::NPC - 8 });
		LeftTopLaserRendererCollision7->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftTopLaserRendererCollision7->Off();

		GameEngineCollision* LeftMidLaserRendererCollision0 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision0->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision0->GetTransform().SetLocalPosition({ 333, -250, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision0->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision0->Off();

		GameEngineCollision* LeftMidLaserRendererCollision1 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision1->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision1->GetTransform().SetLocalPosition({ 383, -300, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision1->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision1->Off();

		GameEngineCollision* LeftMidLaserRendererCollision2 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision2->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision2->GetTransform().SetLocalPosition({ 433, -350, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision2->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision2->Off();

		GameEngineCollision* LeftMidLaserRendererCollision3 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision3->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision3->GetTransform().SetLocalPosition({ 503, -400, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision3->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision3->Off();

		GameEngineCollision* LeftMidLaserRendererCollision4 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision4->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision4->GetTransform().SetLocalPosition({ 543, -450, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision4->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision4->Off();

		GameEngineCollision* LeftMidLaserRendererCollision5 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision5->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision5->GetTransform().SetLocalPosition({ 608, -500, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision5->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision5->Off();

		GameEngineCollision* LeftMidLaserRendererCollision6 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision6->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision6->GetTransform().SetLocalPosition({ 653, -550, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision6->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision6->Off();

		GameEngineCollision* LeftMidLaserRendererCollision7 = CreateComponent<GameEngineCollision>();
		LeftMidLaserRendererCollision7->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		LeftMidLaserRendererCollision7->GetTransform().SetLocalPosition({ 718, -600, (int)ZOrder::NPC - 8 });
		LeftMidLaserRendererCollision7->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftMidLaserRendererCollision7->Off();

		GameEngineCollision* RightTopLaserRendererCollision0 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision0->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision0->GetTransform().SetLocalPosition({ 705.0f, -315, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision0->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision0->Off();

		GameEngineCollision* RightTopLaserRendererCollision1 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision1->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision1->GetTransform().SetLocalPosition({ 655.0f, -355, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision1->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision1->Off();

		GameEngineCollision* RightTopLaserRendererCollision2 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision2->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision2->GetTransform().SetLocalPosition({ 605.0f, -400, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision2->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision2->Off();

		GameEngineCollision* RightTopLaserRendererCollision3 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision3->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision3->GetTransform().SetLocalPosition({ 555.0f, -445, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision3->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision3->Off();

		GameEngineCollision* RightTopLaserRendererCollision4 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision4->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision4->GetTransform().SetLocalPosition({ 505.0f, -480, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision4->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision4->Off();

		GameEngineCollision* RightTopLaserRendererCollision5 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision5->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision5->GetTransform().SetLocalPosition({ 455.0f, -525, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision5->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision5->Off();

		GameEngineCollision* RightTopLaserRendererCollision6 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision6->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision6->GetTransform().SetLocalPosition({ 415.0f, -555, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision6->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision6->Off();

		GameEngineCollision* RightTopLaserRendererCollision7 = CreateComponent<GameEngineCollision>();
		RightTopLaserRendererCollision7->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightTopLaserRendererCollision7->GetTransform().SetLocalPosition({ 395.0f, -575, (int)ZOrder::NPC - 8 });
		RightTopLaserRendererCollision7->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightTopLaserRendererCollision7->Off();

		GameEngineCollision* RightMidLaserRendererCollision0 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision0->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision0->GetTransform().SetLocalPosition({ 905.0f, -310, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision0->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision0->Off();

		GameEngineCollision* RightMidLaserRendererCollision1 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision1->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision1->GetTransform().SetLocalPosition({ 855.0f, -360, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision1->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision1->Off();

		GameEngineCollision* RightMidLaserRendererCollision2 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision2->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision2->GetTransform().SetLocalPosition({ 800.0f, -410, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision2->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision2->Off();

		GameEngineCollision* RightMidLaserRendererCollision3 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision3->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision3->GetTransform().SetLocalPosition({ 745.0f, -460, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision3->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision3->Off();

		GameEngineCollision* RightMidLaserRendererCollision4 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision4->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision4->GetTransform().SetLocalPosition({ 695.0f, -510, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision4->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision4->Off();

		GameEngineCollision* RightMidLaserRendererCollision5 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision5->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision5->GetTransform().SetLocalPosition({ 640.0f, -560, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision5->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision5->Off();

		GameEngineCollision* RightMidLaserRendererCollision6 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision6->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision6->GetTransform().SetLocalPosition({ 585.0f, -610, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision6->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision6->Off();

		GameEngineCollision* RightMidLaserRendererCollision7 = CreateComponent<GameEngineCollision>();
		RightMidLaserRendererCollision7->GetTransform().SetLocalScale({ 10.0f, 10.0f, 1.0f });
		RightMidLaserRendererCollision7->GetTransform().SetLocalPosition({ 515.0f, -660, (int)ZOrder::NPC - 8 });
		RightMidLaserRendererCollision7->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		RightMidLaserRendererCollision7->Off();

		GameEngineCollision* LeftLowLaserRendererCollision = CreateComponent<GameEngineCollision>();
		LeftLowLaserRendererCollision->GetTransform().SetLocalScale({ 1000.0f, 10.0f, 1.0f });
		LeftLowLaserRendererCollision->GetTransform().SetLocalPosition({ 600, -520, (int)ZOrder::NPC - 8 });
		LeftLowLaserRendererCollision->ChangeOrder(ObjectOrder::MONSTER_BULLET);
		LeftLowLaserRendererCollision->Off();

		LaserCollision0.push_back(LeftTopLaserRendererCollision0);
		LaserCollision0.push_back(LeftTopLaserRendererCollision1);
		LaserCollision0.push_back(LeftTopLaserRendererCollision2);
		LaserCollision0.push_back(LeftTopLaserRendererCollision3);
		LaserCollision0.push_back(LeftTopLaserRendererCollision4);
		LaserCollision0.push_back(LeftTopLaserRendererCollision5);
		LaserCollision0.push_back(LeftTopLaserRendererCollision6);
		LaserCollision0.push_back(LeftTopLaserRendererCollision7);

		LaserCollision1.push_back(RightTopLaserRendererCollision0);
		LaserCollision1.push_back(RightTopLaserRendererCollision1);
		LaserCollision1.push_back(RightTopLaserRendererCollision2);
		LaserCollision1.push_back(RightTopLaserRendererCollision3);
		LaserCollision1.push_back(RightTopLaserRendererCollision4);
		LaserCollision1.push_back(RightTopLaserRendererCollision5);
		LaserCollision1.push_back(RightTopLaserRendererCollision6);
		LaserCollision1.push_back(RightTopLaserRendererCollision7);

		LaserCollision2.push_back(LeftMidLaserRendererCollision0);
		LaserCollision2.push_back(LeftMidLaserRendererCollision1);
		LaserCollision2.push_back(LeftMidLaserRendererCollision2);
		LaserCollision2.push_back(LeftMidLaserRendererCollision3);
		LaserCollision2.push_back(LeftMidLaserRendererCollision4);
		LaserCollision2.push_back(LeftMidLaserRendererCollision5);
		LaserCollision2.push_back(LeftMidLaserRendererCollision6);
		LaserCollision2.push_back(LeftMidLaserRendererCollision7);

		LaserCollision3.push_back(RightMidLaserRendererCollision0);
		LaserCollision3.push_back(RightMidLaserRendererCollision1);
		LaserCollision3.push_back(RightMidLaserRendererCollision2);
		LaserCollision3.push_back(RightMidLaserRendererCollision3);
		LaserCollision3.push_back(RightMidLaserRendererCollision4);
		LaserCollision3.push_back(RightMidLaserRendererCollision5);
		LaserCollision3.push_back(RightMidLaserRendererCollision6);
		LaserCollision3.push_back(RightMidLaserRendererCollision7);

		LaserCollision4.push_back(LeftLowLaserRendererCollision);

		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetWorldScale({ 150.0f,100.0f,1.0f });
		Collision->GetTransform().SetLocalPosition({ 640.0f, -300.0f });
		Collision->ChangeOrder(ObjectOrder::MONSTER);
		Collision->Off();

		{
			GameEngineCollision* LaserBodyCollision = CreateComponent<GameEngineCollision>();
			LaserBodyCollision->GetTransform().SetWorldScale({ 100.0f, 100.0f,1.0f });
			LaserBodyCollision->GetTransform().SetLocalPosition({ 300.0f, -154.0f });
			LaserBodyCollision->ChangeOrder(ObjectOrder::MONSTER);
			LaserBodyCollision->Off();
			LaserBodyCollisions.push_back(LaserBodyCollision);
		}

		{
			GameEngineCollision* LaserBodyCollision = CreateComponent<GameEngineCollision>();
			LaserBodyCollision->GetTransform().SetWorldScale({ 100.0f,100.0f,1.0f });
			LaserBodyCollision->GetTransform().SetLocalPosition({ 1000.0f, -133.0f });
			LaserBodyCollision->ChangeOrder(ObjectOrder::MONSTER);
			LaserBodyCollision->Off();
			LaserBodyCollisions.push_back(LaserBodyCollision);
		}

		{
			GameEngineCollision* LaserBodyCollision = CreateComponent<GameEngineCollision>();
			LaserBodyCollision->GetTransform().SetWorldScale({ 100.0f,100.0f,1.0f });
			LaserBodyCollision->GetTransform().SetLocalPosition({ 300.0f, -363.0f });
			LaserBodyCollision->ChangeOrder(ObjectOrder::MONSTER);
			LaserBodyCollision->Off();
			LaserBodyCollisions.push_back(LaserBodyCollision);
		}

		{
			GameEngineCollision* LaserBodyCollision = CreateComponent<GameEngineCollision>();
			LaserBodyCollision->GetTransform().SetWorldScale({ 100.0f,100.0f,1.0f });
			LaserBodyCollision->GetTransform().SetLocalPosition({ 1000.0f, -345.0f });
			LaserBodyCollision->ChangeOrder(ObjectOrder::MONSTER);
			LaserBodyCollision->Off();
			LaserBodyCollisions.push_back(LaserBodyCollision);
		}

		{
			GameEngineCollision* LaserBodyCollision = CreateComponent<GameEngineCollision>();
			LaserBodyCollision->GetTransform().SetWorldScale({ 100.0f,100.0f,1.0f });
			LaserBodyCollision->GetTransform().SetLocalPosition({ 250.0f, -608.0f });
			LaserBodyCollision->ChangeOrder(ObjectOrder::MONSTER);
			LaserBodyCollision->Off();
			LaserBodyCollisions.push_back(LaserBodyCollision);
		}

		{
			GameEngineCollision* LaserBodyCollision = CreateComponent<GameEngineCollision>();
			LaserBodyCollision->GetTransform().SetWorldScale({ 100.0f,100.0f,1.0f });
			LaserBodyCollision->GetTransform().SetLocalPosition({ 1000.0f, -589.0f });
			LaserBodyCollision->ChangeOrder(ObjectOrder::MONSTER);
			LaserBodyCollision->Off();
			LaserBodyCollisions.push_back(LaserBodyCollision);
		}
	}

	srand(time(NULL));

	for (GameEngineTextureRenderer* Renderer : PadRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}
	for (GameEngineTextureRenderer* Renderer : LaserMachineRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}	
	for (GameEngineTextureRenderer* Renderer : LaserMachineBackerRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}	
	for (GameEngineTextureRenderer* Renderer : PadBackRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}	
	for (GameEngineTextureRenderer* Renderer : PadBackBackerRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}	
	for (GameEngineTextureRenderer* Renderer : LaserRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}	
	for (GameEngineTextureRenderer* Renderer : AuraRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}
	for (GameEngineTextureRenderer* Renderer : MachineTeethRenderers)
	{
		GetLevel()->PushRendererToRotateCamera2(Renderer);
	}

}

void DogCopterShooter::End()
{
}

void DogCopterShooter::OnMonsterStateChanged(InGameMonsterState _State)
{
	//MonsterWeaponBase::OnMonsterStateChanged(_State);

	if (_State == InGameMonsterState::Attack1)
	{
		if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
		{
			Parent->SetAttackState(InGameMonsterAttackState::LaserPattern1);
		}
	}
	else if (_State == InGameMonsterState::Attack2)
	{
		if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
		{
			Parent->SetAttackState(InGameMonsterAttackState::DogBowl);
			Collision->On();
		}
	}
}

void DogCopterShooter::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	//MonsterWeaponBase::OnMonsterAttackStateChanged(_AttackState);

	if (_AttackState == InGameMonsterAttackState::LaserPattern1 ||
		_AttackState == InGameMonsterAttackState::LaserPattern2)
	{
		int RandomAttackCount = (rand() % 2) + 1;
		FirstIdx = rand() % 4;
		SecondIdx = RandomAttackCount == 1 ? -1 : rand() % 4;
		while (RandomAttackCount == 2 && SecondIdx == FirstIdx)
		{
			SecondIdx = rand() % 4;
		}

		for (int i = 0; i < RandomAttackCount; ++i)
		{
			int Idx = i == 0 ? FirstIdx : SecondIdx;
			LaserMachineBackerRenderers[Idx]->On();
			LaserMachineBackerRenderers[Idx]->ChangeFrameAnimation("LaserBackerStart");
			LaserBodyCollisions[Idx]->On();

			PadRenderers[Idx]->On();
			PadRenderers[Idx]->ChangeFrameAnimation("PadOpen");
			if ((FirstIdx == 0 && SecondIdx == 2) || (FirstIdx == 2 && SecondIdx == 0))
			{
				PadBackRenderers[6]->On();
			}
			else if ((FirstIdx == 1 && SecondIdx == 3) || (FirstIdx == 3 && SecondIdx == 1))
			{
				PadBackRenderers[7]->On();
			}
			else
			{
				PadBackRenderers[Idx]->On();
			}

			PadBackBackerRenderers[Idx]->ChangeFrameAnimation("PadBackHole");
			PadBackBackerRenderers[Idx]->On();
		}
	}
	else if (_AttackState == InGameMonsterAttackState::LaserPattern3)
	{
		PadRenderers[4]->On();
		PadRenderers[4]->ChangeFrameAnimation("PadOpen");
		PadBackBackerRenderers[4]->ChangeFrameAnimation("PadBackHole");
		PadBackBackerRenderers[4]->On();
		PadBackRenderers[4]->On();
		LaserMachineRenderers[4]->On();
		LaserMachineRenderers[4]->ChangeFrameAnimation("LaserPrepare");
		LaserBodyCollisions[4]->On();

		PadRenderers[5]->On();
		PadRenderers[5]->ChangeFrameAnimation("PadOpen");
		PadBackBackerRenderers[5]->ChangeFrameAnimation("PadBackHole");
		PadBackBackerRenderers[5]->On();
		PadBackRenderers[5]->On();
		LaserMachineRenderers[5]->On();
		LaserMachineRenderers[5]->ChangeFrameAnimation("LaserPrepare");
		LaserBodyCollisions[5]->On();
	}
}

void DogCopterShooter::UpdatePivot()
{

}

CollisionReturn DogCopterShooter::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (CanTakeDamgageTime > 0.5f)
	{
		SetHP(GetHP() - 1);
		CanTakeDamgageTime = 0.0f;
	}
	return CollisionReturn::Break;
}

void DogCopterShooter::Update(float _DeltaTime)
{
	CanTakeDamgageTime += _DeltaTime;
	if (GetHP() <= 0)
	{
		if (DogCopter* Boss = dynamic_cast<DogCopter*>(GetParent()))
		{
			if (Boss->GetState() == InGameMonsterState::Idle)
			{
				DieTime += _DeltaTime;
				if (DieTime > 0.3)
				{
					Boss->SetState(InGameMonsterState::Die);
				}
			}
		}
	}

	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopterShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	LaserBodyCollisions[0]->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopterShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	LaserBodyCollisions[1]->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopterShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	LaserBodyCollisions[2]->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopterShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	LaserBodyCollisions[3]->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopterShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	LaserBodyCollisions[4]->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopterShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	LaserBodyCollisions[5]->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopterShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
}

void DogCopterShooter::OnLaserAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (_Info.CurFrame == 13)
		{
			GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P3_DogCopter_Laser_PreFire_Warning.wav");
			if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
			{
				LaserMachineRenderers[4]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[4]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[4]->On();
				LaserMachineRenderers[5]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[5]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[5]->On();
			}
			else
			{
				LaserMachineRenderers[FirstIdx]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[FirstIdx]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[FirstIdx]->On();
				if (FirstIdx == 0 ||
					FirstIdx == 1)
				{
					AuraRenderers[FirstIdx]->On();
					AuraRenderers[FirstIdx]->ChangeFrameAnimation("LaserAura");
					MachineTeethRenderers[FirstIdx]->On();
					MachineTeethRenderers[FirstIdx]->ChangeFrameAnimation("LaserTeeth");
				}

				if (SecondIdx != -1)
				{
					LaserMachineRenderers[SecondIdx]->ChangeFrameAnimation("LaserWarning");
					LaserRenderers[SecondIdx]->ChangeFrameAnimation("LaserWarning");
					LaserRenderers[SecondIdx]->On();
					if (SecondIdx == 0 ||
						SecondIdx == 1)
					{
						AuraRenderers[SecondIdx]->On();
						AuraRenderers[SecondIdx]->ChangeFrameAnimation("LaserAura");
						MachineTeethRenderers[SecondIdx]->On();
						MachineTeethRenderers[SecondIdx]->ChangeFrameAnimation("LaserTeeth");
					}
				}
			}
		}
	}
}

void DogCopterShooter::OnPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			PadRenderers[4]->ChangeFrameAnimation("PadOpenIdle");
			PadRenderers[5]->ChangeFrameAnimation("PadOpenIdle");
		}
		else
		{
			PadRenderers[FirstIdx]->ChangeFrameAnimation("PadOpenIdle");
			if (SecondIdx != -1)
			{
				PadRenderers[SecondIdx]->ChangeFrameAnimation("PadOpenIdle");
			}
		}
	}
}

void DogCopterShooter::OnPadCloseAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			PadRenderers[4]->ChangeFrameAnimation("PadRendererNothing");
			PadRenderers[4]->Off();
			PadBackRenderers[4]->Off();
			PadBackBackerRenderers[4]->ChangeFrameAnimation("Nothing");
			PadBackBackerRenderers[4]->Off();
			PadRenderers[5]->ChangeFrameAnimation("PadRendererNothing");
			PadRenderers[5]->Off();
			PadBackRenderers[5]->Off();
			PadBackBackerRenderers[5]->ChangeFrameAnimation("Nothing");
			PadBackBackerRenderers[5]->Off();

			Parent->SetState(InGameMonsterState::BeforeRotateCameraIn);
		}
		else
		{
			PadRenderers[FirstIdx]->ChangeFrameAnimation("PadRendererNothing");
			PadRenderers[FirstIdx]->Off();
			if ((FirstIdx == 0 && SecondIdx == 2) || (FirstIdx == 2 && SecondIdx == 0))
			{
				PadBackRenderers[6]->Off();
			}
			else if ((FirstIdx == 1 && SecondIdx == 3) || (FirstIdx == 3 && SecondIdx == 1))
			{
				PadBackRenderers[7]->Off();
			}
			else
			{
				PadBackRenderers[FirstIdx]->Off();
			}
			PadBackBackerRenderers[FirstIdx]->ChangeFrameAnimation("Nothing");
			PadBackBackerRenderers[FirstIdx]->Off();

			if (SecondIdx != -1)
			{
				PadRenderers[SecondIdx]->ChangeFrameAnimation("PadRendererNothing");
				PadRenderers[SecondIdx]->Off();
				if ((FirstIdx == 0 && SecondIdx == 2) || (FirstIdx == 2 && SecondIdx == 0))
				{
					PadBackRenderers[6]->Off();
				}
				else if ((FirstIdx == 1 && SecondIdx == 3) || (FirstIdx == 3 && SecondIdx == 1))
				{
					PadBackRenderers[7]->Off();
				}
				else
				{
					PadBackRenderers[SecondIdx]->Off();
				}
				PadBackBackerRenderers[SecondIdx]->ChangeFrameAnimation("Nothing");
				PadBackBackerRenderers[SecondIdx]->Off();
			}

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

void DogCopterShooter::OnLaserBackerAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			LaserMachineBackerRenderers[4]->ChangeFrameAnimation("Nothing");
			LaserMachineBackerRenderers[5]->ChangeFrameAnimation("Nothing");
		}
		else
		{
			LaserMachineBackerRenderers[FirstIdx]->ChangeFrameAnimation("Nothing");
			if (SecondIdx != -1)
			{
				LaserMachineBackerRenderers[SecondIdx]->ChangeFrameAnimation("Nothing");
			}
		}
	}
}

void DogCopterShooter::OnLaserBackerAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			if (_Info.CurFrame == 1)
			{
				LaserMachineRenderers[4]->On();
				LaserMachineRenderers[4]->ChangeFrameAnimation("LaserPrepare");

				LaserMachineRenderers[5]->On();
				LaserMachineRenderers[5]->ChangeFrameAnimation("LaserPrepare");
			}
		}
		else
		{
			if (_Info.CurFrame == 2)
			{
				LaserMachineRenderers[FirstIdx]->On();
				LaserMachineRenderers[FirstIdx]->ChangeFrameAnimation("LaserPrepare");
			}

			if (SecondIdx != -1)
			{
				if (_Info.CurFrame == 1)
				{
					LaserMachineRenderers[SecondIdx]->On();
					LaserMachineRenderers[SecondIdx]->ChangeFrameAnimation("LaserPrepare");
				}
			}
		}
	}

}

void DogCopterShooter::OnLaserAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			LaserMachineRenderers[4]->ChangeFrameAnimation("LaserWarning");
			LaserRenderers[4]->ChangeFrameAnimation("LaserWarning");
			LaserRenderers[4]->On();
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserWarning");
			LaserRenderers[5]->ChangeFrameAnimation("LaserWarning");
			LaserRenderers[5]->On();
		}
		else
		{
			LaserMachineRenderers[FirstIdx]->ChangeFrameAnimation("LaserWarning");
			LaserRenderers[FirstIdx]->ChangeFrameAnimation("LaserWarning");
			LaserRenderers[FirstIdx]->On();
			if (FirstIdx == 0 ||
				FirstIdx == 1)
			{
				AuraRenderers[FirstIdx]->On();
				AuraRenderers[FirstIdx]->ChangeFrameAnimation("LaserAura");
				MachineTeethRenderers[FirstIdx]->On();
				MachineTeethRenderers[FirstIdx]->ChangeFrameAnimation("LaserTeeth");
			}

			if (SecondIdx != -1)
			{
				LaserMachineRenderers[SecondIdx]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[SecondIdx]->ChangeFrameAnimation("LaserWarning");
				LaserRenderers[SecondIdx]->On();
				if (SecondIdx == 0 ||
					SecondIdx == 1)
				{
					AuraRenderers[SecondIdx]->On();
					AuraRenderers[SecondIdx]->ChangeFrameAnimation("LaserAura");
					MachineTeethRenderers[SecondIdx]->On();
					MachineTeethRenderers[SecondIdx]->ChangeFrameAnimation("LaserTeeth");
				}
			}
		}
	}
}

void DogCopterShooter::OnLaserWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P3_DogCopter_Laser_Fire_01.wav");
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			LaserMachineRenderers[4]->ChangeFrameAnimation("LaserShooting");
			LaserRenderers[4]->ChangeFrameAnimation("LaserBeam");
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserShooting");
			LaserRenderers[5]->ChangeFrameAnimation("LaserBeam");
			LaserCollision4[0]->On();
		}
		else
		{
			LaserMachineRenderers[FirstIdx]->ChangeFrameAnimation("LaserShooting");
			LaserMachineBackerRenderers[FirstIdx]->ChangeFrameAnimation("LaserShootingBacker");
			LaserRenderers[FirstIdx]->ChangeFrameAnimation("LaserBeam");
			if (FirstIdx == 0)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision0[i]->On();
				}
			}
			if (FirstIdx == 1)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision1[i]->On();
				}
			}
			if (FirstIdx == 2)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision2[i]->On();
				}
			}
			if (FirstIdx == 3)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision3[i]->On();
				}
			}
			if (FirstIdx == 0 ||
				FirstIdx == 1)
			{
				AuraRenderers[FirstIdx]->ChangeFrameAnimation("Nothing");

			}

			if (SecondIdx != -1)
			{
				LaserMachineRenderers[SecondIdx]->ChangeFrameAnimation("LaserShooting");
				LaserMachineBackerRenderers[SecondIdx]->ChangeFrameAnimation("LaserShootingBacker");
				LaserRenderers[SecondIdx]->ChangeFrameAnimation("LaserBeam");
				if (SecondIdx == 0)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision0[i]->On();
					}
				}
				if (SecondIdx == 1)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision1[i]->On();
					}
				}
				if (SecondIdx == 2)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision2[i]->On();
					}
				}
				if (SecondIdx == 3)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision3[i]->On();
					}
				}
				if (SecondIdx == 0 ||
					SecondIdx == 1)
				{
					AuraRenderers[SecondIdx]->ChangeFrameAnimation("Nothing");

				}
			}
		}
	}
}

void DogCopterShooter::Test(const FrameAnimation_DESC& _Info)
{
	int a = 0;
}

void DogCopterShooter::Test2(const FrameAnimation_DESC& _Info)
{
	int a = 0;
}

void DogCopterShooter::OnLaserShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			LaserMachineRenderers[4]->ChangeFrameAnimation("LaserClose");
			LaserRenderers[4]->ChangeFrameAnimation("Nothing");
			LaserRenderers[4]->Off();
			LaserCollision4[0]->Off();
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserClose");
			LaserRenderers[5]->ChangeFrameAnimation("Nothing");
			LaserRenderers[5]->Off();
		}
		else
		{
			LaserMachineRenderers[FirstIdx]->ChangeFrameAnimation("LaserClose");
			LaserRenderers[FirstIdx]->ChangeFrameAnimation("Nothing");
			LaserMachineBackerRenderers[FirstIdx]->ChangeFrameAnimation("LaserBackerEnd");
			LaserRenderers[FirstIdx]->Off();
			if (FirstIdx == 0)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision0[i]->Off();
				}
			}
			if (FirstIdx == 1)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision1[i]->Off();
				}
			}
			if (FirstIdx == 2)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision2[i]->Off();
				}
			}
			if (FirstIdx == 3)
			{
				for (int i = 0; i < 8; i++)
				{
					LaserCollision3[i]->Off();
				}
			}
			if (FirstIdx == 0 ||
				FirstIdx == 1)
			{
				MachineTeethRenderers[FirstIdx]->ChangeFrameAnimation("Nothing");
			}

			if (SecondIdx != -1)
			{
				LaserMachineRenderers[SecondIdx]->ChangeFrameAnimation("LaserClose");
				LaserRenderers[SecondIdx]->ChangeFrameAnimation("Nothing");
				LaserMachineBackerRenderers[SecondIdx]->ChangeFrameAnimation("LaserBackerEnd");
				LaserRenderers[SecondIdx]->Off();
				if (SecondIdx == 0)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision0[i]->Off();
					}
				}
				if (SecondIdx == 1)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision1[i]->Off();
					}
				}
				if (SecondIdx == 2)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision2[i]->Off();
					}
				}
				if (SecondIdx == 3)
				{
					for (int i = 0; i < 8; i++)
					{
						LaserCollision3[i]->Off();
					}
				}

				if (SecondIdx == 0 ||
					SecondIdx == 1)
				{
					MachineTeethRenderers[SecondIdx]->ChangeFrameAnimation("Nothing");
				}
			}
		}
	}
}

void DogCopterShooter::OnLaserCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	//LaserMachineRenderers[5]->ChangeFrameAnimation("LaserNothing");
	//LaserMachineRenderers[5]->Off();
	//PadBackRenderers[5]->Off();
	//PadBackBackerRenderers[5]->Off();

	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			PadRenderers[4]->ChangeFrameAnimation("PadClose");
			PadRenderers[5]->ChangeFrameAnimation("PadClose");
			LaserMachineRenderers[4]->ChangeFrameAnimation("LaserNothing");
			LaserMachineRenderers[4]->Off();
			PadBackRenderers[4]->Off();
			LaserMachineBackerRenderers[4]->ChangeFrameAnimation("Nothing");
			LaserMachineBackerRenderers[4]->Off();
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserNothing");
			LaserMachineRenderers[5]->Off();
			PadBackRenderers[5]->Off();
			LaserMachineBackerRenderers[5]->ChangeFrameAnimation("Nothing");
			LaserMachineBackerRenderers[5]->Off();
			LaserBodyCollisions[4]->Off();
			LaserBodyCollisions[5]->Off();
		}
		else
		{
			PadRenderers[FirstIdx]->ChangeFrameAnimation("PadClose");
			LaserMachineRenderers[FirstIdx]->ChangeFrameAnimation("LaserNothing");
			LaserMachineRenderers[FirstIdx]->Off();
			LaserBodyCollisions[FirstIdx]->Off();

			if ((FirstIdx == 0 && SecondIdx == 2) || (FirstIdx == 2 && SecondIdx == 0))
			{
				PadBackRenderers[6]->Off();
			}
			else if ((FirstIdx == 1 && SecondIdx == 3) || (FirstIdx == 3 && SecondIdx == 1))
			{
				PadBackRenderers[7]->Off();
			}
			else
			{
				PadBackRenderers[FirstIdx]->Off();
			}

			LaserMachineBackerRenderers[FirstIdx]->ChangeFrameAnimation("Nothing");
			LaserMachineBackerRenderers[FirstIdx]->Off();

			if (SecondIdx != -1)
			{
				PadRenderers[SecondIdx]->ChangeFrameAnimation("PadClose");
				LaserMachineRenderers[SecondIdx]->ChangeFrameAnimation("LaserNothing");
				LaserMachineRenderers[SecondIdx]->Off();
				LaserBodyCollisions[SecondIdx]->Off();

				if ((FirstIdx == 0 && SecondIdx == 2) || (FirstIdx == 2 && SecondIdx == 0))
				{
					PadBackRenderers[6]->Off();
				}
				else if ((FirstIdx == 1 && SecondIdx == 3) || (FirstIdx == 3 && SecondIdx == 1))
				{
					PadBackRenderers[7]->Off();
				}
				else
				{
					PadBackRenderers[SecondIdx]->Off();
				}

				LaserMachineBackerRenderers[SecondIdx]->ChangeFrameAnimation("Nothing");
				LaserMachineBackerRenderers[SecondIdx]->Off();
			}
		}
	}
}