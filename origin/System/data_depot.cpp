
#include "data_depot.h"


std::string data::file_;

cSystem data::system;
cUser   data::user;
Random  data::random;

cMusicResource data::music;


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


// ゲーム開始時の描画シーン指定
// TIPS: 基本的にデバッグ用。完成版では Title のみを指定する
void data::sceneInit(const state::SceneMode& scene0) {
  system.scene_[play::Last] = scene::None;
  system.scene_[play::Now]  = scene::None;
  system.scene_[play::Next] = scene0;
  system.poli_mode_ = mode::Neutral;
  system.phase_ = phase::Standby;
}


// 新規ゲーム
void data::newGame(const dif& difficulty) {
  user.dif_ = difficulty;

  // TIPS: 乱数を使ってステージの状態を設定
  short r = random.fromZeroToLast(design::AllStage);
  for (short i = 0; i < design::AllStage; ++i) {
    user.map_info[i].flag_ = (r == i) ? true : false;
    user.map_info[i].id_ = random.fromZeroToLast(3);
  }

  user.count.clear_ = 0;
  user.count.battle_ = 0;
  user.count.turn_ = 0;

  user.assets.money_ = 1000;
  user.assets.food_ = 10;

  user.strategy.poison_ = 0;
  user.strategy.fire_ = 0;
  user.strategy.cannon_ = 0;
  user.strategy.spy_ = true;
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

  std::ofstream fstr(file_);
  if (fstr) {

    // TIPS: ゲームの難易度を保存
    fstr << user.dif_;

    // TIPS: マップデータを保存
    for (short i = 0; i < design::AllStage; ++i) {
      fstr << user.map_info[i].flag_ << user.map_info[i].id_;
    }

    // TIPS: クリア回数など、システムに関わるデータの保存
    fstr
      << user.count.clear_
      << user.count.battle_
      << user.count.turn_;

    // TIPS: 資金など、政策画面に関わるデータを保存
    fstr << user.assets.money_ << user.assets.food_;

    // TIPS: 作戦コマンドのデータを保存
    fstr
      << user.strategy.poison_
      << user.strategy.fire_
      << user.strategy.cannon_
      << user.strategy.spy_;

    // TIPS: 作成済みのキャラクター数を保存
    fstr << user.player.size();

    // TIPS: キャラクターデータを保存
    std::vector<cCharacter>::iterator it;
    for (it = user.player.begin(); it != user.player.end(); ++it) {
      fstr
        << it->getInfo().side_
        << it->getInfo().name_
        << it->getInfo().type_
        << it->getInfo().gender_
        << it->getInfo().level_
        << it->getInfo().exp_

        << it->getBaseStatus().pow_
        << it->getBaseStatus().vit_
        << it->getBaseStatus().mag_
        << it->getBaseStatus().spd_
        << it->getBaseStatus().dex_
        << it->getBaseStatus().luk_;
    }

    return true;
  }

  return false;
}


// データ読み込み
// TIPS: 読み込みに失敗したら false を返す
bool data::loadUserData(const short& num) {

  // ファイルパスを取得。失敗なら処理を中断
  if (!getFilePass(num)) { return false; }

  std::ifstream fstr(file_);
  if (fstr) {

    // TIPS: ゲームの難易度を取得
    short temp;
    fstr >> temp;
    user.dif_ = dif(temp);

    // TIPS: マップデータを取得
    for (short i = 0; i < design::AllStage; ++i) {
      fstr >> user.map_info[i].flag_ >> user.map_info[i].id_;
    }

    // TIPS: クリア回数など、システムに関わるデータの取得
    fstr
      >> user.count.clear_
      >> user.count.battle_
      >> user.count.turn_;

    // TIPS: 資金など、政策画面に関わるデータを取得
    fstr >> user.assets.money_ >> user.assets.food_;

    // TIPS: 作戦コマンドのデータを取得
    fstr
      >> user.strategy.poison_
      >> user.strategy.fire_
      >> user.strategy.cannon_
      >> user.strategy.spy_;

    // TIPS: 作成済みのキャラクター数を取得、配列を確保する
    short num;
    fstr >> num;
    for (short i = 0; i < num; ++i) { user.player.emplace_back(); }

    // TIPS: キャラクターデータを取得
    std::vector<cCharacter>::iterator it, begin, end;
    begin = user.player.begin();
    end = user.player.end();
    for (it = begin; it != end; ++it) { it->fileLoad(fstr); }

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
