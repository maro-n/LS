
#pragma once
#include "../System/window_create.h"
#include <string>
#include <fstream>

//
// システムデータ
// TIPS: システムのセーブデータに含むもの一覧
// stage : 獲得したマスの数（初期値：1）
//
class SystemData {
  SystemData() = default;

  static std::string fstr_;

public:
  static Difficulty dif_;

  static short stage_count_;
  static short clear_count_;

  static void BugProof();

  static void DataLoad(const int);
  static void DataSave(const int);
};

typedef SystemData  Sys;
