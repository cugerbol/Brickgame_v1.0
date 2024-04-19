/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "./tests/include.check" instead.
 */

#include <check.h>

#include "../src/brick_game/tetris/tetris.h"
#include "../src/brick_game/tetris/backend.h"
#include "../src/brick_game/tetris/fsm.h"
#include "../src/brick_game/tetris/bonus.h"

START_TEST(moveUp)
{

    TetFigure_t *figure = createRandomFigure();

    int y_start = figure->y = 1;
    int y_end = 2;
    ck_assert_int_eq(y_end, 2);

    moveFigureDown(figure);

    freeFigure(figure);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("move");
    TCase *tc1_1 = tcase_create("move");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, moveUp);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
