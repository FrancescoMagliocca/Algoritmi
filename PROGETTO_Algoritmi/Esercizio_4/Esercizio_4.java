//javac -cp ".:junit-4.12.jar:hamcrest-core-1.3.jar.;" Esercizio_4.java
//java -cp ".:junit-4.12.jar:hamcrest-core-1.3.jar.;" Esercizio_4 input.txt output.txt
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.HashMap;

public class Esercizio_4 {

  public static void checkResult(String correct, String answer) {
    try {
      BufferedReader bwc = new BufferedReader(new FileReader(new File(correct)));
      BufferedReader bwa = new BufferedReader(new FileReader(new File(answer)));
      String c = "";
      String a = "";
      while ((c = bwc.readLine()) != null && (a = bwa.readLine()) != null) {
        if (!c.equalsIgnoreCase(a)) {
          return;
        }
      }
    } catch (Exception e) {
      System.out.println(e.getMessage());
    }

  }
//query
  public static void askQuestion(HashMap graph, String question, BufferedWriter bw) {
    String[] params = question.split(" ");//splitta la stringa question(ovvero la q passata)
    Vertex v1 = new Vertex(Integer.parseInt(params[0])); 
    Vertex v2 = new Vertex(Integer.parseInt(params[1]));//metto ogni valore al posto giusto
    Edge e = new Edge(v1, v2, Integer.parseInt(params[2]));
    try {
      if (Integer.parseInt(params[0]) == Integer.parseInt(params[1])) {//se il vert1 è = al vert2 la risposta è no //cappio al grafo che non coincide
          bw.write("NO\n");
      } else if(((ArrayList)graph.get(v1)).contains(e)) { //prendo l'arco associato al vertice 1
          int index = ((ArrayList)graph.get(v1)).indexOf(e);//prendo l'indice dell'arco,
          int result = ((Edge)((ArrayList)graph.get(v1)).get(index)).compareTo(e);//compara ......tramite compareTo che è una funziona che sta nella classe edge.java
          //sel'arco v1 è maggiore dell'arco e
          if(result == 1) {
            bw.write("YES\n");
          } else {
            bw.write("NO\n");
          }
      } else {//se v1 non contiene l'arco
          ArrayList<Edge> route = findRoute(graph, v1, v2);

          if(route != null) {//tra tutti gli archi di route cerco quello col peso massimo
              int max = route.get(0).getWeight();//peso del primo arco
              for(int i = 1; i < route.size(); i++) {
                  if(max < route.get(i).getWeight()) {
                      max = route.get(i).getWeight();// max = peso arco con peso massimo
                  }
              }
              if(max > e.getWeight()) {//se è maggiore dell'arco preso in considerazione,alllora potrei sostituirlo
                bw.write("YES\n");
              } else {
                bw.write("NO\n");
              }
          }
      }
    } catch (IOException ex) {
      System.out.println(ex.getMessage());
    }
  }

