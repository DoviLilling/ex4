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

#define success 1
#define fail 0

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
        return success;
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

#define pyramidSize 5


int setPyramid(float pyramid[][pyramidSize], int pyramidArraySize) {
    for (int y = pyramidArraySize - 1; y >= 0 ; y--)
        for (int x = pyramidArraySize - 1; x >= y; x--) {
            scanf("%f", &pyramid[x][y]);
            if (pyramid[x][y] < 0) {
                printf("Negative weights are not supported.\n");
                return fail;
            }
        }
    return success;
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
    if (setPyramid(pyramid, pyramidSize) == fail)
        return;
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
    scanf("%*[^\n]c");
    scanf("%*c");
}

int validateParenthesis(char finishChar) {
    char currentChar;
    if (scanf("%c", &currentChar) <= 0)
        return fail;
    if (currentChar == finishChar)
        return success;
    if (currentChar == '(' || currentChar == '{' || currentChar == '[' || currentChar == '<') {
        if (validateParenthesis(getMatchingCloseParenthesis(currentChar)) == success)
            return validateParenthesis(finishChar);
        return fail;
    }
    if (currentChar == ')' || currentChar == '}' || currentChar == ']' || currentChar == '>') {
        clearBuffer();
        return fail;
    }
    if (currentChar == '\n') {
        return fail;
    }
    return validateParenthesis(finishChar);
}

void task3ParenthesisValidator()
{
    clearBuffer();
    printf("Please enter a term for validation:\n");
    if (validateParenthesis('\n') == success)
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
}

/************************************************************************************************/

#define maxBoardSize 20


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
            return fail;

    // check column
    for (i = 0; i < boardSize; i++)
        if (i != column && board[row][i] == 'X')
            return fail;

    // check adjacent
    for (i = row - 1; i <= row + 1; i++)
        for (j = column - 1; j <= column + 1; j++)
            if ((i != row || j != column) && board[i][j] == 'X')
                return fail;

    // check area
    for (i = 0; i < boardSize; i++)
        for (j = 0; j < boardSize; j++)
            if (areas[i][j] == areas[row][column] && board[i][j] == 'X')
                return fail;

    return success;
}

int placeQueens(char board[][maxBoardSize], char areas[][maxBoardSize], int boardSize, int row, int column) {
    if (row == boardSize)
        return success;

    if (column == boardSize)
        return fail;

    if (checkQueenPosition(board, areas, boardSize, row, column) == 1) {
        board[row][column] = 'X';
        if (placeQueens(board, areas, boardSize, row + 1, 0)) {
            return success;
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

#define maxGridSize 30
#define maxSlots 100
#define slotLocationSize 3
#define maxDictionary 100
#define maxWord (15 + 1)
#define slotsIndexForYPosition 0
#define slotsIndexForXPosition 1
#define slotsIndexForLength 2


void initSlotsLocationsArray(int array[][slotLocationSize], int arraySize) {
    for (int row = 0; row < arraySize; row++)
        for (int column = 0; column < slotLocationSize; column++)
            array[row][column] = -1;
}

void initSlotsOrientation(char array[], int arraySize) {
    for (int row = 0; row < arraySize; row++)
        array[row] = 'N';
}

void tempPrintSlotsLocations(int locationsArray[][slotLocationSize], char orientationArray[], int arraySize) {
    printf("X Y L O\n~~~~~~~~\n");
    for (int row = 0; row < arraySize; row++) {
        for (int column = 0; column < slotLocationSize; column++)
            printf("%d ", locationsArray[row][column]);
        printf("%c\n", orientationArray[row]);
    }
}

void tempPrintDict(char dictionary[][maxWord], int dictionarySize) {
    printf("\nDict:\n");
    for (int row = 0; row < dictionarySize; row++)
        printf("%s\n", dictionary[row]);
    printf("\n");
}

int isValidSlotData(int Y, int X, int length, char orientation, int gridSize) {
    if (orientation == 'V' && Y + length > gridSize || orientation == 'H' && X + length > gridSize)
        return fail;
    return success;
}

void getSlotsData(int locations[][slotLocationSize], char orientations[], int arraySize, int gridSize) {
    clearBuffer();
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int row = 0; row < arraySize; row++) {
        // for (int column = 0; column < slotLocationSize; column++)
        //     scanf("%d ", &locationsArray[row][column]);
        scanf("%d ", &locations[row][slotsIndexForYPosition]);
        scanf("%d ", &locations[row][slotsIndexForXPosition]);
        scanf("%d ", &locations[row][slotsIndexForLength]);
        scanf("%[^\n]c", &orientations[row]);
        while (isValidSlotData(locations[row][slotsIndexForYPosition], locations[row][slotsIndexForXPosition],
                               locations[row][slotsIndexForLength], orientations[row], gridSize) == 0) {
            printf("This combination is not valid. ");
            printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
            scanf("%d ", &locations[row][slotsIndexForYPosition]);
            scanf("%d ", &locations[row][slotsIndexForXPosition]);
            scanf("%d ", &locations[row][slotsIndexForLength]);
            scanf("%[^\n]c", &orientations[row]);
        }
    }
}

int getDictionarySize(int minSize) {
    int dictionarySize = 0;
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &dictionarySize);
    while (dictionarySize < minSize) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", minSize);
        scanf("%d", &dictionarySize);
    }
    return dictionarySize;
}

