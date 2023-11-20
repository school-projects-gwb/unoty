
#include "audio_factory.h"
#include "../../engine/include/engine/engine_config.h"
#include "null_audio.h"

namespace engine::audio {

Audio* AudioFactory::CreateAudio(const std::string &file_path) {
  if(engine::EngineConfig::no_sound_mode){
    return new NullAudio(file_path);
  }

  std::filesystem::path file(file_path);

  if(file.extension() == ".wav"){
    return new SdlChunkAudioWav(file_path);
  }
  else if(file.extension() == ".mp3"){
    return new SdlMusicAudioMp3(file_path);
  }

  return nullptr;
}
}
