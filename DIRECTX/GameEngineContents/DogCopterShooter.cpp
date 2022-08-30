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
		GameEngineTextureRenderer* LeftTopTeethRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopTeethRenderer->CreateFrameAnimationFolder("LaserTeeth", FrameAnimation_DESC("LaserTopShootingTeeth", 0.1f, true));
		LeftTopTeethRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopTeethRenderer->ChangeFrameAnimation("LaserTeeth");
		LeftTopTeethRenderer->SetScaleModeImage();
		LeftTopTeethRenderer->GetTransform().SetLocalPosition({ 395, -135, (int)ZOrder::NPC - 9 });
		LeftTopTeethRenderer->Off();

		GameEngineTextureRenderer* RightTopTeethRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopTeethRenderer->CreateFrameAnimationFolder("LaserTeeth", FrameAnimation_DESC("LaserTopShootingTeeth", 0.1f, true));
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
		LeftTopAuraRenderer->CreateFrameAnimationFolder("LaserAura", FrameAnimation_DESC("LaserWarningAuraA", 0.1f, true));
		LeftTopAuraRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopAuraRenderer->ChangeFrameAnimation("LaserAura");
		LeftTopAuraRenderer->SetScaleModeImage();
		LeftTopAuraRenderer->GetTransform().SetLocalPosition({  395, -140, (int)ZOrder::NPC - 8 });
		LeftTopAuraRenderer->Off();


		GameEngineTextureRenderer* RightTopAuraRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopAuraRenderer->CreateFrameAnimationFolder("LaserAura", FrameAnimation_DESC("LaserWarningAuraA", 0.1f, true));
		RightTopAuraRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopAuraRenderer->ChangeFrameAnimation("LaserAura");
		RightTopAuraRenderer->SetScaleModeImage();
		RightTopAuraRenderer->GetTransform().SetLocalPosition({ 900, -140, (int)ZOrder::NPC - 8 });
		RightTopAuraRenderer->GetTransform().PixLocalNegativeX();
		RightTopAuraRenderer->Off();
		
		GameEngineTextureRenderer* BotAuraRenderer = CreateComponent<GameEngineTextureRenderer>();
		BotAuraRenderer->CreateFrameAnimationFolder("LaserAura", FrameAnimation_DESC("LaserWarningAuraC", 0.1f, true));
		BotAuraRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		BotAuraRenderer->ChangeFrameAnimation("LaserAura");
		BotAuraRenderer->SetScaleModeImage();
		BotAuraRenderer->GetTransform().SetLocalPosition({ 320, -540, (int)ZOrder::NPC - 8 });
		BotAuraRenderer->Off();

		AuraRenderers.push_back(LeftTopAuraRenderer);
		AuraRenderers.push_back(RightTopAuraRenderer);
		AuraRenderers.push_back(BotAuraRenderer);
	}

	{
		GameEngineTextureRenderer* LeftTopPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTopBacker", 0.1f, false));
		LeftTopPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		LeftTopPadBackBackerRenderer->SetScaleModeImage();
		LeftTopPadBackBackerRenderer->GetTransform().SetLocalPosition({ 194, -154, (int)ZOrder::NPC - 3 });
		LeftTopPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMidBacker", 0.1f, false));
		LeftMidPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		LeftMidPadBackBackerRenderer->SetScaleModeImage();
		LeftMidPadBackBackerRenderer->GetTransform().SetLocalPosition({ 223, -363, (int)ZOrder::NPC - 3 });
		LeftMidPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* LeftLowPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLowBacker", 0.1f, false));
		LeftLowPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		LeftLowPadBackBackerRenderer->SetScaleModeImage();
		LeftLowPadBackBackerRenderer->GetTransform().SetLocalPosition({ 378, -608, (int)ZOrder::NPC - 3 });
		LeftLowPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* RightTopPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTopBacker", 0.1f, false));
		RightTopPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		RightTopPadBackBackerRenderer->SetScaleModeImage();
		RightTopPadBackBackerRenderer->GetTransform().SetLocalPosition({ 1111, -133, (int)ZOrder::NPC - 3 });
		RightTopPadBackBackerRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* RightMidPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMidBacker", 0.1f, false));
		RightMidPadBackBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadBackBackerRenderer->ChangeFrameAnimation("PadBackHole");
		RightMidPadBackBackerRenderer->SetScaleModeImage();
		RightMidPadBackBackerRenderer->GetTransform().SetLocalPosition({ 1082, -345, (int)ZOrder::NPC - 3 });
		RightMidPadBackBackerRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadBackBackerRenderer->Off();

		GameEngineTextureRenderer* RightLowPadBackBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadBackBackerRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLowBacker", 0.1f, false));
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
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserTopBackerStart", 0.1f, false));
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserTopShootingBacker", 0.1f, false));
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserTopBackerEnd", 0.1f, false));
		LeftTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false)); 
		LeftTopLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerEnd", std::bind(&DogCopterShooter::Test, this, std::placeholders::_1));
		LeftTopLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		LeftTopLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		LeftTopLaserMachineBackerRenderer->SetScaleModeImage();
		LeftTopLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 260, -90, (int)ZOrder::NPC - 4 });
		LeftTopLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* LeftMidLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserMidBackerStart", 0.1f, false));
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserMidShootingBacker", 0.1f, false));
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserMidBackerEnd", 0.1f, false));
		LeftMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerEnd", std::bind(&DogCopterShooter::Test, this, std::placeholders::_1));
		LeftMidLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		LeftMidLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		LeftMidLaserMachineBackerRenderer->SetScaleModeImage();
		LeftMidLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 320, -300, (int)ZOrder::NPC - 4 });
		LeftMidLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserLowBackerStart", 0.1f, false));
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserLowShootingBacker", 0.1f, false));
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserLowBackerEnd", 0.1f, false));
		LeftLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerEnd", std::bind(&DogCopterShooter::Test, this, std::placeholders::_1));
		LeftLowLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		LeftLowLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		LeftLowLaserMachineBackerRenderer->SetScaleModeImage();
		LeftLowLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 200, -550, (int)ZOrder::NPC - 4 });
		LeftLowLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* RightTopLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserTopBackerStart", 0.1f, false));
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserTopShootingBacker", 0.1f, false));
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserTopBackerEnd", 0.1f, false));
		RightTopLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerEnd", std::bind(&DogCopterShooter::Test, this, std::placeholders::_1));
		RightTopLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		RightTopLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		RightTopLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		RightTopLaserMachineBackerRenderer->SetScaleModeImage();
		RightTopLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 1045, -90, (int)ZOrder::NPC - 4 });
		RightTopLaserMachineBackerRenderer->GetTransform().PixLocalNegativeX();
		RightTopLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* RightMidLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserMidBackerStart", 0.1f, false));
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserMidShootingBacker", 0.1f, false));
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserMidBackerEnd", 0.1f, false));
		RightMidLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerEnd", std::bind(&DogCopterShooter::Test, this, std::placeholders::_1));
		RightMidLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerStart", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameChanged, this, std::placeholders::_1));
		RightMidLaserMachineBackerRenderer->AnimationBindEnd("LaserBackerEnd", std::bind(&DogCopterShooter::OnLaserBackerAnimationFrameFinished, this, std::placeholders::_1));
		RightMidLaserMachineBackerRenderer->ChangeFrameAnimation("Nothing");
		RightMidLaserMachineBackerRenderer->SetScaleModeImage();
		RightMidLaserMachineBackerRenderer->GetTransform().SetLocalPosition({ 1000, -300, (int)ZOrder::NPC - 4 });
		RightMidLaserMachineBackerRenderer->GetTransform().PixLocalNegativeX();
		RightMidLaserMachineBackerRenderer->Off();

		GameEngineTextureRenderer* RightLowLaserMachineBackerRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerStart", FrameAnimation_DESC("LaserLowBackerStart", 0.1f, false));
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserShootingBacker", FrameAnimation_DESC("LaserLowShootingBacker", 0.1f, false));
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("LaserBackerEnd", FrameAnimation_DESC("LaserLowBackerEnd", 0.1f, false));
		RightLowLaserMachineBackerRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserMachineBackerRenderer->AnimationBindFrame("LaserBackerEnd", std::bind(&DogCopterShooter::Test, this, std::placeholders::_1));
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
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTop", 0.1f, false));
		LeftTopPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftTopPadBackRenderer->SetScaleModeImage();
		LeftTopPadBackRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 5 });
		LeftTopPadBackRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMid", 0.1f, false));
		LeftMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftMidPadBackRenderer->SetScaleModeImage();
		LeftMidPadBackRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 5 });
		LeftMidPadBackRenderer->Off();

		GameEngineTextureRenderer* LeftLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLow", 0.1f, false));
		LeftLowPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		LeftLowPadBackRenderer->SetScaleModeImage();
		LeftLowPadBackRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 5 });
		LeftLowPadBackRenderer->Off();

		GameEngineTextureRenderer* RightTopPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleTop", 0.1f, false));
		RightTopPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightTopPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightTopPadBackRenderer->SetScaleModeImage();
		RightTopPadBackRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 5 });
		RightTopPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadBackRenderer->Off();

		GameEngineTextureRenderer* RightMidPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleMid", 0.1f, false));
		RightMidPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightMidPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightMidPadBackRenderer->SetScaleModeImage();
		RightMidPadBackRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 5 });
		RightMidPadBackRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadBackRenderer->Off();

		GameEngineTextureRenderer* RightLowPadBackRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadBackRenderer->CreateFrameAnimationFolder("PadBackHole", FrameAnimation_DESC("LeftPawHoleLow", 0.1f, false));
		RightLowPadBackRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowPadBackRenderer->ChangeFrameAnimation("PadBackHole");
		RightLowPadBackRenderer->SetScaleModeImage();
		RightLowPadBackRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 5 });
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
		GameEngineTextureRenderer* LeftTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("TopPadOpen", 0.1f, true)); // 패드 열리기
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("TopPadOpen", 3, 3, 0.1f, false)); // 열린 상태 Idle 
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("TopPadClose", 0.1f, true)); // 패드 닫히기
		LeftTopPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, true)); // 패드 닫히기
		LeftTopPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftTopPadRenderer->SetScaleModeImage();
		LeftTopPadRenderer->GetTransform().SetLocalPosition({ 194, -148, (int)ZOrder::NPC - 6 });
		LeftTopPadRenderer->Off();

		GameEngineTextureRenderer* LeftMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadOpen", FrameAnimation_DESC("MidPadOpen", 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadOpenIdle", FrameAnimation_DESC("MidPadOpen", 2, 2, 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadClose", FrameAnimation_DESC("MidPadClose", 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("PadRendererNothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidPadRenderer->AnimationBindEnd("PadOpen", std::bind(&DogCopterShooter::OnPadOpenAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidPadRenderer->AnimationBindEnd("PadClose", std::bind(&DogCopterShooter::OnPadCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidPadRenderer->ChangeFrameAnimation("PadOpen");
		LeftMidPadRenderer->GetTransform().SetLocalPosition({ 130, -353, (int)ZOrder::NPC - 6 });
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
		LeftLowPadRenderer->GetTransform().SetLocalPosition({ 180, -565, (int)ZOrder::NPC - 6 });
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
		RightTopPadRenderer->GetTransform().SetLocalPosition({ 1109, -128, (int)ZOrder::NPC - 6 });
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
		RightMidPadRenderer->GetTransform().SetLocalPosition({ 1175, -330, (int)ZOrder::NPC - 6 });
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
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserTop", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserTopWarning", 0.1f, true)); // 레이저 기기 경고
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserTopShooting", 0.1f, true)); // 레이저 기기 슈팅
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserTopClose", 0.1f, false)); // 레이저 기기 제거
		LeftTopLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftTopLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftTopLaserMachineRenderer->SetScaleModeImage();
		LeftTopLaserMachineRenderer->GetTransform().SetLocalPosition({ 260, -90, (int)ZOrder::NPC - 7 });
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
		LeftMidLaserMachineRenderer->GetTransform().SetLocalPosition({ 320, -300, (int)ZOrder::NPC - 7 });
		LeftMidLaserMachineRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserMachineRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserPrepare", FrameAnimation_DESC("LaserLow", 0.1f, true)); // 레이저 기기 왼쪽 위 생성
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserLowWarning", 0.1f, true)); // 레이저 기기 경고
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserShooting", FrameAnimation_DESC("LaserLowShooting", 0.1f, true)); // 레이저 기기 슈팅
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserClose", FrameAnimation_DESC("LaserLowClose", 0.1f, false)); // 레이저 기기 제거
		LeftLowLaserMachineRenderer->CreateFrameAnimationFolder("LaserNothing", FrameAnimation_DESC("Nothing", 0.1f, false)); // 레이저 기기 제거
		LeftLowLaserMachineRenderer->AnimationBindFrame("LaserPrepare", std::bind(&DogCopterShooter::Test2, this, std::placeholders::_1));
		LeftLowLaserMachineRenderer->AnimationBindEnd("LaserPrepare", std::bind(&DogCopterShooter::OnLaserAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserMachineRenderer->AnimationBindEnd("LaserClose", std::bind(&DogCopterShooter::OnLaserCloseAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserMachineRenderer->ChangeFrameAnimation("LaserPrepare");
		LeftLowLaserMachineRenderer->SetScaleModeImage();
		LeftLowLaserMachineRenderer->GetTransform().SetLocalPosition({ 200, -550, (int)ZOrder::NPC - 7 });
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
		RightTopLaserMachineRenderer->GetTransform().SetLocalPosition({ 1044, -90, (int)ZOrder::NPC -7 });
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
		RightMidLaserMachineRenderer->GetTransform().SetLocalPosition({ 1000, -300, (int)ZOrder::NPC - 7 });
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
		LeftTopLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningA", 0.1f, true));
		LeftTopLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamTop", 0.1f, true));
		LeftTopLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftTopLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftTopLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftTopLaserRenderer->SetScaleModeImage();
		LeftTopLaserRenderer->GetTransform().SetLocalPosition({ 390, -135, (int)ZOrder::NPC - 8 });
		LeftTopLaserRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		LeftTopLaserRenderer->Off();

		GameEngineTextureRenderer* LeftMidLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningB", 0.1f, false));
		LeftMidLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamMid", 0.1f, false));
		LeftMidLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftMidLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftMidLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftMidLaserRenderer->SetScaleModeImage();
		LeftMidLaserRenderer->GetTransform().SetLocalPosition({ 175, -100, (int)ZOrder::NPC - 6 });
		LeftMidLaserRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		LeftMidLaserRenderer->Off();

		GameEngineTextureRenderer* LeftLowLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftLowLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningC", 0.1f, false));
		LeftLowLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamLow", 0.1f, false));
		LeftLowLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		LeftLowLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		LeftLowLaserRenderer->ChangeFrameAnimation("LaserWarning");
		LeftLowLaserRenderer->SetScaleModeImage();
		LeftLowLaserRenderer->GetTransform().SetLocalPosition({ 250, -440, (int)ZOrder::NPC - 6 });
		LeftLowLaserRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		LeftLowLaserRenderer->Off();

		GameEngineTextureRenderer* RightTopLaserRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningA", 0.1f, true));
		RightTopLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamTop", 0.1f, true));
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
		RightMidLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("LaserWarningB", 0.1f, false));
		RightMidLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("LaserBeamMid", 0.1f, false));
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
		RightLowLaserRenderer->CreateFrameAnimationFolder("LaserWarning", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserRenderer->CreateFrameAnimationFolder("LaserBeam", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		RightLowLaserRenderer->AnimationBindEnd("LaserWarning", std::bind(&DogCopterShooter::OnLaserWarningAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserRenderer->AnimationBindEnd("LaserBeam", std::bind(&DogCopterShooter::OnLaserShootingAnimationFrameFinished, this, std::placeholders::_1));
		RightLowLaserRenderer->ChangeFrameAnimation("LaserWarning");
		RightLowLaserRenderer->SetScaleModeImage();
		RightLowLaserRenderer->GetTransform().SetLocalPosition({ 400, -600, (int)ZOrder::NPC - 8 });
		RightLowLaserRenderer->SetPivot(PIVOTMODE::RIGHTTOP);
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
		}
	}
}

void DogCopterShooter::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	//MonsterWeaponBase::OnMonsterAttackStateChanged(_AttackState);

	if (_AttackState == InGameMonsterAttackState::LaserPattern1)
	{
		int RandomAttackPattern = rand() % 4;
		int RandomAttackCount = rand() % 2;
		LaserMachineBackerRenderers[5]->On();
		LaserMachineBackerRenderers[5]->ChangeFrameAnimation("LaserBackerStart");

		//if (RandomAttackCount == 1)
		//{
		PadRenderers[5]->On();
		PadRenderers[5]->ChangeFrameAnimation("PadOpen");
		PadBackRenderers[5]->On();
		PadBackBackerRenderers[5]->On();

	}
	else if (_AttackState == InGameMonsterAttackState::LaserPattern2)
	{
		RandomAttackPattern = rand() % 4;
		int RandomAttackCount = rand() % 2;

		//if (RandomAttackCount == 1)
		//{
		PadRenderers[4]->On();
		PadRenderers[4]->ChangeFrameAnimation("PadOpen");
		LaserMachineRenderers[4]->On();
		LaserMachineRenderers[4]->ChangeFrameAnimation("LaserPrepare");
		PadBackRenderers[4]->On();
		PadBackBackerRenderers[4]->On();
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

void DogCopterShooter::UpdatePivot()
{

}


void DogCopterShooter::Update(float _DeltaTime)
{
	
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
			PadRenderers[4]->ChangeFrameAnimation("PadOpenIdle");
		}
	}
}

void DogCopterShooter::OnPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			PadRenderers[4]->ChangeFrameAnimation("PadRendererNothing");
			PadBackRenderers[4]->Off();
			PadRenderers[5]->ChangeFrameAnimation("PadRendererNothing");
			PadBackRenderers[5]->Off();
		}
		else
		{
			PadRenderers[4]->ChangeFrameAnimation("PadRendererNothing");
			PadBackRenderers[4]->Off();
			PadBackBackerRenderers[4]->Off();
		}
	}
}

void DogCopterShooter::OnLaserBackerAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserMachineBackerRenderers[4]->ChangeFrameAnimation("Nothing");
}

void DogCopterShooter::OnLaserBackerAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	int a = 0;
	if (_Info.CurFrame == 1/*2*/)
	{
		LaserMachineRenderers[5]->On();
		LaserMachineRenderers[5]->ChangeFrameAnimation("LaserPrepare");
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
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserWarning");
			LaserRenderers[4]->ChangeFrameAnimation("LaserWarning");
			// AuraRenderers[2], [3]은 없음
			AuraRenderers[2]->ChangeFrameAnimation("LaserAura");
			// MachineTeethRenderers[0]과 [1]만 있음
			//MachineTeethRenderers[4]->ChangeFrameAnimation("LaserTeeth");
			LaserRenderers[4]->On();
			AuraRenderers[2]->On();
			//MachineTeethRenderers[4]->On();
		}
	}
}

