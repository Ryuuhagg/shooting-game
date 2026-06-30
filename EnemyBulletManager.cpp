#include"EnemyBulletManager.h"

void EnemyBulletManager::InitPool(int size) {
	bullets.resize(size);

	freeList.clear();

	for (int i = 0; i < size; i++) {
		freeList.push_back(i);
	}
}

void EnemyBulletManager::Add(float x, float y, float dirX, float dirY, float speed, EnemyBulletType type)
{
	if (freeList.empty()) return;

	int index = freeList.back();
	freeList.pop_back();

	bullets[index].Init(x, y, dirX, dirY, speed, type);
}

void EnemyBulletManager::Release(int index) {
	if (!bullets[index].IsActive()) return;

	bullets[index].Deactivate();
	freeList.push_back(index);
}

void EnemyBulletManager::Update(float playerX, float playerY) {
	for (int i = 0; i < bullets.size(); i++)
	{
		auto& b = bullets[i];
		if (!b.IsActive()) continue;

		b.Update(playerX, playerY);

		if (b.IsOutOfScreen())
		{
			Release(i);
		}
	}
}

void EnemyBulletManager::Draw(int offsetX, int offsetY) const {
	for (auto& b : bullets)
	{
		if (!b.IsActive()) continue;
		b.Draw(offsetX, offsetY);
	}
}