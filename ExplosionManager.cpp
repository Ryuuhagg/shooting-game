#include"ExplosionManager.h"

void ExplosionManager::Init(int size) {
	pool.resize(size);
}

void ExplosionManager::Add(float x, float y) {
	for (auto& e : pool)
	{
		if (!e.IsActive())
		{
			e.Init(x, y);
			return;
		}
	}
}
void ExplosionManager::Clear() {
	pool.clear();
}
void ExplosionManager::Update() {
	for (auto& e : pool)
		e.Update();
}
void ExplosionManager::Draw(int offsetX, int offsetY) const {
	for (const auto& e : pool)
		e.Draw(offsetX, offsetY);
}