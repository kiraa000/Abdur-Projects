import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class SudokuGenerator {
    public static void main(String[] args) {
        int[][] board = new int[9][9];
        solve(board, 0, 0);
        printBoard(board);
    }

    public static boolean solve(int[][] board, int row, int col) {
        if (row == 9) {          //board solved all 9 rows
            return true;
        }

        if (col == 9) {            //move to the next column 
            return solve(board, row + 1, 0);
        }

        if (board[row][col] != 0) {       //if the current cell is already filled, move to the next cell in the same row.
            return solve(board, row, col + 1);
        }

        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Collections.shuffle(numbers); //shuffles numbers to induce randomness

        for (int num : numbers) {
            if (valid(board, row, col, num)) { //checks for validity of the number 
                board[row][col] = num;

                if (solve(board, row, col + 1)) {  //tries to find the next number
                    return true;
                }

                board[row][col] = 0;   //if it does not work, set it to 0 and try again
            }
        }

        return false;   //if all fails try the entire process again
    }

    public static boolean valid(int[][] board, int row, int col, int num) {
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num) {   //checks if the number already appears on the column
                return false;
            }

            if (board[row][i] == num) {   //does the same for rows
                return false;
            }

            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) {  //makes sure each number only appears once in a 3x3 square
                return false;
            }
        }

        return true;
    }

    public static void printBoard(int[][] board) {  //prints the board
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }
}