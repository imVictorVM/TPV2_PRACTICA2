#include "GameState.h"

class Texture;

class GameOverState : public GameState {
public:
	GameOverState();
	~GameOverState();
	void enter() override;
	void leave() override;
	void update() override;
private:
	Texture& _msgWin;
	Texture& _msgLose;
	bool win;
};