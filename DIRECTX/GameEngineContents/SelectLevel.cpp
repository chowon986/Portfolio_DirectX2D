#include "PreCompile.h"
#include "SelectLevel.h"
#include "Background.h"
#include <functional>
#include "CharacterState.h"
#include <GameEngineCore/GameEngineBlur.h>
#include "PeaShooterItem.h"
#include "PeaShooter.h"
#include "SuperBeamItem.h"
#include "SuperGhostItem.h"
#include "SuperInvincibleItem.h"
#include "AstalCookieItem.h"
#include "CharacterScore.h"
#include <GameEngineContents/TextureLoadUtils.h>

SelectLevel::SelectLevel()
	: OptionRenderer(nullptr)
	, LetterRenderer(nullptr)
	, PlayerARenderer(nullptr)
	, PlayerBRenderer(nullptr)
	, ScreenLightRenderer(nullptr)
	, SelectScreenRenderer(nullptr)
	, RedSelectBoxRenderer(nullptr)
	, BlackLetterRenderer1(nullptr)
	, BlackLetterRenderer2(nullptr)
	, SelectPlayerRenderer(nullptr)
	, SlotSelectionRenderer(nullptr)
	, SelectOutlineRenderer1(nullptr)
	, SelectOutlineRenderer2(nullptr)
	, SelectOutlineRenderer3(nullptr)
	, RecordNum(1)
	, OptionImageNum(0)
	, CupheadOnOffSwitch(true)
	, CanSelectCharacter(true)
	, SelectCharacterElapsedTime(0.0f)
	, Phase(SelectLevelPhase::SelectOption)
	, OptionNumber(std::to_string(OptionImageNum) + ".png")
	, Score(nullptr)
{
}

SelectLevel::~SelectLevel()
{
}

void SelectLevel::LevelStartEvent()
{
	//Loading
	TextureLoadUtils::LoadTextures("12SelectLevel");

	//Start
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	Score = CreateActor<CharacterScore>(GameObjectGroup::CharacterScore);
	Score->SetLevelOverOn();

	std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
		{
			State = _State;
		}
	}

	{
		Background* SelectBackground = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* SelectBackgroundRenderer = SelectBackground->CreateComponent<GameEngineTextureRenderer>();
		SelectBackgroundRenderer->SetTexture("SelectBackground.png");
		SelectBackgroundRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		SelectBackgroundRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, (int)ZOrder::Background });
	}
}

