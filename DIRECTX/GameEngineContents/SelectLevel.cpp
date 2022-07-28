#include "PreCompile.h"
#include "SelectLevel.h"
#include "Background.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <functional>

SelectLevel::SelectLevel()
	: Num(0)
	, OptionNumber(std::to_string(Num) + ".png")
	, SelectOptionOn(true)
	, SelectDataOn(false)
	, SelectCharacterOn(false)
	, OptionRenderer(nullptr)
	, SelectScreenRenderer(nullptr)
	, RedSelectBoxRenderer(nullptr)
	, SelectOutlineRenderer1(nullptr)
	, SelectOutlineRenderer2(nullptr)
	, SelectOutlineRenderer3(nullptr)
	, LetterRenderer(nullptr)
	, SelectBlockNum(0)
	, OnceCheck(false)
	, CupheadOn(false)
	, MugmanOn(false)
	, DeltaTime(0.0f)
{
}

SelectLevel::~SelectLevel()
{
}

void SelectLevel::Start()
{

	if (false == GameEngineInput::GetInst()->IsKey("MoveDown"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Select", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("ESC", VK_ESCAPE);
	}

	{
		Background* SelectBackground = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = SelectBackground->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 1280,720,1 });
		Renderer->SetTexture("SelectBackground.png");
		Renderer->SetPivot(PIVOTMODE::CENTER);
		Renderer->GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::Background});
	}

	{
		Background* Button = CreateActor<Background>(GameObjectGroup::UI);
		OptionRenderer = Button->CreateComponent<GameEngineTextureRenderer>();
		OptionRenderer->SetTexture("0.png");
		OptionRenderer->ScaleToTexture();
		OptionRenderer->SetPivot(PIVOTMODE::CENTER);
		OptionRenderer->GetTransform().SetLocalPosition({ 0, 100, (int)ZOrder::Background-1 });
	}	

	{
		Background* SelectScreen = CreateActor<Background>(GameObjectGroup::UI);
		SelectScreenRenderer = SelectScreen->CreateComponent<GameEngineTextureRenderer>();
		SelectScreenRenderer->SetTexture("slot_selection_bg.png");
		SelectScreenRenderer->SetPivot(PIVOTMODE::CENTER);
		SelectScreenRenderer->GetTransform().SetLocalPosition({ 0,0,(int)ZOrder::Background-2 });
	}

	{
		Background* RedBox = CreateActor<Background>(GameObjectGroup::UI);
		RedSelectBoxRenderer = RedBox->CreateComponent<GameEngineTextureRenderer>();
		RedSelectBoxRenderer->SetTexture("slot_selection_box_b.png");
		RedSelectBoxRenderer->SetPivot(PIVOTMODE::CENTER);
		RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,+180,(int)ZOrder::Background-3 });
	}

	{
		Background* SelectOutLine = CreateActor<Background>(GameObjectGroup::UI);
		SelectOutlineRenderer1 = SelectOutLine->CreateComponent<GameEngineTextureRenderer>();
		SelectOutlineRenderer1->SetTexture("slot_selection_box_a.png");
		SelectOutlineRenderer1->SetPivot(PIVOTMODE::CENTER);
		SelectOutlineRenderer1->GetTransform().SetLocalPosition({ 0, 180, (int)ZOrder::Background-4 });


		SelectOutlineRenderer2 = SelectOutLine->CreateComponent<GameEngineTextureRenderer>();
		SelectOutlineRenderer2->SetTexture("slot_selection_box_a.png");
		SelectOutlineRenderer2->SetPivot(PIVOTMODE::CENTER);
		SelectOutlineRenderer2->GetTransform().SetLocalPosition({ 0, 25, (int)ZOrder::Background-4 });


		SelectOutlineRenderer3 = SelectOutLine->CreateComponent<GameEngineTextureRenderer>();
		SelectOutlineRenderer3->SetTexture("slot_selection_box_a.png");
		SelectOutlineRenderer3->SetPivot(PIVOTMODE::CENTER);
		SelectOutlineRenderer3->GetTransform().SetLocalPosition({ 0, -130, (int)ZOrder::Background-4 });
	}

	{
		Background* Letter = CreateActor<Background>(GameObjectGroup::UI);
		LetterRenderer = Letter->CreateComponent<GameEngineTextureRenderer>();
		LetterRenderer->SetTexture("NewGame.png");
		LetterRenderer->SetPivot(PIVOTMODE::CENTER);
		LetterRenderer->GetTransform().SetLocalPosition({ 0, 180, (int)ZOrder::Background-5 });

	}

	{
		Background* BlackLetter = CreateActor<Background>(GameObjectGroup::UI);
		BlackLetterRenderer1 = BlackLetter->CreateComponent<GameEngineTextureRenderer>();
		BlackLetterRenderer1->SetTexture("NewGameBlack.png");
		BlackLetterRenderer2 = BlackLetter->CreateComponent<GameEngineTextureRenderer>();
		BlackLetterRenderer2->SetTexture("NewGameBlack.png");
		BlackLetterRenderer1->SetPivot(PIVOTMODE::CENTER);
		BlackLetterRenderer2->SetPivot(PIVOTMODE::CENTER);
		BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0, 25, (int)ZOrder::Background-6 });
		BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0, -130, (int)ZOrder::Background-6 });

	}

	{
		Background* SelectPlayer = CreateActor<Background>(GameObjectGroup::UI);
		SelectPlayerRenderer = SelectPlayer->CreateComponent<GameEngineTextureRenderer>();
		SelectPlayerRenderer->SetTexture("SelectPlayerA.png");
		SelectPlayerRenderer->SetPivot(PIVOTMODE::CENTER);
		SelectPlayerRenderer->GetTransform().SetLocalPosition({ 0,0, (int)ZOrder::Background-7 });
	}

	{
		Background* PlayerA = CreateActor<Background>(GameObjectGroup::UI);
		PlayerARenderer = PlayerA->CreateComponent<GameEngineTextureRenderer>();
		PlayerARenderer->CreateFrameAnimationFolder("SelectCuphead", FrameAnimation_DESC("SelectCuphead", 0.1f));
		PlayerARenderer->CreateFrameAnimationFolder("SelectCupheadOk", FrameAnimation_DESC("SelectCupheadOk", 0.1f));
		PlayerARenderer->AnimationBindEnd("SelectCupheadOk", &SelectLevel::EndAnimation, this);
		PlayerARenderer->CreateFrameAnimationFolder("SelectPlayerALine", FrameAnimation_DESC("SelectPlayerALine", 0.1f));
		PlayerARenderer->ChangeFrameAnimation("SelectCuphead");

	}

	{
		Background* PlayerB = CreateActor<Background>(GameObjectGroup::UI);
		PlayerBRenderer = PlayerB->CreateComponent<GameEngineTextureRenderer>();
		PlayerBRenderer->CreateFrameAnimationFolder("SelectMugman", FrameAnimation_DESC("SelectMugman", 0.1f));
		PlayerBRenderer->CreateFrameAnimationFolder("SelectMugmanOK", FrameAnimation_DESC("SelectMugmanOK", 0.1f));
		PlayerBRenderer->CreateFrameAnimationFolder("SelectPlayerBLine", FrameAnimation_DESC("SelectPlayerBLine", 0.1f));
		PlayerBRenderer->AnimationBindEnd("SelectMugmanOK", &SelectLevel::EndAnimation, this);
		PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");

	}
}

