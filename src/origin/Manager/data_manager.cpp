
#include "data_manager.h"


std::string data::file_;

std::vector<cCharacter>::iterator data::it;
cSystem data::system;
cUser   data::user;
Random  data::random;


// ゲーム開始時の描画シーン指定
// TIPS: 基本的にデバッグ用。完成版では Title のみを指定する
void data::sceneInit(const state::SceneMode& scene0) {
  system.scene_[play::Last] = scene::None;
  system.scene_[play::Now]  = scene::None;
  system.scene_[play::Next] = scene0;
  system.isPause_ = false;
  system.poli_mode_ = mode::Neutral;
}


// データの整合性チェック
// TIPS: ループの最初に実行する
void data::bugProof() {

  // クリア回数
  // TIPS: 回数が増えすぎていないか判定
  {
    u_short& clear = user.count.clear_;
    clear = (clear < 100) ? clear : 100;
  }
}


// スロットのファイルパスを取得
// TIPS: パスの取得に成功したら true を返す
bool data::getFilePass(const short& num) {
  switch (num) {
    case 0: file_ = "res/data/system/user_data1.txt"; break;
    case 1: file_ = "res/data/system/user_data2.txt"; break;
    case 2: file_ = "res/data/system/user_data3.txt"; break;

    // CAUTION: ここの処理は変更しないこと
    // TIPS: 異常な値を受け取ったら、処理を強制的に終了させる
    default: return false;
  }

  return true;
}


// スロットの使用状況を確認
void data::slotCheck() {

  bool& slot1 = data::system.slot_state_[0];
  bool& slot2 = data::system.slot_state_[1];
  bool& slot3 = data::system.slot_state_[2];

  // TIPS: スロットをすべて「未使用」として初期化
  slot1 = slot2 = slot3 = false;

  std::ifstream load("res/data/system/slot_state.txt");
  if (load) { load >> slot1 >> slot2 >> slot3; }
}


// データ保存
// TIPS: 保存できなかったら false を返す
bool data::saveUserData(const short& num) {

  // ファイルパスを取得。失敗なら処理を中断
  if (!getFilePass(num)) { return false; }

  std::fstream fstr(file_);
  if (fstr) {
    return true;
  }

  return false;
}


// データ読み込み
// TIPS: 読み込みに失敗したら false を返す
bool data::loadUserData(const short& num) {

  // ファイルパスを取得。失敗なら処理を中断
  if (!getFilePass(num)) { return false; }

  std::fstream fstr(file_);
  if (fstr) {
    return true;
  }

  return false;
}


// 獲得済み領地の数を取得
short data::getTerritory() {
  short num = 0;

  for (short i = 0; i < design::AllStage; ++i) {
    if (user.map_info[i].flag_) { ++num; }
  }

  return num;
}
