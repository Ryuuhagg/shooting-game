#pragma once
#include"Explosion.h"
#include<vector>
using namespace std;
#pragma region 爆発マネージャー
class ExplosionManager {
	vector<Explosion> pool;

public:
	void Init(int size);

	void Add(float x, float y);

	void Clear();

	void Update();

	void Draw(int offsetX, int offsetY) const;
};
#pragma endregion