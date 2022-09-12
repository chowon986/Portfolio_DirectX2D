#pragma once
#include "BulletBase.h"

class GameEngineCollision;
class GameEngineTextureRenderer;
class AnimalBulletPhysicsComponent;
class AnimalBullet : public BulletBase
{
public:
	AnimalBullet();
	~AnimalBullet();
	AnimalBullet(const AnimalBullet& _Other) = delete;
	AnimalBullet(AnimalBullet&& _Other) noexcept = delete;
	AnimalBullet& operator=(const AnimalBullet& _Other) = delete;
	AnimalBullet& operator=(AnimalBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }
	void SetAnimalBulletPhysicsComponent(AnimalBulletPhysicsComponent* _Physics);
	AnimalBulletPhysicsComponent* GetMonsterPhysicsComponent() { return Physics; }
	std::string GetAnimal() { return Animal; }
	void SetAnimal(std::string _Animal) { Animal = _Animal; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	GameEngineCollision* Collision;
	AnimalBulletPhysicsComponent* Physics;
	std::string Animal;
};

