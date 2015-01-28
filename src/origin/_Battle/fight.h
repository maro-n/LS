
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"

//
// –{•Ò
//

class cFight {
  short i_;
  const Vec2f pWin_size_;
  const Vec2f chip_size_;
  const float gauge_width_;
  float per_;
  Vec2f pos_;
  Vec2f cut_;

  sCharacter p_;
  sCharacter e_;

  struct {
    Vec2f pos_;
  } chip[Map_X * Map_Y];

  void disp_move();
  void disp_unit(const short&);
  void disp_parameter(const short&);

public:
  cFight();

  void update();
  void init();
  void draw();
};
