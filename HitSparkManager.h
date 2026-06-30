#pragma once
#include "HitSpark.h"
#include <vector>
using namespace std;

class HitSparkManager {
private:
	vector<HitSpark> pool;

public:
	void Init(int size);
	void Add(float x, float y);
	void Update();
	void Draw(int offsetX, int offsetY) const;
};