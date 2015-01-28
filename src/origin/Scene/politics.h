
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
// 政策画面
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

  cFunds     funds_;       // 資金繰り
  cArmaments armaments_;   // 軍備
  cStrategy  strategy_;    // 作戦
  cInvasion  invasion_;    // 侵攻：ステージセレクト

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
