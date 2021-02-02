import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.sql.Statement;

public class Data {

    /* sert à stocker les valeurs qu'on va chercher dans la bdd */
    protected String ra;
    protected String dec;
    protected String time;
    protected String mode;

    public Data(String id, String path){
        Connection conn = null;
        try {
            String url="jdbc:sqlite:"+path;
            conn = DriverManager.getConnection(url);

            System.out.println("C'est bon !");

            Statement stmt=null;
            String query = "select ra,dec from HYG where id="+id;
            try {
                stmt=conn.createStatement();
                ResultSet rs = stmt.executeQuery(query);
                while(rs.next()) {
                    setRa(rs.getString("ra"));//Toutes mes données sont dans des chaines de caractères, mais je fais la conversion juste avant l'envoi de string a char[]
                    setDec(rs.getString("dec"));
                    setTime();
                    //printData();
                }
            }
            catch (SQLException e) {
                throw new Error("Probleme :",e);
            }
            finally {
                if (stmt!=null) {stmt.close();}
            }
        }
        catch(SQLException e) {
            throw new Error("Probleme :",e);
        }
        finally {
            try {
                if (conn!= null) {
                    conn.close();
                }
            }
            catch (SQLException ex) {
                System.out.println(ex.getMessage());
            }
        }
    }

    public void setTime(){
        SimpleDateFormat s= new SimpleDateFormat("yyyy;MM;dd;HH;mm;ss");
        Date date=new Date();
        time=s.format(date);
    }

    public void setMode(String m){mode=m+";";}

    public void setRa(String a){ra=a+";";}

    public void setDec(String b){dec=b+";";}

    public void printData(){
        System.out.println(this.ra);
        System.out.println(this.dec);
        System.out.println(this.time);
    }

}
