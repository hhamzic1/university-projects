package ba.unsa.etf.rpr.t7;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.stage.Stage;
import net.sf.jasperreports.engine.JRException;

import java.io.File;
import java.io.IOException;
import java.util.Locale;
import java.util.Optional;
import java.util.ResourceBundle;

public class KorisnikController {
    public TextField fldIme;
    public TextField fldPrezime;
    public TextField fldEmail;
    public TextField fldUsername;
    public ListView<Korisnik> listKorisnici;
    public PasswordField fldPassword;
    public Button btnObrisi;
    public Button btnKraj;
    public MenuItem menuExit;
    public MenuItem menuSave;
    public MenuItem menuAbout;
    private KorisniciModel model;
    public MenuItem printMenu;
    public MenuItem menuEnglish;
    public MenuItem menuBosnian;
    public ResourceBundle bndl;
    public Label lblIme;
    public Label lblPrezz;
    public Label lblemail;
    public Label lblusername;
    public Label lblpass;
    public MenuItem menuHelp;
    public MenuItem menuLanguage;
    public ImageView avatarView;
    public Button imgKorisnik;
    int idUBazi;

    public KorisnikController(KorisniciModel model) {
        this.model = model;
    }

    @FXML
    public void initialize() {

        menuExit.setAccelerator(
                new KeyCodeCombination(KeyCode.E, KeyCombination.CONTROL_DOWN)
        );

        menuExit.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.exit(0);
            }
        });


        printMenu.setAccelerator(
                new KeyCodeCombination(KeyCode.P, KeyCombination.CONTROL_DOWN)
        );
        printMenu.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                try {
                    new PrintReport().showReport(model.getConn());
                } catch (JRException e1) {
                    e1.printStackTrace();
                }
            }
        });

        menuEnglish.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                Locale.setDefault(new Locale("en", "US"));
                restartJezik();
            }
        });

        menuBosnian.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                Locale.setDefault(new Locale("bs", "BA"));
                restartJezik();
            }
        });





        menuSave.setAccelerator(
                new KeyCodeCombination(KeyCode.S, KeyCombination.CONTROL_DOWN)
        );

        menuSave.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                TextInputDialog dialog = new TextInputDialog("sample.txt");
                dialog.setTitle("Odabir datoteke");
                dialog.setHeaderText("Molim odaberite ime datoteke");
                dialog.setContentText("Unesite ime datoteke :");


                Optional<String> result = dialog.showAndWait();
                if (result.isPresent()){
                    String nazivF = result.get();
                    File dat = new File(nazivF);
                    model.zapisiDatoteku(dat);
                }
            }
        });





        menuAbout.setAccelerator(
                new KeyCodeCombination(KeyCode.I, KeyCombination.CONTROL_DOWN)
        );
        menuAbout.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                    FXMLLoader ldr = new FXMLLoader(getClass().getResource("/fxml/about.fxml")); //loadaj fxml fajl
                    AboutController gc = new AboutController();
                    ldr.setResources(ResourceBundle.getBundle("Translation"));
                    ldr.setController(gc);    //setupaj određeni kontroler koji će ga kontrolisati
                Parent p = null;
                try {
                    p = ldr.load();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                Scene s = new Scene(p);
                    Stage prozor = new Stage();
                    prozor.setTitle("Grad");
                    prozor.setScene(s);
                    prozor.setResizable(false);
                    prozor.show();

            }
        });


        listKorisnici.setItems(model.getKorisnici());
        listKorisnici.getSelectionModel().selectedItemProperty().addListener((obs, oldKorisnik, newKorisnik) -> {
            model.setTrenutniKorisnik(newKorisnik);
            listKorisnici.refresh();
         });

        model.trenutniKorisnikProperty().addListener((obs, oldKorisnik, newKorisnik) -> {

            if (oldKorisnik != null) {
                postaviAvatar();
                fldIme.textProperty().unbindBidirectional(oldKorisnik.imeProperty() );
                fldPrezime.textProperty().unbindBidirectional(oldKorisnik.prezimeProperty() );
                fldEmail.textProperty().unbindBidirectional(oldKorisnik.emailProperty() );
                fldUsername.textProperty().unbindBidirectional(oldKorisnik.usernameProperty() );
                fldPassword.textProperty().unbindBidirectional(oldKorisnik.passwordProperty() );
            }
            if (newKorisnik == null) {
                postaviAvatar();
                fldIme.setText("");
                fldPrezime.setText("");
                fldEmail.setText("");
                fldUsername.setText("");
                fldPassword.setText("");
            }
            else {
                postaviAvatar();
                fldIme.textProperty().bindBidirectional( newKorisnik.imeProperty() );
                fldPrezime.textProperty().bindBidirectional( newKorisnik.prezimeProperty() );
                fldEmail.textProperty().bindBidirectional( newKorisnik.emailProperty() );
                fldUsername.textProperty().bindBidirectional( newKorisnik.usernameProperty() );
                fldPassword.textProperty().bindBidirectional( newKorisnik.passwordProperty() );
            }
        });

        fldIme.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty()) {
                fldIme.getStyleClass().removeAll("poljeNijeIspravno");
                fldIme.getStyleClass().add("poljeIspravno");
            } else {
                fldIme.getStyleClass().removeAll("poljeIspravno");
                fldIme.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldPrezime.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty()) {
                fldPrezime.getStyleClass().removeAll("poljeNijeIspravno");
                fldPrezime.getStyleClass().add("poljeIspravno");
            } else {
                fldPrezime.getStyleClass().removeAll("poljeIspravno");
                fldPrezime.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldEmail.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty()) {
                fldEmail.getStyleClass().removeAll("poljeNijeIspravno");
                fldEmail.getStyleClass().add("poljeIspravno");
            } else {
                fldEmail.getStyleClass().removeAll("poljeIspravno");
                fldEmail.getStyleClass().add("poljeNijeIspravno");
            }
        });


        fldUsername.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty()) {
                fldUsername.getStyleClass().removeAll("poljeNijeIspravno");
                fldUsername.getStyleClass().add("poljeIspravno");
            } else {
                fldUsername.getStyleClass().removeAll("poljeIspravno");
                fldUsername.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldPassword.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty()) {
                fldPassword.getStyleClass().removeAll("poljeNijeIspravno");
                fldPassword.getStyleClass().add("poljeIspravno");
            } else {
                fldPassword.getStyleClass().removeAll("poljeIspravno");
                fldPassword.getStyleClass().add("poljeNijeIspravno");
            }
        });



    }

    public void dodajAction(ActionEvent actionEvent) {
        Korisnik k = new Korisnik("", "", "", "", "");
        k.setPutanjaAvatar("file:resources/slike/face-smile.png");
        Image img = new Image(k.getPutanjaAvatar());
        k.setAvatar(img);
        model.getKorisnici().add(k);
        listKorisnici.getSelectionModel().selectLast();
    }


    public void obrisiAction(ActionEvent event){
        if(listKorisnici.getSelectionModel().getSelectedItem()!=null) {
            int ind = listKorisnici.getSelectionModel().getSelectedIndex();
            model.getKorisnici().remove(listKorisnici.getSelectionModel().getSelectedIndex());
            model.azurirajBazu();
            listKorisnici.setItems(model.getKorisnici());
            listKorisnici.getSelectionModel().select(ind);
            listKorisnici.refresh();
        }
    }

    public void krajAction(ActionEvent actionEvent) {
        System.exit(0);
    }

    public void aboutAction(ActionEvent event){
        try {
            ResourceBundle bundle = ResourceBundle.getBundle("Translation");
            FXMLLoader ldr = new FXMLLoader(getClass().getResource("/fxml/about.fxml"),bundle); //loadaj fxml fajl
            AboutController gc = new AboutController();
            ldr.setController(gc);    //setupaj određeni kontroler koji će ga kontrolisati
            Parent p = ldr.load();
            Scene s = new Scene(p);
            Stage prozor = new Stage();
            prozor.setTitle("Grad");
            prozor.setScene(s);
            prozor.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void postaviAvatar(){
        Image img = new Image(model.getTrenutniKorisnik().getPutanjaAvatar());
        ImageView imVju = new ImageView();
        imVju.setFitWidth(128);
        imVju.setFitHeight(128);
        imVju.setImage(img);
        imgKorisnik.setGraphic(imVju);
    }


    public void btnAvatarAction(ActionEvent event){
        Parent p = null;
        try {
            ResourceBundle bundle = ResourceBundle.getBundle("Translation");
            FXMLLoader ldr = new FXMLLoader(getClass().getResource("/fxml/pretragav2.fxml"), bundle);
            ldr.setResources(ResourceBundle.getBundle("Translation"));
            PretragaController pc = new PretragaController();
            ldr.setController(pc);
            p = ldr.load();
            Scene s = new Scene(p);
            Stage prozor = new Stage();
            prozor.setTitle("Pretraga");
            prozor.setScene(s);
            prozor.show();
            prozor.setOnHiding(ev->{
                if(pc.isOkPritisnuto()) {
                    if (pc.getPutanjaSlike() != null) {
                        model.getTrenutniKorisnik().setPutanjaAvatar(pc.getPutanjaSlike());
                        postaviAvatar();
                    }
                }
            });


        } catch (IOException e) {
            e.printStackTrace();
        }
    }



}
