
#pragma once
#include "../System/data_depot.h"

//
// �}�b�v���Ǘ�
//

class cMapData {
  Texture back_ground_;
  Texture map_;

public:
  cMapData();

  bool mapInit(const u_short&);
  void draw(const float&);
};