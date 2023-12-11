#ifndef ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_AUDIO_MANAGER_H
#define ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_AUDIO_MANAGER_H

#define CALCULATE_VOLUME(v) ((MIX_MAX_VOLUME * v) / 100)

#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include <string>

#include <SDL.h>
#include <SDL_mixer.h>

namespace engine::audio {

class SDLMixerAdapter {
 public:
  SDLMixerAdapter(const SDLMixerAdapter &) = delete;
  SDLMixerAdapter(SDLMixerAdapter &&) = delete;
  SDLMixerAdapter &operator=(const SDLMixerAdapter &) = delete;
  SDLMixerAdapter &operator=(SDLMixerAdapter &&) = delete;

  /// @brief Returns the singleton instance of the SDLMixerAdapter.
  static SDLMixerAdapter &GetInstance();

  /// @brief Quits SDL_mixer
  static void CleanUp();

  /// @brief Adds a new Mix_Music object to the playlist.
  ///
  /// @param file_path The path to the music file.
  int EnqueueMusic(const std::string &file_path);

  /// @brief Plays the music track at the given location in the list of music.
  ///
  /// @param index Which music track to play.
  /// @param volume The volume at which to play the music track.
  /// @param loop The amount of times the track should loop. -1 to loop until manually stopped.
  void PlayMusic(int index, int volume, int loops);

  /// @brief Stops the currently playing music if the given track number matches.
  ///
  /// @param track_number The track number of the music to be stopped.
  void StopMusic(int track_number);

  /// @brief Pauses the currently playing music if the given track number matches.
  ///
  /// @param track_number The track number of the music to be paused.
  ///
  /// @return True when paused, false when resumed.
  bool PauseMusic(int track_number);

  /// @brief Changes the volume of the music channel if the track number matches the playing music.
  ///
  /// @param track_number The track number.
  /// @param volume The new volume, between 0 and MIX_MAX_VOLUME. -1 to query.
  ///
  /// @return The new volume of the music channel.
  int ChangeMusicVolume(int track_number, int volume);

  /// @brief Adds the given Mix_Chunk to the pool of available sounds.
  ///
  /// @param file_path The path where the .wav is saved.
  ///
  /// @return The key under which the chunk is saved.
  std::string AddSound(const std::string &file_path);

  /// @brief Plays the sound saved under the given string.
  ///
  /// @param s The key under which the chunk is saved.
  /// @param loops How many times the sound should loop. -1 to loop until manually stopped..
  ///
  /// @return The channel in which the sound is being played.
  int PlaySound(const std::string &s, int loops);

  /// @brief Stops the sound saved under the given string, if it's currently playing.
  ///
  /// @param s The key under which the chunk is saved.
  /// @param channel The channel in which the sound is being played.
  void StopSound(const std::string &s, int channel);

  /// @brief Attempts to pause the sound being played in the given channel.
  ///
  /// @param s The key under which the chunk is saved.
  /// @param channel The channel in which the sound is being played.
  ///
  /// @return True when paused, false when resumed.
  bool PauseSound(const std::string &s, int channel);

  /// @brief Changes the volume of the given sound channel.
  ///
  /// @param s The key under which the sound chunk is saved.
  /// @param volume The new volume, between 0 and MIX_MAX_VOLUME. -1 to query.
  ///
  /// @return The previous volume of the channel.
  int ChangeSoundVolume(const std::string &s, int volume);

  /// @brief Frees the chunk stored at the given key from memory.
  ///
  /// @param s The key under which the sound chunk is saved.
  void FreeChunk(const std::string &s);

  /// @brief Frees the music object stored at the given key from memory.
  ///
  /// @param m The key under which the music object is stored.
  void FreeMusic(int m);

  ~SDLMixerAdapter();

 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;

  SDLMixerAdapter();
};
} // namespace engine::audio

#endif // ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_AUDIO_MANAGER_H
