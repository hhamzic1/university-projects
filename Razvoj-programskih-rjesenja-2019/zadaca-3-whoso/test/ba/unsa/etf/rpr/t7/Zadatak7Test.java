package ba.unsa.etf.rpr.t7;

import org.junit.jupiter.api.Test;
import org.testfx.api.FxRobot;

import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class Zadatak7Test {
    @Test
    void testBazaDirekt() {
        // Provjeravamo direktno u bazi da li postoji kolona slika
        File dbfile = new File("baza.db");
        dbfile.delete();

        {
            // Konstruktor klase KorisniciModel će kreirati bazu
            KorisniciModel model = new KorisniciModel();
            model.diskonektuj();
            // I odmah će se diskonektovati jer prestaje da postoji
        }

        Connection conn;
        try {
            conn = DriverManager.getConnection("jdbc:sqlite:korisnici.db");
            try {
                PreparedStatement korisnikUpit = conn.prepareStatement("SELECT slika FROM korisnik");
                korisnikUpit.execute();
                conn.close();
            } catch (SQLException e) {
                fail("Ne postoji kolona slika");
            }
        } catch (SQLException e) {
            fail("Datoteka sa bazom ne postoji ili je nedostupna");
        }
    }

    @Test
    void testKlasaKorisnik() {
        // Koristimo stari konstruktor
        Korisnik k = new Korisnik("ime", "prezime", "email", "username", "password");
        // Možete dodati još jedan konstruktor po želji, ali sljedeće metode trebaju postojati
        k.setSlika("https://zamger.etf.unsa.ba/static/images/etf-50x50.png");
        assertEquals("https://zamger.etf.unsa.ba/static/images/etf-50x50.png", k.getSlika());
    }

    @Test
    void testKorisnikModel() {
        // Provjeravamo da li će podatak u slici ostati trajno upisan u bazi (perzistirati)
        {
            KorisniciModel model = new KorisniciModel();
            model.napuni();
            Korisnik prvi = model.getKorisnici().get(0);
            Korisnik drugi = model.getKorisnici().get(1);
            model.setTrenutniKorisnik(prvi);
            prvi.setSlika("https://zamger.etf.unsa.ba/static/images/etf-50x50.png");
            // Promjena trenutnog korisnika bi trebala izvršiti ažuriranje baze
            model.setTrenutniKorisnik(drugi);
            model.diskonektuj();
        }
        {
            KorisniciModel model = new KorisniciModel();
            model.napuni();
            Korisnik prvi = model.getKorisnici().get(0);
            assertEquals("https://zamger.etf.unsa.ba/static/images/etf-50x50.png", prvi.getSlika());
        }
    }
}
