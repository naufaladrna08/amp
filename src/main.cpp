#include <iostream>
#include <app/Window.hpp>
#include <core/GLBuffer.hpp>
#include <core/GLShader.hpp>
#include <core/GLFramebuffer.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

const float WIDTH = 800.0f;
const float HEIGHT = 600.0f;
Window* window = new Window(WIDTH, HEIGHT, "OpenGL");
GLFramebuffer* framebuffer = new GLFramebuffer();

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  framebuffer->Bind();
  framebuffer->ResizeFramebuffer(width, height);
  framebuffer->Unbind();
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  framebuffer->Bind();
  framebuffer->ResizeFramebuffer(width, height);
  framebuffer->Unbind();
}

int main(int argc, char const *argv[]) {
  glfwSetFramebufferSizeCallback(window->getWindow(), framebufferSizeCallback);
  glfwSetWindowSizeCallback(window->getWindow(), windowSizeCallback);

  GLBuffer* buffer = new GLBuffer();
  GLShader* shader = new GLShader("shaders/Basic.vs", "shaders/Basic.fs");

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 2
  };

  buffer->BufferData(sizeof(vertices), vertices, sizeof(indices), indices, GL_STATIC_DRAW);
  buffer->Unbind();

  framebuffer->Bind();
  framebuffer->ResizeFramebuffer(WIDTH, HEIGHT);
  framebuffer->CheckStatus();
  framebuffer->Unbind();

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
  ImGui::StyleColorsDark();

  ImGui_ImplOpenGL3_Init("#version 330 core");

  float workspaceWindowWidth  = 0.0f;
  float workspaceWindowHeight = 0.0f;

  while (!window->isClosed()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //
    framebuffer->Bind();
    shader->Use();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 3D Projection
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);
    shader->SetMat4("uProjection", projection);

    // 3D Model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, 0.0, -3.0));
    // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0, 1.0, 0.0));
    shader->SetMat4("uModel", model);

    // 3D View
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0, 0.0, 0.0));
    shader->SetMat4("uView", view);

    // Color
    shader->SetVec4("uColor", glfwGetTime(), 1.0f, 1.0f, 1.0f);
    
    buffer->BindVAO();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    
    framebuffer->Unbind();
    //

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (ImGui::Begin("Workspace")) {
      ImVec2 workspaceWindowSize = ImGui::GetContentRegionAvail();
      workspaceWindowWidth = workspaceWindowSize.x;
      workspaceWindowHeight = workspaceWindowSize.y; 

      framebuffer->Bind();
      framebuffer->ResizeFramebuffer(workspaceWindowWidth, workspaceWindowHeight);
      glViewport(0, 0, workspaceWindowWidth, workspaceWindowHeight);
      framebuffer->Unbind();
      ImGui::Image((void*)(intptr_t)framebuffer->GetID(), ImVec2(workspaceWindowWidth, workspaceWindowHeight), ImVec2(0, 1), ImVec2(1, 0));
      ImGui::End();
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
