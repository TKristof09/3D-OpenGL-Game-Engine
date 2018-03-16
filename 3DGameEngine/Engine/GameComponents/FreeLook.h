#ifndef FREELOOK_H
#define FREELOOK_H
#include "GameComponent.h"

class FreeLook : public GameComponent
{
public:
    FreeLook();
    ~FreeLook();
    void Input() override;

private:
    
};

#endif //!FREELOOK_H