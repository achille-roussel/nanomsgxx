#include <nnxx/nn.h>

namespace nnxx {

  symbol_properties symbol(int i)
  {
    symbol_properties sp;
    sp.value = 0;
    sp.name  = nullptr;
    sp.ns    = 0;
    sp.type  = 0;
    sp.unit  = 0;
    nn_symbol_info(i, &sp, sizeof(sp));
    return sp;
  }

  void term()
  { nn_term(); }

}
