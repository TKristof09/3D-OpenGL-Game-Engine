#ifndef WINDOW_H
#define WINDOW_H

#include <string>

class Window
{
public:
	static void Create(int width, int height, const std::string& title);

	static void Render();
	static void Close();

	static inline int* GetWidth() { return &m_width; };
	static inline int* GetHeight() { return &m_height; };
	static inline std::string* GetTitle() { return &m_title; };
	static bool IsCloseRequested();
	static inline void SetFullScreen(bool value);


private:
	static int m_width;
	static int m_height;
	static std::string m_title;
};


#endif // !WINDOW_H
