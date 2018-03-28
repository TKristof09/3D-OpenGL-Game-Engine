#ifndef FREEMOVE_H
#define FREEMOVE_H
#include "GameComponent.h"

class FreeMove : public GameComponent
{
public:
    FreeMove();
    ~FreeMove();
    void Input() override;

private:

};

#endif //!FREELOOK_H