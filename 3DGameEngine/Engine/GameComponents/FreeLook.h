#ifndef FREELOOK_H
#define FREELOOK_H
#include "GameComponent.h"

class FreeLook : public GameComponent
{
public:
	FreeLook() = default;
	~FreeLook() = default;
	void Update() override;

private:
};

#endif //!FREELOOK_H
