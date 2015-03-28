#include "GateKeeper.h"


int main()
{
  GateKeeper gk(*(new SGO()), new Marx::Map(1, 1), 1, 1);

  return 0;
}
