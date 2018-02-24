#include <stdio.h>

#define sudoku_x 9
#define sudoku_y 9
#define little_box_x 3
#define little_box_y 3

int startCode(int sudoku[sudoku_x][sudoku_y], int i, int j);

void findMissings(int sudoku[sudoku_x][sudoku_y], int pInt[sudoku_x], int i, int j);

void print(int sudoku[sudoku_x][sudoku_y]);

void startSudoku(int sudoku[sudoku_x][sudoku_y], int i, int i1);

int main() {

    int sudoku1[sudoku_x][sudoku_y] =
            {
                    {5, 6, 0, 4, 0, 0, 3, 2, 0},
                    {4, 0, 0, 8, 0, 6, 0, 0, 0},
                    {0, 7, 0, 0, 0, 0, 0, 1, 6},
                    {3, 0, 0, 0, 9, 0, 0, 0, 0},
                    {7, 0, 2, 0, 5, 0, 1, 0, 4},
                    {0, 0, 0, 0, 3, 0, 0, 0, 9},
                    {2, 4, 0, 0, 0, 0, 0, 6, 0},
                    {0, 0, 0, 9, 0, 1, 0, 0, 7},
                    {0, 8, 7, 0, 0, 2, 0, 4, 3},
            };
    int sudoku[sudoku_x][sudoku_y] =
            {
                    {0, 2, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 6, 0, 0, 0, 0, 3},
                    {0, 7, 4, 0, 8, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 3, 0, 0, 2},
                    {0, 8, 0, 0, 4, 0, 0, 1, 0},
                    {6, 0, 0, 5, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 7, 8, 0},
                    {5, 0, 0, 0, 0, 9, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 4, 0},
            };
    startSudoku(sudoku, 0, 0);
    startSudoku(sudoku1, 0, 0);
    return 0;
}

void startSudoku(int sudoku[sudoku_x][sudoku_y], int i, int i1) {
    int returnValue = startCode(sudoku, 0, 0);
    if (returnValue == -2)
        print(sudoku);
    else
        printf("Cannot Solve Sudoku !!");
    printf("\n");
}

void print(int sudoku[sudoku_x][sudoku_y]) {

    for (int i = 0; i < sudoku_x; ++i) {
        for (int j = 0; j < sudoku_y; ++j) {
            printf(" %d", sudoku[i][j]);
        }
        printf("\n");
    }
}

int startCode(int sudoku[sudoku_x][sudoku_y], int i, int j) {
    if (sudoku[i][j] < 1) {
        int probs[sudoku_x] = {0};
        findMissings(sudoku, probs, i, j);
        for (int k = 0; k < sudoku_x; ++k) {
            if (probs[k] < 1) {
                sudoku[i][j] = k + 1;
                if (j == sudoku_y - 1) {
                    if (i == sudoku_x - 1) {
                        return -2;//code complated
                    } else {
                        int result = startCode(sudoku, i + 1, 0);
                        if (result == -2) {
                            return -2;
                        } else {
                            sudoku[i][j] = 0;
                            continue;
                        }
                    }
                } else {
                    int result = startCode(sudoku, i, j + 1);
                    if (result == -2) {
                        return -2;
                    } else {
                        sudoku[i][j] = 0;
                        continue;
                    }
                }

            }
        }
    } else {
        if (j == sudoku_y - 1) {
            if (i == sudoku_x - 1) {
                return -2;//code complated
            } else {
                int result = startCode(sudoku, i + 1, 0);
                if (result == -2)
                    return -2;
            }
        } else {
            int result = startCode(sudoku, i, j + 1);
            if (result == -2)
                return -2;
        }
    }
    return 0;

}

void findMissings(int sudoku[sudoku_x][sudoku_y], int pInt[sudoku_x], int i, int j) {
    for (int k = 0; k < sudoku_x; ++k) {
        if (sudoku[i][k] > 0) {
            pInt[sudoku[i][k] - 1] = sudoku[i][k];
        }
    }
    for (int k = 0; k < sudoku_y; ++k) {
        if (sudoku[k][j] > 0) {
            pInt[sudoku[k][j] - 1] = sudoku[k][j];
        }
    }
    int temp_x = i - (i % little_box_x);
    int temp_y = j - (j % little_box_y);
    for (int l = temp_x; l < temp_x + little_box_x; ++l) {
        for (int k = temp_y; k < temp_y + little_box_y; ++k) {
            if (sudoku[l][k] > 0) {
                pInt[sudoku[l][k] - 1] = sudoku[l][k];
            }
        }
    }
}