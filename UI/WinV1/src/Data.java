import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class Data {

    /* sert à stocker les valeurs qu'on va chercher dans la bdd */
    protected char[] ra;
    protected char[] dec;
    protected char[] time;

    public Data(){
    }

    public void setTime(){
        SimpleDateFormat s= new SimpleDateFormat("yyyy;MM;dd;HH;mm;ss");
        Date date=new Date();
        time=s.format(date).toCharArray();
    }

    public void setRa(char[] a){ra=a;}

    public void setDec(char[] b){dec=b;}

    public void printData(){
        System.out.println(this.ra);
        System.out.println(this.dec);
        System.out.println(this.time);
    }

}
