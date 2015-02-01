
#pragma once
#include "../../System/draw_window.h"
#include "../../System/data_depot.h"
#include "../../Object/collision.h"
#include "../../Resource/telop.hpp"

//
// Ž‘‹àŒJ‚è
//

class cFunds {
  cTelop telop_;

  short i;
  Vec2f pos_;
  const Vec2f size_;
  bool on_mouse_;
  bool init_;

  enum {
    Worker,
    Sell_Fire,
    Sell_Bomb,
    Sell_Trap,
    Sell_Poison,
    Back,

    All_Text,
  };
  std::string text[All_Text];

  struct {
    short time_;
    short blink_;
    float alpha_;
  } anime;

  mode& mode_;
  short& poli_state_;
  bool& pause_;
  short state_;
  short id_;

  float x[All_Text];

  u_int& money_;
  u_short& fire_;
  u_short& cannon_;
  u_short& trap_;
  u_short& poison_;
  bool is_sell_;

  void init();

  bool stateChange();
  void moveMode();
  void blinkMode();
  void backMode();
  void buttonSelect();

  void incomeMoney();
  void is_worker();
  void is_fire();
  void is_bomb();
  void is_trap();
  void is_poison();

  void isAbleToSell(const short&);
  void buttonPosTranslate(const short&);
  void buttonPosInit();

  void disp_telop(const short&);

public:
  cFunds();

  void update();
  void draw();
};
