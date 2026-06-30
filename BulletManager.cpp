#include"BulletManager.h"

void BulletManager::InitPool(int size) {
	bullets.resize(size);
	freeList.clear();

	for (int i = 0; i < size; i++) {
		freeList.push_back(i);
	}
}

void BulletManager::Release(int index) {
	bullets[index].Deactivate();
	freeList.push_back(index);
}

void BulletManager::Add(float x, float y, float speed, int atk) {
	if (freeList.empty()) return;

	int index = freeList.back();
	freeList.pop_back();

	bullets[index].Init(x, y, speed, atk);
}

void BulletManager::Update() {
	for (int i = 0; i < bullets.size(); i++)
	{
		auto& b = bullets[i];
		if (!b.IsActive()) continue;

		b.Move();

		if (b.IsOutOfScreen())
		{
			b.Deactivate();
			freeList.push_back(i);
		}
	}
}

void BulletManager::Draw(int offsetX, int offsetY)const {
	for (auto& b : bullets)
	{
		if (!b.IsActive()) continue;
		b.Draw(offsetX, offsetY);
	}
}