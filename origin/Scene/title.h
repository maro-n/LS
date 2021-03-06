
#pragma once
#include "../System/draw_window.h"
#include "../System/data_depot.h"
#include "../Object/collision.h"
#include "../Resource/telop.hpp"

//
// タイトル画面
//

class cTitle {
  Texture bg_;
  Texture sea_;
  Texture fog_;
  Texture logo_;

  short i, begin_, end_;
  cTelop telop_;
  Vec2f pos_;
  const Vec2f size_;
  bool on_mouse_;
  bool& clear_;

  enum {
    Click,
    Back,
    NewGame,
    Continue,

    Easy,
    Normal,
    Hard,

    All_Text
  };
  std::string text[All_Text];
  short click_mode_;

  struct {
    u_short time_;
    u_short blink_;
    float scroll_;
    float alpha_;
  } anime;

  enum {
    Start,
    Blink1,
    Mode,
    Blink2,
    Change,
    Select,
    Blink3,

    Cancel = -1,
  };
  short state_;
  short blink_timer_;


  bool clickStart();
  void modeSelect();
  void modeShift(const short&);
  void sceneChange();

  void effectPlay();
  void disp_title();
  void disp_click();
  void disp_mode();

  void buttonPosTranslate(const short&);
  void buttonDataTranslate();

public:
  cTitle();

  void update();
  void init();
  void draw();
};
