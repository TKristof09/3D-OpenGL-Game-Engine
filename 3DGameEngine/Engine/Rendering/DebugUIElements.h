#ifndef DEBUGUIELEMENTS_H
#define DEBUGUIELEMENTS_H
#include <vector>
#include <3DMath/Vector2.h>
#include <3DMath/3DMath.h>
#include "imgui/imgui.h"
#include <map>
#include <functional>
#include "../Core/Color.h"
#include <iostream>

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

class DragFloat : public DebugUIElement
{
    DragFloat(float* value, const std::string& name = "Float", float min = 0, float max = 0, const void* id = nullptr) :
        m_min(min),
        m_max(max),
        m_value(value)
    {
        m_name = name;
        m_id = id;
    };

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::DragFloat(m_name.c_str(), m_value, 1, m_min, m_max);
        if(m_id)
            ImGui::PopID();
    }

    float* GetValue() const
    {
        return m_value;
    }
private:
    float m_min, m_max;
    float* m_value;
};

class DragVector3 : public DebugUIElement
{
public:
    DragVector3(math::Vector3* value, const std::string& name = "Vector3", float min = 0, float max = 0, const void* id = nullptr) :
        m_min(min),
        m_max(max),
        m_value(value)
    {
        m_name = name;
        m_id = id;
    };
    
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::DragFloat3(m_name.c_str(), &m_value->x, 1, m_min, m_max);

        if (m_id)
            ImGui::PopID();
    }
    
    math::Vector3* GetValue() const
    {
        return m_value;
    }
private:
    float m_min, m_max;
    math::Vector3* m_value;
};

class DragVector4 : public DebugUIElement
{
public:
    DragVector4(math::Vector4* value, const std::string& name = "Vector4", float min = 0, float max = 0, const void* id = nullptr) :
        m_min(min),
        m_max(max),
        m_value(value)
    {
        m_name = name;
        m_id = id;
    };

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::DragFloat4(m_name.c_str(), &m_value->x, 1, m_min, m_max);

        if (m_id)
            ImGui::PopID();
    }

    math::Vector4* GetValue() const
    {
        return m_value;
    }
private:
    float m_min, m_max;
    math::Vector4* m_value;
};

class DragQuaternion : public DebugUIElement
{
public:
    DragQuaternion(math::Quaternion* value, const std::string& name = "Quaternion", float min = 0, float max = 0, const void* id = nullptr) :
        m_min(min),
        m_max(max),
        m_value(value)
    {
        m_name = name;
        m_id = id;
    };

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::DragFloat4(m_name.c_str(), &m_value->w, 1, m_min, m_max);

        if (m_id)
            ImGui::PopID();
    }

    math::Quaternion* GetValue() const
    {
        return m_value;
    }
private:
    float m_min, m_max;
    math::Quaternion* m_value;
};

class ColorEdit3 : public DebugUIElement
{
public:
    ColorEdit3(Color* value, const std::string& name = "Color", const void* id = nullptr):
        m_value(value)
    {
        m_name = name;
        m_id = id;
    }
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::ColorEdit3(m_name.c_str(), &m_value->r);

        if (m_id)
            ImGui::PopID();
    }
    Color* GetValue() const
    {
        return m_value;
    }
private:
    Color* m_value;
};

class ColorEdit4 : public DebugUIElement
{
public:
    ColorEdit4(Color* value, const std::string& name = "Color", const void* id = nullptr):
        m_value(value)

    {
        m_name = name;
        m_id = id;
    }
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::ColorEdit4(m_name.c_str(), &m_value->r);

        if (m_id)
            ImGui::PopID();
    }

    Color* GetValue() const
    {
        return m_value;
    }
private:
    Color* m_value;
};

class CheckBox : public DebugUIElement
{
public:
    CheckBox(bool* value, const std::string& name = "CheckBox", const void* id = nullptr):
        m_value(value)
    {
        m_name = name;
        m_id = id;
    }
    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::Checkbox(m_name.c_str(), m_value);

        if (m_id)
            ImGui::PopID();
    }

    bool GetValue() const
    {
        return *m_value;
    }

private:
    bool* m_value;
};

class Button : public DebugUIElement
{
public: 
    Button(const std::string& name = "Button", bool* value = nullptr, const void* id = nullptr):
        m_value(value),
        m_callback(nullptr)
    {
        m_name = name;
        m_id = id;
    }

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);
        bool val = false;
        if(m_value)
            *m_value = ImGui::Button(m_name.c_str());
        else
            val = ImGui::Button(m_name.c_str());

        if ((m_value && *m_value) || val)
        {
            if(m_callback)
                m_callback(this);
        }

        if (m_id)
            ImGui::PopID();
    }

    void RegisterCallback(std::function<void(Button*)> callback)
    {
        m_callback = callback;
    }

    bool GetValue() const
    {
        return *m_value;
    }

private:
    bool* m_value;
    std::function<void(Button*)> m_callback;
    

};

class TreeNode : public DebugUIElement
{
public:
    TreeNode(const std::string& text, bool* value,const void* id = nullptr):
        m_value(value)
    {
        m_name = text;
        m_id = id;
    }

    void Update() override
    {
        if (m_id)
            ImGui::PushID(m_id);

        ImGui::AlignTextToFramePadding();
        *m_value = ImGui::TreeNode(m_name.c_str());
        if(*m_value)
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

    bool GetValue() const
    {
        return *m_value;
    }

private:
    bool* m_value;
    std::vector<DebugUIElement*> m_elements;
};

class Separator : public DebugUIElement
{
public:
    Separator(const std::string& name = "Separator")
    {
        m_name = name;
    }
    void Update() override
    {
        ImGui::Separator();
    }
};

class DebugUIWindow
{
public:
    DebugUIWindow(const std::string& name = "Debug", bool opened = true) : m_debugUI(nullptr),                                                    m_index(0),       
      m_name(name), 
      m_opened(opened) {}

    ~DebugUIWindow();

    void AddElement(DebugUIElement* element, unsigned int column = 1)
    {
        while(m_elements.size() < column)
        {
            m_elements.push_back(std::map<std::string, DebugUIElement*>());
        }
        m_elements[column - 1][element->GetName()] = element;
    }

    DebugUIElement* GetElement(const std::string& name, unsigned int column = 1)
    {
        if (m_elements.size() < column)
        {
            std::cerr << "Column higher than the existing columns" << std::endl;
            return nullptr;
        }
        auto it = m_elements[column - 1].find(name);
        if (it != m_elements[column - 1].end())
        {
            return m_elements[column - 1][name];
        }
        std::cerr << "Element can't be found" << std::endl;
        return nullptr;
    }

    void RemoveElement(const std::string& name, unsigned int column = 1)
    {
        if(m_elements.size() < column)
        {
            std::cerr << "Column higher than the existing columns" << std::endl;
        }
        auto it = m_elements[column - 1].find(name);
        if(it != m_elements[column - 1].end())
        {
            m_elements[column - 1].erase(it);
        }
    }

    void Clear(unsigned int column = 1)
    {
        if (m_elements.size() < column)
            return;
        m_elements[column - 1].clear();
    }

    void Update()
    {
        if(m_opened)
        {
            ImGui::Begin(m_name.c_str(), &m_opened);
            ImGui::Columns(m_elements.size());
            for (auto map : m_elements)
            {
                for (auto pair : map)
                {
                    pair.second->Update();
                }
                ImGui::NextColumn();
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
    std::vector<std::map<std::string, DebugUIElement*>> m_elements;
};

#endif
