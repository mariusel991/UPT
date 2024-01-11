import java.util.*;

class DestinatarDuplicat extends Exception{}

abstract class Destinatar{

    public abstract void receptioneaza(Utilizator user, String mesaj);
    public abstract String getNume();
    
}

class Utilizator extends Destinatar{

    private String nume;
    private ArrayList <String> jurnal = new ArrayList<>();
    
    public Utilizator(String nume){
        this.nume = nume;
    }
    
    public void trimite(Destinatar destinatar, String mesaj){
        jurnal.add("Trimis catre " + destinatar.getNume() + " mesajul: " + mesaj);
        destinatar.receptioneaza(this,mesaj);
    }
    
    public void receptioneaza(Utilizator expeditor, String mesaj){
        this.jurnal.add("Primit de la " + expeditor.nume + " mesajul: " + mesaj);
    }
    
    public String getNume(){
        return this.nume;
    }
    
    public String toString(){
    
        String rez = "" + this.nume +":\n";
        Iterator<String> it = this.jurnal.iterator();
        
        while(it.hasNext()){
            String s = it.next();
            rez = rez + s + "\n";
        }
        
        return rez;
    
    }
}

class Grup extends Destinatar{

    private ArrayList<Destinatar> destinatari = new ArrayList<>();
    private String nume;
    
    public Grup(String nume){
        this.nume = nume;
    }
    
    public void inscrie(Destinatar destinatar) throws DestinatarDuplicat{
        
        if(destinatari.contains(destinatar)){
            throw new DestinatarDuplicat();
        }
        else{
            destinatari.add(destinatar);
        }
        
    }
    
    public String getNume(){
        return nume;
    }
    
    public void receptioneaza(Utilizator expeditor, String mesaj){
        for(Destinatar i: destinatari){
            if(!i.getNume().equals(expeditor.getNume())){
                i.receptioneaza(expeditor,mesaj);
            }
        }
    }
}

class Main{
    
    public static void main(String[] args){
    
        Utilizator u1 = new Utilizator("Dan");
        Utilizator u2 = new Utilizator("Marius");
        Utilizator u3 = new Utilizator("Alex");
        
        Grup g1 = new Grup("Carnivorii");
        
        
        try{
            g1.inscrie(u1);
            g1.inscrie(u2);
            g1.inscrie(u3);
            //g1.inscrie(u1);
        
        }
        catch(DestinatarDuplicat e){
            e.printStackTrace();
        }
        
        u1.trimite(g1,"Am deschis");
        u2.trimite(g1,"Vin acuma");
        
        System.out.println(u1);
        System.out.println(u2);
        System.out.println(u3);
        
    }
    
}
