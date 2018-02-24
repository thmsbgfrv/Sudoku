#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

/*
Made By Tahnasib Gafarov
https://github.com/thmsbgfrv
*/

#define sudoku_x 9
#define sudoku_y 9
#define little_box_x 3
#define little_box_y 3

int level = 1; // (1) easy (each small box 4-6 seen number)  (2) hard (each small box 1-3 seen number) :D
int easyLowerNumber = 4;
int easyHigherNumber = 6;
int hardLowerNumber = 2;
int hardHigherNumber = 4;

int startCodeToGenerate(int sudoku[sudoku_x][sudoku_y], int i, int j);

void findMissingsForGenerate(int sudoku[sudoku_x][sudoku_y], int pInt[sudoku_x], int i, int j);

void print(int sudoku[sudoku_x][sudoku_y]);

void startSudokuForGenerate(int sudoku[sudoku_x][sudoku_y], int i, int i1);

void setNull(int sudoku[sudoku_x][sudoku_y]);


void setLevel(int sudoku[sudoku_x][sudoku_y]);


int startCode(int sudoku[sudoku_x][sudoku_y], int i, int j);

void findMissings(int sudoku[sudoku_x][sudoku_y], int pInt[sudoku_x], int i, int j);

void startSudoku(int sudoku[sudoku_x][sudoku_y], int i, int i1);


int main() {
    time_t t;
    srand((unsigned) time(&t));
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

    startSudokuForGenerate(sudoku, 0, 0);
    startSudoku(sudoku, 0, 0);

    return 0;
}

void setNull(int sudoku[sudoku_x][sudoku_y]) {
    for (int i = 0; i < sudoku_x; ++i) {
        for (int j = 0; j < sudoku_y; ++j) {
            sudoku[i][j] = 0;
        }
    }
}

void startSudokuForGenerate(int sudoku[sudoku_x][sudoku_y], int i, int i1) {
    setNull(sudoku);
    int returnValue = startCodeToGenerate(sudoku, 0, 0);
    if (returnValue == -2) {
        printf("\n Generating Sudoku's answer \n");
        print(sudoku);
    } else {
        printf("Cannot Generate Sudoku !!");
    }
    setLevel(sudoku);
    printf("\n Generating Sudoku\n");
    print(sudoku);
}

void setLevel(int sudoku[sudoku_x][sudoku_y]) {
    int numberOfSeenNumber = 0;
    if (level == 1) {
        for (int j = 0; j < sudoku_x; ++j) {
            numberOfSeenNumber = (rand() % (easyHigherNumber - easyLowerNumber + 1)) + easyLowerNumber;
            for (int i = 0; i < sudoku_x - numberOfSeenNumber; ++i) {
                int k = 0;
                while (sudoku[j][k = rand() % sudoku_x] < 1);
                sudoku[j][k] = 0;
            }
        }
    } else if (level == 2) {
        for (int j = 0; j < sudoku_x; ++j) {
            numberOfSeenNumber = (rand() % (hardHigherNumber - hardLowerNumber + 1)) + hardLowerNumber;
            for (int i = 0; i < sudoku_x - numberOfSeenNumber; ++i) {
                int k = 0;
                while (sudoku[j][k = rand() % sudoku_x] < 1);
                sudoku[j][k] = 0;
            }
        }
    }


}

void print(int sudoku[sudoku_x][sudoku_y]) {

    for (int k = 0; k < sudoku_x * 3 + little_box_x + 1; ++k) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < sudoku_x; ++i) {
        if (i % little_box_y == 0 && i > 0) {
            for (int k = 0; k < sudoku_x * 3 + little_box_x + 1; ++k) {
                printf("-");
            }
            printf("\n");
        }
        printf("|");
        for (int j = 0; j < sudoku_y; ++j) {
            if (j % (little_box_x) == 0 && j > 0) {
                if (sudoku[i][j] == 0) {
                    printf("|   ");
                } else {
                    printf("| %d ", sudoku[i][j]);
                }
            } else {
                if (sudoku[i][j] == 0) {
                    printf("   ");
                } else {
                    printf(" %d ", sudoku[i][j]);
                }
            }

        }
        printf("|\n");
    }
    for (int k = 0; k < sudoku_x * 3 + little_box_x + 1; ++k) {
        printf("-");
    }
}

int startCodeToGenerate(int sudoku[sudoku_x][sudoku_y], int i, int j) {
    if (sudoku[i][j] < 1) {
        int probs[sudoku_x] = {0};
        findMissingsForGenerate(sudoku, probs, i, j);
        for (int k = 0; k < sudoku_x; ++k) {
            if (probs[k] > 0) {
                sudoku[i][j] = probs[k];
                if (j == sudoku_y - 1) {
                    if (i == sudoku_x - 1) {
                        return -2;//code complated
                    } else {
                        int result = startCodeToGenerate(sudoku, i + 1, 0);
                        if (result == -2) {
                            return -2;
                        } else {
                            sudoku[i][j] = 0;
                            continue;
                        }
                    }
                } else {
                    int result = startCodeToGenerate(sudoku, i, j + 1);
                    if (result == -2) {
                        return -2;
                    } else {
                        sudoku[i][j] = 0;
                        continue;
                    }
                }

            }
        }
    }
    return 0;

}

void findMissingsForGenerate(int sudoku[sudoku_x][sudoku_y], int pInt[sudoku_x], int i, int j) {
    int tempPInt[sudoku_x] = {0};
    for (int k = 0; k < sudoku_x; ++k) {
        if (sudoku[i][k] > 0) {
            tempPInt[sudoku[i][k] - 1] = sudoku[i][k];
        }
    }
    for (int k = 0; k < sudoku_y; ++k) {
        if (sudoku[k][j] > 0) {
            tempPInt[sudoku[k][j] - 1] = sudoku[k][j];
        }
    }
    int temp_x = i - (i % little_box_x);
    int temp_y = j - (j % little_box_y);
    for (int l = temp_x; l < temp_x + little_box_x; ++l) {
        for (int k = temp_y; k < temp_y + little_box_y; ++k) {
            if (sudoku[l][k] > 0) {
                tempPInt[sudoku[l][k] - 1] = sudoku[l][k];
            }
        }
    }

    int nn = 0;
    for (int m = 0; m < sudoku_x; ++m) {
        if (tempPInt[m] < 1) {
            pInt[nn++] = m + 1;
        }
    }
    for (int n = 0; n < nn; ++n) {
        int temp = 0;

        while ((temp = rand() % sudoku_x) == n);

        int rr = pInt[temp];
        pInt[temp] = pInt[n];
        pInt[n] = rr;
    }

}


void startSudoku(int sudoku[sudoku_x][sudoku_y], int i, int i1) {
    int returnValue = startCode(sudoku, 0, 0);
    if (returnValue == -2) {

        printf("\n Generating Sudoku's Solution \n");
        print(sudoku);
    } else {
        printf("Cannot Solve Sudoku !!");
    }
    printf("\n");
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
