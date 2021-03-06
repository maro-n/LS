
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
  short dif_;

  // 読み込むマップデータと獲得済み判定
  // TIPS: 新規ゲーム開始した時のみ、ランダムに値を設定
  struct {
    bool flag_;
    u_short id_;
  } map_info[design::AllStage];

  // 各種カウントデータ
  // TIPS: エンディングの評価画面で使う（予定）
  struct {
    u_short clear_;     // ゲームのクリア回数
    u_short battle_;    // 戦闘回数
    u_short command_;   // 戦略コマンドを実行した回数
  } count;

  // 政策コマンド実行用データ
  u_int money_;   // 資金

  // 戦闘コマンド実行用データ
  // TIPS: ポーズ画面で使用する
  struct {
    u_short fire_;
    u_short cannon_;
    u_short trap_;
    u_short poison_;
    bool spy_;
  } strategy;

  // 戦闘済みのマップフラグ
  bool wasInvasion[design::AllStage];

  // ユニット情報
  std::vector<cCharacter> player;   // プレイヤー
};
