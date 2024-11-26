#include <ui/SplashScreen.hpp>

bool SplashScreen::m_showSplashScreen = true;

void SplashScreen::init() {
  m_showSplashScreen = true;

  // Load splash screen image
  m_splashTexture = LoadTexture("resources/images/splash.png");

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
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos(); // Get the top-left corner of the image
    ImVec2 size = ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 16, ImGui::GetIO().DisplaySize.y / 2 - 64); // Size of the image
    float rounding = 8.0f; // Corner rounding radius

    // Define the rounded rectangle area
    ImVec2 topLeft = pos;
    ImVec2 bottomRight = ImVec2(pos.x + size.x, pos.y + size.y);

    // Create a clipping rectangle for the rounded corners
    drawList->PushClipRect(topLeft, bottomRight, true);
    drawList->AddRectFilled(topLeft, bottomRight, IM_COL32(0, 0, 0, 0), rounding); // Optional background
    drawList->AddImageRounded(
     (void*)(intptr_t)m_splashTexture,  // Texture ID
     topLeft,                           // Top-left corner
     bottomRight,                       // Bottom-right corner
     ImVec2(0, 0),                      // UV0
     ImVec2(1, 1),                      // UV1
     IM_COL32_WHITE,                    // Tint color
     rounding                           // Corner rounding radius
    );
    drawList->PopClipRect();

    // Set cursor position to the bottom of the image
    ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + size.y + 10));
  
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
        const char* items[] = { "Here There and Everywhere Take 7", "A Day in the Life sda" };
        static int item_current = 0;
        ImGui::ListBox("##RecentProjects", &item_current, items, IM_ARRAYSIZE(items), 4);

        ImGui::EndTabItem();
      }

      ImGui::EndTabBar();
    }

    ImGui::End();
  }
}