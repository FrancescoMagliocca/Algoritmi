//javac -cp "junit-4.12.jar; hamcrest-core-1.3.jar;." EditTest.java
//java -cp "junit-4.12.jar;hamcrest-core-1.3.jar;." org.junit.runner.JUnitCore EditTest


import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class EditTest extends EditLibrary{

  @Test
  public void restTest() {
    String prova = "albero";
    assertEquals("lbero", rest(prova));
  }

  @Test
  public void edit_distance_statTest() {
    String s1 = "marina";
    String s2 = "mari";

    assertEquals(2, edit_distance_stat(s1, s2));
    assertEquals(2 ,edit_distance_stat(s2, s1));
  }

  @Test
  public void edit_distance_dyn() {
    String s1 = "addio";
    String s2 = "addi";

    assertEquals(1, edit_distance_dyn(s1, s2));
    assertEquals(1 ,edit_distance_dyn(s2, s1));
  }
}
