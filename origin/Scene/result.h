
#pragma once
#include "../System/draw_window.h"
#include "../System/data_depot.h"
#include "../Object/collision.h"
#include "../Resource/telop.hpp"

//
// ƒŠƒUƒ‹ƒg‰æ–Ê
//

class cResult {
  cTelop telop_;
  Texture bg_;

  struct {
    u_short wait_;
    u_short time_;
    u_short blink_;
    float alpha_;
  } anime;

  enum ClickState {
    Start,
  };
  short state_;

  phase& phase_;
  u_short& exp_;

  short level_up_;
  Vec2f pos_;

  void phaseWin();
  void phaseLose();

  bool isLevelUp();

  void disp_bg();
  void disp_logo();
  void disp_telop();

public:
  cResult();

  void update();
  void init();
  void draw();
};
