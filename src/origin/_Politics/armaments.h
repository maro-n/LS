
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"
#include "../Resource/telop.h"

//
// �R��
//

class cArmaments {
  cTelop telop_;

  Vec2f pos_;
  Vec2f size_;
  float move_speed;
  float alpha;

  std::string a_mode[5];
  enum {
    Training,
    Making,
    Restructur,
    Development,
    Back,
  };

public:
  cArmaments();

  void update();
  void draw();
};