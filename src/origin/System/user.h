
#pragma once
#include "../common.h"
#include "../Object/character.h"
#include <vector>

//
// ユーザーデータ
// TIPS: 外部に保存するデータ類
//     : データの管理は cDataManager クラスで行う
//

class cUser {
public:
  cUser() = default;

  // ゲームの難易度
  // TIPS: 新規ゲーム開始した時のみ値を設定
  design::Difficulty dif_;

  // 読み込むマップデータと獲得済み判定
  // TIPS: 新規ゲーム開始した時のみ、ランダムに値を設定
  struct {
    bool flag_;
    u_short id_;
  } map_info[design::AllStage];

  // 各種カウントデータ
  struct {
    u_short clear_;    // ゲームのクリア回数
    u_short battle_;   // 戦闘回数
    u_short turn_;     // 政策コマンドを実行した回数
  } count;

  // 政策コマンド実行用データ
  struct {
    u_int money_;    // 資金
    u_short food_;   // 兵糧
  } assets;

  // 戦闘コマンド実行用データ
  struct {
    u_short poison_;
    u_short fire_;
    u_short cannon_;
    bool side_attack_;
    bool spy_;
  } strategy;

  std::vector<cCharacter> player;
  std::vector<cCharacter> enemy;
};
