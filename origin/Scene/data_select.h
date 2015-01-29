
#pragma once
#include "../System/draw_window.h"
#include "../System/data_depot.h"
#include "../Object/collision.h"
#include "../Resource/telop.hpp"

//
// データのセーブ、ロード
//

class cDataSelect {
  Texture bg_;

  std::vector<cCharacter>::iterator it, begin, end;

  short i;
  cTelop telop_;
  Vec2f pos_;
  const Vec2f slot_size_;
  bool on_mouse_;

  enum {
    Slot1,
    Slot2,
    Slot3,
    Back,

    Save,
    Load,

    All_Text,
  };
  std::string text[All_Text];
  short text_id_;

  scene& now_;


  void disp_back();
  void disp_slot();
  void disp_info();

  void buttonPosTranslate(const short&);

public:
  cDataSelect();

  void update();
  void init();
  void draw();
};
