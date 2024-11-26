#include <app/Window.hpp>

Window::Window(int width, int height, const char* title) {
  m_width = width;
  m_height = height;
  m_title = title;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW!\n";
    glfwTerminate();
  }
  
  m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

  glfwMaximizeWindow(m_window);
  
  if (!m_window) {
    std::cout << "Failed to create GLFW window!\n";
    glfwTerminate();
  }
  
  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD!\n";
  }

  glEnable(GL_DEPTH_TEST);
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

