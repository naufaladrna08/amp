#include <iostream>
#include <app/Window.hpp>
#include <ui/UI.hpp>
#include <ui/SplashScreen.hpp>
#include <engine/AudioEngineManager.hpp>
#include <engine/implementation/Jack.hpp>

const float WIDTH = 1280.0f;
const float HEIGHT = 720.0f;
Window* window = new Window(WIDTH, HEIGHT, "OpenGL");

int main(int argc, char const *argv[]) {
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
  ImGui::StyleColorsDark();

  ImGui_ImplOpenGL3_Init("#version 330 core");

  /* Fonts */
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("resources/fonts/Segoe-UI.ttf", 18.0f);
  io.Fonts->AddFontFromFileTTF("resources/fonts/Segoe-UI.ttf", 24.0f);
  float baseFontSize = 18.0f; // 13.0f is the size of the default font. Change to the font size you use.
  float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
  ImFontConfig icons_config; 
  icons_config.MergeMode = true; 
  icons_config.PixelSnapH = true; 
  icons_config.GlyphMinAdvanceX = iconFontSize;
  io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS, iconFontSize, &icons_config, icons_ranges );

  embraceTheDarkness();

  /* Audio Engine */
  AudioEngineManager engineManager;
  std::string selectedEngine = "JACK";
  std::string selectedInputDevice;
  std::vector<std::string> availableInputs;

  SplashScreen splashScreen;
  splashScreen.init();

  while (!window->isClosed()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    splashScreen.draw(engineManager);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window->update();
  }  
  
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  return 0;
}
