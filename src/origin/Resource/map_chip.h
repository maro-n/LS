
#pragma once
#include "../Manager/data_manager.h"

//
// �}�b�v���Ǘ�
//

class cMapData {
  Texture map_;

public:
  cMapData();

  bool mapInit(const u_short&);
  void draw(const float&);
};
