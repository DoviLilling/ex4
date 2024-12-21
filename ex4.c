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
        for (int x = pyramidArraySize - 1; x >= y; x--) {
            printf("%.2f", getPyramidWeight(pyramid, pyramidArraySize, x, y));
            if (x>y)
                printf(" ");
        }
        printf("\n");
    }
}

void task2HumanPyramid()
{
    float pyramid[pyramidSize][pyramidSize];
    printf("Please enter the weights of the cheerleaders:\n");
    if (setPyramid(pyramid, pyramidSize) == fail)
        return;
    printf("The total weight on each cheerleader is:\n");
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
    // clearBuffer();
    printf("Please enter a term for validation:\n");
    if (validateParenthesis('\n') == success)
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
}

/************************************************************************************************/

#define maxBoardSize 20
#define blankSpot '*'
#define queen 'X'


void initBoard(char boardAreas[][maxBoardSize], int boardSize) {
    for (int row = 0; row < boardSize; row++)
        for (int column = 0; column < boardSize; column++)
            boardAreas[row][column] = blankSpot;
}

void getAreas(char boardAreas[][maxBoardSize], int boardSize) {
    clearBuffer();
    printf("Please enter a %d*%d puzzle board:\n", boardSize, boardSize);
    for (int row = 0; row < boardSize; row++)
        for (int column = 0; column < boardSize; column++)
            scanf(" %c", &boardAreas[row][column]);
}

void printBoard(char board[][maxBoardSize], int boardSize) {
    for (int row = 0; row < boardSize; row++) {
        for (int column = 0; column < boardSize; column++) {
            printf("%c", board[row][column]);
            if (column < boardSize - 1)
                printf(" ");
        }
        printf("\n");
    }
}

int checkQueenPosition(char board[][maxBoardSize], char areas[][maxBoardSize], int boardSize, int row, int column) {
    int i, j;

    // check row
    for (i = 0; i < boardSize; i++)
        if (i != row && board[i][column] == queen)
            return fail;

    // check column
    for (i = 0; i < boardSize; i++)
        if (i != column && board[row][i] == queen)
            return fail;

    // check adjacent
    for (i = row - 1; i <= row + 1; i++)
        for (j = column - 1; j <= column + 1; j++)
            if ((i != row || j != column) && board[i][j] == queen)
                return fail;

    // check area
    for (i = 0; i < boardSize; i++)
        for (j = 0; j < boardSize; j++)
            if (areas[i][j] == areas[row][column] && board[i][j] == queen)
                return fail;

    return success;
}

int placeQueens(char board[][maxBoardSize], char areas[][maxBoardSize], int boardSize, int row, int column) {
    if (row == boardSize)
        return success;

    if (column == boardSize)
        return fail;

    if (checkQueenPosition(board, areas, boardSize, row, column) == success) {
        board[row][column] = queen;
        if (placeQueens(board, areas, boardSize, row + 1, 0)) {
            return success;
        }
        board[row][column] = blankSpot;
    }
    return placeQueens(board, areas, boardSize, row, column + 1);
}

void task4QueensBattle()
{
    char board[maxBoardSize][maxBoardSize] = {0}, areas[maxBoardSize][maxBoardSize] = {0};
    int boardSize = 0;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &boardSize);
    initBoard(board, boardSize);
    getAreas(areas, boardSize);
    if (placeQueens(board, areas, boardSize, 0, 0) == fail)
        printf("This puzzle cannot be solved.\n");
    else {
        printf("Solution:\n");
        printBoard(board, boardSize);
    }
}

/************************************************************************************************/

#define blockedSpace '#'
#define freeSpace ' '
#define maxGridSize 30
#define maxSlots 100
#define slotLocationSize 3
#define maxDictionary 100
#define maxWord (15 + 1)
#define slotsIndexForYPosition 0
#define slotsIndexForXPosition 1
#define slotsIndexForLength 2
#define dictWordNotUsed 0
#define dictWordUsed 1


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
                               locations[row][slotsIndexForLength], orientations[row], gridSize) == fail) {
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

void getDictionary(char dictionary[][maxWord], int dictionarySize, int maxWordLength) {
    printf("Please enter the words for the dictionary:\n");
    for (int row = 0; row < dictionarySize; row++)
        scanf("%s", dictionary[row]);
}

void initGrid(char grid[][maxGridSize], int gridSize, int slots[][slotLocationSize], char slotsOrientations[], int slotsNum) {
    for (int row = 0; row < gridSize; row++)
        for (int column = 0; column < gridSize; column++)
            grid[row][column] = blockedSpace;
    for (int slot = 0; slot < slotsNum; slot++){
        for (int i = 0; i < slots[slot][slotsIndexForLength]; i++) {
            if (slotsOrientations[slot] == 'H')
                grid[slots[slot][slotsIndexForXPosition] + i][slots[slot][slotsIndexForYPosition]] = freeSpace;
            else // (slotsOrientations[slot] == 'V')
                grid[slots[slot][slotsIndexForXPosition]][slots[slot][slotsIndexForYPosition] + i] = freeSpace;
        }
    }
}

void printGrid(char grid[][maxGridSize], int gridSize) {
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++)
            printf("| %c ", grid[column][row]);
        printf("|\n");
    }
}

