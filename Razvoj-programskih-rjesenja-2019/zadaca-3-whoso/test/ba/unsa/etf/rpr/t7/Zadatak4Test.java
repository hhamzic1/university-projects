package ba.unsa.etf.rpr.t7;

import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

public class Zadatak4Test {

    @Test
    void testZapisiDatoteku() {
        // Brišemo podatke koje su promijenili raniji testovi
        File dbfile = new File("korisnici.db");
        dbfile.delete();

        // Default podaci
        KorisniciModel model = new KorisniciModel();
        model.napuni();

        File file = new File("test.txt");
        model.zapisiDatoteku(file);

        try {
            Scanner scanner = new Scanner(file);
            assertEquals("vedranlj:test:1:1:Vedran Ljubović::", scanner.nextLine().trim());
            assertEquals("amrad:test:2:2:Amra Delić::", scanner.nextLine().trim());
            assertEquals("tariks:test:3:3:Tarik Sijerčić::", scanner.nextLine().trim());
            assertEquals("rijadf:test:4:4:Rijad Fejzić::", scanner.nextLine().trim());
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }


    }

    @Test
    void testNemojZapisatiDatoteku() {
        // Default podaci
        KorisniciModel model = new KorisniciModel();
        model.napuni();

        // Metoda ne smije da se krahira ako se pošalje null datoteka
        // (tj. ako je korisnik na dijalogu kliknuo Cancel)
        model.zapisiDatoteku(null);
    }
}
