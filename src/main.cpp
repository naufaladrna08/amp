#include <iostream>
#include <app/Window.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <ui/FileDialog.hpp>
#include <ui/ImGuiTheme.hpp>
#include <ui/IconsFontAwesome6.hpp>
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

  while (!window->isClosed()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImGui::Begin("Audio Engine");
      // Select Engine
      if (ImGui::BeginCombo("Audio Engine", selectedEngine.c_str())) {
        if (ImGui::Selectable("JACK", selectedEngine == "JACK")) {
          selectedEngine = "JACK";
          engineManager.setEngine(std::make_unique<JackEngine>());
        }
        if (ImGui::Selectable("PulseAudio", selectedEngine == "PulseAudio")) {
          selectedEngine = "PulseAudio";
          // engineManager.setEngine(std::make_unique<PulseAudioEngine>());
        }
        ImGui::EndCombo();
      }

      // Select Input Device
      if (engineManager.getEngine()) {
        availableInputs = engineManager.getEngine()->getAvailableInputDevices();
        if (ImGui::BeginCombo("Input Device", selectedInputDevice.c_str())) {
          for (const auto &input : availableInputs) {
            if (ImGui::Selectable(input.c_str(), selectedInputDevice == input)) {
              selectedInputDevice = input;
              engineManager.getEngine()->setInputDevice(input);
            }
          }
          ImGui::EndCombo();
        }
      }

      // Status 
      if (engineManager.getEngine()) {
        ImGui::Text("Backend Running: %s", engineManager.getEngine()->isBackendRunning() ? "Yes" : "No");
      }

      // Start/Stop Backend
      if (engineManager.getEngine()) {
        if (ImGui::Button("Start Backend")) {
          engineManager.getEngine()->startBackend();
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop Backend")) {
          engineManager.getEngine()->stopBackend();
        }
      }

      // Start/Stop Recording
      if (engineManager.getEngine()) {
        if (ImGui::Button("Start Recording")) {
          engineManager.getEngine()->startRecording();
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop Recording")) {
          engineManager.getEngine()->stopRecording();
        }
      }

    ImGui::End();

    if (engineManager.getEngine()) {
      if (engineManager.getEngine()->isRecording()) {
        std::cout << "Writing audio buffer" << std::endl;
        engineManager.getEngine()->writeAudioBuffer();
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
