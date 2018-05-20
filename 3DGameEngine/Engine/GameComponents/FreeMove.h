#ifndef FREEMOVE_H
#define FREEMOVE_H
#include "GameComponent.h"

class FreeMove : public GameComponent
{
public:
	FreeMove() = default;
	~FreeMove() = default;
	void Update() override;

private:
};

#endif //!FREELOOK_H
