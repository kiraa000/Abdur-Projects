import java.util.Scanner;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;

public class CrosswordProject {
    static Scanner sc= new Scanner(System.in);
    static ArrayList<String> words = new ArrayList<>();
    public static void main(String[] args){
        for(int i=0; i<5; i++){
            System.out.println("Enter word "+(i+1));
            String word= sc.nextLine();
            CheckValid(word.toUpperCase());
        }
        words.sort(Comparator.comparing(String::length).reversed()); //arranged the list in order of length
        System.out.println(words);
        CheckCommon(words); //checks if the words given are able to be turned into a crossword
        //System.out.println(words);

    }

    public static void CheckValid(String word){ //checks for validity 
        while(!word.matches("[ABCDEFGHIJKLMNOPQRSTUVWXYZ]+") || word.length()<3){
            System.out.println("Invalid. Re-enter word ");
            word = sc.nextLine().toUpperCase();
        }
        words.add(word);

    }

    public static void CheckCommon(ArrayList<String> words){
        String common="";
        String word1 = words.get(0);
        String word2 = words.get(1);
        String word3 = words.get(2);
        int index12= -1;
        int index13=-1;
        int index21= -1;
        int index31= -1;

        outerloop: //looks for the first instance of a common word 
        for(int i=0; i<word1.length(); i++){
            char a= word1.charAt(i);
            for(int j=0; j<word2.length(); j++){
                char b= word2.charAt(j);
                if (a==b ){
                    common+=a;
                    index12= i;
                    index21= j;
                    System.out.println("Index12: "+ index12+" Index21: "+index21);
                    break outerloop;
                }
            }
        }

        while(common.length()<1){  //if there is no common letter, ask user to reinput
            String temp= word2;
            System.out.println("'"+word2+"' is not able to be turned into a crossword. Enter another word length "+word2.length()+" that shares a common letter with "+word1);
            word2= sc.nextLine().toUpperCase();
            while(!word2.matches("[ABCDEFGHIJKLMNOPQRSTUVWXYZ]+") || word2.length()<3 || temp.length() != word2.length()){
                System.out.println("Invalid. Re-enter word 2");
                word2 = sc.nextLine().toUpperCase();
            }
            words.set(1,word2);
            CheckCommon(words);
            return;
        }

        ArrayList<Character> word1extra = new ArrayList<>();
        for (char c : word1.toCharArray()) {
            word1extra.add(c);
        }


        if (common.length() > 0) { //removes the letter used by the intersection of word 1 and 2
            word1extra.remove((Character) common.charAt(0));
        }
        String word1extraStr= "";       
        for(int i=0; i<word1extra.size(); i++){
            word1extraStr+=word1extra.get(i);

        }
        boolean word13common= false;
        outerloop:   //checks for common letter between word 1 and 3
        for(int i=word1.length()-1; i>=0; i--){
            char a= word1.charAt(i);
            for(int j=0; j<word3.length(); j++){
                char b= word3.charAt(j);
                if (a==b && word1extraStr.contains(String.valueOf(a))){
                    common+=a;
                    index13=i;
                    index31= j;
                    System.out.println("Index 13: "+index13+" Index31: "+index31);
                    word13common=true;
                    break outerloop;
                }
            }
        }

        if(!word13common){ //invalid input handle case
            String temp= word3;
            System.out.println("'"+word3+"' cannot be turned into a crossword. Enter another word length "+word3.length()+
            "\nthat shares a common letter with "+word1+" that is not '"+common+"'");
            word3= sc.nextLine().toUpperCase();
            while(!word3.matches("[ABCDEFGHIJKLMNOPQRSTUVWXYZ]+") || word3.length()<3 || temp.length() != word3.length()){
                System.out.println("Invalid. Re-enter word 3");
                word3 = sc.nextLine().toUpperCase();
            }
            words.set(2,word3);
            CheckCommon(words);
        }


        if(common.length()==2){
            makeCrossword(words, index12, index13, index21, index31, word1extraStr, common);
        }


    }

    public static void makeCrossword(ArrayList<String> words, int index12, int index13, int index21, int index31,String word1extraStr, String common){
        String word1 = words.get(0);
        String word2 = words.get(1);
        String word3 = words.get(2);

        int len= words.get(0).length();  //creates a grid based on the length of word 1
        String[][] grid= new String[3*len][2*len+1];

        for(int i = 0; i < grid.length; i++){ 
            for(int j = 0; j < grid[i].length; j++){
                grid[i][j] = "0";
            }
        }

        for(int i= 0; i<word1.length(); i++){ //word 1
            grid[len][len+i]= String.valueOf(word1.charAt(i));
        }

        for(int i=0; i<word2.length(); i++){  //word 2
            grid[len-index21+i][len+index12]= String.valueOf(word2.charAt(i));
        }
        for(int i=0; i<word3.length(); i++){ //word 3
            grid[len-index31+i][len+index13]= String.valueOf(word3.charAt(i));
        }

        altCrossword(words, index12, index13,index21,index31, word1extraStr, common, grid, len);
        addWordToGrid(words.get(3), 3, grid, sc);
        addWordToGrid(words.get(4), 4, grid, sc);
        ArrayList<String> crossword= getCrossword(grid);
        printCrossword(crossword);


    }

