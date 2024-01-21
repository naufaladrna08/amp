#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
  public:
    Window(int width, int height, const char* title);
    ~Window();
    void update();
    bool isClosed();

    GLFWwindow* getWindow() { return m_window; }
    void OnResize(int width, int height);
  
  private:
    GLFWwindow* m_window;
    int m_width, m_height;
    const char* m_title;
};

#endif 