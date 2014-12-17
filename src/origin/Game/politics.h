
#pragma once
#include "../System/window_create.h"
#include "../../lib/random.hpp"
#include "../Object/collision.h"
#include "../../lib/font.hpp"
#include <ctime>

//
// ê≠çÙâÊñ 
//

struct Button {
  Vec2f pos;
  Color color;
  int mode;

  Button() {}
  Button(Vec2f pos0, Color col, int m) {
    pos = pos0;
    color = col;
    mode = m;
  }
};

class Politics {
  Texture BG;

  Button button[12];
  Random random;
  Col color_variation;
  Font font;

  int r;
  int on_box;
  int click_pos;

public:
  Politics();

  void draw(int&);
  void update(int&, bool&);

  void politics_draw();
  void politics_update();

  void politics_reset();

  void stage_draw();
  void stage_update(bool&);

  void stage_reset();

  void win();
};
