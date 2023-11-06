
#include "audio_factory.h"

Audio* engine::audio::audio_factory::CreateAudio(const std::string& filePath) {
  return new SdlAudio(" ");
}
