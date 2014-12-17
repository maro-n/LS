
#include "window_create.h"

//
// ウィンドウ生成クラス（実装）
//

// ウィンドウ生成フラグ
bool win::isCreate = false;

// ゲーム実行環境のインスタンス
std::unique_ptr<AppEnv> win::app;

// マウスカーソル位置（ｘ、ｙ）
Vec2f win::mouse;

// ウィンドウ生成命令
// TIPS: 必ず main() の一番最初に呼び出すようにする
void win::create() {
  if (!isCreate) {
    app = std::make_unique<AppEnv>(WIDTH, HEIGHT, false, true);
    isCreate = true;
  }
}

// マウス座標の取得
void win::mouse_translate() {
  mouse = app->mousePosition();
}
