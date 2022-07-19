#include "PreCompile.h"
#include "SelectLevel.h"
#include "Background.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

SelectLevel::SelectLevel()
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
	}

	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	{
		Background* SelectBackground = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = SelectBackground->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 1280,720,100 });
		Renderer->SetTexture("SelectBackground.png");
	}

	{
		Background* Button = CreateActor<Background>(GameObjectGroup::UI);
		OptionRenderer = Button->CreateComponent<GameEngineTextureRenderer>();
		OptionRenderer->GetTransform().SetLocalScale({ 61,128,100 });
		OptionRenderer->GetTransform().SetLocalPosition({ 0,100,0 });
		OptionRenderer->SetTexture("Start.png");
	}	
}

void SelectLevel::Update(float _DeltaTime)
{
	// ĳ���� �����ϸ� �ִϸ��̼�
	// �ִϸ��̼��� ������
	// GEngine::ChangeLevel(""); // DLC ����

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		// �Ʒ� Ű�� ���Ȱ�,
		// ���� �ִϸ��̼��� Start�� -> Option
		// Option -> DLC
		// DLC -> End
		// End -> Start
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{

		// �Ʒ� Ű�� ���Ȱ�,
		// End -> DLC
		// DLC -> Option
		// Option�� -> Start
		// Start -> End
	}

	// ���� �ִϸ��̼��� Start�� -> ���Ͱ� ����������
	// Option â�� �ߵ���

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Hourglass");
	}
}


void SelectLevel::End()
{
	int a = 0;
}