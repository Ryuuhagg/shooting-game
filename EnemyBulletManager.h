#pragma once
#include"EnemyBullet.h"
#include<vector>
using namespace std;
#pragma region 敵弾のマネージャークラス
class EnemyBulletManager {
	vector<EnemyBullet> bullets;
	vector<int> freeList;
public:
	void InitPool(int size);

	void Add(float x, float y, float dirX, float dirY, float speed, EnemyBulletType type);

	void Release(int index);

	void Update(float playerX, float playerY);

	void Draw(int offsetX, int offsetY) const;

	vector<EnemyBullet>& Get() { return bullets; }
};
#pragma endregion