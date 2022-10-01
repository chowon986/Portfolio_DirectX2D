#include "PreCompile.h"
#include "ScoreLevel.h"
#include "CharacterState.h"
#include "CharacterScore.h"
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineContents/TextureLoadUtils.h>

ScoreLevel::ScoreLevel()
	: BackgroundRenderer(nullptr)
	, IrisRenderer(nullptr)
	, State(nullptr)
	, ElapsedTime(0.0f)
	, IntervalTime(0.1f)
	, Num(0)
{
}

ScoreLevel::~ScoreLevel()
{
}

void ScoreLevel::LevelStartEvent()
{
	//Start
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetBackgroundCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera2()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	TextureLoadUtils::LoadTextures("08ScoreLevel");

	{
		GameEngineActor* Iris = CreateActor<GameEngineActor>();
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->CreateFrameAnimationFolder("LightOn", FrameAnimation_DESC("IrisA", 0, 0, 0.05f, true));
		IrisRenderer->ChangeFrameAnimation("LightOn");
		IrisRenderer->GetTransform().SetLocalScale(float4{ 1280.0f,720.0f,1.0f });
		IrisRenderer->GetTransform().SetLocalPosition(float4{ 640.0f,-360.0f,(int)ZOrder::UI });
	}
	{
		GameEngineActor* Background = CreateActor<GameEngineActor>();
		BackgroundRenderer = Background->CreateComponent<GameEngineTextureRenderer>();
		BackgroundRenderer->SetTexture("WinScreen.png");
		BackgroundRenderer->ScaleToTexture();
		BackgroundRenderer->GetTransform().SetLocalPosition(float4{ 640.0f,-360.0f,(int)ZOrder::Background });
	}
	{
		GameEngineActor* ResultTitle = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* TitleRenderer = ResultTitle->CreateComponent<GameEngineTextureRenderer>();
		TitleRenderer->CreateFrameAnimationFolder("ResultTitle", FrameAnimation_DESC("ResultTitle", 0.05f, true));
		TitleRenderer->ChangeFrameAnimation("ResultTitle");
		TitleRenderer->SetScaleModeImage();
		TitleRenderer->GetTransform().SetLocalPosition(float4{ 640.0f, -100.0f,(int)ZOrder::Foreground });
	}
	{
		GameEngineActor* Board = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* BoardRenderer = Board->CreateComponent<GameEngineTextureRenderer>();
		BoardRenderer->CreateFrameAnimationFolder("Board", FrameAnimation_DESC("Board", 0.05f, false));
		BoardRenderer->ChangeFrameAnimation("Board");
		BoardRenderer->SetScaleModeImage();
		BoardRenderer->GetTransform().SetLocalPosition(float4{ 750.0f, -425.0f,(int)ZOrder::Foreground });
	}

	if (State == nullptr)
	{
		GameEngineActor* Player = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
		PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true));
		PlayerRenderer->ChangeFrameAnimation("WinCuphead");
		PlayerRenderer->SetScaleModeImage();
		PlayerRenderer->GetTransform().SetLocalPosition(float4{ 320, -400.0f,(int)ZOrder::Foreground });

		GameEngineActor* PlayerName = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* PlayerNameRenderer = PlayerName->CreateComponent<GameEngineTextureRenderer>();
		PlayerNameRenderer->CreateFrameAnimationFolder("CupheadName", FrameAnimation_DESC("CupheadName", 0.1f, false));
		PlayerNameRenderer->ChangeFrameAnimation("CupheadName");
		PlayerNameRenderer->SetScaleModeImage();
		PlayerNameRenderer->GetTransform().SetLocalPosition(float4{ 320.0, -660.0f,(int)ZOrder::Foreground - 1 });
	}
	else
	{
		if (State->Type == CharacterType::Cuphead)
		{
			GameEngineActor* Player = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
			PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true));
			PlayerRenderer->ChangeFrameAnimation("WinCuphead");
			PlayerRenderer->SetScaleModeImage();
			PlayerRenderer->GetTransform().SetLocalPosition(float4{ 320, -400.0f,(int)ZOrder::Foreground });

			GameEngineActor* PlayerName = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerNameRenderer = PlayerName->CreateComponent<GameEngineTextureRenderer>();
			PlayerNameRenderer->CreateFrameAnimationFolder("CupheadName", FrameAnimation_DESC("CupheadName", 0.1f, false));
			PlayerNameRenderer->ChangeFrameAnimation("CupheadName");
			PlayerNameRenderer->SetScaleModeImage();
			PlayerNameRenderer->GetTransform().SetLocalPosition(float4{ 320.0, -660.0f,(int)ZOrder::Foreground - 1 });
		}
		else if (State->Type == CharacterType::Chalice)
		{
			GameEngineActor* Player = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
			PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true)); // Need to chk : 챌리스 이미지 적용하기
			PlayerRenderer->ChangeFrameAnimation("WinCuphead"); // Need to chk : 상동
			PlayerRenderer->SetScaleModeImage();
			PlayerRenderer->GetTransform().SetLocalPosition(float4{ 320, -400.0f,(int)ZOrder::Foreground });

			GameEngineActor* PlayerName = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerNameRenderer = PlayerName->CreateComponent<GameEngineTextureRenderer>();
			PlayerNameRenderer->CreateFrameAnimationFolder("CupheadName", FrameAnimation_DESC("CupheadName", 0.1f, false)); // Need to chk : 상동
			PlayerNameRenderer->ChangeFrameAnimation("CupheadName");
			PlayerNameRenderer->SetScaleModeImage();
			PlayerNameRenderer->GetTransform().SetLocalPosition(float4{ 320.0, -660.0f,(int)ZOrder::Foreground - 1 });
		}
	}

	// Time
	{
		GameEngineActor* FontA = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererA = FontA->CreateComponent<GameEngineFontRenderer>();
		FontRendererA->SetText("00", "Yoon-Backjae");
		FontRendererA->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererA->SetSize(35);
		FontRendererA->SetScreenPostion(float4{ 850.0f, 250.0f, (int)ZOrder::Foreground - 1 });
		FontRendererA->SetRenderingOrder(10000);

		GameEngineActor* FontB = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererB = FontB->CreateComponent<GameEngineFontRenderer>();
		FontRendererB->SetText(" : ", "Yoon-Backjae");
		FontRendererB->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererB->SetSize(35);
		FontRendererB->SetScreenPostion(float4{ 885.0f, 250.0f, (int)ZOrder::Foreground - 1 });
		FontRendererB->SetRenderingOrder(10000);

		GameEngineActor* FontC = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererC = FontC->CreateComponent<GameEngineFontRenderer>();
		FontRendererC->SetText("00", "Yoon-Backjae");
		FontRendererC->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererC->SetSize(35);
		FontRendererC->SetScreenPostion(float4{ 910.0f, 250.0f, (int)ZOrder::Foreground - 1 });
		FontRendererC->SetRenderingOrder(10000);

		GameEngineActor* FontD = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererD = FontD->CreateComponent<GameEngineFontRenderer>();
		FontRendererD->SetText(" /3", "Yoon-Backjae");
		FontRendererD->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererD->SetSize(35);
		FontRendererD->SetScreenPostion(float4{ 905.0f, 295.0f, (int)ZOrder::Foreground - 1 });
		FontRendererD->SetRenderingOrder(10000);

		GameEngineActor* FontE = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererE = FontE->CreateComponent<GameEngineFontRenderer>();
		FontRendererE->SetText(" /3", "Yoon-Backjae");
		FontRendererE->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererE->SetSize(35);
		FontRendererE->SetScreenPostion(float4{ 905.0f, 340.0f, (int)ZOrder::Foreground - 1 });
		FontRendererE->SetRenderingOrder(10000);

		GameEngineActor* FontF = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererF = FontF->CreateComponent<GameEngineFontRenderer>();
		FontRendererF->SetText(" /6", "Yoon-Backjae");
		FontRendererF->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererF->SetSize(35);
		FontRendererF->SetScreenPostion(float4{ 905.0f, 385.0f, (int)ZOrder::Foreground - 1 });
		FontRendererF->SetRenderingOrder(10000);

		GameEngineActor* FontG = CreateActor<GameEngineActor>(); // HP
		GameEngineFontRenderer* FontRendererG = FontG->CreateComponent<GameEngineFontRenderer>();
		FontRendererG->SetText("0", "Yoon-Backjae");
		FontRendererG->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererG->SetSize(35);
		FontRendererG->SetScreenPostion(float4{ 895.0f, 295.0f, (int)ZOrder::Foreground - 1 });
		FontRendererG->SetRenderingOrder(10000);

		GameEngineActor* FontH = CreateActor<GameEngineActor>(); // Parry
		GameEngineFontRenderer* FontRendererH = FontG->CreateComponent<GameEngineFontRenderer>();
		FontRendererH->SetText("0", "Yoon-Backjae");
		FontRendererH->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererH->SetSize(35);
		FontRendererH->SetScreenPostion(float4{ 895.0f, 340.0f, (int)ZOrder::Foreground - 1 });
		FontRendererH->SetRenderingOrder(10000);

		GameEngineActor* FontI = CreateActor<GameEngineActor>(); // UseCard
		GameEngineFontRenderer* FontRendererI = FontI->CreateComponent<GameEngineFontRenderer>();
		FontRendererI->SetText("0", "Yoon-Backjae");
		FontRendererI->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererI->SetSize(35);
		FontRendererI->SetScreenPostion(float4{ 895.0f, 385.0f, (int)ZOrder::Foreground - 1 });
		FontRendererI->SetRenderingOrder(10000);

		FontRenderers.insert(std::make_pair(0, FontRendererA));
		FontRenderers.insert(std::make_pair(1, FontRendererC));
		FontRenderers.insert(std::make_pair(2, FontRendererG));
		FontRenderers.insert(std::make_pair(3, FontRendererH));
		FontRenderers.insert(std::make_pair(4, FontRendererI));
	}

	//{
	//	GameEngineActor* Font = CreateActor<GameEngineActor>();
	//	GameEngineFontRenderer* FontRenderer = Font->CreateComponent<GameEngineFontRenderer>();
	//	FontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
	//	FontRenderer->SetText("00 ", "Yoon-Backjae");
	//	FontRenderer->SetColor({ (1.0 / 255) * 237.0f, (1.0 / 255) * 237.0f, (1.0 / 255) * 237.0f, 1.0 });
	//	FontRenderer->SetSize(30);
	//	FontRenderer->SetScreenPostion(float4{ 800.0f, 200.0f,(int)ZOrder::Foreground - 1 });
	//	FontRenderer->SetRenderingOrder(10000);
	//}

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });

	Phase = ScorePhase::Minute;

	{
		std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
		for (GameEngineActor* Actor : Actors)
		{
			if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
			{
				State = _State;
			}
		}
	}

	{
		std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterScore);
		for (GameEngineActor* Actor : Actors)
		{
			if (CharacterScore* _Score = dynamic_cast<CharacterScore*>(Actor))
			{
				Score = _Score;
				PlayMinute = static_cast<int>(Score->PlayTime) / 60;
				PlaySecond = static_cast<int>(Score->PlayTime) % 60;
			}
		}
	}
}

