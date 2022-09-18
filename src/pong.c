#include <math.h>
#include <stdio.h>

#define width_of_field 80
#define height_of_field 25
#define score_to_win 21
#define high_ground '-'
#define left_middle_right '|'

int score(int *score_one, int *score_two);
void make_field(int ball_x, int ball_y, int first_y, int second_y);
void make_score_table(int *score_one, int *score_two);
void coord_parser(int *first_y, int *second_y, int *ball_x, int *ball_y,
                  int *vector_x, int *vector_y, int *score_one, int *score_two);

int main() {
    int score_one = 0;
    int score_two = 0;
    int first_y = 15;
    int second_y = 15;
    int ball_x = 39;
    int ball_y = 12;
    int vector_x = 1;
    int vector_y = 1;
    int max_score = score(&score_one, &score_two);
    while (max_score < 21) {
        printf("\e[1;1H\e[2J");
        make_score_table(&score_one, &score_two);
        make_field(ball_x, ball_y, first_y, second_y);
        coord_parser(&first_y, &second_y, &ball_x, &ball_y, &vector_x,
                     &vector_y, &score_one, &score_two);
        max_score = score(&score_one, &score_two);
    }
}

void make_field(int ball_x, int ball_y, int first_y, int second_y) {
    for (int i = 0; i < height_of_field; i++) {
        for (int j = 0; j < width_of_field; j++) {
            if (i == 0 || i == height_of_field - 1) {
                printf("%c", high_ground);
            } else if (j == ball_x && i == ball_y) {
                printf("%c", 'O');
            } else if (j == 0 || j == width_of_field - 1 ||
                       j == width_of_field / 2 - 1) {
                printf("%c", left_middle_right);
            } else if (j == 1 &&
                       (i == first_y || i == first_y + 1 || i == first_y + 2)) {
                printf("%c", left_middle_right);
            } else if (j == width_of_field - 2 &&
                       (i == second_y || i == second_y + 1 ||
                        i == second_y + 2)) {
                printf("%c", left_middle_right);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void make_score_table(int *score_one, int *score_two) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < width_of_field; j++) {
            if (i == 0 || i == 4) {
                printf("%c", '*');
            } else if (i == 1 && j == 36) {
                printf("SCORE:");
                j += 6;
            } else if (i == 2 && j == 34) {
                printf("P1: %d  P2: %d", *score_one, *score_two);
                j += 10;
            } else if (i == 3 && j == 15) {
                printf("Use keys A-Z and K-M to move rackets and ^C to exit");
                j += 47;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int score(int *score_one, int *score_two) {
    if (*score_one < 21 && *score_two < 21) {
        return *score_one ? *score_one > *score_two : *score_two;
    } else if (*score_one == 21) {
        printf("Congratulation First Player");
        return 21;
    } else {
        printf("Congratulation Second Player");
        return 21;
    }
}

void coord_parser(int *first_y, int *second_y, int *ball_x, int *ball_y,
                  int *vector_x, int *vector_y, int *score_one,
                  int *score_two) {
    char comand_control;
    if (scanf("%c", &comand_control) == 1) {
        if (comand_control == 'a' || comand_control == 'A') {
            if (*first_y - 1 > 0) {
                *first_y -= 1;
            }
        } else if (comand_control == 'Z' || comand_control == 'z') {
            if (*first_y + 1 < height_of_field - 3) {
                *first_y += 1;
            }
        } else if (comand_control == 'k' || comand_control == 'K') {
            if (*second_y - 1 > 0) {
                *second_y -= 1;
            }
        } else if (comand_control == 'M' || comand_control == 'm') {
            if (*second_y + 1 < height_of_field - 3) {
                *second_y += 1;
            }
        }
    }
    if (((*ball_y + *vector_y == *first_y ||
          *ball_y + *vector_y == *first_y + 1 ||
          *ball_y + *vector_y == *first_y + 2) &&
         *ball_x == 2) ||
        (*ball_x == width_of_field - 3 &&
         (*ball_y + *vector_y == *second_y ||
          *ball_y + *vector_y == *second_y + 1 ||
          *ball_y + *vector_y == *second_y + 2))) {
        *vector_x *= -1;
    } else if (*ball_x + *vector_x == 0) {
        *score_two += 1;
        *ball_x = 39;
        *ball_y = 12;
    } else if (*ball_x + *vector_x == width_of_field - 1) {
        *score_one += 1;
        *ball_x = 39;
        *ball_y = 12;
    }
    if (*ball_y + *vector_y == 0 ||
        *ball_y + *vector_y == height_of_field - 1) {
        *vector_y *= -1;
    }
    *ball_x += *vector_x;
    *ball_y += *vector_y;
}
