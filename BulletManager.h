#pragma once
#include<vector>
#include"Bullet.h"
using namespace std;
#pragma region 弾のマネージャークラス
class BulletManager {
	vector<Bullet> bullets;
	vector<int> freeList;
public:
	void InitPool(int size);
	void Add(float x, float y, float speed, int atk);
	void Release(int index);
	void Update();
	void Draw(int offsetX, int offsetY)const;
	vector<Bullet>& Get() {
		return bullets;
	}
};
#pragma endregion