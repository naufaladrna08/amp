#include <engine/implementation/Jack.hpp>

JackEngine::JackEngine() : m_client(nullptr), m_inputPort(nullptr) {}

JackEngine::~JackEngine() {
  if (m_isRecording) {
    stopRecording();
  }

  if (m_client != NULL) {
    shutdown();
  }
}

bool JackEngine::initialize() {
  m_client = jack_client_open("DAW", JackNullOption, NULL);
  if (m_client == NULL) {
    return false;
  }

  m_inputPort = jack_port_register(m_client, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
  if (m_inputPort == NULL) {
    return false;
  }

  return true;
}

void JackEngine::shutdown() {
  if (m_client != NULL) {
    jack_client_close(m_client);
  }
}

void JackEngine::processAudio() {
  // Process audio here
}

std::vector<std::string> JackEngine::getAvailableInputDevices() {
  const char** ports = jack_get_ports(m_client, NULL, NULL, JackPortIsPhysical | JackPortIsOutput);
  std::vector<std::string> devices;
  if (ports != NULL) {
    for (int i = 0; ports[i] != NULL; i++) {
      devices.push_back(ports[i]);
    }
    jack_free(ports);
  }

  return devices;
}

std::vector<std::string> JackEngine::getAvailableOutputDevices() {
  std::vector<std::string> devices;
  return devices;
}

bool JackEngine::setInputDevice(const std::string& device) {
  // Set input device here
  return jack_connect(m_client, device.c_str(), jack_port_name(m_inputPort));
}

bool JackEngine::setOutputDevice(const std::string& device) {
  // Set output device here
  return true;
}

bool JackEngine::isBackendRunning() {
  jack_client_t *client = jack_client_open("CheckJack", JackNoStartServer, nullptr);
  if (client) {
    jack_client_close(client);
    return true;
  }

  return false;
}

void JackEngine::startBackend() {
  jack_activate(m_client);
}

void JackEngine::stopBackend() {
  jack_deactivate(m_client);
}

void JackEngine::startRecording() {
  m_sfInfo.channels = 1;
  m_sfInfo.samplerate = jack_get_sample_rate(m_client);
  m_sfInfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  m_sndFile = sf_open("recording.wav", SFM_WRITE, &m_sfInfo);
  if (m_sndFile == NULL) {
    return;
  }

  m_isRecording = true;
  std::cout << "Recording started" << std::endl;
}

void JackEngine::stopRecording() {
  if (m_sndFile) {
    sf_write_float(m_sndFile, m_recordingBuffer.data(), m_recordingBuffer.size()); // Write remaining data
    sf_close(m_sndFile);
    m_sndFile = nullptr;
  }

  m_recordingBuffer.clear();
  m_isRecording = false;
  std::cout << "Recording stopped" << std::endl;
}

bool JackEngine::isRecording() {
  return m_isRecording;
}

bool JackEngine::writeAudioBuffer() {
  if (!m_sndFile) return false;

  sf_write_float(m_sndFile, m_recordingBuffer.data(), m_recordingBuffer.size());
  m_recordingBuffer.clear(); // Clear the buffer after writing
}

int JackEngine::processCallback(jack_nframes_t nframes, void* arg) {
  JackEngine* engine = static_cast<JackEngine*>(arg);
  jack_default_audio_sample_t* inputBuffer = static_cast<jack_default_audio_sample_t*>(jack_port_get_buffer(engine->m_inputPort, nframes));

  // Process audio here
  engine->m_recordingBuffer.insert(engine->m_recordingBuffer.end(), inputBuffer, inputBuffer + nframes);

  return 0;
}