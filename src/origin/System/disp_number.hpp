
#pragma once
#include "../common.h"
#include <vector>

//
// システム（数値関係）
//

class cDispNumber {
  Texture number_;
  std::vector<short> val_;
  std::vector<short>::iterator it_;
  short i;

  enum CutSize {
    Num_W = 32,   // Number Width
    Num_H = 40,   // Number Height
  };

public:
  cDispNumber() :
    number_(Texture("res/png/sys02_number.png")) {}

  // 数値の表示
  // pos : 表示させる座標ｘとｙ（中心点）
  // scale : 画像の縮尺
  // color : 色（red, green, blue, alpha）
  void dispValue(const Vec2f& pos,
                 const float& scale = 1.0f,
                 const Color& color = Color(1.f, 1.f, 1.f, 1.f)) {

    // TIPS: １の桁から一番大きい桁に向かって描画する（右から左に）
    for (it_ = val_.begin(), i = 0; it_ != val_.end(); ++it_, ++i) {

      drawTextureBox(pos.x() - i * (Num_W * scale), pos.y(),
        Num_W, Num_H,
        0, (*it_) * Num_H, Num_W, Num_H,
        number_, color,
        0, Vec2f(scale, scale), Vec2f(Num_W / 2, Num_H / 2));
    }
  }

  // データの桁ごとに値を抽出
  void inputValue(int n) {
    // TIPS: 呼び出した時にデータが残っていたら先にリセットする
    if (val_.size()) { val_.clear(); }

    // TIPS: 配列が空なので、必ず１つは要素を取得する
    do {
      val_.emplace_back(n % 10);
      n /= 10;
    } while (n > 0);
  }
};
