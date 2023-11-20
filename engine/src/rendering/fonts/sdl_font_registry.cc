#include "sdl_font_registry.h"
#include "string"
#include "utility/debug.h"
#include "utility/path_helper.h"

namespace engine::ui {

SdlFontRegistry::FontMap SdlFontRegistry::font_map;

TTF_Font* SdlFontRegistry::GetFont(const std::string& font_path, int font_size) {
  auto font_iterator = font_map.find(GetFormattedKey(font_path, font_size));
  if (font_iterator != font_map.end()) {
    return font_iterator->second;
  } else {
    return LoadFont(font_path, font_size);
  }
}

TTF_Font* SdlFontRegistry::LoadFont(const std::string& font_path, int font_size) {
  std::string key = GetFormattedKey(font_path, font_size);
  std::string full_font_path;

  if (font_map.find(key) == font_map.end()) {
    // Not found, create new font from font at path
    std::string full_path = helpers::PathHelper::GetFullPathFromRelative(font_path);
    TTF_Font* font = TTF_OpenFont(full_path.c_str(), font_size);
    if (font) {
      font_map[key] = font;
      return font;
    }

    helpers::Debug::Error("Failed to load font at path: " + full_path);
  }
  return nullptr;
}

// TODO implement this cleanup function call somewhere @jvanhouts
void SdlFontRegistry::Cleanup() {
  for (const auto& fontPair : font_map) {
    TTF_CloseFont(fontPair.second);
  }

  font_map.clear();
}

std::string SdlFontRegistry::GetFormattedKey(const std::string &font_path, int font_size) {
  return font_path + std::to_string(font_size);
}

}