int checkLetter(char wordToCheck[], int letterIndex, char grid[][maxGridSize], int slots[][slotLocationSize], char slotsOrientations[], int slot) {
    if (wordToCheck[letterIndex] == '\0')
        return success;

    int gridLocationX = slots[slot][slotsIndexForXPosition], gridLocationY = slots[slot][slotsIndexForYPosition];
    if (slotsOrientations[slot] == 'H')
        gridLocationX += letterIndex;
    else gridLocationY += letterIndex;

char tmp = grid[gridLocationX][gridLocationY];
    if (grid[gridLocationX][gridLocationY] == blockedSpace)
        return fail;

    if (grid[gridLocationX][gridLocationY] != freeSpace && grid[gridLocationX][gridLocationY] != wordToCheck[letterIndex])
        return fail;

    if (checkLetter(wordToCheck, letterIndex + 1, grid, slots, slotsOrientations, slot) == success) {
        grid[gridLocationX][gridLocationY] = wordToCheck[letterIndex];
        return success;
    }
    return fail;
}

int checkWord(char wordToCheck[], char grid[][maxGridSize], int slots[][slotLocationSize], char slotsOrientations[], int slot) {
    if (strlen(wordToCheck) != slots[slot][slotsIndexForLength])
        return fail;
    return checkLetter(wordToCheck, 0, grid, slots, slotsOrientations, slot);
}

void writeWordToGrid(char wordToWrite[], char grid[][maxGridSize], int slots[][slotLocationSize], char slotsOrientations[], int slot, int letterIndex) {
    int gridLocationX = slots[slot][slotsIndexForXPosition], gridLocationY = slots[slot][slotsIndexForYPosition];
    if (wordToWrite[letterIndex] == '\0')
        return;
    if (slotsOrientations[slot] == 'H')
        gridLocationX += letterIndex;
    else gridLocationY += letterIndex;
    grid[gridLocationX][gridLocationY] = wordToWrite[letterIndex];
    writeWordToGrid(wordToWrite, grid, slots, slotsOrientations, slot, letterIndex + 1);
}

void clearSlotInGrid(char grid[][maxGridSize], int slots[][slotLocationSize], char slotsOrientations[], int slot, int letterIndex) {
    int gridLocationX = slots[slot][slotsIndexForXPosition], gridLocationY = slots[slot][slotsIndexForYPosition];
    if (letterIndex < 0)
        return;
    if (slotsOrientations[slot] == 'H')
        gridLocationX += letterIndex;
    else gridLocationY += letterIndex;
    grid[gridLocationX][gridLocationY] = ' ';
    clearSlotInGrid(grid, slots, slotsOrientations, slot, letterIndex - 1);
}

int fillSlotInCrossword(char grid[][maxGridSize], int slots[][slotLocationSize], char slotsOrientations[], int slotsNum, char dictionary[][maxWord], int usedDictionaryWords[], int dictionarySize, int slot, int dictIdx) {
    if (slot == slotsNum)
        return success;

    if (dictIdx == dictionarySize)
        return fail;

    if (usedDictionaryWords[dictIdx] == dictWordNotUsed && checkWord(dictionary[dictIdx], grid, slots, slotsOrientations, slot) == success) {
        writeWordToGrid(dictionary[dictIdx], grid, slots, slotsOrientations, slot, 0);
        usedDictionaryWords[dictIdx] = dictWordUsed;
        if (fillSlotInCrossword(grid, slots, slotsOrientations, slotsNum, dictionary, usedDictionaryWords, dictionarySize, slot + 1, 0))
            return success;
        usedDictionaryWords[dictIdx] = dictWordNotUsed;
        clearSlotInGrid(grid, slots, slotsOrientations, slot, strlen(dictionary[dictIdx]) - 1);
    }
    return fillSlotInCrossword(grid, slots, slotsOrientations, slotsNum, dictionary, usedDictionaryWords, dictionarySize, slot, dictIdx + 1);
}

void task5CrosswordGenerator()
{
    int gridSize = 0, slotsNum = 0, slots[maxSlots][slotLocationSize], dictionarySize, usedDictionaryWords[maxDictionary] = {0};
    char slotsOrientations[maxSlots], dictionary[maxDictionary][maxWord], grid[maxGridSize][maxGridSize];
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &gridSize);
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &slotsNum);
    initSlotsLocationsArray(slots, slotsNum);
    initSlotsOrientation(slotsOrientations, slotsNum);
    getSlotsData(slots, slotsOrientations, slotsNum, gridSize);
    dictionarySize = getDictionarySize(slotsNum);
    getDictionary(dictionary, dictionarySize, maxWord);
    initGrid(grid, gridSize, slots, slotsOrientations, slotsNum);
    if (fillSlotInCrossword(grid, slots, slotsOrientations, slotsNum, dictionary, usedDictionaryWords, dictionarySize, 0, 0) == success)
        printGrid(grid, gridSize);
    else
        printf("This crossword cannot be solved.\n");
}
