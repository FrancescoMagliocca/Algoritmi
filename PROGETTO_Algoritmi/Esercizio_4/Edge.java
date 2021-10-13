//bordo
import java.util.Objects;

public class Edge implements Comparable{
  private Vertex v1;
  private Vertex v2;
  private int weight;

  public Edge() {
    this.v1 = null;
    this.v2 = null;
    this.weight = 0;
  }

  public Edge(Vertex v1, Vertex v2, int weight) {
    this.v1 = v1;
    this.v2 = v2;
    this.weight = weight;
  }

  public int getWeight() {
    return weight;
  }

  public Vertex getV1() {
    return v1;
  }

  public Vertex getV2() {
    return v2;
  }

  @Override
  public String toString() {
    return "Edge {" + "v1 = " + v1.getValue() + ", v2 = " + v2.getValue() + ", weight = " + weight + '}';
  }

  @Override
  public int hashCode() {
    int hash = 7;
    hash = 79 * hash + Objects.hashCode(this.v1);
    hash = 79 * hash + Objects.hashCode(this.v2);
    return hash;
  }

  @Override
  public int compareTo(Object o) {//guarda se sono lo stesso oggetto ,compara un oggetto di tipo edge con 0 ,
    if(o instanceof Edge && o != null) {//se o è un oggetto di tipo edge
        if(this.equals(o)) {
            if(this.getWeight() == ((Edge)o).getWeight()) {
                return 0;
            } else if(this.getWeight() < ((Edge)o).getWeight()){
                return -1;
            } else {
                return 1;//se il peso di quest arco è maggiore ritorno 1
            }
        } else {
            throw new UnsupportedOperationException();
        }
    } else {
        throw new NullPointerException();
    }
  }

  @Override
  public boolean equals(Object obj) {//se 2 archi sono uguali se hanno il vertice uguale e il peso uguale
   if(obj instanceof Edge) {
       if( (this.v1.getValue() == ((Edge) obj).v1.getValue() &&
               this.v2.getValue() == ((Edge) obj).v2.getValue() ) ||
                (this.v1.getValue() == ((Edge) obj).v2.getValue() &&
               this.v2.getValue() == ((Edge) obj).v1.getValue() ) ) {
            return true;
        } else {
           return false;
        }
    } else {
        return false;
    }
  }
}
