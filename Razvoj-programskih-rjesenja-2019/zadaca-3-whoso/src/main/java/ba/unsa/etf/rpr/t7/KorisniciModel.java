package ba.unsa.etf.rpr.t7;

import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.concurrent.Task;
import javafx.scene.image.Image;

import java.io.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class KorisniciModel {
    private Connection conn;
    private ObservableList<Korisnik> korisnici = FXCollections.observableArrayList();
    private SimpleObjectProperty<Korisnik> trenutniKorisnik = new SimpleObjectProperty<>();
    private PreparedStatement dajSveKorisnikeUpit, updateKorisnikUpit, dajIdUBazi, izbrisiRekorde, dodajKorisnikaUpit, dajIdKorisnikaUpit;

    public KorisniciModel() {
        try {
            conn = DriverManager.getConnection("jdbc:sqlite:korisnici.db"); //uspostavi konekciju sa bazom
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try { //provjeri da li je uspostavljena dobra konekcija
            dajSveKorisnikeUpit = conn.prepareStatement("SELECT ime, prezime, email, username, password, slika FROM korisnik");
        } catch (SQLException e) {
            regenerisiBazu(); //ako nije uspostavljena, probaj regenerisat bazu iz .sql datoteke koja je exportovana
            try {
                dajSveKorisnikeUpit = conn.prepareStatement("SELECT ime, prezime, email, username, password, slika FROM korisnik");
            } catch (SQLException e1) {
                e1.printStackTrace();
            }
        }
    }

    public void napuni() {
            try{
                ResultSet rs = dajSveKorisnikeUpit.executeQuery();
                List<Korisnik> lista = new ArrayList<>();
                lista = dajSveKorisnikeIzResultSeta(rs);
                korisnici.addAll(lista);
            } catch (SQLException ex) {
                ex.printStackTrace();
            }

            trenutniKorisnik.set(null);
    }


    private List<Korisnik> dajSveKorisnikeIzResultSeta(ResultSet rs) {

        List<Korisnik> rezultat=new ArrayList<>();

        try{
            while(rs.next())
            {
                Korisnik k = new Korisnik(rs.getString(1), rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5));
                k.setPutanjaAvatar(rs.getString(6));
                rezultat.add(k);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rezultat;

    }

    public ObservableList<Korisnik> getKorisnici () {
        return korisnici;
    }

    public void setKorisnici (ObservableList < Korisnik > korisnici) {
        this.korisnici = korisnici;
    }

    public Korisnik getTrenutniKorisnik () {
        return trenutniKorisnik.get();
    }

    public SimpleObjectProperty<Korisnik> trenutniKorisnikProperty () {
        return trenutniKorisnik;
    }

    public void setTrenutniKorisnik (Korisnik trenutniKorisnik){
        azurirajBazu();
        this.trenutniKorisnik.set(trenutniKorisnik);
    }

    public void setTrenutniKorisnik (int i){
        this.trenutniKorisnik.set(korisnici.get(i));
    }

    private void regenerisiBazu () {
        Scanner ulaz = null;
        try {
            ulaz = new Scanner(new FileInputStream("korisnici.db.sql"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String upitSql = "";
        while (ulaz.hasNext()) {
            upitSql += ulaz.nextLine();
            if (upitSql.charAt(upitSql.length() - 1) == ';') {
                try {
                    Statement stmt = conn.createStatement();
                    stmt.execute(upitSql);
                    upitSql = "";
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        ulaz.close();
    }

    public void diskonektuj() {
        if(this!=null) {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }



    public void azurirajBazu() //može i preko batcha ili običnog stringbuildera da se odjednom sve izvrši, al kako se ne traži brzina već prolazak autotestova, to nećemo raditi
    {
        Statement stmt = null;
        try {
            stmt = conn.createStatement();
            stmt.execute("DELETE FROM korisnik");
            stmt.close();
            StringBuilder str = new StringBuilder();

            str.append("INSERT INTO korisnik VALUES\n");
            int noviId=1;
            for(Korisnik k : korisnici)
            {
                str.append("("+noviId+",\"").append(k.getIme()).append("\",").append("\"").append(k.getPrezime()).append("\",")
                .append("\"").append(k.getEmail()).append("\",").append("\"").append(k.getUsername()).append("\",").append("\"").append(k.getPassword()).append("\",\"").append(k.getPutanjaAvatar()).append("\"").append("),\n");
                noviId++;
            }

            str = new StringBuilder(str.substring(0, str.length() - 2));
            str.append(";");

            try {
                stmt = conn.createStatement();
                stmt.executeUpdate(str.toString());
                stmt.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }



    }

    public int getIdUBazi() {
        try{
            dajIdUBazi=conn.prepareStatement("SELECT Max(id)+1 FROM korisnik");
            ResultSet rs = dajIdUBazi.executeQuery();
                return rs.getInt(1);
        } catch (SQLException e) {
            e.printStackTrace();
            throw new IllegalArgumentException("ne valja uzimanje ID iz baze");
        }
    }

    public void dodajKorisnika(Korisnik k)
    {
        try{
            int noviId=getIdUBazi();
            dodajKorisnikaUpit=conn.prepareStatement("INSERT INTO korisnik VALUES(?,?,?,?,?,?)");
            dodajKorisnikaUpit.setInt(1,noviId);
            dodajKorisnikaUpit.setString(2, k.getIme());
            dodajKorisnikaUpit.setString(3, k.getPrezime());
            dodajKorisnikaUpit.setString(4, k.getEmail());
            dodajKorisnikaUpit.setString(5, k.getUsername());
            dodajKorisnikaUpit.setString(6,k.getPassword());
            dodajKorisnikaUpit.executeUpdate();
        } catch (SQLException e) {
            System.out.println("NEŠTO OVDJE NIJE DOBRO");
            e.printStackTrace();
        }
    }


    public void zapisiDatoteku(File file) {


        BufferedWriter writer = null;
        if(file!=null) {
            try {
                dajIdKorisnikaUpit = conn.prepareStatement("SELECT id from korisnik where ime=? AND prezime=? AND email=? AND username=? AND password=?");
                writer = new BufferedWriter(new FileWriter(file));
                StringBuilder stringB = new StringBuilder();
                for (Korisnik k : korisnici) {
                    int id = -1;
                    dajIdKorisnikaUpit.setString(1, k.getIme());
                    dajIdKorisnikaUpit.setString(2, k.getPrezime());
                    dajIdKorisnikaUpit.setString(3, k.getEmail());
                    dajIdKorisnikaUpit.setString(4, k.getUsername());
                    dajIdKorisnikaUpit.setString(5, k.getPassword());
                    ResultSet rs = dajIdKorisnikaUpit.executeQuery();
                    if (rs.next()) id = rs.getInt(1);
                    if (id == -1) throw new IllegalArgumentException("NE VALJA MAJOR NESTO");
                    stringB.append(k.getUsername()).append(":").append(k.getPassword()).append(":").append(id).append(":").append(id).append(":").append(k.getIme()).append(" ").append(k.getPrezime()).append("::\n");
                }
                writer.write(stringB.toString());
                writer.close();
            } catch (IOException | SQLException e) {
                e.printStackTrace();

            }
        }
    }

    public Connection getConn() {
        return this.conn;
    }
}

