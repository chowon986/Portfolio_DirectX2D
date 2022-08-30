#pragma once
#include "IInGameMonsterBase.h"
#include <string>

class SecretLeader : public IInGameMonsterBase
{
public:
	SecretLeader();
	~SecretLeader();

	SecretLeader(const SecretLeader& _Other) = delete;
	SecretLeader(SecretLeader&& _Other) noexcept = delete;
	SecretLeader& operator=(const SecretLeader& _Other) = delete;
	SecretLeader& operator=(SecretLeader&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void TakeDamage() override;
	void Prepare() override;
	void Idle() override;
	void Shoot() override;
	void Die() override;

private:
};