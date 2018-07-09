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
        window->SetIndex(m_index++);
        window->SetDebugUI(this);
        m_windows[m_index] = window;
    }

    void RemoveWindow(unsigned int index)
    {
        auto it = m_windows.find(index);
        if (it != m_windows.end())
            m_windows.erase(it);
    }

    void FrameUpdate();
private:
    
    unsigned int m_index;
    std::map<unsigned int, DebugUIWindow*> m_windows;

    
};
#endif
