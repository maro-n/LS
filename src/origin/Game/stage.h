
#pragma once
#include "../System/window_create.h"
#include "../System/disp_number.hpp"
#include "../../lib/font.hpp"
#include "../Object/collision.h"
#include <string>

//
// –{•Ò
//

struct Data {
  Texture own;

  u_int hp_max;
  u_int hp;

  u_short type;
  u_short wait_time;
  u_short count;

  u_int attack;
  u_int defend;
  u_int speed;
  u_int move;
};

struct Button_ {
  Button_() {}
  Button_(Vec2f pos0, Color color0, std::string str0) :
    pos(pos0), color(color0), str(str0) {}

  Vec2f pos;
  Color color;
  std::string str;
};

class Stage {
  DispNumber num;

  Texture bg;
  Texture temp;

  Data player;
  Data enemy;
  Button_ button[3];

  Font font;

  bool turn;
  u_short temp_time;
  u_short count;

  void draw_bg();
  void draw_player();
  void draw_enemy();

  void draw_button();

  void draw_turn_list();
  void draw_hp();

public:
  Stage();

  void draw();
  void update();

  void reset();
  bool game_set(int&, int&);
};
