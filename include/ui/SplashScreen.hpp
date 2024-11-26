#ifndef SPLASH_SCREEN_HPP
#define SPLASH_SCREEN_HPP

#include <iostream>
#include <ui/UI.hpp>
#include <engine/AudioEngineManager.hpp>
#include <stb_image.h>
#include <core/LoadTexture.hpp>
#include <vector>

class SplashScreen {
  public:
    void init();
    void draw(const AudioEngineManager& emRef);

  private:
    static bool m_showSplashScreen;
    GLuint m_splashTexture;
    std::vector<std::string> m_recentProjects;
};

#endif