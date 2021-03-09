import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.sql.Statement;


public class falseQuery {
    //Data coords = new Data();
    public falseQuery(String id, String path){
        //Data coords = new Data();
        // id = id de l'astre voulu
        //path = D:\\............\\database.db
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
                    //coords.setRa(rs.getString("ra").toCharArray());//Toutes mes données sont dans des chaines de caractères
                    //coords.setDec(rs.getString("dec").toCharArray());
                    //coords.setTime();
                    //coords.printData();
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
}
