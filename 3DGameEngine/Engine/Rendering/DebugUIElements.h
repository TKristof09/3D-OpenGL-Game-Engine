#ifndef DEBUGUIELEMENTS_H
#define DEBUGUIELEMENTS_H
#include <vector>
#include <3DMath/Vector2.h>
#include <3DMath/3DMath.h>
#include "imgui/imgui.h"
#include <map>
#include <functional>


class DebugUI;

class DebugUIElement
{
public:
    virtual ~DebugUIElement() = default;
    virtual void Update() = 0;
    std::string GetName() const
    {
        return m_name;
    }
protected:
    std::string m_name;
    const void* m_id = nullptr;
};

class Text : public DebugUIElement
{
public:
    Text(const std::string& text, const void* id = nullptr) :
        m_text(text)
    {
        m_name = text;
        m_id = id;
    }
    void Update() override
    {
        if(m_id)
            ImGui::PushID(m_id);

        ImGui::Text(m_text.c_str());

        if(m_id)
            ImGui::PopID();
    }
private:
    std::string m_text;
};

class SliderFloat : public DebugUIElement
{
    SliderFloat(float min, float max, const std::string& name = "Float", const void* id = nullptr) :
        m_min(min),
        m_max(max),
        m_value(0)
    {
        m_name = name;
        m_id = id;
    };

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::SliderFloat(m_name.c_str(), &m_value, m_min, m_max);
        if(m_id)
            ImGui::PopID();
    }

    float GetValue() const
    {
        return m_value;
    }
private:
    float m_min, m_max;
    float m_value;
};

class SliderVector3 : public DebugUIElement
{
public:
    SliderVector3(float min, float max, const std::string& name = "Vector3", const void* id = nullptr) :
        m_min(min),
        m_max(max),
        m_value(math::Vector3(0))
    {
        m_name = name;
        m_id = id;
    };
    
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::SliderFloat3(m_name.c_str(), &m_value.x, m_min, m_max);

        if (m_id)
            ImGui::PopID();
    }
    
    math::Vector3 GetValue() const
    {
        return m_value;
    }
private:
    float m_min, m_max;
    math::Vector3 m_value;
};

class ColorEdit3 : public DebugUIElement
{
public:
    ColorEdit3(const std::string& name = "Color", const void* id = nullptr):
        m_value(math::Vector3(0))
    {
        m_name = name;
        m_id = id;
    }
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::ColorEdit3(m_name.c_str(), &m_value.x);

        if (m_id)
            ImGui::PopID();
    }
    math::Vector3 GetValue() const
    {
        return m_value;
    }
private:
    math::Vector3 m_value;
};

class ColorEdit4 : public DebugUIElement
{
public:
    ColorEdit4(const std::string& name = "Color", const void* id = nullptr):
        m_value(math::Vector4(0))

    {
        m_name = name;
        m_id = id;
    }
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::ColorEdit3(m_name.c_str(), &m_value.x);

        if (m_id)
            ImGui::PopID();
    }

    math::Vector4 GetValue() const
    {
        return m_value;
    }
private:
    math::Vector4 m_value;
};

class CheckBox : public DebugUIElement
{
public:
    CheckBox(const std::string& name = "CheckBox", const void* id = nullptr):
        m_value(false)
    {
        m_name = name;
        m_id = id;
    }
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::Checkbox(m_name.c_str(), &m_value);

        if (m_id)
            ImGui::PopID();
    }

    bool GetValue() const
    {
        return m_value;
    }

private:
    bool m_value;
};

class Button : public DebugUIElement
{
public: 
    Button(const std::string& name = "Button", const void* id = nullptr):
        m_value(false),
        m_callback(nullptr)
    {
        m_name = name;
        m_id = id;
    }

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        m_value = ImGui::Button(m_name.c_str());
        if (m_value)
            if(m_callback)
                m_callback(this);

        if (m_id)
            ImGui::PopID();
    }

    void RegisterCallback(std::function<void(Button*)> callback)
    {
        m_callback = callback;
    }

    bool GetValue() const
    {
        return m_value;
    }

private:
    bool m_value;
    std::function<void(Button*)> m_callback;
    

};

class TreeNode : public DebugUIElement
{
public:
    TreeNode(const std::string& text, const void* id = nullptr)
    {
        m_name = text;
        m_id = id;
    }

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        bool isOpen = ImGui::TreeNode(m_name.c_str());
        if(isOpen)
        {
            for (DebugUIElement* element : m_elements)
            {
                element->Update();
            }
            ImGui::TreePop();
        }

        if (m_id)
            ImGui::PopID();
    }

    void AddElement(DebugUIElement* element)
    {
        m_elements.push_back(element);
    }

private:
    std::vector<DebugUIElement*> m_elements;
};

class DebugUIWindow
{
public:
    DebugUIWindow(const std::string& name = "Debug", bool opened = true) :
        m_name(name),
        m_opened(opened){}
    ~DebugUIWindow();

    void AddElement(DebugUIElement* element)
    {
        m_elements[element->GetName()] = element;
    }

    DebugUIElement* GetElement(const std::string& name)
    {
        return m_elements[name];
    }

    void Clear()
    {
        m_elements.clear();
    }

    void Update()
    {
        if(m_opened)
        {
            ImGui::Begin(m_name.c_str(), &m_opened);
            for (auto element : m_elements)
            {
                element.second->Update();
            }
            ImGui::End();
        }
    }

    void SetIndex(unsigned int index)
    {
        m_index = index;
    }


    void SetDebugUI(DebugUI* ui)
    {
        m_debugUI = ui;
    }

private:
    DebugUI* m_debugUI;
    unsigned int m_index;
    std::string m_name;
    bool m_opened;
    std::map<std::string, DebugUIElement*> m_elements;
};




#endif
