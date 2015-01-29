
#pragma once
#include "../../System/draw_window.h"
#include "../../System/data_depot.h"
#include "../../Object/collision.h"
#include "../../Resource/telop.hpp"

//
// êNçU
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

class cInvasion {
  cTelop telop_;

  Vec2f cmd;
  Button button[3][4];
  Vec2f size;
  Color color;

  int r_x;
  int r_y;
  int on_box_y[3];
  int on_box_x[4];
  int click_pos[3][4];

public:
  cInvasion();

  void update();
  void draw();
  void win();
};
