#include <bits/stdc++.h>
using namespace std;

/*
============================================================
LeetCode #36 - Valid Sudoku
Difficulty: Medium
Topics: Arrays, Hashing
============================================================

PROBLEM STATEMENT:
Determine if a 9 x 9 Sudoku board is valid.

A board is valid if:
1. Each row contains no repeated digits 1-9.
2. Each column contains no repeated digits 1-9.
3. Each 3 x 3 sub-box contains no repeated digits 1-9.

IMPORTANT:
- Empty cells are represented by '.'.
- Only filled cells need to be checked.
- The board does not need to be solvable.
- A digit may appear once in each row, column, and box.

EXAMPLE 1:
Input:
board = {
  {'5','3','.','.','7','.','.','.','.'},
  {'6','.','.','1','9','5','.','.','.'},
  {'.','9','8','.','.','.','.','6','.'},
  {'8','.','.','.','6','.','.','.','3'},
  {'4','.','.','8','.','3','.','.','1'},
  {'7','.','.','.','2','.','.','.','6'},
  {'.','6','.','.','.','.','2','8','.'},
  {'.','.','.','4','1','9','.','.','5'},
  {'.','.','.','.','8','.','.','7','9'}
}
Output: true

EXAMPLE 2:
If two '5' digits appear in the same row, column, or
3 x 3 box, output false.

CONSTRAINTS:
- board.size() == 9
- board[i].size() == 9
- board[i][j] is a digit '1'-'9' or '.'

YOUR TASK:
Implement:
bool isValidSudoku(vector<vector<char>>& board);

HINTS:
- Each filled cell must be checked against its row, column,
  and 3 x 3 box.
- Hash sets can help detect duplicates.
- Ignore '.' cells.

TEST CASES:
1. Standard valid board -> true
2. Duplicate in a row -> false
3. Duplicate in a column -> false
4. Duplicate in a 3 x 3 box -> false
5. Empty board -> true
6. One filled cell -> true

============================================================
*/

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        // Intialize vector of sets
        //set stores unit chars
        //vector contains 9 sets.
        //set contains unique elements.
        vector<set<char>> rows(9);
        vector<set<char>> cols(9);
        vector<set<char>> boxes(9);

        // board.size() returns number of rows
        for (int i = 0; i < board.size(); i++)
        {
            //board[i].size() returns the number of columns in that row.
            for (int j = 0; j < board[i].size(); j++)
            {
                //ignore '.'
                if (board[i][j] == '.')
                {
                    continue;
                }

                //if row contains a duplicate num return false; else insert that in the set and move on.
                if (rows[i].contains(board[i][j]))
                {
                    return false;
                }
                else
                {
                    rows[i].insert(board[i][j]);
                }

                if (cols[j].contains(board[i][j]))
                {
                    return false;
                }
                else
                {
                    cols[j].insert(board[i][j]);
                }

                //boxIndex calculation
                int boxIndex = (i / 3) * 3 + (j / 3);

                if (boxes[boxIndex].contains(board[i][j]))
                {
                    return false;
                }
                else
                {
                    boxes[boxIndex].insert(board[i][j]);
                }
            }
        }

        return true;
    }
};

void runTest(vector<vector<char>> board, bool expected, int testNumber)
{
    Solution solution;
    bool actual = solution.isValidSudoku(board);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: " << boolalpha << expected
             << ", Actual: " << actual << '\n';
    }
}

int main()
{
    vector<vector<char>> validBoard = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    vector<vector<char>> duplicateRow = validBoard;
    duplicateRow[0][2] = '5';

    vector<vector<char>> duplicateColumn = validBoard;
    duplicateColumn[2][0] = '5';

    vector<vector<char>> duplicateBox = validBoard;
    duplicateBox[1][1] = '8';

    vector<vector<char>> emptyBoard(9, vector<char>(9, '.'));

    vector<vector<char>> oneCell(9, vector<char>(9, '.'));
    oneCell[0][0] = '7';

    runTest(validBoard, true, 1);
    runTest(duplicateRow, false, 2);
    runTest(duplicateColumn, false, 3);
    runTest(duplicateBox, false, 4);
    runTest(emptyBoard, true, 5);
    runTest(oneCell, true, 6);

    return 0;
}
