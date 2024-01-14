#include "unit_tests.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  Suite *s_calculate = make_calculate_suite();

  SRunner *runner = srunner_create(s_calculate);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
