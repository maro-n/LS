
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"
#include "../Resource/telop.h"

//
// �����J��
//

class cFunds {
  cTelop telop_;

  short i;
  float move_speed;
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