    public static void altCrossword(ArrayList<String> words, int index12, int index13, int index21, int index31, String word1extraStr, String common, String[][] grid, int len){
        String word1 = words.get(0);
        String word3 = words.get(2);
        boolean word13common=false;
        int diff= index13-index12; //removes clutter if word 2 and 3 are right next to each other
        outerloop:
        if(diff==1){
            for(int i=0; i<word1.length(); i++){
            char a= word1.charAt(i);
                for(int j=0; j<word3.length(); j++){
                    char b= word3.charAt(j);
                    if (a==b && word1extraStr.contains(String.valueOf(a))){
                        common+=a;
                        index13=i;
                        index31= j;
                        System.out.println("Index 13: "+index13+" Index31: "+index31);
                        word13common=true;
                        break outerloop;
                    }
                }
            }
        }
        if(word13common){
            for(int i=0; i<word3.length(); i++){
                grid[len-index31+i][len+index13]= String.valueOf(word3.charAt(i));
            }
        }
    }
    public static ArrayList<String> getCrossword(String[][] grid){
        ArrayList<String> crossword = new ArrayList<>();
        int minRow = grid.length, maxRow = 0, minCol = grid[0].length, maxCol = 0;

        // Find the minimum and maximum row and column numbers that contain a letter
        for(int i = 0; i < grid.length; i++){
            for(int j = 0; j < grid[i].length; j++){
                if(!grid[i][j].equals("0")) {
                    minRow = Math.min(minRow, i);
                    maxRow = Math.max(maxRow, i);
                    minCol = Math.min(minCol, j);
                    maxCol = Math.max(maxCol, j);
                }
            }
        }

        // Adds the lines to the crossword, excluding the rows and columns that only contain spaces
        for(int i = minRow; i <= maxRow; i++){
            StringBuilder sb = new StringBuilder();
            for(int j = minCol; j <= maxCol; j++){
                if(!grid[i][j].equals("0")) {
                    sb.append(grid[i][j]);
                } else {
                    sb.append(" "); // append a space 
                }
            }
            String line = sb.toString();
            // Only adds the line to the array if it contains a letter
            if(line.matches(".*[a-zA-Z]+.*")) {
                crossword.add(line);
            }
        }
        return crossword;
    }
    public static void addWordToGrid(String word, int wordIndex, String[][] grid, Scanner sc) {
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            for (int row = 0; row < grid.length; row++) {
                for (int col = 0; col < grid[row].length; col++) {
                    if (grid[row][col].equals(String.valueOf(c))) {
                        if (canAddWordHorizontally(word, i, row, col, grid)) {
                            addWordHorizontally(word, i, row, col, grid);
                            return;
                        } else if (canAddWordVertically(word, i, row, col, grid)) {
                            addWordVertically(word, i, row, col, grid);
                            return;
                        }
                    }
                }
            }
        }

        // If the code reaches this point, the word cannot be added to the grid
        System.out.println("The word '" + word + "' cannot be added to the crossword. Please enter a new word:");
        String newWord = sc.nextLine().toUpperCase();
        while (!newWord.matches("[ABCDEFGHIJKLMNOPQRSTUVWXYZ]+") || newWord.length() != word.length()) {
            System.out.println("Invalid. The word should only contain uppercase alphabets and should be of the same length as the previous word. Please re-enter the word:");
            newWord = sc.nextLine().toUpperCase();
        }
        words.set(wordIndex, newWord);
        addWordToGrid(newWord, wordIndex, grid, sc);
    }


    public static boolean canAddWordHorizontally(String word, int index, int row, int col, String[][] grid) {
        int startCol = col - index;
        int endCol = startCol + word.length() - 1;
        if (startCol < 0 || endCol >= grid[row].length) {
            return false; // The word goes out of the grid boundaries
        }
        for (int j = startCol; j <= endCol; j++) {
            if (!grid[row][j].equals("0") && j != col) {
                return false; // The word overlaps with an existing word
            }
        }
        return true;
    }

    public static void addWordHorizontally(String word, int index, int row, int col, String[][] grid) {
        int startCol = col - index;
        for (int j = 0; j < word.length(); j++) {
            grid[row][startCol + j] = String.valueOf(word.charAt(j));
        }
    }

    public static boolean canAddWordVertically(String word, int index, int row, int col, String[][] grid) {
        int startRow = row - index;
        int endRow = startRow + word.length() - 1;
        if (startRow < 0 || endRow >= grid.length) {
            return false; // The word goes out of the grid boundaries
        }
        for (int i = startRow; i <= endRow; i++) {
            if (!grid[i][col].equals("0") && i != row) {
                return false; // The word overlaps with an existing word
            }
        }
        return true;
    }

    public static void addWordVertically(String word, int index, int row, int col, String[][] grid) {
        int startRow = row - index;
        for (int i = 0; i < word.length(); i++) {
            grid[startRow + i][col] = String.valueOf(word.charAt(i));
        }
    }



    public static void printCrossword(ArrayList<String> crossword){
        for(String line : crossword){
            System.out.println(line);
        }
    }

    public static ArrayList<Character> getRepeatedLetters(ArrayList<String> words) { 
        HashMap<Character, Integer> counts = new HashMap<>();
        ArrayList<Character> repeatedLetters = new ArrayList<>();
      //gets the repeated letters of word 1
        for (int j=0; j<3; j++) {
            String word= words.get(j);
            for (int i = 0; i < word.length(); i++) {
                char letter = word.charAt(i);
                int count = counts.getOrDefault(letter, 0);
                if (count > 0) {
                    repeatedLetters.add(letter);
                }
                counts.put(letter, count + 1);
            }
        }

        return repeatedLetters;
    }


}
