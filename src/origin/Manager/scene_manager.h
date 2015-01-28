
#pragma once
#include "win_manager.h"
#include "data_manager.h"
#include "../Scene/title.h"
#include "../Scene/politics.h"
#include "../Scene/battle.h"
#include "../Scene/result.h"
#include "../Scene/data_select.h"
#include "../Scene/pause.h"

//
// 場面管理クラス
//

class cSceneManager {
  cTitle      title_;
  cPolitics   politics_;
  cBattle     battle_;
  cResult     result_;
  cDataSelect select_;
  cPause      pause_;

  // 画面切り替え演出用のメンバ変数
  struct {
    fade mode_;     // 切り替え処理の状態

    short time_;    // 演出のタイムカウンタ
    float alpha_;   // 透明度
  } anime;

  bool sceneShift();
  void sceneChange();

  void fadeShift();
  bool fadeOut();
  bool fadeIn();

  void effectInit();

public:
  cSceneManager();

  void update();
  void init();
  void draw();

  bool exit();
};