  private static String[] fillGraph(HashMap graph, String input_file) {
    File file = new File(input_file);
    try (BufferedReader br = new BufferedReader(new FileReader(file))) {
        String line;
        Vertex v1;
        Vertex v2;
        Edge e;
        if ((line = br.readLine()) != null) { //finchè non arrriva alla fine
            int input = Integer.parseInt(line); //mette in INPUT il valore di LINE traformando la stringa di intero ad un intero (ovvero il numero di nodi del grafo)
            for (int i = 0; i < input-1 && (line = br.readLine()) != null; i++) {
                String[] inputs = line.split(" ");//crea un array dove la usccessione degli elementi è dettata da uno spazio
                v1 = new Vertex(Integer.parseInt(inputs[0]));//primo vertice
                v2 = new Vertex(Integer.parseInt(inputs[1]));//secondo vertice
                if (!graph.containsKey(v1)) { //se l'hashmap non contiene la chiave di v1(nuovo elemento) la aggiungo
                    graph.put(v1, new ArrayList<Edge>());
                }
                if (!graph.containsKey(v2)) {
                    graph.put(v2, new ArrayList<Edge>());//......v2....
                }
                e = new Edge(v1, v2, Integer.parseInt(inputs[2]));//e è tutto l'arco,inputs[2] è il peso
                ((ArrayList)graph.get(v1)).add(e);//in arraylist aggiungiamo l'arco
                ((ArrayList)graph.get(v2)).add(e);//....
            }
            int questions = Integer.parseInt(br.readLine());//leggo la linea e la casto in intero
            String[] result = new String[questions];//crea un array di stringhe grosso quanto questions
            for (int j = 0; j < questions && (line = br.readLine()) != null; j++) {//in ogni elemento dell'array mette l'arco
                result[j] = line;
            }
            return result;
        } else {
            return null;
        }
    } catch (IOException e) {
        e.printStackTrace();
        return null;
    }
  }
//trova il cammimo minimo,prende il vertice sorgente e destinazione e trova il cammino minimo tra sorgente e destinazione
  private static ArrayList<Edge> findRoute(HashMap graph, Vertex source, Vertex dest) {
    ArrayList<Edge> edgeList = (ArrayList)graph.get(source);
    ArrayList<Edge> result = null;
    for (int i = 0; i < edgeList.size() && result == null; i++) {
        result = findRouteRec(graph, source, dest, edgeList.get(i));//vertice e seguono tutti gli archi
    }
    return result;
  }
//prende un arco per volta e prende poii  la partenza dal nodo successivo.from 
  private static ArrayList<Edge> findRouteRec(HashMap graph, Vertex prev, Vertex dest, Edge from){//restituisce il cammino
    Vertex curr;
    ArrayList<Edge> route = new ArrayList<>();
    if(from.getV1().equals(prev)) {//se il v1 del'arco è uguale al nodo di sorgente
        curr = from.getV2();//currr è uguale al nodo destinazione
    } else {
        curr = from.getV1(); //altrimenti resta qui.curr è il vertice
    }
//cerca e prende di volta in volta il nodo a costo minimo.Prende il nodo e cerca tra gli altri quelello col costo minimo e ci va
    if(curr.equals(dest)) {//algoritmo di prm
        route.add(from);
        return route;
    } else {
        ArrayList<Edge> edgeList = (ArrayList)graph.get(curr);
        if(edgeList.size() == 1) {
            return null;
        } else {
            route = null;//prendo e aggiungo a route tutti gli archi collegati a curr(v1 o v2)
            for(int j = 0; j < edgeList.size() && route == null; j++) {//vede gli archi collegati al vertice e li percorre tutti
                if(!edgeList.get(j).equals(from)) {
                    route = findRouteRec(graph, curr, dest, edgeList.get(j));
                }
            }
            if(route == null) {
                return null;
            } else {
                route.add(from);
                return route;
            }
        }
    }
  }

  public static void main(String[] args) {

    for (int i = 1; i < 11; i++) { //per ogni cartella test
      Timestamp timestamp = new Timestamp(System.currentTimeMillis());//stampa ora attuale
      System.out.println("Avvio esecuzione del test " + i + " : " + timestamp);
      HashMap graph = new HashMap<Vertex, ArrayList<Edge>>();//crea una hashmap vuota con i parametri vertex e lista nodi
      String[] questions = fillGraph(graph, "./test" + i + "/" + args[0]);//args[0] è input.txt,qui FILLGRAPH prende come parametri la hasmap precedentemente creata e i valori del grafo datogli da input
      timestamp = new Timestamp(System.currentTimeMillis());
      System.out.println("Grafo creato,ora rispondo alle domande : " + timestamp);
      File file = new File("./test" + i + "/" + args[1]);//args[1] è output.txt
      try (BufferedWriter bw = new BufferedWriter(new FileWriter(file))) {//scrive nel file output.txt
        for ( String q : questions) {//scorro tutto l'array e associo alla stringa Q tutto l'arco presente nel primo elemento di questions
            askQuestion(graph, q, bw);
        }
        bw.close();//chiudo il buffer writer
      } catch (IOException exc) {
        System.out.println(exc.getMessage());
      }
      timestamp = new Timestamp(System.currentTimeMillis());
      System.out.println("Test " + i + " finito : " + timestamp);
      checkResult("./test" + i + "/correct.txt","./test" + i + "/output.txt");


    }
  }
}
