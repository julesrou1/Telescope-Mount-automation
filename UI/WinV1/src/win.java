import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import javax.swing.text.*;
import javax.swing.event.*;
import javax.swing.GroupLayout.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.sql.Statement;

public class win extends JFrame implements ActionListener {
    protected JTextField search;
    protected JTextArea affiche;

    public void actionPerformed(ActionEvent e) {
        searchDB();
//        String ID = search.getText();
//        affiche.append(ID);
//        search.selectAll();
//        affiche.setCaretPosition(affiche.getDocument().getLength());
    }


    public void searchDB(){
        String s = search.getText();
        Connection con = null;
        try{
            String url="jdbc:sqlite:D:\\Cours\\2A\\Projet2A\\Telescope-Mount-automation\\Database\\data2.db";
            con = DriverManager.getConnection(url);

            System.out.println("C'est bon !");

            Statement stmt=null;
            String query = "Select ra,dec from HYG where id==" + s;
        try{
            stmt=con.createStatement();
            ResultSet rs =stmt.executeQuery(query);
            while(rs.next()){
                String ra = rs.getString("ra");
                String dec = rs.getString("dec");
                System.out.println("ra="+ ra + "; dec=" + dec);
            }

        }
        catch(SQLException e){
            throw new Error("Problème :"+ e);

            }
        finally{
            if (stmt==null){stmt.close();}
        }
        }
        catch(SQLException e){
            throw new Error("Problème :"+ e);
        }
        finally{
            try{
                if (con!=null){
                    con.close();
                }
            }
            catch(SQLException ex) {
                System.out.println(ex.getMessage());
            }
        }
    }


    public win(String titre, int x, int y){
        super(titre);
        this.setLocation(400,200);
        this.setSize(x,y);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel label= new JLabel();


        Container pan = getContentPane() ;

        JPanel textPanel = new JPanel();
        JTextField search = new JTextField(20);
        search.addActionListener(this);
        search.setBorder(BorderFactory.createLineBorder(Color.black));
        //label.setText("Entre l'ID");

        JTextArea affiche = new JTextArea();
        affiche.setEditable(false);


        textPanel.setLayout(new GridLayout(2,1));
        textPanel.add(search);
        textPanel.add(affiche);

        pan.add(textPanel, "North");

        this.setVisible(true);
    }
}
