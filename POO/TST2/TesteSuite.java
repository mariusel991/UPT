import java.util.*;

class WrongQualityIndicatorException extends RuntimeException{
}

class WrongComponentIndicatorException extends RuntimeException{}


abstract class Teste{

    public abstract int getNumarTeste();
}

class Integration_test extends Teste{

    private String nume;
    private int quality_index;
    
    public Integration_test(String nume, int quality_index){
        this.nume = nume;
        
        if(quality_index < 0 || quality_index > 10){
            throw new WrongQualityIndicatorException();
        }
        else{
            this.quality_index =  quality_index;
        }
        
    }
    
    public int getNumarTeste(){
        return 1;
    }
    
    public String toString(){
        String rez = "Integration_test(name=[" + nume +"], quality indicator=["+quality_index+"])" ;
        return rez;
    }
}

class ComponentTest extends Teste{

    private String nume;
    private int quality_index;
    private int complexity;
    
    public ComponentTest(String nume, int quality_index, int complexity){
        
        this.nume = nume;
        
        if(quality_index < 0 || quality_index > 10){
            throw new WrongQualityIndicatorException();
        }
        else{
            this.quality_index =  quality_index;
        }
        
        if(complexity == 0){
            throw new WrongComponentIndicatorException();
        }
        else{
            this.complexity = complexity;
        }
    }
    
    public int getNumarTeste(){
        return 1;
    }
    
    public String toString(){
        String rez = "Integration_test(name=[" + nume +"], quality indicator=["+quality_index+"], component complexity indicator=[" + complexity+"])" ;
        return rez;
    }
}

class TestSuite extends Teste{
    
    private ArrayList <Teste> teste;
    
    public TestSuite(ArrayList <Teste> teste){
        this.teste = teste;
    }
    
    public boolean addNewIntegrationTest(String name, int indicator){
        try{
            Integration_test t = new Integration_test(name,indicator);
            
        }
        catch(WrongQualityIndicatorException e){
            e.printStackTrace();
            return false;
        }
        
        teste.add(new Integration_test(name,indicator));
        return true;
    }
    
    public boolean addNewComponentTest(String name, int indicator, int complexity){
        try{
            ComponentTest t = new ComponentTest(name,indicator,complexity);
            
        }
        catch(WrongQualityIndicatorException e){
            e.printStackTrace();
            return false;
        }
        catch(WrongComponentIndicatorException e){
            throw e;
        }
        
        teste.add(new ComponentTest(name,indicator,complexity));
        return true;
    }
    
    public String toString(){
        String rez = "TesteSuite(";
        Iterator<Teste> it = teste.iterator();
        
        while(it.hasNext()){
            Teste o = it.next();
            rez = rez + o +" ";
        }
        
        rez = rez + "\b)";
        return rez;
    }
    
    public int getNumarTeste(){
        int sum = 0;
        Iterator<Teste> it = teste.iterator();
        
        while(it.hasNext()){
            Teste o = it.next();
            sum = sum + o.getNumarTeste();
        }
        
        return sum;
    }
}

class Main{

    public static void main(String[] args){
        
        try{
            ArrayList <Teste> teste = new ArrayList<>();
            TestSuite Tsts = new TestSuite(teste);
            
            Tsts.addNewIntegrationTest("Ti1",3);
            Tsts.addNewIntegrationTest("Ti2",7);
            
            Tsts.addNewComponentTest("tc1",6,32);
            Tsts.addNewComponentTest("Tc2",3,0);
            
            System.out.println(Tsts);
        
        }
        catch(WrongComponentIndicatorException e){
            e.printStackTrace();
            System.out.println("a aparut o exceptie");
        }
    }
}