void DogCopterShooter::OnLaserWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	{
		if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
		{
			LaserMachineRenderers[4]->ChangeFrameAnimation("LaserShooting");
			LaserRenderers[4]->ChangeFrameAnimation("LaserBeam");
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserShooting");
			LaserRenderers[5]->ChangeFrameAnimation("LaserBeam");
		}
		else
		{

			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserShooting");
			LaserMachineBackerRenderers[5]->ChangeFrameAnimation("LaserShootingBacker");
			LaserRenderers[4]->ChangeFrameAnimation("LaserBeam");
			AuraRenderers[2]->ChangeFrameAnimation("Nothing");
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
			//PadRenderers[4]->ChangeFrameAnimation("PadClose");
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserClose");
			LaserRenderers[5]->ChangeFrameAnimation("Nothing");
			LaserRenderers[5]->Off();
			//PadRenderers[5]->ChangeFrameAnimation("PadClose");
		}
		else
		{
			LaserMachineRenderers[5]->ChangeFrameAnimation("LaserClose");
			LaserRenderers[4]->ChangeFrameAnimation("Nothing");
			LaserMachineBackerRenderers[5]->ChangeFrameAnimation("LaserBackerEnd");
			LaserRenderers[4]->Off();
			//MachineTeethRenderers[4]->ChangeFrameAnimation("Nothing");
			//PadRenderers[4]->ChangeFrameAnimation("PadClose");
		}
	}
}

