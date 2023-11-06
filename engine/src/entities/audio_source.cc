//
// Created by devli on 31/10/2023.
//

#include "entities/audio_source.h"
#include "audio/audio_factory.h"
#include "helpers/path_helper.h"
#include <iostream>

namespace engine::entities {

class AudioSource::Impl : public Component {
 public:
  explicit Impl(const std::string &track) {
    auto t = helpers::PathHelper::GetFullPathFromRelative(track);

  }
  void Start(){
    audio_->Start(false);
  }
 private:
  Audio* audio_;
};

AudioSource::~AudioSource() = default;
AudioSource::AudioSource(const std::string &track) : impl_(std::make_unique<Impl>(track)) {

}
void AudioSource::Start() {
  impl_->Start();
}
}