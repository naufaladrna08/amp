#ifndef AUDIO_ENGINE_HPP
#define AUDIO_ENGINE_HPP
#include <vector>
#include <string>

class AudioEngine {
  public:
    virtual ~AudioEngine() = default;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    virtual void processAudio() = 0;
    virtual std::vector<std::string> getAvailableInputDevices() = 0;
    virtual std::vector<std::string> getAvailableOutputDevices() = 0;
    virtual bool setInputDevice(const std::string& device) = 0;
    virtual bool setOutputDevice(const std::string& device) = 0;
    
    /* Backend: Engine */
    virtual bool isBackendRunning() = 0;
    virtual void startBackend() = 0;
    virtual void stopBackend() = 0;

    /* Recording Logic */
    virtual void startRecording() = 0;
    virtual void stopRecording() = 0;
    virtual bool isRecording() = 0;
    virtual bool writeAudioBuffer() = 0;
};

#endif