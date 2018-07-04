#ifndef DEBUGUIELEMENTS_H
#define DEBUGUIELEMENTS_H
#include <vector>
#include <3DMath/Vector2.h>
#include <3DMath/3DMath.h>
#include "imgui/imgui.h"
#include <map>


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
};

class Text : public DebugUIElement
{
public:
    Text(const std::string& text) :
        m_text(text)
    {
        m_name = text;
    }
    void Update() override
    {
        ImGui::Text(m_text.c_str());
    }
private:
    std::string m_text;
};

class SliderFloat : public DebugUIElement
{
    SliderFloat(float min, float max, const std::string& name = "Float") :
        m_min(min),
        m_max(max),
        m_value(0)
    {
        m_name = name;
    };

    void Update() override
    {
        ImGui::SliderFloat(m_name.c_str(), &m_value, m_min, m_max);
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
    SliderVector3(float min, float max, const std::string& name = "Vector3") :
        m_min(min),
        m_max(max),
        m_value(math::Vector3(0))
    {
        m_name = name;
    };
    
    void Update() override
    {
        ImGui::SliderFloat3(m_name.c_str(), &m_value.x, m_min, m_max);
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
    ColorEdit3(const std::string& name = "Color"):
        m_value(math::Vector3(0))
    {
        m_name = name;
    }
    void Update() override
    {
        ImGui::ColorEdit3(m_name.c_str(), &m_value.x);
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
    ColorEdit4(const std::string& name = "Color"):
        m_value(math::Vector4(0))

    {
        m_name = name;
    }
    void Update() override
    {
        ImGui::ColorEdit3(m_name.c_str(), &m_value.x);
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
    CheckBox(const std::string& name = "CheckBox"): 
        m_value(false)
    {
        m_name = name;
    }
    void Update() override
    {
        ImGui::Checkbox(m_name.c_str(), &m_value);
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
    Button(const std::string& name = "Button"):
        m_value(false)
    {
        m_name = name;
    }
    void Update() override
    {
        m_value = ImGui::Button(m_name.c_str());
    }

    bool GetValue() const
    {
        return m_value;
    }

private:
    bool m_value;

};

class DebugUIWindow
{
public:
    DebugUIWindow(const std::string& name = "Debug", bool opened = true) :
        m_name(name),
        m_opened(opened){}

    void AddElement(DebugUIElement* element)
    {
        m_elements[element->GetName()] = element;
    }

    DebugUIElement* GetElement(const std::string& name)
    {
        return m_elements[name];
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

private:
    std::string m_name;
    bool m_opened;
    std::map<std::string, DebugUIElement*> m_elements;
};


#endif