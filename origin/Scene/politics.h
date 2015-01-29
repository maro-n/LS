
#pragma once
#include "../System/draw_window.h"
#include "../System/data_depot.h"
#include "../Object/collision.h"
#include "../Resource/telop.hpp"
#include "Politics/funds.h"
#include "Politics/armaments.h"
#include "Politics/strategy.h"
#include "Politics/invasion.h"

//
// 準備画面
//

class cPolitics {
  cFunds     funds_;       // 資金繰り
  cArmaments armaments_;   // 軍備
  cStrategy  strategy_;    // 作戦
  cInvasion  invasion_;    // 侵攻：ステージセレクト

  Texture bg_;
  Texture sea_;
  Texture fog_;
  cTelop telop_;

  short i;
  Vec2f pos_;
  const Vec2f size_;
  bool on_mouse_;

  std::string text[mode::All_Mode];

  enum {
    Save,
    Load,
    Back,

    All_Command,
  };
  std::string choice[All_Command];

  struct {
    short time_;
    short blink_;
    float scroll_;
    float alpha_;
  } anime;

  mode& mode_;
  short& state_;
  short id_;

  float x[mode::All_Mode - 1];


  bool stateShift();
  void moveMode();
  void blinkMode();
  void backMode();

  void commandSelect();
  void dataSelect();
  void commandChange(const mode&);

  void effectPlay();
  void disp_back();
  void disp_mode();
  void disp_info();
  void disp_button();
  void disp_select();
  void disp_telop();

  void buttonPosTranslate(const short&);
  void buttonPosInit();

public:
  cPolitics();

  void update();
  void init();
  void draw();
};
