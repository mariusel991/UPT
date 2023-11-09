class Avion{

    private String PlaneID;
    private int totalEnginePower;
    
    public Avion(String PlaneID, int totalEnginePower){
        this.PlaneID = PlaneID;
        this.totalEnginePower = totalEnginePower;
    }
    
    public int getTotalEnginePower(){
        return this.totalEnginePower;
    }
    
    public String getPlaneID(){
        return this.PlaneID;
    }
    
    public void takeOff(){
        System.out.println(PlaneID + " - Initiating takeoff procedure - Starting engines - Accelerating down the runway - Taking off - Retracting gear - Takeoff complete");
    }
    
    public void fly(){
        System.out.println(PlaneID + " - Flying");
    }
    
    public void land(){
        System.out.println(PlaneID + " - Initiating landing procedure - Enabling airbrakes - Lowering gear - Contacting runway - Decelerating - Stopping engines - Landing complete");
    }
}

/// ############# AVIOANE CALATORI ##################################

class Avioane_Calatori extends Avion {

    private int maxPassengers;
    
    
    public Avioane_Calatori(int maxPassengers, String PlaneID, int totalEnginePower){
        super(PlaneID,totalEnginePower);
        this.maxPassengers = maxPassengers;
    }
    
    public int getMaxPassengers(){
        return this.maxPassengers;
    }
}

class Concorde extends Avioane_Calatori{
    
    public Concorde(int maxPassengers, String PlaneID, int totalEnginePower){
        super(maxPassengers,PlaneID,totalEnginePower);
    }
    
    public void goSuperSonic(){
        System.out.println(this.getPlaneID() + " - Supersonic mode activated");
    }
    
    public void goSubSonic(){
        System.out.println(this.getPlaneID() + " - Supersonic mode deactivated");
    }
}

class Boeing extends Avioane_Calatori{
    public Boeing(int maxPassengers, String PlaneID, int totalEnginePower){
        super(maxPassengers,PlaneID,totalEnginePower);
    }
}
///################## ___________ END OF AVIOANE CALATORI ___________________##################


class Avioane_Lupta extends Avion{

    public Avioane_Lupta(String PlaneID, int totalEnginePower){
        super(PlaneID, totalEnginePower);
    }

    public void launchMissile(){
         System.out.println(this.getPlaneID() + " - Initiating missile launch procedure - Acquiring target - Launching missile - Breaking away - Missile launch complete");
    }
}

class Mig extends Avioane_Lupta{
    
    public Mig(String PlaneID, int totalEnginePower){
        super(PlaneID, totalEnginePower);
    }
    
    public void highSpeedGeometry(){
        System.out.println(this.getPlaneID() + " - High speed geometry selected");
    }
    
    public void normalGeometry(){
        System.out.println(this.getPlaneID() + " - Normal geometry selected");
    }
}

class TomCat extends Avioane_Lupta{

    public TomCat(String PlaneID, int totalEnginePower){
        super(PlaneID, totalEnginePower);
    }

    public void refuel(){
        System.out.println(this.getPlaneID() + "- Initiating refueling procedure - Locating refueller - Catching up - Refueling - Refueling complete");
    }
}


class Main{

    public static void main(String[] args){
    
        Avion Concorde = new Concorde(30, "PLC1", 1500);
        Avion Boeing = new Boeing(100, "PLC2", 2000);
        Avion Mig = new Mig("PLF1", 3000);
        Avion TomCat = new TomCat("PLF2", 3500);
        
        Concorde.takeOff();
        if (Concorde instanceof Avioane_Calatori){
            if(Concorde instanceof Concorde){
            ((Concorde)Concorde).goSuperSonic();
            ((Concorde)Concorde).fly();
            ((Concorde)Concorde).goSubSonic();
            ((Concorde)Concorde).land();
            System.out.println(((Concorde)Concorde).getMaxPassengers());
            }
        }
    }
}
