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
	, OnceCheck(false)
	, PlusXIndex(0)
	, StarElapsedTime(0.0f)
	, TTLGrade(0)
	, GradeOnceCheck(false)
	, ScoreDone(false)
	, ScoreStartOn(false)
{
}

ScoreLevel::~ScoreLevel()
{
}

void ScoreLevel::LevelStartEvent()
{
	if (false == TextureLoadUtils::LoadTextures("08ScoreLevel"))
	{
		return;
	}

	//Start
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetBackgroundCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera2()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	{
		GameEngineActor* Iris = CreateActor<GameEngineActor>();
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->CreateFrameAnimationFolder("LightOn", FrameAnimation_DESC("IrisA", 0.05f, false));
		IrisRenderer->CreateFrameAnimationFolder("LightOff", FrameAnimation_DESC("IrisB", 0.05f, true));
		IrisRenderer->ChangeFrameAnimation("LightOn");
		IrisRenderer->GetTransform().SetLocalScale(float4{ 1280.0f,720.0f,1.0f });
		IrisRenderer->GetTransform().SetLocalPosition(float4{ 0.0f, 0.0f, -10 });
		IrisRenderer->AnimationBindFrame("LightOff", std::bind(&ScoreLevel::OnLightOffAnimationFrameChanged, this, std::placeholders::_1));
		IrisRenderer->AnimationBindFrame("LightOn", std::bind(&ScoreLevel::OnLightOnAnimationFrameChanged, this, std::placeholders::_1));
		IrisRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
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

		GameEngineActor* FontB = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererB = FontB->CreateComponent<GameEngineFontRenderer>();
		FontRendererB->SetText(" : ", "Yoon-Backjae");
		FontRendererB->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererB->SetSize(35);
		FontRendererB->SetScreenPostion(float4{ 885.0f, 250.0f, (int)ZOrder::Foreground - 1 });

		GameEngineActor* FontC = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererC = FontC->CreateComponent<GameEngineFontRenderer>();
		FontRendererC->SetText("00", "Yoon-Backjae");
		FontRendererC->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererC->SetSize(35);
		FontRendererC->SetScreenPostion(float4{ 910.0f, 250.0f, (int)ZOrder::Foreground - 1 });

		GameEngineActor* FontD = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererD = FontD->CreateComponent<GameEngineFontRenderer>();
		FontRendererD->SetText(" /3", "Yoon-Backjae");
		FontRendererD->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererD->SetSize(35);
		FontRendererD->SetScreenPostion(float4{ 905.0f, 295.0f, (int)ZOrder::Foreground - 1 });

		GameEngineActor* FontE = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererE = FontE->CreateComponent<GameEngineFontRenderer>();
		FontRendererE->SetText(" /3", "Yoon-Backjae");
		FontRendererE->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererE->SetSize(35);
		FontRendererE->SetScreenPostion(float4{ 905.0f, 340.0f, (int)ZOrder::Foreground - 1 });

		GameEngineActor* FontF = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRendererF = FontF->CreateComponent<GameEngineFontRenderer>();
		FontRendererF->SetText(" /6", "Yoon-Backjae");
		FontRendererF->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererF->SetSize(35);
		FontRendererF->SetScreenPostion(float4{ 905.0f, 385.0f, (int)ZOrder::Foreground - 1 });

		GameEngineActor* FontG = CreateActor<GameEngineActor>(); // HP
		GameEngineFontRenderer* FontRendererG = FontG->CreateComponent<GameEngineFontRenderer>();
		FontRendererG->SetText("0", "Yoon-Backjae");
		FontRendererG->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererG->SetSize(35);
		FontRendererG->SetScreenPostion(float4{ 895.0f, 295.0f, (int)ZOrder::Foreground - 1 });

		GameEngineActor* FontH = CreateActor<GameEngineActor>(); // Parry
		GameEngineFontRenderer* FontRendererH = FontG->CreateComponent<GameEngineFontRenderer>();
		FontRendererH->SetText("0", "Yoon-Backjae");
		FontRendererH->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererH->SetSize(35);
		FontRendererH->SetScreenPostion(float4{ 895.0f, 340.0f, (int)ZOrder::Foreground - 1 });

		GameEngineActor* FontI = CreateActor<GameEngineActor>(); // UseCard
		GameEngineFontRenderer* FontRendererI = FontI->CreateComponent<GameEngineFontRenderer>();
		FontRendererI->SetText("0", "Yoon-Backjae");
		FontRendererI->SetColor({ (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, (1.0 / 255) * 190.0f, 1.0f });
		FontRendererI->SetSize(35);
		FontRendererI->SetScreenPostion(float4{ 895.0f, 385.0f, (int)ZOrder::Foreground - 1 });
		
		FontRenderers.insert(std::make_pair(0, FontRendererA));
		FontRenderers.insert(std::make_pair(1, FontRendererC));
		FontRenderers.insert(std::make_pair(2, FontRendererG));
		FontRenderers.insert(std::make_pair(3, FontRendererH));
		FontRenderers.insert(std::make_pair(4, FontRendererI));
	}

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

void ScoreLevel::LevelEndEvent()
{
	Controller.Stop();
}

void ScoreLevel::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;
	CountElapsedTime += _DeltaTime;

	if (nullptr != Score && ScoreStartOn == true)
	{
		if (CountElapsedTime > 0.3)
		{
			Controller = GameEngineSound::SoundPlayControl("win_score_tick_02.wav");
			CountElapsedTime = 0.0f;
		}

		if (ElapsedTime > IntervalTime)
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
							if (Num > 3)
							{
								Num = 3;
							}

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
							if (Num > 3)
							{
								Num = 3;
							}

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
							if (Num > 6)
							{
								Num = 6;
							}

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
						Phase = ScorePhase::SkillLevel;
					}
				}
			}

			else if (Phase == ScorePhase::SkillLevel)
			{
				if (false == OnceCheck)
				{
					StarElapsedTime += _DeltaTime;

					if (PlusXIndex <= Score->SkillLevel)
					{
						if (StarElapsedTime > 0.2)
						{
							GameEngineActor* StarActor = CreateActor<GameEngineActor>();
							GameEngineTextureRenderer* Renderer = StarActor->CreateComponent<GameEngineTextureRenderer>();
							Renderer->CreateFrameAnimationFolder("LittileStar", FrameAnimation_DESC("LittileStar", 0.05f, false));
							Renderer->ChangeFrameAnimation("LittileStar");
							Renderer->SetScaleModeImage();
							Renderer->GetTransform().SetWorldPosition({ (895.0f + (PlusXIndex * 30)), -452.0f,(int)ZOrder::Foreground - 1 });
							if (PlusXIndex == Score->SkillLevel - 1)
							{
								OnceCheck = true;
								StarElapsedTime = 0.0f;
							}
							else
							{
								++PlusXIndex;
								StarElapsedTime = 0.0f;
							}
						}
					}
				}
				else // Grade
				{
					if (false == GradeOnceCheck)
					{
						TTLGrade += Score->HP; // Max 3
						TTLGrade += Score->Parry; // Max 3
						TTLGrade += Score->UseCard; // Max 6
						TTLGrade += Score->SkillLevel; // Max 2
						if (PlayMinute < 1)
						{
							TTLGrade += 1; // TTL Max 15
						}

						if (TTLGrade > 12)
						{
							Grade = "A";
						}
						else if (TTLGrade > 9 && TTLGrade <= 12)
						{
							Grade = "B";
						}
						else if (TTLGrade > 6 && TTLGrade <= 9)
						{
							Grade = "C";
						}
						else if (TTLGrade > 3 && TTLGrade <= 6)
						{
							Grade = "D";
						}
						else if (TTLGrade <= 3)
						{
							Grade = "E";
						}

						GradeOnceCheck = true;
					}
					else
					{
						GradeElapsedTime += _DeltaTime;
						if (GradeElapsedTime > 0.5)
						{
							if (ScoreDone == false)
							{
								GameEngineActor* TTLGrade = CreateActor<GameEngineActor>();
								GameEngineFontRenderer* GradeRenderer = TTLGrade->CreateComponent<GameEngineFontRenderer>();
								GradeRenderer->SetText(Grade, "Yoon-Backjae");
								GradeRenderer->SetColor({ (1.0 / 255) * 198.0f, (1.0 / 255) * 164.0f, (1.0 / 255) * 41.0f, 1.0f });
								GradeRenderer->SetSize(50);
								GradeRenderer->SetScreenPostion(float4{ 850.0f, 500.0f, (int)ZOrder::Foreground - 1 });
								GradeRenderer->SetRenderingOrder(10000);
								GradeElapsedTime = 0.0f;
								ScoreDone = true;
							}
							else
							{
								Score->Win = true;
								if (GradeElapsedTime > 1.0f)
								{
									IrisRenderer->ChangeFrameAnimation("LightOff");
								}

							}
						}
					}
				}
			}
		}
	}
}
void ScoreLevel::End()
{
}

void ScoreLevel::OnLightOffAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 15)
	{
		GEngine::ChangeLevel("WorldMap");
	}
}

void ScoreLevel::OnLightOnAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 16)
	{
		ScoreStartOn = true;
		GameEngineSound::SoundPlayOneShot("MUS_VictoryScreen.wav");
	}
}
