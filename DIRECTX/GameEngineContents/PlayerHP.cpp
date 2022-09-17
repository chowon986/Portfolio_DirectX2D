#include "PreCompile.h"
#include "PlayerHP.h"
#include "IInGameCharacterBase.h"
#include "InGameCuphead.h"

PlayerHP::PlayerHP()
{
}

PlayerHP::~PlayerHP()
{
}

void PlayerHP::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("HP0", FrameAnimation_DESC("HP0", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("HP1", FrameAnimation_DESC("HP1", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("HP1Switch", FrameAnimation_DESC("HP1Switch", 0.05f, true));
	Renderer->CreateFrameAnimationFolder("HP2", FrameAnimation_DESC("HP2", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("HP3", FrameAnimation_DESC("HP3", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("HP4", FrameAnimation_DESC("HP4", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("HP5", FrameAnimation_DESC("HP5", 0.1f, false));
	Renderer->AnimationBindEnd("HP1", std::bind(&PlayerHP::HP1AnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
}

void PlayerHP::Update(float _DeltaTime)
{
	if (nullptr != Player)
	{
		if (InGameCuphead* Cuphead = dynamic_cast<InGameCuphead*>(Player))
		{
			int _HP = Cuphead->GetHP();
			ChangeHPUI(_HP);
		}
	}


}

void PlayerHP::End()
{
}

void PlayerHP::ChangeHPUI(int _HP)
{
	if (HP != _HP)
	{
		HP = _HP;
		switch (HP)
		{
		case 0:
			Renderer->ChangeFrameAnimation("HP0");
			break;
		case 1:
			Renderer->ChangeFrameAnimation("HP1");
			break;
		case 2:
			Renderer->ChangeFrameAnimation("HP2");
			break;
		case 3:
			Renderer->ChangeFrameAnimation("HP3");
			break;
		case 4:
			Renderer->ChangeFrameAnimation("HP4");
			break;
		case 5:
			Renderer->ChangeFrameAnimation("HP5");
			break;
		}
	}
}

void PlayerHP::HP1AnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("HP1Switch");
}
