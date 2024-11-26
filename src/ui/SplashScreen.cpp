#include <ui/SplashScreen.hpp>

bool SplashScreen::m_showSplashScreen = true;

void SplashScreen::init() {
  m_showSplashScreen = true;

  // Load splash screen image
  m_splashTexture = LoadTexture("resources/images/splashscreen.png");

  // Mock recent projects
  m_recentProjects.push_back("Here There and Everywhere Take 7");
  m_recentProjects.push_back("A Day in the Life sda");
}

void SplashScreen::draw(const AudioEngineManager& emRef) {
  if (m_showSplashScreen) {
    
    // Next window size is window size / 2 and position center
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 + 180));
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 4, ImGui::GetIO().DisplaySize.y / 4 - 90));

    ImGui::Begin("Splash Screen", &m_showSplashScreen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse  | ImGuiWindowFlags_NoBringToFrontOnFocus);
    
    // Image from resources/images/splash.png
    ImGui::Image((void*)(intptr_t) m_splashTexture, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2));

    ImGuiIO& io = ImGui::GetIO();
    ImGui::PushFont(io.Fonts->Fonts[1]);

    ImGui::Text("Welcome to the Audio Engine!");
    ImGui::PopFont();

    // Create two tabs for Settings and Recent Projects
    if (ImGui::BeginTabBar("SplashScreenTabs")) {
      if (ImGui::BeginTabItem("Settings")) {
        ImGui::Text("Select Audio Engine:");
        // ImGui::SameLine();
        // ImGui::SetNextItemWidth(200);
        // ImGui::Combo("##audioEngine", &emRef.selectedEngine, emRef.availableEngines.data(), emRef.availableEngines.size());

        // ImGui::Text("Select Input Device:");
        // ImGui::SameLine();
        // ImGui::SetNextItemWidth(200);
        // ImGui::Combo("##inputDevice", &emRef.selectedInputDevice, emRef.availableInputs.data(), emRef.availableInputs.size());

        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("Recent Projects")) {
        for (auto& project : m_recentProjects) {
          ImGui::Text(project.c_str());
        }

        ImGui::EndTabItem();
      }

      ImGui::EndTabBar();
    }

    ImGui::End();
  }
}