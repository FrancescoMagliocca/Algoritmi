public class Vertex {  //vertice

  private int value;

  public int getValue(){
    return this.value;
  }

  public Vertex() {
    this.value = 0;
  }

  public Vertex(int value) {
    this.value = value;
  }

  @Override
  public int hashCode() {
    int hash = 5;
    hash = 97 * hash + this.value;
    return hash;
  }

  @Override
  public String toString(){
    return "\nVertex { Value : " + this.getValue() + " }";
  }

  @Override
  public boolean equals(Object obj) {
    if(obj instanceof Vertex) {
        if (this.getValue() == ((Vertex)obj).getValue()) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
  }
}
