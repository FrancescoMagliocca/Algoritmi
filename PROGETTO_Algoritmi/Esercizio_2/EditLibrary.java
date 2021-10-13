import java.lang.Math;
import java.util.Arrays;

class EditLibrary {

  public static int edit_distance_dyn_rec(String s1, String s2, int[][] matrix, int row, int column) {
    if(row == matrix.length && column == 1) {
      return matrix[matrix.length-1][matrix[0].length-1];//ritorna l'intero che c'è li
    } else if(column < matrix[0].length) {
      int result = 0;
      if(s1.charAt(row-1) == s2.charAt(column-1)) {//se sono uguali
        result = 0;
      } else {
        result = 2;
      }
      matrix[row][column] = Math.min(Math.min(matrix[row-1][column]+1,matrix[row][column-1]+1), matrix[row-1][column-1]+result);
      return edit_distance_dyn_rec(s1, s2, matrix, row, column+1);
    } else {
      return edit_distance_dyn_rec(s1, s2, matrix, row+1, 1);
    }
  }
  
  public static int edit_distance_stat(String s1, String s2) {
    if(s1.equalsIgnoreCase(s2)){//se sono uguali ritorna 0
      return 0;
    } else if(s1.length() == 0) {
      return s2.length();
    } else if(s2.length() == 0) {
      return s1.length();
    } else {
      if(s1.charAt(0) == s2.charAt(0)) {
        int no_op = 0 + edit_distance_stat(rest(s1), rest(s2));
        return no_op;
      } else {
        int del_op = 1 + edit_distance_stat(s1, rest(s2));
        int ins_op =  1 + edit_distance_stat(rest(s1), s2);
        if(del_op < ins_op) {
          return del_op;//elimino
        } else {
          return ins_op;//inserisco nuova lettera
        }
      }
    }
  }

  public static int edit_distance_dyn(String s1, String s2) { //ogni volta crea la matrice di dimensione diversa
    if(s1.equalsIgnoreCase(s2)) {
      return 0; //ritorna solamente quando trova la parola a distanza minima
    } else if(s1.length() == 0) {
      return s2.length();
    } else if(s2.length() == 0) {
      return s1.length();
    } else {
      int row = s1.length()+1;
      int column = s2.length()+1;
      int[][] matrix = new int[row][column];
      matrixCreation(matrix, 0);//crea una matrice dinamica(la dimensione varia)
      int result = edit_distance_dyn_rec(s1, s2, matrix, 1, 1);
      return result;
    }
  }

  public static void printmatrix(int[][] matrix) {
    for(int i = 0; i < matrix.length; i++) {
      System.out.println(Arrays.toString(matrix[i]));
    }
  }

  public static void matrixCreation(int[][] matrix, int i) {//crea e popola la matrice in base alla riga e poi in base alla colonna
    if(i == 0) {
      matrix[0][0] = 0;
      matrixCreation(matrix, i+1);
    } else if((i < matrix.length) || (i < matrix[0].length)) {
      if(i < matrix.length)
        matrix[i][0] = i;
      if(i < matrix[0].length)
        matrix[0][i] = i;
      matrixCreation(matrix, i+1);
    }
  }

  public static String rest(String s) {
    return s.substring(1, s.length());
  }

}
