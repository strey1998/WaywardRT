// WaywardRT/WaywardRT/include/WaywardRT/Textures/Checkered.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_CHECKERED_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_CHECKERED_H_

#include "WaywardRT_export.h"

#include <memory>

#include "WaywardRT/Color.h"
#include "WaywardRT/Textures/Texture.h"
#include "WaywardRT/util.h"
namespace WaywardRT { class Vec3; }

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Abstract class for textures
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Checkered : public Texture {
 private:
  std::shared_ptr<Texture> m_Texture1;
  std::shared_ptr<Texture> m_Texture2;
 public:
  Checkered() = delete;
  Checkered(const Color& c1, const Color& c2);
  Checkered(std::shared_ptr<Texture> t1, std::shared_ptr<Texture> t2);

  //////////////////////////////////////////////////////////////////////////////
  /// {@inheritDocs}
  //////////////////////////////////////////////////////////////////////////////
  Color value(real u, real v, const Vec3& p) const override;
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_TEXTURES_CHECKERED_H_
