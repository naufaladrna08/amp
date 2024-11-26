#ifndef AUDIO_ENGINE_MANAGER_HPP
#define AUDIO_ENGINE_MANAGER_HPP
#include <memory>
#include <engine/AudioEngine.hpp>

class AudioEngineManager {
  public:
    void setEngine(std::unique_ptr<AudioEngine> engine);
    AudioEngine* getEngine();

  private:
    std::unique_ptr<AudioEngine> m_engine;
};

#endif