
#pragma once
#include "../Manager/win_manager.h"

//
// “–‚½‚è”»’è
//

namespace Collision {
  bool box_to_cursor(const Vec2f&, const Vec2f&);
  bool box_to_box();
}

using namespace Collision;
