
#include "system_data.h"

std::string Sys::fstr_;

Difficulty Sys::dif_;
short Sys::stage_count_;
short Sys::clear_count_;

// バグ回避
// TIPS: 必ずゲーム本編ループ内の最初に実行
void Sys::BugProof() {
  // 1 <= stage <= 12 の判定
  stage_count_ = short(std::min(float(GameStart),
    std::max(float(stage_count_), float(GameClear))));
}

void Sys::DataLoad(const int slot) {
  switch (slot) {
    case  0: fstr_ = "res/data/system/save_1.txt"; break;
    case  1: fstr_ = "res/data/system/save_2.txt"; break;
    case  2: fstr_ = "res/data/system/save_3.txt"; break;
    default: fstr_ = "res/data/system/default.txt";
  }

  std::ifstream load(fstr_);
  if (load) {
  }
}

void Sys::DataSave(const int slot) {
  switch (slot) {
    case  0: fstr_ = "res/data/system/save_1.txt"; break;
    case  1: fstr_ = "res/data/system/save_2.txt"; break;
    case  2: fstr_ = "res/data/system/save_3.txt"; break;
    default: return;   // セーブ処理を強制的に中断
  }

  std::ofstream save(fstr_);
  if (save) {
  }
}
