#pragma once

#pragma region スコアClass
class Score {
private:
	int score;
public:
	Score() : score(0) {}
	void Add(int value);
	int Get() const { return score; }
	void Draw() const;
};
#pragma endregion

#pragma region スコアポップClass
class ScorePop {
private:
	float x, y;
	int value;
	int life;
	int maxLife;
	bool active = false;
public:
	ScorePop() : x(0), y(0), value(0), life(0), maxLife(60), active(false) {}

	void Init(float px, float py, int val);

	void Update();

	void Draw(int offsetX = 0, int offsetY = 0) const;

	bool IsDead() const {
		return active == false;
	}

	bool IsActive() const { return active; }
};
#pragma endregion