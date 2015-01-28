
#include "scene_manager.h"

typedef cSceneManager  manager;


cSceneManager::cSceneManager() {
  anime.mode_ = fade::FadeIn;
  anime.time_ = 0;
  anime.alpha_ = 1.0f;
}


void manager::update() {

  // TIPS: 画面切り替え中なら、一切の入力を許可しない
  if (sceneShift()) { fadeShift(); return; }

  win::mouseTranslate();

  // TIPS: ポーズ画面のとき、その他の入力を許可しない
  if (pause_.update()) { return; }

  // TIPS: 各シーンごとの更新処理
  switch (data::system.scene_[play::Now]) {
    case scene::Title   : title_.update();    break;
    case scene::Politics: politics_.update(); break;
    case scene::Battle  : battle_.update();   break;
    case scene::Result  : result_.update();   break;
    default: select_.update(); break;
  }
}


// 全てのシーン演出を初期化する
void manager::init() {
  data::bugProof();
  if (sceneShift() && !fadeOut()) { effectInit(); }
}


void manager::effectInit() {
  switch (data::system.scene_[play::Next]) {
    case scene::Title   : title_.init();    break;
    //case scene::Politics: politics_.init(); break;
    case scene::Battle  : battle_.init();   break;
    //case scene::Result  : result_.init();   break;

    default:;
  }
}


void manager::draw() {
  win::app->setupDraw();

  // TIPS: 各シーンごとの描画処理
  switch (data::system.scene_[play::Now]) {
    case scene::Title   : title_.draw();    break;
    case scene::Politics: politics_.draw(); break;
    case scene::Battle  : battle_.draw();   break;
    case scene::Result  : result_.draw();   break;
    default: select_.draw(); break;
  }

  // TIPS: 画面切り替えが発生したらアニメーション開始
  sceneChange();

  // TIPS: ポーズ中ならポーズ画面の描画
  if (data::system.isPause_) { pause_.draw(); }

  win::app->update();
}


// ゲームそのものを終了する
bool manager::exit() {
  return data::system.scene_[play::Now] == scene::Exit;
}


// 画面切り替えを検出
bool manager::sceneShift() {
  if (data::system.scene_[play::Now] != data::system.scene_[play::Next]) {
    anime.mode_ = fade::FadeOut;
  }
  return anime.mode_ != fade::Stop;
}


// 画面の切り替え演出
// TIPS: 黒い四角で塗りつぶして見えないようにする
void manager::sceneChange() {
  drawFillBox(-size::WIDTH / 2, -size::HEIGHT / 2,
    size::WIDTH, size::HEIGHT,
    Color(0, 0, 0, anime.alpha_));
}


// フェードイン、フェードアウトの処理
void manager::fadeShift() {
  switch (anime.mode_) {
    case fade::FadeOut:
      if (!fadeOut()) {
        anime.mode_ = fade::FadeIn;
        data::system.scene_[play::Now] = data::system.scene_[play::Next];
      }
      break;

    case fade::FadeIn:
      if (!fadeIn()) { anime.mode_ = fade::Stop; }
      break;

    default:;
  }
}


// フェードアウト
// TIPS: 画面を見えないようにするので、黒を不透明にする
bool manager::fadeOut() {
  if (anime.alpha_ < 1.0f) { anime.alpha_ += 0.05f; }
  return anime.alpha_ < 1.0f;
}


// フェードイン
// TIPS: 画面を見えるようにするので、黒を透明にしていく
bool manager::fadeIn() {
  if (anime.alpha_ > 0) { anime.alpha_ -= 0.05f; }
  return anime.alpha_ > 0;
}
