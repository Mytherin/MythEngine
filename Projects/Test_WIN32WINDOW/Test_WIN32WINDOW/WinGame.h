
#include <myth\managers\game.h>

using namespace myth::managers;

class WinGame : public Game
{
public:
	WinGame(){}
	~WinGame(){}

	void Update(float t) final {}
	void Draw(float t) final{}
private:
};