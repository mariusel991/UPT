import java.util.*;

abstract class Statistica_stringuri{

    public abstract void calculeaza(ArrayList <String> secventa_stringuri);
}

class StatisticaNumarAparitii extends Statistica_stringuri{
    
    private ArrayList <String> secventa_stringuri;
    private ArrayList <String> Jurnal;
    
    public StatisticaNumarAparitii(ArrayList <String> secventa_stringuri){
        this.secventa_stringuri = secventa_stringuri;
        this.Jurnal = new ArrayList<>();
    }
    
    public void calculeaza(ArrayList <String> secventa_stringuri){
        
        this.Jurnal = new ArrayList<>();
    
        int contor_secventa = 0;
        String rez1 = "{";
        String rez2 = "{";
        
        for (String i : this.secventa_stringuri){
            rez1 = rez1 + i + ",";
        }
        rez1 = rez1 + "\b}";
        
        for (String i : secventa_stringuri){
            rez2 = rez2 + i + ",";
        }
        rez2 = rez2 + "\b}";
        
        
        for (String i: this.secventa_stringuri){
            for(String j : secventa_stringuri){
                if(i.equals(j)){
                    contor_secventa++;
                }
            }
        }
        
        Jurnal.add("In");
        Jurnal.add("secventa");
        
        for(String i: secventa_stringuri){
            Jurnal.add(i);
        }
        
        Jurnal.add("apar");
        Jurnal.add("" + contor_secventa);
        Jurnal.add("siruri");
        Jurnal.add("din");
        Jurnal.add("secventa");
        
        for(String i: this.secventa_stringuri){
            Jurnal.add(i);
        }
        
        /*
        Iterator it1 = this.secventa_stringuri.iterator();
        
        while(it1.hasNext()){
            
            String i = it1.next();
            Iterator it2 = secventa_stringuri.iterator();
            
            while(it2.hasNext()){
                String j = it2.next();
                if(i.equals(j)){
                    contor_secventa++;
                }
            }
            
        }
        
        */
        
        
    }
    
    public String toString(){
        String rez = "";
        
        Iterator<String> it = Jurnal.iterator();
        
        while(it.hasNext()){
            String i = it.next();
            rez = rez + i + "\n";
        }
        
        rez = rez + "\n";
        return rez;
    }
}

class StatisticaNumereNonReale extends Statistica_stringuri{
    
    private ArrayList <String> Jurnal = new ArrayList<>();
    
    public void calculeaza(ArrayList <String> secventa_stringuri){
    
        this.Jurnal = new ArrayList<>();
        
        int contor_NonNumeral = 0;
        
        Iterator<String> it = secventa_stringuri.iterator();
        
        while(it.hasNext()){
            String str = it.next();
            
            try{
                double nr = Double.parseDouble(str);
            }
            catch(NumberFormatException e){
                contor_NonNumeral++;
            }
        }
        
        Jurnal.add("In");
        Jurnal.add("secventa");
        
        for(String i: secventa_stringuri){
            Jurnal.add(i);
        }
        
        Jurnal.add("avem");
        Jurnal.add("" + contor_NonNumeral);
        Jurnal.add("siruri");
        Jurnal.add("ce");
        Jurnal.add("nu");
        Jurnal.add("sunt");
        Jurnal.add("numerale");
        Jurnal.add("reale");
        
    }
    
    public String toString(){
        String rez = "";
        
        Iterator<String> it = Jurnal.iterator();
        
        while(it.hasNext()){
            String i = it.next();
            rez = rez + i + "\n";
        }
        
        rez = rez + "\n";
        return rez;
    }
}
    
    
class Executor{
    
    private ArrayList <Statistica_stringuri> Stats;
    
    public Executor(ArrayList <Statistica_stringuri> Stats){
        this.Stats = Stats;
    }
    
    public void executa(ArrayList <String> secventa_stringuri){
        Iterator<Statistica_stringuri> it = Stats.iterator();
        
        while(it.hasNext()){
            Statistica_stringuri o = it.next();
            o.calculeaza(secventa_stringuri);
            System.out.println(o);
        }
    }
} 

class Main{

    public static void main(String[] args){
    
        ArrayList<String> a1 = new ArrayList<>();
        a1.add("mere");
        a1.add("pere");
        a1.add("banane");

        StatisticaNumarAparitii st1 = new StatisticaNumarAparitii(a1);
        StatisticaNumereNonReale st2 = new StatisticaNumereNonReale();

        ArrayList<Statistica_stringuri> statistici = new ArrayList<>();
        statistici.add(st1);
        statistici.add(st2);

        Executor e = new Executor(statistici);
        ArrayList<String> a2 = new ArrayList<>();
        a2.add("ana");
        a2.add("are");
        a2.add("mere");
        e.executa(a2);

        ArrayList<String> a3 = new ArrayList<>();
        a3.add("maria");
        a3.add("are");
        a3.add("3");
        a3.add("mere");
        e.executa(a3);
    }
}
