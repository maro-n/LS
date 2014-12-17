
#pragma once
#include "../System/window_create.h"
#include "../../lib/font.hpp"
#include "../Object/collision.h"
#include <string>

//
// ƒŠƒUƒ‹ƒg‰æ–Ê
//

class Result {

  Vec2f cmd[2];
  Vec2f size;
  Color color[2];
  std::string str;

  Texture BG;
  Font font;
  Col color_variation;

  void stage_clear();
  void game_over();
  void game_clear();

public:
  Result();

  void draw(int&);
  void update(bool&, bool&);

  void reset();
};
