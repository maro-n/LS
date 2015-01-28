
#pragma once
#include "../Manager/data_manager.h"

//
// ƒ}ƒbƒvî•ñŠÇ—
//

class cMapData {
  Texture map_;

public:
  cMapData();

  bool mapInit(const u_short&);
  void draw(const float&);
};
