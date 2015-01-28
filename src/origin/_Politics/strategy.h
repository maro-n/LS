
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"
#include "../Resource/telop.h"

//
// çÏêÌ
//

class cStrategy {
  cTelop telop_;

  Vec2f pos_;
  Vec2f size;
  short i;
  short v;
  float move_speed[5];
  float alpha;

  std::string s_mode[5];
  enum {
    Fire,
    Bombar,
    Trap,
    Poison,
    Back,
  };

public:
  cStrategy();

  void update();
  void draw();
};
