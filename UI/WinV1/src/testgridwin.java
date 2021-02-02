import java.io.IOException;

public class testgridwin {
    private static GridWin win = new GridWin("STARFINDER",500,400);
    Data data;

    {
        data = new Data("30", "C:\\Users\\Ggvg1\\Documents\\GitHub\\Telescope-Mount-automation\\Database\\data2.db");
        data.setTime();
        data.printData();
    }


    private static ArduinoConnect con;

    static {
        try {
            con = new ArduinoConnect("COM5","1;40.03158;-0.24587;2021;02;01;15;30;12;");
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    //private static Query test = new Query("30","C:\\Users\\Ggvg1\\Documents\\GitHub\\Telescope-Mount-automation\\Database\\data2.db");
    public static void main (String args[]){
    }
}

