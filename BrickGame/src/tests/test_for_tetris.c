#include <check.h>

#include "../brick_game/tetris/tetris.h"

static Tetris game;

START_TEST(test_initialize_game) {
  init_game(&game);
  ck_assert_int_eq(game.level, 0);
  ck_assert_int_eq(game.score, 0);
  ck_assert_ptr_nonnull(game.field.field);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      ck_assert_int_eq(game.field.field[i][j], 0);
    }
  }
}
END_TEST

START_TEST(test_generate_random_tetromino) {
  FigureInfo figure = generate_figure();
  ck_assert(figure.type_f >= 0 && figure.type_f < 7);
  ck_assert_int_eq(figure.rotation, 0);
}
END_TEST

START_TEST(test_rotate_piece) {
  init_game(&game);
  FigureInfo original_piece = game.current_figure;
  rotate_figure(&game);
  ck_assert_int_ne(original_piece.rotation, game.current_figure.rotation);
}
END_TEST

START_TEST(test_move_piece_left) {
  init_game(&game);
  FigureInfo original_piece = game.current_figure;
  move_figure_left_right(&game, 'l');
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(game.current_figure.Position[i].x,
                     original_piece.Position[i].x);
    ck_assert_int_eq(game.current_figure.Position[i].y,
                     original_piece.Position[i].y);
  }
}
END_TEST

START_TEST(test_move_piece_right) {
  init_game(&game);
  FigureInfo original_piece = game.current_figure;
  move_figure_left_right(&game, 'r');
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(game.current_figure.Position[i].x,
                     original_piece.Position[i].x + 1);
    ck_assert_int_eq(game.current_figure.Position[i].y,
                     original_piece.Position[i].y);
  }
}
END_TEST

START_TEST(test_move_piece_down) {
  init_game(&game);
  FigureInfo original_piece = game.current_figure;
  move_figure_down(&game);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(game.current_figure.Position[i].x,
                     original_piece.Position[i].x);
    ck_assert_int_eq(game.current_figure.Position[i].y,
                     original_piece.Position[i].y + 1);
  }
}
END_TEST

START_TEST(test_lock_piece) {
  init_game(&game);
  FigureInfo piece = game.current_figure;
  lock_figure(&game);
  for (int i = 0; i < 4; ++i) {
    int x = piece.Position[i].x;
    int y = piece.Position[i].y;
    ck_assert_int_eq(game.field.field[y][x], 1);
  }
}
END_TEST

START_TEST(test_clear_lines) {
  init_game(&game);
  for (int j = 0; j < WIDTH; ++j) {
    game.field.field[HEIGHT - 1][j] = 1;
  }
  clear_lines(&game);
  for (int j = 0; j < WIDTH; ++j) {
    ck_assert_int_eq(game.field.field[HEIGHT - 1][j], 0);
  }
  ck_assert_int_eq(game.score, 100);
}
END_TEST

START_TEST(test_spawn_new_piece) {
  init_game(&game);
  FigureInfo cur_piece = game.next_figure;
  spawn_new_figure(&game);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(game.current_figure.Position[i].x,
                     cur_piece.Position[i].x);
    ck_assert_int_eq(game.current_figure.Position[i].y,
                     cur_piece.Position[i].y);
  }
  ck_assert_int_ne(cur_piece.type_f, game.next_figure.type_f);
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_initialize_game);
  tcase_add_test(tc_core, test_generate_random_tetromino);
  tcase_add_test(tc_core, test_rotate_piece);
  tcase_add_test(tc_core, test_move_piece_left);
  tcase_add_test(tc_core, test_move_piece_right);
  tcase_add_test(tc_core, test_move_piece_down);
  tcase_add_test(tc_core, test_lock_piece);
  tcase_add_test(tc_core, test_clear_lines);
  tcase_add_test(tc_core, test_spawn_new_piece);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = tetris_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}