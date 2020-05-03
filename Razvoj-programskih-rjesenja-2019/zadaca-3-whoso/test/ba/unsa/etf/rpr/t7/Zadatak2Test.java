package ba.unsa.etf.rpr.t7;

import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import java.io.File;
import java.util.ResourceBundle;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

@ExtendWith(ApplicationExtension.class)
public class Zadatak2Test {
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
    void imaLiDugme(FxRobot robot) {
        Button btnObrisi = robot.lookup("#btnObrisi").queryAs(Button.class);
        assertNotNull(btnObrisi);
       model.diskonektuj();
    }

    @Test
    void obrisiLista(FxRobot robot) {
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#btnObrisi");
        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = lista.getItems();
        String s = "";
        for(Korisnik k : korisniks)
            s += k;
        String expected = "Ljubović VedranDelić AmraFejzić Rijad";
        assertEquals(expected, s);
        model.diskonektuj();
    }

    @Test
    void obrisiModel(FxRobot robot) {
        robot.clickOn("Delić Amra");
        robot.clickOn("#btnObrisi");
        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = model.getKorisnici();
        String s = "";
        for(Korisnik k : korisniks)
            s += k;
        String expected = "Ljubović VedranSijerčić TarikFejzić Rijad";
        assertEquals(expected, s);
        model.diskonektuj();
    }

    @Test
    void obrisiIzaberi(FxRobot robot) {
        robot.clickOn("Delić Amra");
        robot.clickOn("#btnObrisi");
        robot.clickOn("Fejzić Rijad");
        TextField polje = robot.lookup("#fldIme").queryAs(TextField.class);
        assertEquals("Rijad", polje.getText());
        model.diskonektuj();
    }
}
