
#pragma once
#include "../Manager/data_manager.h"

//
// マップ情報管理
//

class cMapData {
  Texture map_;

public:
  cMapData();

  bool mapInit(const u_short&);
  void draw(const float&);
};
