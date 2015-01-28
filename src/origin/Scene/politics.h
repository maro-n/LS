
#pragma once
#include "../Manager/win_manager.h"
#include "../Manager/data_manager.h"
#include "../Object/collision.h"
#include "../Resource/telop.h"
#include "../_Politics/funds.h"
#include "../_Politics/armaments.h"
#include "../_Politics/strategy.h"
#include "../_Politics/invasion.h"

//
// ������
//

class cPolitics {
  cTelop telop_;

  short i;
  float move_speed;
  float alpha;
  Vec2f pos_;
  Vec2f size_;

  std::string mode_[5];
  std::string choice_[2];
  enum {
    Yes,
    No,
  };

  cFunds     funds_;       // �����J��
  cArmaments armaments_;   // �R��
  cStrategy  strategy_;    // ���
  cInvasion  invasion_;    // �N�U�F�X�e�[�W�Z���N�g

  void dataSelect();
  void modeSelect();
  void stateChange(const mode&);

  void drawButton();

public:
  cPolitics();

  void update();
  void init();
  void draw();
};
