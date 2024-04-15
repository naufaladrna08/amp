#include <iostream>
#include <app/Window.hpp>
#include <core/GLBuffer.hpp>
#include <core/GLShader.hpp>
#include <engine/Mesh.hpp>
#include <engine/Model.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <ui/FileDialog.hpp>
#include <ui/ImGuiTheme.hpp>
#include <ui/IconsFontAwesome6.hpp>

const float WIDTH = 1280.0f;
const float HEIGHT = 720.0f;
Window* window = new Window(WIDTH, HEIGHT, "OpenGL");

std::vector<std::string> allowedExtensions = {".obj", ".gltf"};

/* Rotate with mouse */
bool middleMousePressed = false;
double lastMouseX, lastMouseY;

/* Drag with shift */
bool shiftPressed = false;

/* Camera */
GLfloat cameraRadius = 5.0f;
GLfloat cameraYaw = 0.0f;
GLfloat cameraPitch = 0.0f;
GLfloat cameraSpeed = 0.1f;
GLfloat zoomSpeed = 0.1f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, cameraRadius);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
    middleMousePressed = true;
  } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
    middleMousePressed = false;
  }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
  double deltaX = xpos - lastMouseX;
  double deltaY = ypos - lastMouseY;

  if (middleMousePressed && !shiftPressed) {
    cameraYaw += deltaX * cameraSpeed;
    cameraPitch += deltaY * cameraSpeed;
  }

  lastMouseX = xpos;
  lastMouseY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  cameraRadius -= yoffset * zoomSpeed;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
    shiftPressed = true;
  } else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
    shiftPressed = false;
  }
}

int main(int argc, char const *argv[]) {
  glfwSetFramebufferSizeCallback(window->getWindow(), framebufferSizeCallback);
  glfwSetWindowSizeCallback(window->getWindow(), windowSizeCallback);
  glfwSetMouseButtonCallback(window->getWindow(), mouseButtonCallback);
  glfwSetCursorPosCallback(window->getWindow(), mouseCallback);
  glfwSetScrollCallback(window->getWindow(), scrollCallback);
  glfwSetKeyCallback(window->getWindow(), keyCallback);

  GLShader* shader = new GLShader("shaders/Basic.vs", "shaders/Basic.fs");
  Model modelBackpack;

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
  ImGui::StyleColorsDark();

  ImGui_ImplOpenGL3_Init("#version 330 core");

  /* Fonts */
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("resources/fonts/Segoe-UI.ttf", 18.0f);
  float baseFontSize = 18.0f; // 13.0f is the size of the default font. Change to the font size you use.
  float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
  ImFontConfig icons_config; 
  icons_config.MergeMode = true; 
  icons_config.PixelSnapH = true; 
  icons_config.GlyphMinAdvanceX = iconFontSize;
  io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS, iconFontSize, &icons_config, icons_ranges );

  embraceTheDarkness();

  float workspaceWindowWidth  = 0.0f;
  float workspaceWindowHeight = 0.0f;
  bool m_fileDialogOpen;
  ImFileDialogInfo m_fileDialogInfo;

  while (!window->isClosed()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader->Use();

    // 3D Projection
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);
    shader->SetMat4("uProjection", projection);

    // 3D Model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    shader->SetMat4("uModel", model);

    // 3D View
    glm::mat4 view = glm::mat4(1.0f);

    cameraPos.x = cameraRadius * cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    cameraPos.y = cameraRadius * sin(glm::radians(cameraPitch));
    cameraPos.z = cameraRadius * sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), cameraUp);

    shader->SetMat4("uView", view);
    
    modelBackpack.Draw(*shader);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Control");
    
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FOLDER_OPEN " Open Model")) {
      m_fileDialogOpen = true;
      m_fileDialogInfo.title = "Open Model";
      m_fileDialogInfo.type = ImGuiFileDialogType_OpenFile;
      m_fileDialogInfo.directoryPath = std::filesystem::current_path();
      m_fileDialogInfo.allowedExtensions = allowedExtensions;
    }

    /* Slider float for zoom and camera speed */
    ImGui::SliderFloat("Zoom Speed", &zoomSpeed, 0.0f, 1.0f);
    ImGui::SliderFloat("Camera Speed", &cameraSpeed, 0.0f, 1.0f);

    ImGui::End();

    if (ImGui::FileDialog(&m_fileDialogOpen, &m_fileDialogInfo)) {
      if (m_fileDialogInfo.resultPath.has_extension()) {
        std::string extension = m_fileDialogInfo.resultPath.extension().string();
        if (std::find(allowedExtensions.begin(), allowedExtensions.end(), extension) != allowedExtensions.end()) {
          modelBackpack.reloadModel(m_fileDialogInfo.resultPath.string());
        }
      }
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window->update();
  }  
  
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  return 0;
}
