#ifndef DEBUGUI_H
#define DEBUGUI_H
#include "DebugUIElements.h"

enum Style
{
    LIGHT,
    DARK
};

class DebugUI {
public:
    DebugUI(Style style);
    ~DebugUI();

    void AddWindow(DebugUIWindow* window)
    {
        m_windows.push_back(window);
    }
    void FrameUpdate();
private:
    std::vector<DebugUIWindow*> m_windows;

    
};
#endif
