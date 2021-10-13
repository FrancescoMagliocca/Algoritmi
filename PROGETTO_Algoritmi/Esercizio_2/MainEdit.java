//javac -cp "junit-4.12.jar; hamcrest-core-1.3.jar;." MainEdit.java
//java -cp "junit-4.12.jar;hamcrest-core-1.3.jar;." MainEdit
import java.io.*;
import java.util.*;


class MainEdit extends EditLibrary {


  public static void main(String[] args) {

    try {
      BufferedReader reader_corr = new BufferedReader(new FileReader("correctme.txt"));//legge il file
      String line_corr;//linea correctme
      String line_dic;//linea dizionario

      HashMap<String, ArrayList> correct = new HashMap<String, ArrayList>();//crea una hashmap

      while((line_corr = reader_corr.readLine()) != null) {
        String[] words = line_corr.split("\\ |\\,|\\.|\\:");//ogni casella contiene una parola

        int result = 0;
        for(int i = 0; i < words.length; i++) {
           if(!words[i].equalsIgnoreCase("")) {//se la parola non è spazio vuoto
              System.out.println(words[i] + ":");//stampo la parola:
              correct.put(words[i], new ArrayList<String>());//metto la parola nella hashmap
              correct.get(words[i]).add("999");//aggiungo un numero grande per il fututro confronto con la prima parola che disterà sicuramente meno da 999
              BufferedReader reader_dic = new BufferedReader(new FileReader("dictionary.txt"));
              while((line_dic = reader_dic.readLine()) != null) {// legge ogni linea del dizionario
                result = EditLibrary.edit_distance_dyn(words[i], line_dic);//trova la distanza
                if(result < Integer.parseInt(String.valueOf(correct.get(words[i]).get(0)))) { //se result è più piccolo del numero presente alla posizione 0 di correct,nel primo caso si aggiungerà sempre perchè all'inizio get(0)=999
                  correct.get(words[i]).clear();//elimina gli elementi precedenti
                  correct.get(words[i]).add(Integer.toString(result));//aggiunge la nuova distanza minima
                  correct.get(words[i]).add(line_dic);//aggiunge la parola
                } else if (result == Integer.parseInt(String.valueOf(correct.get(words[i]).get(0)))) { //se il result trovato(distanza minima) è la stessa distanza dell'altra parola,semplicemente aggiungo
                   correct.get(words[i]).add(line_dic);
                }
             }
             System.out.println(words[i] + ", " + correct.get(words[i]).toString());
           } 
         }
      } 

    }

    catch (IOException e) {
      System.out.println(e);
      System.out.println(" Errore tipo IOException");
    }
  }
}
