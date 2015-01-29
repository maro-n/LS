
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
  short Worker_count;
  Vec2f pos_;
  const Vec2f size_;
  bool on_mouse_;
  bool init_;

  enum {
    Worker,
    Sell_fire,
    Sell_bomb,
    Sell_trap,
    Sell_poison,
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
  short state_;
  short id_;

  float x[All_Text];

  u_int& money_;
  u_short& food_;

  u_short& fire_;
  u_short& cannon_;
  u_short& trap_;
  u_short& poison_;

  void init();

  void earn();

  bool stateChange();
  void moveMode();
  void blinkMode();
  void backMode();
  void buttonSelect();

  void buttonPosTranslate(const short&);
  void buttonPosInit();

public:
  cFunds();

  void update();
  void draw();
};
