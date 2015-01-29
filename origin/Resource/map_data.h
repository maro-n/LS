
#pragma once
#include "../System/data_depot.h"

//
// ƒ}ƒbƒvî•ñŠÇ—
//

class cMapData {
  Texture back_ground_;
  Texture map_;

public:
  cMapData();

  bool mapInit(const u_short&);
  void draw(const float&);
};
