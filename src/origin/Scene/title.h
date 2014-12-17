
#pragma once
#include "../System/window_create.h"
#include "../../lib/font.hpp"

//
// ƒ^ƒCƒgƒ‹‰æ–Ê
//

class Title {
  std::unique_ptr<Font> font;

  Texture bg;

  void draw_bg();
  void draw_logo();

public:
  Title();

  void draw();
  void update();

  void reset();
};
