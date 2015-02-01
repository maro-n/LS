
#pragma once
#include "../../System/draw_window.h"
#include "../../System/data_depot.h"
#include "../../Object/collision.h"
#include "../../Resource/telop.hpp"

//
// ŒR”õ
//

class cArmaments {
  cTelop telop_;

  short i;
  Vec2f pos_;
  const Vec2f size_;
  bool on_mouse_;
  bool init_;

  enum {
    Growth,
    ClassChange,
    ReMake,
    Delete,
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

  void init();

  bool stateChange();
  void moveMode();
  void blinkMode();
  void backMode();
  void buttonSelect();

  void buttonPosTranslate(const short&);
  void buttonPosInit();

public:
  cArmaments();

  void update();
  void draw();
};
