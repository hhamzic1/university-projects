package ba.unsa.etf.rpr.t7;

import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.ResourceBundle;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(ApplicationExtension.class)
public class Zadatak7Test2 {
    KorisniciModel model;

    @Start
    public void start(Stage stage) throws Exception {
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
    void testSlika(FxRobot robot) {
        // Provjeravamo da li postoji dugme sa slikom
        Button imgKorisnik = robot.lookup("#imgKorisnik").queryAs(Button.class);
        assertNotNull(imgKorisnik);

        // Klikamo na dugme da vidimo hoće li se otvoriti dijalog
        robot.clickOn("#imgKorisnik");
        robot.lookup("Cancel").tryQuery().isPresent();
        robot.clickOn("Cancel");
    }
}