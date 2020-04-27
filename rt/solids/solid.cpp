#include <rt/solids/solid.h>

namespace rt {

  Solid::Solid(CoordMapper* texMapper, Material* material)
  {
      this->material = material;
      this->texMapper = texMapper;
  }

}
