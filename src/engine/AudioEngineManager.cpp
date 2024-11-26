#include <engine/AudioEngineManager.hpp>

void AudioEngineManager::setEngine(std::unique_ptr<AudioEngine> engine) {
  if (m_engine != nullptr) {
    m_engine->shutdown();
  }

  m_engine = std::move(engine);
  m_engine->initialize();
}

AudioEngine* AudioEngineManager::getEngine() {
  return m_engine.get();
}