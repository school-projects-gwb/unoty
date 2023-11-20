#ifndef ENGINE_SRC_RENDERING_FONTS_ENGINE_SRC_RENDERING_FONTS_SDL_FONT_REGISTRY_H_
#define ENGINE_SRC_RENDERING_FONTS_ENGINE_SRC_RENDERING_FONTS_SDL_FONT_REGISTRY_H_

#include <map>
#include <string>
#include <SDL_ttf.h>

namespace engine::ui {

class SdlFontRegistry {
 public:
  using FontMap = std::map<std::string, TTF_Font*>;

  static TTF_Font* GetFont(const std::string& font_path, int font_size);
  static void Cleanup();

 private:
  static FontMap font_map;
  static TTF_Font*  LoadFont(const std::string& font_path, int font_size);
  static std::string GetFormattedKey(const std::string& font_path, int font_size);
};

}

#endif //ENGINE_SRC_RENDERING_FONTS_ENGINE_SRC_RENDERING_FONTS_SDL_FONT_REGISTRY_H_
