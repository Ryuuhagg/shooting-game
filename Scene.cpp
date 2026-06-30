#include"Scene.h"
#include"Game.h"
#include<string>
#pragma region シーン派生クラス関数定義
void TitleScene::Update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		game.ChangeScene(make_unique<GameScene>(game));
	}
}
void TitleScene::Draw() const {
	DrawString(200, 200, "TITLE", GetColor(255, 255, 255));
	DrawFormatString(WIDTH / 2 - 80, HEIGHT / 2, WHITE, "PUSH ENTER KEY");
}

GameScene::GameScene(Game& g) : Scene(g) { game.ResetGame(); }

void GameScene::Update() {
	game.UpdateGame();

	if (game.IsPlayerDead()) {
		game.ChangeScene(
			std::make_unique<GameOverScene>(game, game.GetScore())
		);
	}
}
void GameScene::Draw() const {
	game.DrawGame();
}
void GameOverScene::Update() {
	if (CheckHitKey(KEY_INPUT_R))
	{
		game.ChangeScene(std::make_unique<GameScene>(game));
	}
	if (CheckHitKey(KEY_INPUT_T))
	{
		game.ChangeScene(std::make_unique<TitleScene>(game));
	}
}
void GameOverScene::Draw() const {
	DrawFormatString(WIDTH / 2 - 80, HEIGHT / 2, RED, "GAME OVER");
	DrawFormatString(WIDTH / 2 - 80, HEIGHT / 2 + 40, WHITE,
		"SCORE: %d", finalScore);
	DrawString(WIDTH / 2 - 80, HEIGHT / 2 + 80,
		"Press R to Retry", WHITE);
	DrawString(WIDTH / 2 - 80, HEIGHT / 2 + 120,
		"Press T to Title", WHITE);
}

#pragma endregion