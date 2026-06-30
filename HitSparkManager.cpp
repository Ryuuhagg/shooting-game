#include "HitSparkManager.h"

void HitSparkManager::Init(int size) {
	pool.resize(size);
}

void HitSparkManager::Add(float x, float y) {
	for (auto& s : pool) {
		if (!s.IsActive()) {
			s.Init(x, y);
			return;
		}
	}
}

void HitSparkManager::Update() {
	for (auto& s : pool) {
		s.Update();
	}
}

void HitSparkManager::Draw(int offsetX, int offsetY) const {
	for (const auto& s : pool) {
		s.Draw(offsetX, offsetY);
	}
}