//
// システム（数値関係）
//

#pragma once
#include "../common.h"
#include <vector>
#include <memory>


class DispNumber {
  std::shared_ptr<Texture> number;
  std::vector<short> val;
  std::vector<short>::iterator it;
  short i;

  // 画像切り取りサイズ
  enum CutSize {
    Num_W = 32,   // Number Width
    Num_H = 48,   // Number Height
  };

public:
  DispNumber() :
    number(std::make_shared<Texture>("res/png/sys01_number.png")) {}

  // 数値の表示
  void disp_value(float x, float y,
                  float scale = 1.0f,
                  Color color = Color(1.0f, 1.0f, 1.0f, 1.0f)) {
    for (it = val.begin(), i = 0; it != val.end(); ++it, ++i) {
      drawTextureBox(x - i * (Num_W * scale), y, Num_W, Num_H,
        0, (*it) * Num_H, Num_W, Num_H,
        *number, color,
        0, Vec2f(scale, scale), Vec2f(Num_W / 2, Num_H / 2));
    }
  }

  // データの桁ごとに値を抽出
  void init_value(int n) {
    // 呼び出した時にデータが残っていたらリセット
    if (val.size()) { val.clear(); }
    do {
      val.emplace_back(n % 10);
      n /= 10;
    } while (n > 0);
  }
};
