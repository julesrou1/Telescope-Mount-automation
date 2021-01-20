//package application;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.sql.Statement;




public class testJDBC {
	public static void main(String args[]) {
		//System.out.println("Hello JavaWorld");
		Connection conn = null;
		try {
			String url="jdbc:sqlite:D:\\Cours\\2A\\Projet2A\\Telescope-Mount-automation\\Database\\data2.db";
			conn = DriverManager.getConnection(url);
			
			System.out.println("C'est bon !");
			
			Statement stmt=null;
			String query = "select * from HYG";
		try {
			stmt=conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);
			while(rs.next()) {
				String angle=rs.getString("ra");
				System.out.println(angle);
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
