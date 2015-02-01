
#pragma once
#include "../System/draw_window.h"
#include "../System/data_depot.h"
#include "../Object/collision.h"
#include "../Resource/telop.hpp"
#include "../Resource/map_data.h"

//
// êÌì¨âÊñ 
//

class cBattle {
  cTelop telop_;
  cMapData map_data_;

  short i;
  short enemy_num_;   // èoåªÇ≥ÇπÇÈìGÇÃêî
  std::vector<cCharacter> enemy;
  std::vector<cCharacter>::iterator it, begin, end;
  std::vector<cCharacter>::iterator target, begin_, end_;

  float camera_x_;

  struct {
    u_short time_;
    u_short blink_;
    float alpha_;
  } anime;

  struct {
    short player_;
    short enemy_;
    short count_;
  } dead;

  Vec2f pos_;
  Vec2f cut_;

  void unitSummon();

  void countInit();
  void deadCount();
  void battleFinish();
  void unitUpdate();

  void timeCount();
  void unit_animePlay();
  void unit_action();
  void physicalAttack();
  void magicalAttack();
  void cure();

  void getEnemyInfo();
  void getPlayerInfo();

  void dispUnitInfo();
  void dispPlayerInfo();
  void dispEnemyInfo();

public:
  cBattle();

  void update();
  void init();
  void draw();
};
