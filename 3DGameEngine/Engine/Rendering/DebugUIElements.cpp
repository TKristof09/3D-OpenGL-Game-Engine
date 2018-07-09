#include "DebugUIElements.h"
#include "DebugUI.h"

DebugUIWindow::~DebugUIWindow()
{
    m_debugUI->RemoveWindow(m_index);
}