void SelectLevel::Update(float _DeltaTime)
{
	SelectCharacterElapsedTime += _DeltaTime;

	if (GetPhase() == SelectLevelPhase::SelectOption)
	{
		if (OptionRenderer == nullptr)
		{
			OptionNumber = std::to_string(OptionImageNum) + ".png";

			Background* Button = CreateActor<Background>(GameObjectGroup::UI);
			OptionRenderer = Button->CreateComponent<GameEngineTextureRenderer>();
		}

		if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
		{
			++OptionImageNum;

			if (OptionImageNum < 4)
			{
				OptionNumber = std::to_string(OptionImageNum) + ".png";
			}
			else
			{
				OptionImageNum = 0;
				OptionNumber = std::to_string(OptionImageNum) + ".png";
			}
		}

		else if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
		{
			--OptionImageNum;
			if (OptionImageNum >= 0)
			{
				OptionNumber = std::to_string(OptionImageNum) + ".png";
			}
			else
			{
				OptionImageNum = 3;
				OptionNumber = std::to_string(OptionImageNum) + ".png";
			}
		}
		OptionRenderer->SetTexture(OptionNumber);
		OptionRenderer->ScaleToTexture();
		OptionRenderer->GetTransform().SetLocalPosition({ 0.0f, 100.0f, (int)ZOrder::Background - 1 });

		if (true == GameEngineInput::GetInst()->IsDown("Select") && OptionImageNum == 0)
		{
			SetPhase(SelectLevelPhase::SelectRecord);
			SelectCharacterElapsedTime = 0.0f;
		}
	}

	if (GetPhase() == SelectLevelPhase::SelectRecord)
	{
		if (SelectScreenRenderer == nullptr)
		{
			CreateSelectRecordPhaseRenderer();
		}

		if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
		{
			++RecordNum;
			if (RecordNum > 3)
			{
				RecordNum = 1;
			}
		}

		else if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
		{
			--RecordNum;
			if (RecordNum <= 0)
			{
				RecordNum = 3;
			}
		}

		if (RecordNum == 1)
		{
			RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 0.0f, 180.0f, (int)ZOrder::Background - 3 });
			SelectOutlineRenderer1->SetTexture("None.png");
			SelectOutlineRenderer2->SetTexture("slot_selection_box_a.png");
			SelectOutlineRenderer3->SetTexture("slot_selection_box_a.png");
			LetterRenderer->SetTexture("NewGame.png");
			BlackLetterRenderer1->SetTexture("NewGameBlack.png");
			BlackLetterRenderer2->SetTexture("NewGameBlack.png");
		}
		else if (RecordNum == 2)
		{
			RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 0.0f, 25.0f, (int)ZOrder::Background - 3 });
			SelectOutlineRenderer1->SetTexture("slot_selection_box_a.png");
			SelectOutlineRenderer2->SetTexture("None.png");
			SelectOutlineRenderer3->SetTexture("slot_selection_box_a.png");
			LetterRenderer->SetTexture("NewGameBlack.png");
			BlackLetterRenderer1->SetTexture("NewGame.png");
			BlackLetterRenderer2->SetTexture("NewGameBlack.png");
		}

		else
		{
			RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 0.0f, -130.0f, (int)ZOrder::Background - 3 });
			SelectOutlineRenderer1->SetTexture("slot_selection_box_a.png");
			SelectOutlineRenderer2->SetTexture("slot_selection_box_a.png");
			SelectOutlineRenderer3->SetTexture("None.png");
			LetterRenderer->SetTexture("NewGameBlack.png");
			BlackLetterRenderer1->SetTexture("NewGameBlack.png");
			BlackLetterRenderer2->SetTexture("NewGame.png");
		}

		if (true == GameEngineInput::GetInst()->IsDown("Select") && SelectCharacterElapsedTime > 0.3f)
		{
			if (RecordNum == 1)
			{
				LetterRenderer->SetTexture("None.png");
			}
			else if (RecordNum == 2)
			{
				BlackLetterRenderer1->SetTexture("None.png");
			}
			else
			{
				BlackLetterRenderer2->SetTexture("None.png");
			}
			SetPhase(SelectLevelPhase::SelectPlayer);
			SelectCharacterElapsedTime = 0.0f;
		}

		if (true == GameEngineInput::GetInst()->IsDown("ESC"))
		{
			SelectScreenRenderer->Death();
			SelectScreenRenderer = nullptr;
			RedSelectBoxRenderer->Death();
			RedSelectBoxRenderer = nullptr;
			SelectOutlineRenderer1->Death();
			SelectOutlineRenderer1 = nullptr;
			SelectOutlineRenderer2->Death();
			SelectOutlineRenderer2 = nullptr;
			SelectOutlineRenderer3->Death();
			SelectOutlineRenderer3 = nullptr;
			LetterRenderer->Death();
			LetterRenderer = nullptr;
			BlackLetterRenderer1->Death();
			BlackLetterRenderer1 = nullptr;
			BlackLetterRenderer2->Death();
			BlackLetterRenderer2 = nullptr;
			SetPhase(SelectLevelPhase::SelectOption);
		}
	}

	if (GetPhase() == SelectLevelPhase::SelectPlayer)
	{
		if (CanSelectCharacter == true)
		{
			CreateSelectPlayerPhaseRenderer();

			if (true == GameEngineInput::GetInst()->IsDown("MoveRight") || true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
			{
				CupheadOnOffSwitch = !CupheadOnOffSwitch;
			}

			if (CupheadOnOffSwitch == true)
			{
				RedSelectBoxRenderer->SetTexture("slot_selection_box_b.png");
				if (RecordNum == 1)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100.0f, 180.0f, (int)ZOrder::Background - 7 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80.0f, 180.0f, (int)ZOrder::Player });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200.0f, 180.0f, (int)ZOrder::Background - 8 });
				}
				else if (RecordNum == 2)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100.0f, 25.0f, (int)ZOrder::Background - 7 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80.0f, 25.0f, (int)ZOrder::Background - 8 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200.0f, 25.0f, (int)ZOrder::Background - 8 });
				}
				else
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100.0f, -130.0f, (int)ZOrder::Background - 7 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80.0f, -130.0f, (int)ZOrder::Background - 8 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200.0f, -130.0f, (int)ZOrder::Background - 8 });
				}

				SelectPlayerRenderer->SetTexture("SelectPlayerA.png");
				SlotSelectionRenderer->SetTexture("slot_selection_bg_bottom_CH.png");
				PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
				PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
			}

			else if (CupheadOnOffSwitch == false)
			{
				RedSelectBoxRenderer->SetTexture("slot_selection_box_b_MM.png");
				if (RecordNum == 1)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100.0f, 180.0f, (int)ZOrder::Background - 7 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80.0f, 180.0f, (int)ZOrder::Player });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200.0f, 180.0f, (int)ZOrder::Background - 8 });
				}
				else if (RecordNum == 2)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100.0f, 25.0f, (int)ZOrder::Background - 7 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80.0f, 25.0f, (int)ZOrder::Background - 8 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200.0f, 25.0f, (int)ZOrder::Background - 8 });
				}
				else
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100.0f, -130.0f, (int)ZOrder::Background - 7 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80.0f, -130.0f, (int)ZOrder::Background - 8 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200.0f, -130.0f, (int)ZOrder::Background - 8 });
				}

				SelectPlayerRenderer->SetTexture("SelectPlayer.png");
				PlayerARenderer->ChangeFrameAnimation("SelectPlayerALine");
				PlayerBRenderer->ChangeFrameAnimation("SelectMugman");
				SlotSelectionRenderer->SetTexture("slot_selection_bg_bottom_MM.png");
			}

			if (true == GameEngineInput::GetInst()->IsDown("Select"))
			{
				if (SelectCharacterElapsedTime > 0.3f)
				{
					if (CupheadOnOffSwitch == true)
					{
						State->Type = CharacterType::Cuphead;
						CanSelectCharacter = false;
						PlayerARenderer->ChangeFrameAnimation("SelectCupheadOk");
					}

					else
					{
						State->Type = CharacterType::Mugman;
						CanSelectCharacter = false;
						PlayerBRenderer->ChangeFrameAnimation("SelectMugmanOk");
					}
				}
			}

			if (true == GameEngineInput::GetInst()->IsDown("ESC"))
			{
				RedSelectBoxRenderer->SetTexture("slot_selection_box_b.png");
				SlotSelectionRenderer->Death();
				SlotSelectionRenderer = nullptr;
				SelectPlayerRenderer->Death();
				SelectPlayerRenderer = nullptr;
				PlayerARenderer->Death();
				PlayerARenderer = nullptr;
				PlayerBRenderer->Death();
				PlayerBRenderer = nullptr;
				ScreenLightRenderer->Death();
				ScreenLightRenderer = nullptr;
				SetPhase(SelectLevelPhase::SelectRecord);
			}
		}
	}
}