void loadDictionary(char dictionary[][maxWord], int dictionarySize, int maxWordLength) {
    printf("Please enter the words for the dictionary:\n");
    for (int row = 0; row < dictionarySize; row++)
        scanf("%s", dictionary[row]);
}

void initCrossword(char crossword[][maxWord], int slots[][slotLocationSize], int slotsNum) {
    for (int slot = 0; slot < slotsNum; slot++){
        for (int i = 0; i < slots[slot][slotsIndexForLength]; i++)
            crossword[slot][i] = ' ';
        crossword[slot][slots[slot][slotsIndexForLength]] = '\0';
    }
}

void tempPrintCrossword(char crossword[][maxWord], int slotsNum) {
    for (int slot = 0; slot < slotsNum; slot++)
        printf("%s|\n", crossword[slot]);
}

void printGrid(int gridSize, int slots[][slotLocationSize], char slotsOrientations[], char crossword[][maxWord], int slotsNum) {
    char grid[gridSize][gridSize];
    for (int row = 0; row < gridSize; row++)
        for (int column = 0; column < gridSize; column++)
            grid[row][column] = '#';
    for (int slot = 0; slot < slotsNum; slot++) {
        for (int i = 0; i < slots[slot][slotsIndexForLength]; i++) {
            if (slotsOrientations[slot] == 'H')
                grid[slots[slot][slotsIndexForXPosition] + i][slots[slot][slotsIndexForYPosition]] = crossword[slot][i];
            else // (slotsOrientations[slot] == 'V')
                grid[slots[slot][slotsIndexForXPosition]][slots[slot][slotsIndexForYPosition] + i] = crossword[slot][i];
        }
    }
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++)
            printf("| %c ", grid[column][row]);
        printf(" |\n");
    }
}

int embedWordInCrossword(char crossword[][maxWord], int slots[][slotLocationSize], char slotsOrientations[], int slotsNum, char dictionary[][maxWord], int dictionarySize, int slot) {
    if (slot > slotsNum)
        return success;
}

int solveCrossword(char crossword[][maxWord], int slots[][slotLocationSize], char slotsOrientations[], int slotsNum, char dictionary[][maxWord], int dictionarySize) {
    if (embedWordInCrossword(crossword, slots, slotsOrientations, slotsNum, dictionary, dictionarySize, 0) == 1)
        return success;
    return fail;
}

void task5CrosswordGenerator()
{
    int gridSize = 0, slotsNum = 0, slots[maxSlots][slotLocationSize], dictionarySize;
    char slotsOrientations[maxSlots], dictionary[maxDictionary][maxWord], crossword[maxSlots][maxWord];
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &gridSize);
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &slotsNum);
    initSlotsLocationsArray(slots, slotsNum);
    initSlotsOrientation(slotsOrientations, slotsNum);
    tempPrintSlotsLocations(slots, slotsOrientations, slotsNum);
    getSlotsData(slots, slotsOrientations, slotsNum, gridSize);
    tempPrintSlotsLocations(slots, slotsOrientations, slotsNum);
    dictionarySize = getDictionarySize(slotsNum);
    loadDictionary(dictionary, dictionarySize, maxWord);
    tempPrintDict(dictionary, dictionarySize);
    initCrossword(crossword, slots, slotsNum);
    tempPrintCrossword(crossword, slotsNum);
    printGrid(gridSize, slots, slotsOrientations, crossword, slotsNum);
    if (solveCrossword(crossword, slots, slotsOrientations, slotsNum, dictionary, dictionarySize) == 1)
        printGrid(gridSize, slots, slotsOrientations, crossword, slotsNum);
    else
        printf("This crossword cannot be solved.\n");
    // Todo
}
