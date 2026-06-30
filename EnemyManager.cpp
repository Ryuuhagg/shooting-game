#include"EnemyManager.h"
#include"Game.h"
void EnemyManager::Init() {
	straightPool.clear();
	wavePool.clear();
	zigzagPool.clear();
	shotPool.clear();
	stalkerPool.clear();
	bigPool.clear();
	bossPool.clear();

	straightPool.resize(30);
	wavePool.resize(30);
	zigzagPool.resize(30);
	shotPool.resize(20);
	stalkerPool.resize(20);
	bigPool.resize(10);
	bossPool.resize(1);
}

void EnemyManager::Spawn(int type, float x, float y, Game& g) {
	int phase = g.GetPhase();
	int hp = 1 + phase * 3;
	float spd = 3.0f + phase / 10.0f;

	switch (type) {
	case 0:
		for (auto& e : straightPool)
			if (!e.IsActive()) { e.Init(x, y, hp, spd); return; }
		break;

	case 1:
		for (auto& e : wavePool)
			if (!e.IsActive()) { e.Init(x, y, hp, spd); return; }
		break;

	case 2:
		for (auto& e : zigzagPool)
			if (!e.IsActive()) { e.Init(x, y, hp, spd); return; }
		break;

	case 3:
		for (auto& e : shotPool)
			if (!e.IsActive()) { e.Init(x, y, g, hp); return; }
		break;

	case 4:
		for (auto& e : stalkerPool)
			if (!e.IsActive()) { e.Init(x, y, g, hp, spd); return; }
		break;
	case 5:
		for(auto& e : bigPool)
			if (!e.IsActive()) { e.Init(x, y, g, hp, spd); return; }
		break;
	}
}

void EnemyManager::SpawnBoss(float x, float y, Game& g) {
	int hp = 100 + g.GetPhase() * 100;

	for (auto& e : bossPool) {
		if (!e.IsActive()) {
			e.Init(x, y, g, hp);
			return;
		}
	}
}

void EnemyManager::Update() {
	for (auto& e : straightPool) {
		if (!e.IsActive()) continue;
		e.Move();
	}

	for (auto& e : wavePool) {
		if (!e.IsActive()) continue;
		e.Move();
	}

	for (auto& e : zigzagPool) {
		if (!e.IsActive()) continue;
		e.Move();
	}

	for (auto& e : shotPool) {
		if (!e.IsActive()) continue;
		e.Move();
	}

	for (auto& e : stalkerPool) {
		if (!e.IsActive()) continue;
		e.Move();
	}

	for (auto& e : bigPool) {
		if (!e.IsActive()) continue;
		e.Move();
	}

	for (auto& e : bossPool) {
		if (!e.IsActive()) continue;
		e.Move();
	}
}

void EnemyManager::Draw(int offsetX, int offsetY)const {
	for (const auto& e : straightPool) {
		if (!e.IsActive()) continue;
		e.Draw(offsetX, offsetY);
	}

	for (const auto& e : wavePool) {
		if (!e.IsActive()) continue;
		e.Draw(offsetX, offsetY);
	}

	for (const auto& e : zigzagPool) {
		if (!e.IsActive()) continue;
		e.Draw(offsetX, offsetY);
	}

	for (const auto& e : shotPool) {
		if (!e.IsActive()) continue;
		e.Draw(offsetX, offsetY);
	}

	for (const auto& e : stalkerPool) {
		if (!e.IsActive()) continue;
		e.Draw(offsetX, offsetY);
	}

	for (const auto& e : bigPool) {
		if (!e.IsActive()) continue;
		e.Draw(offsetX, offsetY);
	}

	for (const auto& e : bossPool) {
		if (!e.IsActive()) continue;
		e.Draw(offsetX, offsetY);
	}
}

void EnemyManager::DeactivateDeadEnemies() {
	for (auto& e : straightPool) {
		if (!e.IsActive()) continue;
		if (e.IsDead() || e.IsOutOfScreen()) e.Deactivate();
	}

	for (auto& e : wavePool) {
		if (!e.IsActive()) continue;
		if (e.IsDead() || e.IsOutOfScreen()) e.Deactivate();
	}

	for (auto& e : zigzagPool) {
		if (!e.IsActive()) continue;
		if (e.IsDead() || e.IsOutOfScreen()) e.Deactivate();
	}

	for (auto& e : shotPool) {
		if (!e.IsActive()) continue;
		if (e.IsDead() || e.IsOutOfScreen()) e.Deactivate();
	}

	for (auto& e : stalkerPool) {
		if (!e.IsActive()) continue;
		if (e.IsDead() || e.IsOutOfScreen()) e.Deactivate();
	}

	for (auto& e : bigPool) {
		if (!e.IsActive()) continue;
		if (e.IsDead() || e.IsOutOfScreen()) e.Deactivate();
	}

	for (auto& e : bossPool) {
		if (!e.IsActive()) continue;
		if (e.IsDead() || e.IsOutOfScreen()) e.Deactivate();
	}
}
