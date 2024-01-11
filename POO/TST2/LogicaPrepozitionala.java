import java.util.*;

abstract class Propozitie{
    
    public abstract boolean determinaValoareAdevar(ArrayList <Boolean> valori);
}

class PropozitieAtomica extends Propozitie {

    private int index;
    
    public PropozitieAtomica(int index){
        this.index = index;
    }
    
    public boolean determinaValoareAdevar(ArrayList <Boolean> valori){
        
        Iterator <Boolean> it = valori.iterator();
        Boolean o = it.next();
        int poz = 1;
        
        if(poz == this.index){
            return Boolean.valueOf(o);
        }
        
        poz++;
        
        while(it.hasNext()){
        
            o = it.next();
            if(poz == this.index){
                break;
            }
            poz++;
        }
        
        return Boolean.valueOf(o);
    }
    
    public String toString(){
        String rez = "";
        rez = rez + "Atom" + this.index;
        return rez;
    }
}

class Negatie extends Propozitie{

    private Propozitie p;
    
    public Negatie(Propozitie p){
        this.p = p;
    }

    
    public boolean determinaValoareAdevar(ArrayList <Boolean> valori){
    
        if(p.determinaValoareAdevar(valori)){
            return true;
        }
        else{
            return false;
        }
    }
    
    public String toString(){
        String rez = "!";
        rez = rez + p;
        
        return rez;
    }

}

class SiMultiplu extends Propozitie{
    
    private ArrayList <Propozitie> propozitii;
    
    public SiMultiplu(ArrayList <Propozitie> propozitii){
        this.propozitii = propozitii;
    }
    
    public boolean determinaValoareAdevar(ArrayList <Boolean> valori){
    
        int cnt1 = 0;
        int cnt2 = 0;
        
        for(Boolean i: valori){
            cnt1++;
        }
        
        for(Propozitie i: propozitii){
            cnt2++;
        }
        
        if(cnt1 != cnt2){
            throw new IndexOutOfBoundsException();
        }
    
        for(Propozitie i : propozitii){
            if(!i.determinaValoareAdevar(valori)){
                return false;
            }
        }
        return true;
    }
    
    public String toString(){
        String rez = "(";
        
        for(Propozitie i : propozitii){
            rez = rez + i + "&";
        }
        rez = rez + "\b)";
        
        return rez;
    }
    
}

class Main{

    public static void main(String[] args){
    
        PropozitieAtomica a1 = new PropozitieAtomica(1);
        PropozitieAtomica a2 = new PropozitieAtomica(7);
        PropozitieAtomica a3 = new PropozitieAtomica(3);
        PropozitieAtomica a4 = new PropozitieAtomica(4);
        
        Negatie n1 = new Negatie(a2);
        
        ArrayList <Propozitie> p1 = new ArrayList<>();
        ArrayList <Boolean> valori = new ArrayList<>();
        
        
        valori.add(new Boolean(true));
        valori.add(new Boolean(false));
        valori.add(new Boolean(true));
        valori.add(new Boolean(true));
        
        boolean exp = false;
        
        
        p1.add(a1);
        p1.add(n1);
        p1.add(a3);
        p1.add(a4);
        
        SiMultiplu S = new SiMultiplu(p1);
        
        try{
           exp = S.determinaValoareAdevar(valori);
    
        }
        catch(IndexOutOfBoundsException e){
            e.printStackTrace();
        }
        
        System.out.println(S);
        System.out.println(exp);
        
    }
}
