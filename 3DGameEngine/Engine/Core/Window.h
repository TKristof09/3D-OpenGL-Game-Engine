#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <iostream>


class Window
{
public:
	void Create(int width, int height, const std::string& title);

	void ClearScreen();
	void Render();
	void Close();

	inline int* GetWidth() { return &m_width; };
	inline int* GetHeight() { return &m_height; };
	inline std::string* GetTitle() { return &m_title; };
	bool IsCloseRequested();
	inline void SetFullScreen(bool value);


private:
	int m_width;
	int m_height;
	std::string m_title;


};


#endif // !WINDOW_H