void SelectLevel::End()
{
	GameEngineInput::GetInst()->Reset();
}

void SelectLevel::EndAnimation(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Hourglass");
}

SelectLevelPhase SelectLevel::GetPhase()
{
	return Phase;
}

void SelectLevel::SetPhase(SelectLevelPhase _Phase)
{
	if (Phase != _Phase)
	{
		Phase = _Phase;
	}
}

void SelectLevel::CreateSelectRecordPhaseRenderer()
{
	Background* SelectScreen = CreateActor<Background>(GameObjectGroup::UI);
	SelectScreenRenderer = SelectScreen->CreateComponent<GameEngineTextureRenderer>();
	SelectScreenRenderer->SetTexture("slot_selection_bg.png");
	SelectScreenRenderer->ScaleToTexture();
	SelectScreenRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, (int)ZOrder::Background - 2 });

	if (RedSelectBoxRenderer == nullptr)
	{
		Background* RedBox = CreateActor<Background>(GameObjectGroup::UI);
		RedSelectBoxRenderer = RedBox->CreateComponent<GameEngineTextureRenderer>();
		RedSelectBoxRenderer->SetTexture("slot_selection_box_b.png");
		RedSelectBoxRenderer->ScaleToTexture();
		RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 0.0f, +180.0f, (int)ZOrder::Background - 3 });
	}

	if (SelectOutlineRenderer1 == nullptr)
	{
		Background* SelectOutLineA = CreateActor<Background>(GameObjectGroup::UI);
		SelectOutlineRenderer1 = SelectOutLineA->CreateComponent<GameEngineTextureRenderer>();
		SelectOutlineRenderer1->SetTexture("None.png");
		SelectOutlineRenderer1->ScaleToTexture();
		SelectOutlineRenderer1->GetTransform().SetLocalPosition({ 0.0f, 180.0f, (int)ZOrder::Background - 4 });
	}

	if (SelectOutlineRenderer2 == nullptr)
	{
		Background* SelectOutLineB = CreateActor<Background>(GameObjectGroup::UI);
		SelectOutlineRenderer2 = SelectOutLineB->CreateComponent<GameEngineTextureRenderer>();
		SelectOutlineRenderer2->SetTexture("slot_selection_box_a.png");
		SelectOutlineRenderer2->ScaleToTexture();
		SelectOutlineRenderer2->GetTransform().SetLocalPosition({ 0.0f, 25.0f, (int)ZOrder::Background - 4 });
	}

	if (SelectOutlineRenderer3 == nullptr)
	{
		Background* SelectOutLineC = CreateActor<Background>(GameObjectGroup::UI);
		SelectOutlineRenderer3 = SelectOutLineC->CreateComponent<GameEngineTextureRenderer>();
		SelectOutlineRenderer3->SetTexture("slot_selection_box_a.png");
		SelectOutlineRenderer3->ScaleToTexture();
		SelectOutlineRenderer3->GetTransform().SetLocalPosition({ 0.0f, -130.0f, (int)ZOrder::Background - 4 });
	}

	if (LetterRenderer == nullptr)
	{
		Background* Letter = CreateActor<Background>(GameObjectGroup::UI);
		LetterRenderer = Letter->CreateComponent<GameEngineTextureRenderer>();
		LetterRenderer->SetTexture("NewGame.png");
		LetterRenderer->ScaleToTexture();
		LetterRenderer->GetTransform().SetLocalPosition({ 0.0f, 180.0f, (int)ZOrder::Background - 5 });
	}

	if (BlackLetterRenderer1 == nullptr)
	{
		Background* BlackLetterA = CreateActor<Background>(GameObjectGroup::UI);
		BlackLetterRenderer1 = BlackLetterA->CreateComponent<GameEngineTextureRenderer>();
		BlackLetterRenderer1->SetTexture("NewGameBlack.png");
		BlackLetterRenderer1->ScaleToTexture();
		BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0.0f, 25.0f, (int)ZOrder::Background - 6 });
	}

	if (BlackLetterRenderer2 == nullptr)
	{
		Background* BlackLetterB = CreateActor<Background>(GameObjectGroup::UI);
		BlackLetterRenderer2 = BlackLetterB->CreateComponent<GameEngineTextureRenderer>();
		BlackLetterRenderer2->SetTexture("NewGameBlack.png");
		BlackLetterRenderer2->ScaleToTexture();
		BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0.0f, -130.0f, (int)ZOrder::Background - 6 });
	}
}

