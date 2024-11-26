/*
 * Jack Audio Interface Implementation
 * 
 * This class is an implementation of the AudioInterface class using the Jack Audio Connection Kit.
 */

#include <engine/AudioEngine.hpp>
#include <jack/jack.h>
#include <sndfile.h>
#include <iostream>

class JackEngine : public AudioEngine {
  public:
    JackEngine();
    ~JackEngine();

    bool initialize() override;
    void shutdown() override;
    void processAudio() override;

    std::vector<std::string> getAvailableInputDevices() override;
    std::vector<std::string> getAvailableOutputDevices() override;

    bool setInputDevice(const std::string& device) override;
    bool setOutputDevice(const std::string& device) override;

    bool isBackendRunning() override;
    void startBackend() override;
    void stopBackend() override;

    void startRecording() override;
    void stopRecording() override;
    bool isRecording() override;
    bool writeAudioBuffer() override;

    std::vector<float> m_recordingBuffer;

  private:
    jack_client_t* m_client;
    jack_port_t* m_inputPort;

    bool m_isRecording = false;
    
    SNDFILE* m_sndFile;
    SF_INFO m_sfInfo;

    static int processCallback(jack_nframes_t nframes, void* arg);
};