
#include <myth\managers\game.h>


using namespace myth::managers;

class TestGraphics : public Game
{
public:
	TestGraphics(){}
	~TestGraphics(){}

	void LoadContent() final;
	void UnloadContent() final;
	void Input(myth::input::InputHandler& input) final;
	void Update(float t) final;
	void Draw(float t) final;
private:
};