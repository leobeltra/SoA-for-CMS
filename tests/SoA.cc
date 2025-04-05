#include <tuple> 
#include <memory>

#include "SoALayout.h"
#include "SoACommon.h"
#include "SoAView.h"

// clang-format off
GENERATE_SOA_LAYOUT(SimpleLayoutTemplate,
    SOA_COLUMN(float, x),
    SOA_COLUMN(float, y),
    SOA_COLUMN(float, z),
    SOA_COLUMN(float, t))
  // clang-format on
  
  using SimpleLayout = SimpleLayoutTemplate<>;

  int main() {}