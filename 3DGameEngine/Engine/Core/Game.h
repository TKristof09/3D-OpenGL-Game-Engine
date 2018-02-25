#ifndef GAME_H
#define GAME_H

class Game
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Input() = 0;
	virtual void Render() = 0;

};

#endif // !GAME_H

