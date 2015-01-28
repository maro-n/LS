
#pragma once
#include "../Manager/data_manager.h"
#include "../Object/collision.h"

//
// 編成画面
//

class cUnitSelect {
  short i_;
  const Vec2f size_;
  const Vec2f select_;
  Vec2f pos_;

  struct {
    Vec2f pos_;
    SelectState state_;
  } icon[PT_Member];


  void act_out();
  void act_click();
  void init_select(const short&);

  bool selectFinish();
  void phaseShift();
  void act_shift(const short&);

  void disp_other();
  void disp_info();
  void disp_unit();
  void disp_telop();
  void disp_select();

public:
  cUnitSelect();

  void update();
  void init();
  void draw();
};


/*実装リスト

実装済み

・クリック判定
・クリック回数上限
・戦闘シーン移行
・ボタンカラーの詳細設定
・ウィンドウ、ボタンの描画


予定

・存在しないユニットは選択不可能
・存在しないユニットのボタンカラー変更
・テロップ表示
・キャラクター名の描画
・出撃メンバーの登録処理


※要画像

・背景描画
・キャラクター描画

*/
