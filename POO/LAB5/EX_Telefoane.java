/*
Un obiect telefon este caracterizat de numele proprietarului (String) ce se setează la crearea obiectului
respectiv. Un telefon mai conține un tablou (eventual și un contor dacă se consideră necesar ;)) ce
memorează nume de proprietari de telefoane (String-uri) care au apelat telefonul respectiv. Pentru
simplitate, acest tablou va conține maxim 100 de elemente.
Cu un telefon se pot realiza următoarele operații:
• apeleaza: această metodă primește ca parametru o referință la obiectul telefon apelat de
telefonul curent. În continuare se adaugă numele proprietarului telefonului pe care s-a apelat
metoda, în lista de nume a telefonului dat ca parametru la aceasta metodă. Dacă nu mai este
loc în tabloul respectiv, metoda apelare întoarce valoarea false (adică apelul nu a reușit).
Altfel, metoda întoarce valoarea true.
• numarDeApeluri: această metodă primește ca parametru un String reprezentând numele unui
proprietar de telefon și întoarce o referintă la un obiect Integer ce conține numărul de apeluri
efectuate de respectiva persoană la telefonul curent.
• toString: returnează un șir de caractere conținând numele proprietarului și numele tuturor
persoanelor care au apelat telefonul respectiv.
Pentru exemplificare, creați o clasă separată care conține o metodă main în care:
• Se citește de la intrarea standard un număr întreg. Acest număr reprezintă câte telefoane
trebuie create. Se vor crea apoi aceste telefoane și se vor memora într-un tablou referințe la
ele. Numele proprietarilor vor fi citite tot de la intrarea standard.
• Se citește de la intrarea standard un număr A reprezentând un număr de apeluri de efectuat.
Apoi se generează aleator A perechi de numere întregi (x,y) semnificând faptul ca telefonul x
din tabloul de mai sus apelează telefonul y din același tablou. Pentru generarea de numere
aleatoare vezi documentația de aici sau de aici (în al doilea caz trebuind să aveți un import
java.util.Random; la începutul fișierului).
• Se citește de la intrarea standard un nume de proprietar. Pentru fiecare telefon se va afișa la
ieșirea standard reprezentarea sa sub formă de șir de caractere și de căte ori persoana cu
numele dat a apelat acel telefon.
*/


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Random;

class Telefon{

    private String NumeProprietar;
    private String[] Apeluri_Recente = new String[100];
    
    private int index = 0;
    
    public Telefon(String NumeProprietar){
        this.NumeProprietar = NumeProprietar;
    }
    
    public boolean apeleaza(Telefon t){
        
        if(t.index < t.Apeluri_Recente.length){
            t.Apeluri_Recente[t.index++] = this.NumeProprietar;
            return true;
        }
        
        return false;
    }
    
    public Integer numarDeApeluri(String Nume){
        int aparitii = 0;
        
        for(int i = 0; i < index; i++){
            if(this.Apeluri_Recente[i].equals(Nume)){
                aparitii++;
            }
        }
        
        
        return Integer.valueOf(aparitii);
    }
    
    public String toString(){
        String rez = "";
        rez = rez + "Nume Proprietar: " + this.NumeProprietar + "\n";
        
        for(int i = 0; i < index;  i++){
            rez = rez + Apeluri_Recente[i] + "\n";
        }
        
        return rez;
    }

}

class Main{

    public static void main(String[] args){
    
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int Numar_Telefoane;
        int A;
        String Nume_Cautat;
            
        try {
        
        System.out.print("Numarul de telefoane:");
        Numar_Telefoane = Integer.parseInt(bf.readLine());
        
        System.out.print("Numarul de Apeluri:");
        A = Integer.parseInt(bf.readLine());
        
        ///Vectorul de telefoane
        Telefon[] Telefoane = new Telefon[Numar_Telefoane];
        
        ///Citim un utilizatori de telfon
        for(int i = 0; i < Numar_Telefoane; i++){
            
            System.out.print("Utilizatorul telefonului " + (i+1) + ":");
            String Nume_Proprietar = bf.readLine();
            
            Telefoane[i] = new Telefon(Nume_Proprietar);
            
        }
        
        // Generam perechi de numere aleatoare
        Random rand = new Random();
        int x,y = x = -1;
        
        
        for (int i = 0; i < A; i++){
            
        x = rand.nextInt(Numar_Telefoane);
        y = rand.nextInt(Numar_Telefoane);
        
        /// Ne asiguram ca nu se poate apelea un telefon pe el insusi
            while (x == y){
            x = rand.nextInt(Numar_Telefoane);
            y = rand.nextInt(Numar_Telefoane);
            }
            
            Telefoane[x].apeleaza(Telefoane[y]);
            //System.out.println("Telefonul " + x + " apeleaza telefonul " + y);
        }
        
        
        System.out.println("Numele Apelantului: ");
        Nume_Cautat = bf.readLine();
        
        for(int i = 0; i < Numar_Telefoane; i++){
            System.out.println(Telefoane[i] + Nume_Cautat + " a apelat de " + Telefoane[i].numarDeApeluri(Nume_Cautat) + " ori");
        }
        
        
        } catch (IOException e){
            e.printStackTrace();
        }
            
    }

}