void DogCopterShooter::OnLaserCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	LaserMachineRenderers[5]->ChangeFrameAnimation("LaserNothing");
	PadRenderers[4]->ChangeFrameAnimation("PadClose");
	PadRenderers[4]->ChangeFrameAnimation("PadClose");
	PadRenderers[5]->ChangeFrameAnimation("PadClose");

	//if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	//{
	//	if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
	//	{
	//		LaserMachineRenderers[4]->ChangeFrameAnimation("LaserNothing");
	//		LaserMachineRenderers[4]->Off();
	//		PadBackRenderers[4]->Off();
	//		LaserMachineRenderers[5]->ChangeFrameAnimation("LaserNothing");
	//		LaserMachineRenderers[5]->Off();
	//		PadBackRenderers[5]->Off();
	//	}
	//	else
	//	{
	//		LaserMachineRenderers[4]->ChangeFrameAnimation("LaserNothing");
	//		LaserMachineRenderers[4]->Off();
	//		PadBackRenderers[4]->Off();
	//	}
	//}

	//if (DogCopter* Parent = dynamic_cast<DogCopter*>(GetParent()))
	//{
	//	//if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern3)
	//	//{
	//	//	Parent->SetState(InGameMonsterState::BeforeRotateCameraIn);
	//	//}
	//	//else
	//	//{
	//	//	if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern1)
	//	//	{
	//	//		Parent->SetAttackState(InGameMonsterAttackState::LaserPattern2);
	//	//	}
	//	//	else if (Parent->GetAttackState() == InGameMonsterAttackState::LaserPattern2)
	//	//	{
	//	//		Parent->SetAttackState(InGameMonsterAttackState::LaserPattern3);
	//	//	}
	//	//}
	//}
}