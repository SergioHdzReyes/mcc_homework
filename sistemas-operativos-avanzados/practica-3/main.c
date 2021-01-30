#include <stdio.h>
#include "menu.h"
#include "file_tools.h"

int main(void)
{
  load_config();
  create_base_file();

  return 0;
}
