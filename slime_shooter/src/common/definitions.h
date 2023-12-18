#ifndef SLIME_SHOOTER_SRC_COMMON_SLIME_SHOOTER_SRC_COMMON_DEFINITIONS_H_
#define SLIME_SHOOTER_SRC_COMMON_SLIME_SHOOTER_SRC_COMMON_DEFINITIONS_H_

#include "entities/structs/color.h"

using namespace engine::entities;

namespace slime_shooter {

/// @brief GameColor struct for easy access to colors based on game's color scheme
///
/// Example usage: GameColor::Green::Shade1
/// The lower the shade the darker the GameColor; i.e. Shade1 is the darkest, Shade4 is the lightest variant of a GameColor
struct GameColor {
  struct Green {
    static constexpr engine::entities::Color Shade1 = {50, 100, 112};
    static constexpr engine::entities::Color Shade2 = {0, 153, 133};
    static constexpr engine::entities::Color Shade3 = {75, 172, 130};
    static constexpr engine::entities::Color Shade4 = {133, 190, 133};
  };

  struct DarkGreen {
    static constexpr engine::entities::Color Shade1 = {6, 34, 49};
    static constexpr engine::entities::Color Shade2 = {47, 72, 88};
    static constexpr engine::entities::Color Shade3 = {50, 100, 112};
    static constexpr engine::entities::Color Shade4 = {61, 128, 129};
  };

  struct Coral {
    static constexpr engine::entities::Color Shade1 = {234, 121, 118};
    static constexpr engine::entities::Color Shade2 = {253, 149, 145};
    static constexpr engine::entities::Color Shade3 = {255, 167, 162};
    static constexpr engine::entities::Color Shade4 = {255, 190, 186};
  };

  struct Purple {
    static constexpr engine::entities::Color Shade1 = {136, 42, 140};
    static constexpr engine::entities::Color Shade2 = {255, 137, 255};
    static constexpr engine::entities::Color Shade3 = {255, 162, 255};
    static constexpr engine::entities::Color Shade4 = {255, 185, 255};
  };

  struct Orange {
    static constexpr engine::entities::Color Shade1 = {175, 100, 45};
    static constexpr engine::entities::Color Shade2 = {208, 123, 64};
    static constexpr engine::entities::Color Shade3 = {235, 152, 94};
    static constexpr engine::entities::Color Shade4 = {255, 206, 146};
  };

  /// @brief Exception to other colors: This contains colors for various UI components and doesn't use Shade naming
  struct Ui {
    static constexpr engine::entities::Color BackgroundDark = {5, 13, 26};
    static constexpr engine::entities::Color TextWhite = {234, 243, 233};
    static constexpr engine::entities::Color TextGray = {125, 125, 125};
    static constexpr engine::entities::Color TextRed = {255, 153, 151};
    static constexpr engine::entities::Color TextGreen = {185, 205, 147};
    static constexpr engine::entities::Color TextPink = {239, 175, 243};

    static constexpr engine::entities::Color PrimaryButtonText = {185, 205, 147};
    static constexpr engine::entities::Color PrimaryButtonBackground = {47, 72, 88};

    static constexpr engine::entities::Color SecondaryButtonText = {185, 205, 147};
    static constexpr engine::entities::Color SecondaryButtonBackground = {23, 44, 58};
  };
};

struct GameFont {
  static std::string Default;
};

std::string GameFont::Default = "resources/fonts/PressStart2P-Regular.ttf";

}

#endif //SLIME_SHOOTER_SRC_COMMON_SLIME_SHOOTER_SRC_COMMON_DEFINITIONS_H_
