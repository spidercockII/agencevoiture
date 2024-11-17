class Erreur extends Exception{}
class Err1 extends Erreur {}
class Err2 extends Erreur {}

class A {
     public A(int n) throws Erreur{
        try{
            if( n == 1 ) throw new Err1();
            if( n == 2 ) throw new Err2();
            if( n == 3 ) throw new Erreur();
        }
        catch (Err1 e){
            System.out.println("Caught Exc1");
        }
        catch (Erreur e){
            System.out.println("Caught Exc");
            throw e;
        }
     }
}

public class Main{
    public static void main(String[] args){
        int n;
        for(n = 1; n <= 3; n++){
            try{
                A a = new A(n);
            }
            catch( Err1 e ){
                System.out.println("**Err1 in Main**");
            }
            catch ( Err2 e ){
                System.out.println("**Err2 in Main**");
            }
            catch ( Erreur e ){
                System.out.println("**Erreur in Main**");
                System.out.println("------------------");
            }
        }
        System.out.println("fin main");
    }
}
