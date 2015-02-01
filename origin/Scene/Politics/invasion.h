
#pragma once
#include "../../System/draw_window.h"
#include "../../System/data_depot.h"
#include "../../Object/collision.h"
#include "../../Resource/telop.hpp"

//
// êNçU
//

class cInvasion {
  Texture icon_;
  cTelop telop_;

  short i;
  Vec2f pos_;
  const Vec2f size_;
  const Vec2f icon_size_;
  bool on_mouse_;
  bool init_;

  mode& mode_;
  short& poli_state_;
  bool& pause_;
  u_short& stage_id_;
  bool flag_;

  enum { Back = -2 };
  short state_;
  short id_;

  float x;
  float icon_y[design::AllStage];

  struct {
    short time_;
    short blink_;
    float alpha_;
  } anime;

  void init();

  bool stateChange();
  void moveMode();
  void blinkMode();
  void backMode();
  void buttonSelect();

  void back_command();
  void disp_command();

  void buttonPosTranslate(const short&);
  void buttonPosInit();

public:
  cInvasion();

  void update();
  void draw();
};
