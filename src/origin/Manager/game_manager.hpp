
#pragma once
#include "win_manager.h"
#include "data_manager.h"
#include "scene_manager.h"
#include "../Resource/image.h"

//
// ゲーム管理クラス
// TIPS:
// * このクラスのコンストラクタは最後に実行されるようなので、
// * 乱数を扱う場合はシード値の設定後か、更新処理の内部で行うこと
//

class cGameManager {
  cSceneManager scene_;

public:
  // TIPS: 起動時、必要な初期化を行う
  cGameManager() {
    // CAUTION:
    // * シード値初期化のタイミングがわからなくなるので、
    // * この場所から移動させないこと
    data::random.setSeed(u_int(time(nullptr)));

    // TIPS: 描画開始するシーンを指定
    data::sceneInit(scene::Title);

    //data::system.slotCheck();
    //win::app->bgColor(win::color(paint::Green, 0.5f));
  }

  // ゲーム実行
  // CAUTION: この関数以外に while ループを作らない
  void run() {
    while (win::app->isOpen() && !scene_.exit()) {
      //scene_.init();
      scene_.update();
      scene_.draw();
    }
  }
};
