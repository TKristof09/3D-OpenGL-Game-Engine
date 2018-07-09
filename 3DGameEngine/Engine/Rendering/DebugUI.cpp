#include "DebugUI.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../Core/SDL_Backend.h"

DebugUI::DebugUI(Style style):
    m_index(0)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui_ImplSDL2_InitForOpenGL(GetWindow(), *GetContext());
    ImGui_ImplOpenGL3_Init();

    if (style == LIGHT)
        ImGui::StyleColorsClassic();
    else
        ImGui::StyleColorsDark();
}

DebugUI::~DebugUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void DebugUI::FrameUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(GetWindow());
    ImGui::NewFrame();

    for (auto pair : m_windows)
    {
        pair.second->Update();
    }
    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