void ScoreLevel::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;
	//if (IrisRenderer->GetPixelData().PlusColor.a > -1.0f)
	//{
	//	IrisRenderer->GetPixelData().PlusColor.a -= _DeltaTime * 0.3;
	//}
	//BackgroundRenderer->GetTransform().SetLocalRotate({0.0f, 0.0f, 10 * _DeltaTime});
	if (nullptr != Score && ElapsedTime > IntervalTime)
	{
		if (Phase == ScorePhase::Minute)
		{
			if (nullptr != FontRenderers[0])
			{
				if (PlayMinute != 0)
				{
					if (Num <= PlayMinute)
					{
						if (PlayMinute < 10)
						{
							FontRenderers[0]->SetText("0" + std::to_string(Num), "Yoon-Backjae");
							ElapsedTime = 0.0f;
							++Num;
						}
						else
						{
							FontRenderers[0]->SetText(std::to_string(Num), "Yoon-Backjae");
							ElapsedTime = 0.0f;
							++Num;
						}
					}

					if (Num > PlayMinute)
					{
						Num = 0;
						ElapsedTime = 0.0f;
						Phase = ScorePhase::Second;
					}
				}
				else
				{
					FontRenderers[0]->SetText("00", "Yoon-Backjae");
					if (Num != 0)
					{
						Num = 0;
					}
					ElapsedTime = 0.0f;
					Phase = ScorePhase::Second;
				}
			}
		}

		else if (Phase == ScorePhase::Second)
		{
			if (nullptr != FontRenderers[1])
			{
				if (PlaySecond != 0)
				{
					if (Num <= PlaySecond)
					{
						if (PlaySecond < 10)
						{
							FontRenderers[1]->SetText("0" + std::to_string(Num), "Yoon-Backjae");
							ElapsedTime = 0.0f;
							++Num;
						}
						else
						{
							FontRenderers[1]->SetText(std::to_string(Num), "Yoon-Backjae");
							ElapsedTime = 0.0f;
							++Num;
						}
					}

					if (Num > PlaySecond)
					{
						Num = 0;
						ElapsedTime = 0.0f;
						Phase = ScorePhase::HP;
					}
				}
				else
				{
					FontRenderers[1]->SetText("00", "Yoon-Backjae");
					Num = 0;
					ElapsedTime = 0.0f;
					Phase = ScorePhase::HP;
				}
			}
		}
	

		else if (Phase == ScorePhase::HP)
		{
			if (nullptr != FontRenderers[2])
			{
				if (Score->HP != 0)
				{
					if (Num <= Score->HP)
					{
						FontRenderers[2]->SetText(std::to_string(Num), "Yoon-Backjae");
						ElapsedTime = 0.0f;
						++Num;
					}

					if (Num > Score->HP)
					{
						Num = 0;
						ElapsedTime = 0.0f;
						Phase = ScorePhase::Parry;
					}
				}
				else
				{
					FontRenderers[2]->SetText("0", "Yoon-Backjae");
					Num = 0;
					ElapsedTime = 0.0f;
					Phase = ScorePhase::Parry;
				}
			}
		}

		else if (Phase == ScorePhase::Parry)
		{
			if (nullptr != FontRenderers[3])
			{
				if (Score->Parry != 0)
				{
					if (Num <= Score->Parry)
					{
						FontRenderers[3]->SetText(std::to_string(Num), "Yoon-Backjae");
						ElapsedTime = 0.0f;
						++Num;
					}

					if (Num > Score->Parry)
					{
						Num = 0;
						ElapsedTime = 0.0f;
						Phase = ScorePhase::UseCard;
					}
				}
				else
				{
					FontRenderers[3]->SetText("0", "Yoon-Backjae");
					Num = 0;
					ElapsedTime = 0.0f;
					Phase = ScorePhase::UseCard;
				}
			}
		}

		else if (Phase == ScorePhase::UseCard)
		{
			if (nullptr != FontRenderers[4])
			{
				if (Score->UseCard != 0)
				{
					if (Num <= Score->UseCard)
					{
						FontRenderers[3]->SetText(std::to_string(Num), "Yoon-Backjae");
						ElapsedTime = 0.0f;
						++Num;
					}

					if (Num > Score->UseCard)
					{
						Num = 0;
						ElapsedTime = 0.0f;
						Phase = ScorePhase::SkillLevel;
					}
				}

				else
				{
					FontRenderers[4]->SetText("0", "Yoon-Backjae");
					Num = 0;
					ElapsedTime = 0.0f;
				}
			}
		}

		else if (Phase == ScorePhase::SkillLevel)
		{
			if (nullptr != FontRenderers[5])
			{
				for (int i = 0; i < Score->SkillLevel; i++)
				{

				}
			}
		}
	}
}

void ScoreLevel::End()
{
}
