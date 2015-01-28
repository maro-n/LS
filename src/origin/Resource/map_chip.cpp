
#include "map_chip.h"

typedef cMapData  mapdata;


cMapData::cMapData() {
}


// マップ情報の初期化
// TIPS: 侵攻時、受け取った番号に対応したマップ情報を展開
// TIPS: データの取得に成功したときのみ true を返す
bool mapdata::mapInit(const u_short& id) {
  std::string chip_pass;

  // TIPS: 番号に対応したファイルパスを取得
  // CAUTION: 追加作業はコピペのみ。case 以外を変更しないこと
  switch (data::user.map_info[id].id_) {
    case  0: chip_pass = "res/png/map_01.png"; break;
      //TODO:画像パスを追加

    // TIPS: 異常な値を受け取ったら処理を中断
    default: return false;
  }

  // TIPS: 取得したパスをもとにファイルを読み込む
  map_ = Texture(chip_pass);

  return true;
}


//TODO:切り取りサイズを正規のデータに置き換え
void mapdata::draw(const float& camera_x) {
  drawTextureBox(-size::WIDTH / 2, -size::HEIGHT / 2, size::WIDTH, size::HEIGHT,
    camera_x, 0, 0, 0,
    map_, Color(1, 1, 1),
    0, Vec2f(1, 1), Vec2f(0, 0));
}
