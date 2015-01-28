
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"
#include "../Resource/telop.h"

//
// Ž‘‹àŒJ‚è
//

class cFunds {
  cTelop telop_;

  short i;
  short v;
  float move_speed[4];
  float alpha;
  Vec2f pos_;
  Vec2f size;

  std::string f_mode[4];
  enum {
    Business,
    Worker,
    Sell,
    Back,
  };

public:
  cFunds();

  void update();
  void draw();
};
