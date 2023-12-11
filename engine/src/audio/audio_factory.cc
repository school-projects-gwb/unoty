#include "audio_factory.h"

namespace engine::audio {
Audio *AudioFactory::CreateAudio(const std::string &file_path, bool no_sound_mode) {
  if (no_sound_mode) {
    return new NullAudio(file_path);
  }

  std::filesystem::path file(file_path);

  try {
    if (file.extension() == ".ogg") {
      return new SDLMusicWrapper(file_path);
    } else {
      return new SDLSoundEffectWrapper(file_path);
    }
  } catch (std::invalid_argument &e) {
    std::cerr << "[AudioFactory]: Failed to load sound file at " << e.what() << std::endl;
  }

  return nullptr;
}

} // namespace engine::audio