void SelectLevel::Update(float _DeltaTime)
{
	DeltaTime += GameEngineTime::GetDeltaTime();
	if (true == SelectDataOn)
	{
		if (true == GameEngineInput::GetInst()->IsDown("ESC"))
		{
			SelectOptionOn = true;
			SelectDataOn = false;
			SelectCharacterOn = false;
			OnceCheck = false;
			CupheadOn = false;
			MugmanOn = false;
			SelectScreenRenderer->GetTransform().SetLocalScale({ 0, 0, 1 });
			RedSelectBoxRenderer->GetTransform().SetLocalScale({ 0, 0, 1 });
			LetterRenderer->GetTransform().SetLocalScale({ 0, 0, 1 });
			BlackLetterRenderer1->GetTransform().SetLocalScale({ 0, 0, 1 });
			BlackLetterRenderer2->GetTransform().SetLocalScale({ 0, 0, 1 });
			SelectOutlineRenderer1->GetTransform().SetLocalScale({ 0, 0, 1 });
			SelectOutlineRenderer2->GetTransform().SetLocalScale({ 0, 0, 1 });
			SelectOutlineRenderer3->GetTransform().SetLocalScale({ 0, 0, 1 });
			SelectPlayerRenderer->GetTransform().SetLocalScale({ 0, 0, 1 });
			PlayerARenderer->GetTransform().SetLocalScale({ 0, 0, 1 });
			PlayerBRenderer->GetTransform().SetLocalScale({ 0, 0, 1 });
		}

		if (true == GameEngineInput::GetInst()->IsDown("Select") && Num >= 0 && Num <3)
		{
			SelectCharacterOn = true;
			SelectBlockNum = Num;
			Num = 0;
		}
	} 

	if (SelectCharacterOn == true)
	{
		LetterRenderer->GetTransform().SetLocalScale({ 0, 0, 1 });
		
		if (OnceCheck == false)
		{
			SelectPlayerRenderer->SetTexture("SelectPlayerA.png");
			SelectPlayerRenderer->ScaleToTexture(); 
			PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
			PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
			PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
			CupheadOn = true;
			MugmanOn = false;
			DeltaTime = 0.0f;
			if (SelectBlockNum == 0)
			{
				SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,+180, (int)ZOrder::Background - 7 });
				PlayerARenderer->GetTransform().SetLocalPosition({ 80, 180, (int)ZOrder::Background-8 });
				PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 180, (int)ZOrder::Background-8 });
			}
			if (SelectBlockNum == 1)
			{
				SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,+25,(int)ZOrder::Background - 7 });
				PlayerARenderer->GetTransform().SetLocalPosition({ 80, 25, (int)ZOrder::Background-8 });
				PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 25, (int)ZOrder::Background - 8 });
			}
			if (SelectBlockNum == 2)
			{
				SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,-130, (int)ZOrder::Background - 7 });
				PlayerARenderer->GetTransform().SetLocalPosition({ 80, -130, (int)ZOrder::Background-8 });
				PlayerBRenderer->GetTransform().SetLocalPosition({ 200, -130, (int)ZOrder::Background-8 });
			}
			OnceCheck = true;
		}

		if (true == GameEngineInput::GetInst()->IsDown("Select"))
		{
			if (DeltaTime > 0.5f)
			{
				if (CupheadOn == true)
				{
					PlayerARenderer->ChangeFrameAnimation("SelectCupheadOk");
				}

				else if (MugmanOn == true)
				{
					PlayerBRenderer->ChangeFrameAnimation("SelectMugmanOk");
				}
			}
		}

		if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
		{
			Num += 1;
			if (Num > 1)
			{
				Num = 0;
			}

			if (Num == 0)
			{
				RedSelectBoxRenderer->SetTexture("slot_selection_box_b.png");
				RedSelectBoxRenderer->ScaleToTexture();
				SelectPlayerRenderer->SetTexture("SelectPlayerA.png");
				SelectPlayerRenderer->ScaleToTexture();
				if (SelectBlockNum == 0)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,+180,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,+180,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 180, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 180, (int)ZOrder::Background-8 });
					CupheadOn = true;
					MugmanOn = false;
				}
				if (SelectBlockNum == 1)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,25,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,25,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 25, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 25, (int)ZOrder::Background-8 });
					CupheadOn = true;
					MugmanOn = false;
				}
				if (SelectBlockNum == 2)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,-130,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,-130,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, -130, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, -130, (int)ZOrder::Background-8 });
					CupheadOn = true;
					MugmanOn = false;
				}
			}

			if (Num == 1)
			{
				RedSelectBoxRenderer->SetTexture("slot_selection_box_b_MM.png");
				RedSelectBoxRenderer->ScaleToTexture();
				SelectPlayerRenderer->SetTexture("SelectPlayer.png");
				SelectPlayerRenderer->ScaleToTexture();
				if (SelectBlockNum == 0)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,+180,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ -1,+180,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectPlayerALine");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 180, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectMugman");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 180, (int)ZOrder::Background-8 });
					CupheadOn = false;
					MugmanOn = true;
				}
				if (SelectBlockNum == 1)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,25,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ -1,25,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectPlayerALine");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 25, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectMugman");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 25, (int)ZOrder::Background - 8 });
					CupheadOn = false;
					MugmanOn = true;
				}
				if (SelectBlockNum == 2)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,-130,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ -1,-130,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectPlayerALine");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, -130, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectMugman");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, -130, (int)ZOrder::Background - 8 });
					CupheadOn = false;
					MugmanOn = true;
				}
			}
		}

		if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
		{
			Num -= 1;

			if (Num < 0)
			{
				Num = 1;
			}

			if (Num == 0)
			{
				RedSelectBoxRenderer->SetTexture("slot_selection_box_b.png");
				RedSelectBoxRenderer->ScaleToTexture();
				SelectPlayerRenderer->SetTexture("SelectPlayerA.png");
				SelectPlayerRenderer->ScaleToTexture();
				if (SelectBlockNum == 0)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,+180,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,+180,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 180, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 180, (int)ZOrder::Background - 8 });
					CupheadOn = true;
					MugmanOn = false;
				}
				if (SelectBlockNum == 1)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,25,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,25,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 25, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 25, (int)ZOrder::Background-8 });
					CupheadOn = true;
					MugmanOn = false;
				}
				if (SelectBlockNum == 2)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,-130,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,-130,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectCuphead");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, -130, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectPlayerBLine");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, -130, (int)ZOrder::Background-8 });
					CupheadOn = true;
					MugmanOn = false;
				}
			}

			if (Num == 1)
			{
				RedSelectBoxRenderer->SetTexture("slot_selection_box_b_MM.png");
				RedSelectBoxRenderer->ScaleToTexture();
				SelectPlayerRenderer->SetTexture("SelectPlayer.png");
				SelectPlayerRenderer->ScaleToTexture();
				if (SelectBlockNum == 0)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,+180,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ -1,+180,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectPlayerALine");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 180, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectMugman");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 180, (int)ZOrder::Background-8 });
					CupheadOn = false;
					MugmanOn = true;
				}
				if (SelectBlockNum == 1)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,25,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ -1,25,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectPlayerALine");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, 25, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectMugman");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, 25, (int)ZOrder::Background-8 });
					CupheadOn = false;
					MugmanOn = true;
				}
				if (SelectBlockNum == 2)
				{
					SelectPlayerRenderer->GetTransform().SetLocalPosition({ -100,-130,(int)ZOrder::Background - 7 });
					RedSelectBoxRenderer->GetTransform().SetLocalPosition({ -1,-130,(int)ZOrder::Background - 3 });
					PlayerARenderer->ChangeFrameAnimation("SelectPlayerALine");
					PlayerARenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerARenderer->GetTransform().SetLocalPosition({ 80, -130, (int)ZOrder::Background-8 });
					PlayerBRenderer->ChangeFrameAnimation("SelectMugman");
					PlayerBRenderer->GetTransform().SetLocalScale({ 111, 111, 1 });
					PlayerBRenderer->GetTransform().SetLocalPosition({ 200, -130, (int)ZOrder::Background-8 });
					CupheadOn = false;
					MugmanOn = true;
				}
			}
		}
	}

	if (SelectCharacterOn == false && true == GameEngineInput::GetInst()->IsDown("Select") && Num == 0)
	{
		SelectOptionOn = false;
		SelectDataOn = true;
		Num = 0;
		SelectScreenRenderer->ScaleToTexture();
		RedSelectBoxRenderer->ScaleToTexture();
		RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3, +180, (int)ZOrder::Background - 3 });
		SelectOutlineRenderer1->GetTransform().SetLocalScale({ 0, 0, 1 });
		SelectOutlineRenderer2->ScaleToTexture();
		SelectOutlineRenderer3->ScaleToTexture();
		LetterRenderer->ScaleToTexture(); 
		BlackLetterRenderer1->ScaleToTexture(); 
		BlackLetterRenderer2->ScaleToTexture();
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		Num += 1;
		if (SelectOptionOn)
		{
			if (Num < 4)
			{
				OptionNumber = std::to_string(Num) + ".png";
			}
			else
			{
				Num = 0;
				OptionNumber = std::to_string(Num) + ".png";
			}
			OptionRenderer->SetTexture(OptionNumber);
		}
		else if(SelectCharacterOn == false)
		{
			if (Num > 2)
			{
				Num = 0;
			}

			if (Num == 0)
			{
				SelectScreenRenderer->ScaleToTexture();
				RedSelectBoxRenderer->ScaleToTexture();
				RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,+180,(int)ZOrder::Background - 3 });
				SelectOutlineRenderer1->GetTransform().SetLocalScale({ 0, 0, 1 });
				LetterRenderer->ScaleToTexture();
				LetterRenderer->GetTransform().SetLocalPosition({ 0,+180,(int)ZOrder::Background - 5 });
				BlackLetterRenderer1->ScaleToTexture();
				BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0,+25,(int)ZOrder::Background - 6 });
				BlackLetterRenderer2->ScaleToTexture();
				BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0,-130,(int)ZOrder::Background - 6 });
				SelectOutlineRenderer2->ScaleToTexture();
				SelectOutlineRenderer3->ScaleToTexture();
			}

			if (Num == 1)
			{
				SelectScreenRenderer->ScaleToTexture();
				RedSelectBoxRenderer->ScaleToTexture();
				RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,25,(int)ZOrder::Background - 3 });
				SelectOutlineRenderer1->ScaleToTexture();
				LetterRenderer->ScaleToTexture();
				LetterRenderer->GetTransform().SetLocalPosition({ 0,25,(int)ZOrder::Background - 5 });
				BlackLetterRenderer1->ScaleToTexture();
				BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0,+180,(int)ZOrder::Background - 6 });
				BlackLetterRenderer2->ScaleToTexture();
				BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0,-130,(int)ZOrder::Background - 6 });
				SelectOutlineRenderer2->GetTransform().SetLocalScale({ 0, 0, 1 });
				SelectOutlineRenderer3->ScaleToTexture();
			}

			if (Num == 2)
			{
				SelectScreenRenderer->ScaleToTexture();
				RedSelectBoxRenderer->ScaleToTexture();
				RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,-130,(int)ZOrder::Background - 3 });
				LetterRenderer->ScaleToTexture();
				LetterRenderer->GetTransform().SetLocalPosition({ 0,-130,(int)ZOrder::Background - 5 });
				BlackLetterRenderer1->ScaleToTexture();
				BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0,25,(int)ZOrder::Background - 6 });
				BlackLetterRenderer2->ScaleToTexture();
				BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0,180,(int)ZOrder::Background - 6 });
				SelectOutlineRenderer1->ScaleToTexture();
				SelectOutlineRenderer2->ScaleToTexture();
				SelectOutlineRenderer3->GetTransform().SetLocalScale({ 0, 0, 1 });
			}
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		Num -= 1;
		if (SelectOptionOn)
		{
			if (Num >= 0)
			{
				OptionNumber = std::to_string(Num) + ".png";
			}
			else
			{
				Num = 3;
				OptionNumber = std::to_string(Num) + ".png";
			}

			OptionRenderer->SetTexture(OptionNumber);
		}
		else if(SelectCharacterOn == false)
		{
			if (Num < 0)
			{
				Num = 2;
			}

			if (Num == 0)
			{
				SelectScreenRenderer->ScaleToTexture();
				RedSelectBoxRenderer->ScaleToTexture();
				RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,+180,(int)ZOrder::Background - 3 });
				SelectOutlineRenderer1->GetTransform().SetLocalScale({ 0, 0, 1 });
				LetterRenderer->ScaleToTexture();
				LetterRenderer->GetTransform().SetLocalPosition({ 0,+180,(int)ZOrder::Background - 5 });
				BlackLetterRenderer1->ScaleToTexture();
				BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0,+25,(int)ZOrder::Background - 6 });
				BlackLetterRenderer2->ScaleToTexture();
				BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0,-130,(int)ZOrder::Background - 6 });
				SelectOutlineRenderer2->ScaleToTexture();
				SelectOutlineRenderer3->ScaleToTexture();

			}

			if (Num == 1)
			{
				SelectScreenRenderer->ScaleToTexture();
				RedSelectBoxRenderer->ScaleToTexture();
				RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,25,(int)ZOrder::Background - 3 });
				SelectOutlineRenderer1->ScaleToTexture();
				LetterRenderer->ScaleToTexture();
				LetterRenderer->GetTransform().SetLocalPosition({ 0,25,(int)ZOrder::Background - 5 });
				BlackLetterRenderer1->ScaleToTexture();
				BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0,+180,(int)ZOrder::Background - 6 });
				BlackLetterRenderer2->ScaleToTexture();
				BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0,-130,(int)ZOrder::Background - 6 });
				SelectOutlineRenderer2->GetTransform().SetLocalScale({ 0, 0, 1 });
				SelectOutlineRenderer3->ScaleToTexture();
			}

			if (Num == 2)
			{
				SelectScreenRenderer->ScaleToTexture();
				RedSelectBoxRenderer->ScaleToTexture();
				RedSelectBoxRenderer->GetTransform().SetLocalPosition({ 3,-130,(int)ZOrder::Background - 3 });
				LetterRenderer->ScaleToTexture();
				LetterRenderer->GetTransform().SetLocalPosition({ 0,-130,(int)ZOrder::Background - 5 });
				BlackLetterRenderer1->ScaleToTexture();
				BlackLetterRenderer1->GetTransform().SetLocalPosition({ 0,25,(int)ZOrder::Background - 6 });
				BlackLetterRenderer2->ScaleToTexture();
				BlackLetterRenderer2->GetTransform().SetLocalPosition({ 0,180,(int)ZOrder::Background - 6 });
				SelectOutlineRenderer1->ScaleToTexture();
				SelectOutlineRenderer2->ScaleToTexture();
				SelectOutlineRenderer3->GetTransform().SetLocalScale({ 0, 0, 1 });
			}
		}
	}

	// 현재 애니메이션이 Start고 -> 엔터가 눌러졌으면
	// Option 창이 뜨도록

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Hourglass");
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
