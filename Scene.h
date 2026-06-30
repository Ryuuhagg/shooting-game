#pragma once
class Game;
class Scene {
protected:
	Game& game;
public:
	Scene(Game& g) : game(g) {}
	virtual ~Scene() = default;

	virtual void Update() = 0;
	virtual void Draw() const = 0;
};

#pragma region シーン派生クラス
class GameOverScene : public Scene {
private:
	int finalScore;
public:
	GameOverScene(Game& g, int score) : Scene(g), finalScore(score) {}
	void Update() override;
	void Draw() const override;
};

class GameScene : public Scene {
public:
	GameScene(Game& g);
	void Update() override;
	void Draw() const override;
};

class TitleScene : public Scene {
public:
	TitleScene(Game& g) : Scene(g) {}
	void Update() override;
	void Draw() const override;
};
#pragma endregion