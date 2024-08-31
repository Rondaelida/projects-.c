#include "test.h"

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;
  Suite *list_cases[] = {
      suite_abs(),  suite_sin(),  suite_cos(),   suite_atan(),
      suite_acos(), suite_asin(), suite_fabs(),  suite_sqrt(),
      suite_tan(),  suite_exp(),  suite_fmod(),  suite_log(),
      suite_pow(),  suite_ceil(), suite_floor(), NULL};

  for (int i = 0; list_cases[i] != NULL; i++) {
    s = list_cases[i];
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
