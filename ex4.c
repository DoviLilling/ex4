/******************
Name:
ID:
Assignment:
*******************/
#include <math.h>
#include <stdio.h>
#include <string.h>

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();

#define pyramidSize 5
#define maxBoardSize 20

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                task1RobotPaths();
                break;
            case 2:
                task2HumanPyramid();
                break;
            case 3:
                task3ParenthesisValidator();
                break;
            case 4:
                task4QueensBattle();
                break;
            case 5:
                task5CrosswordGenerator();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

/************************************************************************************************/

int getPaths(int column, int row) {
    if (row == 0 || column == 0)
        return 1;
    return getPaths(column, row - 1) + getPaths(column - 1, row);
}

void task1RobotPaths()
{
    int column, row, paths = 0;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d:", &column, &row);
    if (column >= 0 && row >= 0)
        paths = getPaths(column, row);
    printf("The total number of paths the robot can take to reach home is: %d\n", paths);
}

/************************************************************************************************/

void setPyramid(float pyramid[][pyramidSize], int pyramidArraySize) {
    for (int y = pyramidArraySize - 1; y >= 0 ; y--)
        for (int x = pyramidArraySize - 1; x >= y; x--)
            scanf("%f", &pyramid[x][y]);
}

float getPyramidWeight(float pyramid[][pyramidSize], int pyramidArraySize, int x, int y) {
    if (x == pyramidArraySize - 1 && y == pyramidArraySize - 1)
        return pyramid[x][y];
    if (x == pyramidArraySize - 1)
        return getPyramidWeight(pyramid, pyramidArraySize, x, y + 1) / 2 + pyramid[x][y];
    if (x == y)
        return getPyramidWeight(pyramid, pyramidArraySize, x + 1, y + 1) / 2 + pyramid[x][y];
    return getPyramidWeight(pyramid, pyramidArraySize, x + 1, y + 1) / 2
           + getPyramidWeight(pyramid, pyramidArraySize, x, y + 1) / 2
           + pyramid[x][y];
}

void printPyramid(float pyramid[][pyramidSize], int pyramidArraySize) {
    for (int y = pyramidArraySize - 1; y >= 0 ; y--)
    {
        for (int x = pyramidArraySize - 1; x >= y; x--)
            printf("%.2f ", getPyramidWeight(pyramid, pyramidArraySize, x, y));
        printf("\n");
    }
}

void task2HumanPyramid()
{
    float pyramid[pyramidSize][pyramidSize];
    printf("Please enter the weights of the cheerleaders:\n");
    setPyramid(pyramid, pyramidSize);
    printPyramid(pyramid, pyramidSize);
}

/************************************************************************************************/

char getMatchingCloseParenthesis(char open) {
    if (open == '(')
        return ')';
    if (open == '{')
        return '}';
    if (open == '[')
        return ']';
    if (open == '<')
        return '>';
    return ' ';
}

void clearBuffer(void) {
    char dummy;
    while (scanf("%c", &dummy) == 1 && dummy != '\n');
}

int validateParenthesis(char finishChar) {
    char currentChar;
    if (scanf("%c", &currentChar) <= 0)
        return -1;
    if (currentChar == finishChar)
        return 0;
    if (currentChar == '(' || currentChar == '{' || currentChar == '[' || currentChar == '<') {
        if (validateParenthesis(getMatchingCloseParenthesis(currentChar)) == 0)
            return validateParenthesis(finishChar);
        return -1;
    }
    if (currentChar == ')' || currentChar == '}' || currentChar == ']' || currentChar == '>') {
        clearBuffer();
        return -1;
    }
    if (currentChar == '\n') {
        return -1;
    }
    return validateParenthesis(finishChar);
}

void task3ParenthesisValidator()
{
    clearBuffer();
    printf("Please enter a term for validation:\n");
    if (validateParenthesis('\n') == 0)
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
}

/************************************************************************************************/

void initBoard(char boardAreas[][maxBoardSize], int boardSize, char initChar) {
    for (int row = 0; row < boardSize; row++)
        for (int column = 0; column < boardSize; column++)
            boardAreas[row][column] = initChar;
}

void getAreas(char boardAreas[][maxBoardSize], int boardSize) {
    clearBuffer();
    printf("Please enter the %d*%d puzzle board\n", boardSize, boardSize);
    for (int row = 0; row < boardSize; row++)
        for (int column = 0; column < boardSize; column++)
            scanf(" %c", &boardAreas[row][column]);
}

void printBoard(char board[][maxBoardSize], int boardSize) {
    for (int row = 0; row < boardSize; row++) {
        for (int column = 0; column < boardSize; column++)
            printf("%c ", board[row][column]);
        printf("\n");
    }
    printf("\n");
}

int checkQueenPosition(char board[][maxBoardSize], char areas[][maxBoardSize], int boardSize, int row, int column) {
    int i, j;

    // check row
    for (i = 0; i < boardSize; i++)
        if (i != row && board[i][column] == 'X')
            return 0;

    // check column
    for (i = 0; i < boardSize; i++)
        if (i != column && board[row][i] == 'X')
            return 0;

    // check adjacent
    for (i = row - 1; i <= row + 1; i++)
        for (j = column - 1; j <= column + 1; j++)
            if ((i != row || j != column) && board[i][j] == 'X')
                return 0;

    // check area
    for (i = 0; i < boardSize; i++)
        for (j = 0; j < boardSize; j++)
            if (areas[i][j] == areas[row][column] && board[i][j] == 'X')
                return 0;

    return 1;
}

int placeQueens(char board[][maxBoardSize], char areas[][maxBoardSize], int boardSize, int row, int column) {
    if (row == boardSize)
        return 1;

    if (column == boardSize)
        return 0;

    if (checkQueenPosition(board, areas, boardSize, row, column) == 1) {
        board[row][column] = 'X';
        if (placeQueens(board, areas, boardSize, row + 1, 0)) {
            return 1;
        }
        board[row][column] = '*';
    }
    return placeQueens(board, areas, boardSize, row, column + 1);
}

void task4QueensBattle()
{
    char board[maxBoardSize][maxBoardSize] = {0}, areas[maxBoardSize][maxBoardSize] = {0};
    int boardSize = 0;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &boardSize);
    initBoard(board, boardSize, '*');
    getAreas(areas, boardSize);
    if (placeQueens(board, areas, boardSize, 0, 0) == 0)
        printf("This puzzle cannot be solved.\n");
    else {
        printf("Solution:\n");
        printBoard(board, boardSize);
    }
}

/************************************************************************************************/

void task5CrosswordGenerator()
{
    // Todo
}
