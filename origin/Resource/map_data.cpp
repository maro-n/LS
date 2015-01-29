
#include "map_data.h"

typedef cMapData  mapdata;


cMapData::cMapData() :
back_ground_(Texture("res/png/back_grass.png")) {
}


// マップ情報の初期化
// TIPS: 侵攻時、受け取った番号に対応したマップ情報を展開
// TIPS: データの取得に成功したときのみ true を返す
bool mapdata::mapInit(const u_short& id) {
  std::string chip_pass;

  // TIPS: 番号に対応したファイルパスを取得
  // CAUTION: 追加作業はコピペのみ。case 以外を変更しないこと
  switch (data::user.map_info[id].id_) {
    case  0: chip_pass = "res/png/stage_grass.png";    break;
    case  1: chip_pass = "res/png/stage_forest.png";   break;
    case  2: chip_pass = "res/png/stage_mountain.png"; break;

    // TIPS: 異常な値を受け取ったら処理を中断
    default: return false;
  }

  // TIPS: 取得したパスをもとにファイルを読み込む
  map_ = Texture(chip_pass);

  return true;
}


// TIPS: スクロール用のデータを引数として渡す
void mapdata::draw(const float& camera_x) {

  // TIPS: 背景描画
  {
    drawTextureBox(-size::WIDTH / 2, size::HEIGHT / 4, size::WIDTH, size::HEIGHT / 4,
      camera_x * 0.25f, 0, 512, 128,
      back_ground_, Color(1, 1, 1));

    drawTextureBox(-size::WIDTH / 2, 0, size::WIDTH, size::HEIGHT / 4,
      camera_x * 0.5f, 128, 512, 128,
      back_ground_, Color(1, 1, 1));
  }

  drawTextureBox(-size::WIDTH / 2, -size::HEIGHT / 2, size::WIDTH, size::HEIGHT,
    camera_x, 0, size::WIDTH, size::HEIGHT,
    map_, Color(1, 1, 1),
    0, Vec2f(1, 1), Vec2f(0, 0));
}
