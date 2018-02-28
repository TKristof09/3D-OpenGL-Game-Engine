#ifndef GAME_H
#define GAME_H

#include "GameObject.h"

class Game
{
public:
	virtual ~Game() = default;
	virtual void Init() = 0;
	virtual void Update()
	{
		m_root.Update();
	};
	virtual void Input()
	{
		m_root.Input();
	};

	GameObject* GetRootObject() { return &m_root; };

private:
	GameObject m_root;

};

#endif // !GAME_H

