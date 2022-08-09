#include "PreCompile.h"
#include "BulldogPlane.h"

BulldogPlane::BulldogPlane()
	:Renderer(nullptr)
{
}

BulldogPlane::~BulldogPlane()
{
}

void BulldogPlane::SetRenderer(GameEngineTextureRenderer* _Renderer)
{
	Renderer = _Renderer;
}

void BulldogPlane::Start()
{
	{
		GetTransform().SetWorldPosition({ 640, -300, (int)ZOrder::NPC });

		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFront", FrameAnimation_DESC("BulldogPlaneFront", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFront");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
		//Renderer->GetTransform().SetLocalPosition({ 640, -435, (int)ZOrder::UI });
		
		Renderer->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x + 0, GetTransform().GetWorldPosition().y -200, (int)ZOrder::UI });
	}

	//{
	//	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	//	Renderer->CreateFrameAnimationFolder("BulldogPlaneWingLeft", FrameAnimation_DESC("BulldogPlaneWingLeft", 0.1f, true));
	//	Renderer->ChangeFrameAnimation("BulldogPlaneWingLeft");
	//	Renderer->ScaleToTexture();
	//	Renderer->SetPivot(PIVOTMODE::BOT);
	//	Renderer->GetTransform().SetLocalPosition({ 300, -400, (int)ZOrder::NPC + 3 });
	//}
}

void BulldogPlane::Update(float _DeltaTime)
{
	//Renderer->ScaleToTexture();

}

void BulldogPlane::End()
{
}