void SelectLevel::CreateSelectPlayerPhaseRenderer()
{
	if (SelectPlayerRenderer == nullptr)
	{
		Background* SelectPlayer = CreateActor<Background>(GameObjectGroup::UI);
		SelectPlayerRenderer = SelectPlayer->CreateComponent<GameEngineTextureRenderer>();
		SelectPlayerRenderer->SetTexture("SelectPlayerA.png");
		SelectPlayerRenderer->ScaleToTexture();
		SelectPlayerRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, (int)ZOrder::Background - 7 });
	}

	if (PlayerARenderer == nullptr)
	{
		Background* PlayerA = CreateActor<Background>(GameObjectGroup::UI);
		PlayerARenderer = PlayerA->CreateComponent<GameEngineTextureRenderer>();
		PlayerARenderer->CreateFrameAnimationFolder("SelectCuphead", FrameAnimation_DESC("SelectCuphead", 0.1f));
		PlayerARenderer->CreateFrameAnimationFolder("SelectCupheadOk", FrameAnimation_DESC("SelectCupheadOk", 0.1f));
		PlayerARenderer->AnimationBindEnd("SelectCupheadOk", std::bind(&SelectLevel::EndAnimation, this, std::placeholders::_1));
		PlayerARenderer->CreateFrameAnimationFolder("SelectPlayerALine", FrameAnimation_DESC("SelectPlayerALine", 0.1f));
		PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
		PlayerARenderer->SetScaleModeImage();
	}

	if (PlayerBRenderer == nullptr)
	{
		Background* PlayerB = CreateActor<Background>(GameObjectGroup::UI);
		PlayerBRenderer = PlayerB->CreateComponent<GameEngineTextureRenderer>();
		PlayerBRenderer->CreateFrameAnimationFolder("SelectMugman", FrameAnimation_DESC("SelectMugman", 0.1f));
		PlayerBRenderer->CreateFrameAnimationFolder("SelectMugmanOK", FrameAnimation_DESC("SelectMugmanOK", 0.1f));
		PlayerBRenderer->CreateFrameAnimationFolder("SelectPlayerBLine", FrameAnimation_DESC("SelectPlayerBLine", 0.1f));
		PlayerBRenderer->AnimationBindEnd("SelectMugmanOK", std::bind(&SelectLevel::EndAnimation, this, std::placeholders::_1));
		PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
		PlayerBRenderer->SetScaleModeImage();
	}

	if (ScreenLightRenderer == nullptr)
	{
		Background* ScreenLight = CreateActor<Background>(GameObjectGroup::UI);
		ScreenLightRenderer = ScreenLight->CreateComponent <GameEngineTextureRenderer>();
		ScreenLightRenderer->CreateFrameAnimationFolder("LightDown", FrameAnimation_DESC("IrisB", 0, 0, 0.1f));
		ScreenLightRenderer->ChangeFrameAnimation("LightDown");
		ScreenLightRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, (int)ZOrder::UI + 1 });
		ScreenLightRenderer->GetPixelData().PlusColor.a = 0.3f;
	}

	if (SlotSelectionRenderer == nullptr)
	{
		Background* SlotSelection = CreateActor<Background>(GameObjectGroup::UI);
		SlotSelectionRenderer = SlotSelection->CreateComponent <GameEngineTextureRenderer>();
		SlotSelectionRenderer->SetTexture("slot_selection_bg_bottom_CH.png");
		SlotSelectionRenderer->ScaleToTexture();
		SlotSelectionRenderer->GetTransform().SetLocalPosition({ -1.5f, -242.0f, (int)ZOrder::Background - 3 });
	}
}
