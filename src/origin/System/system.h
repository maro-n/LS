
#pragma once
#include "../common.h"
#include <fstream>

//
// システムデータ
// TIPS: 外部に保存しないデータ類
//     : データの管理は cDataManager クラスで行う
//

class cSystem {
public:
  cSystem() = default;

  // セーブデータの状態
  // TIPS: 使用状態のみを管理するデータを読み込んでゲームに反映する
  bool slot_state_[3];

  // ポーズ画面判定
  bool isPause_;

  // 描画シーンの状態
  // TIPS: 起動時の初期化は cGameManager クラスで行う
  // * 以降は scene_manager クラス内で管理
  // * play::Now, Last, Next で各段階の描画状態を参照する
  state::SceneMode scene_[3];

  // 政策画面のコマンド選択状態
  state::PoliticsMode poli_mode_;

  // ステージセレクトで選択したステージのID
  // TIPS: マップ情報読み込みの処理で使う
  u_short stage_id_;

  // 戦闘シーンの状態
  // TIPS: 戦闘、リザルトの各シーン内で処理を切り替える
  // *
  // * phase::Win, Lose でリザルトの処理を切り替える
  state::BattlePhase phase_;
};
