#include <app/Window.hpp>

Window::Window(int width, int height, const char* title) {
  m_width = width;
  m_height = height;
  m_title = title;
  
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW!\n";
    glfwTerminate();
  }
  
  m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
  
  if (!m_window) {
    std::cout << "Failed to create GLFW window!\n";
    glfwTerminate();
  }
  
  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD!\n";
  }
}

Window::~Window() {
  glfwTerminate();
}

void Window::update() {
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

bool Window::isClosed() {
  return glfwWindowShouldClose(m_window);
}

