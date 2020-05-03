package ba.unsa.etf.rpr.t7;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import java.io.File;
import java.sql.*;
import java.util.ResourceBundle;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(ApplicationExtension.class)
public class Zadatak1Test {
    KorisniciModel model;

    @Start
    public void start (Stage stage) throws Exception {
        File dbfile = new File("korisnici.db");
        dbfile.delete();

        model = new KorisniciModel();
        model.napuni();
        KorisnikController ctrl = new KorisnikController(model);

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/korisnici.fxml"));
        loader.setResources(ResourceBundle.getBundle("Translation"));
        loader.setController(ctrl);
        Parent root = loader.load();
        stage.setTitle("Korisnici");
        stage.setScene(new Scene(root, USE_COMPUTED_SIZE, USE_COMPUTED_SIZE));
        stage.show();
        stage.toFront();
    }

    @Test
    void testBazaPostoji() {
        // Test koji zaobilazi Model klasu i direktno radi sa bazom
        File dbfile = new File("baza.db");
        dbfile.delete();

        {
            // Konstruktor klase KorisniciModel će kreirati bazu
            KorisniciModel model = new KorisniciModel();
            // I odmah će se diskonektovati jer prestaje da postoji
        }

        Connection conn;
        try {
            conn = DriverManager.getConnection("jdbc:sqlite:korisnici.db");
            try {
                PreparedStatement korisnikUpit = conn.prepareStatement("SELECT * FROM korisnik");
                korisnikUpit.execute();
                conn.close();
            } catch (SQLException e) {
                fail("Tabela korisnik ne postoji u bazi");
            }
        } catch (SQLException e) {
            fail("Datoteka sa bazom ne postoji ili je nedostupna");
        }

    }

    @Test
    void testBazaGui(FxRobot robot) {
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#fldIme").write("bbb");
        robot.clickOn("Fejzić Rijad");
        model.diskonektuj();
        Connection conn;
        try {
            conn = DriverManager.getConnection("jdbc:sqlite:korisnici.db");
            try {
                PreparedStatement nadmorskaUpit = conn.prepareStatement("SELECT ime FROM korisnik WHERE prezime='Sijerčić'");
                ResultSet rs = nadmorskaUpit.executeQuery();
                rs.next();
                String ime = rs.getString(1);
                assertEquals("Tarikbbb", ime);
                conn.close();
            } catch (SQLException e) {
                fail("Nije uspio upit na korisnika sa prezimenom 'Sijerčić'");
            }
        } catch (SQLException e) {
            fail("Datoteka sa bazom ne postoji ili je nedostupna");
        }

        model.diskonektuj();

    }


    @Test
    void testBazaModel(FxRobot robot) {
        // Provjera da li izmjena podatka u modelu ostaje trajno (perzistira)
        {
            KorisniciModel model = new KorisniciModel();
            model.napuni();
            Korisnik prvi = model.getKorisnici().get(0);
            Korisnik drugi = model.getKorisnici().get(1);
            model.setTrenutniKorisnik(prvi);
            prvi.setIme("Test");
            // Promjena trenutnog korisnika bi trebala izvršiti ažuriranje baze
            model.setTrenutniKorisnik(drugi);
        }
        {
            KorisniciModel model = new KorisniciModel();
            model.napuni();
            Korisnik prvi = model.getKorisnici().get(0);
            assertEquals("Test", prvi.getIme());
        }
        model.diskonektuj();
    }
}
