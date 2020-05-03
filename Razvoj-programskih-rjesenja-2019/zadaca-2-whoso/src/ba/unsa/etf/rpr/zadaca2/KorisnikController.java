package ba.unsa.etf.rpr.zadaca2;

import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.security.SecureRandom;
import java.util.Random;
import java.util.stream.Stream;

public class KorisnikController {
    public TextField fldIme;
    public TextField fldPrezime;
    public TextField fldEmail;
    public TextField fldUsername;
    public ListView<Korisnik> listKorisnici;
    public PasswordField fldPassword;
    public PasswordField fldPasswordRepeat;
    public Button btnDodaj;
    public Button btnKraj;
    public Button btnObrisi;
    public Button btnGenerisi;
    public CheckBox cbAdmin;
    public Slider sliderGodinaRodjenja;


    private KorisniciModel model;

    public KorisnikController(KorisniciModel model) {
        this.model = model;
    }

    @FXML
    public void initialize() {
        listKorisnici.setItems(model.getKorisnici());
        listKorisnici.getSelectionModel().selectedItemProperty().addListener((obs, oldKorisnik, newKorisnik) -> {
            model.setTrenutniKorisnik(newKorisnik);
            if(newKorisnik instanceof Administrator) cbAdmin.setSelected(true);   //ako je nova osoba admin, čekiraj joj box
            else{cbAdmin.setSelected(false);}   //a ako nije admin ostavi je ko običnog smrtnika :P
            listKorisnici.refresh();
         });

        model.trenutniKorisnikProperty().addListener((obs, oldKorisnik, newKorisnik) -> { //unbind sa prethodnog trenutnog korisnika
            if (oldKorisnik != null) {
                fldIme.textProperty().unbindBidirectional(oldKorisnik.imeProperty() ); //ovi property's će se mijenjati kao jedan odnosno kako se mijenja
                fldPrezime.textProperty().unbindBidirectional(oldKorisnik.prezimeProperty() );//textfield tako će se i mijenjati ime, prezime, email trenutnog korisnika itd
                fldEmail.textProperty().unbindBidirectional(oldKorisnik.emailProperty() );
                fldUsername.textProperty().unbindBidirectional(oldKorisnik.usernameProperty() );
                fldPassword.textProperty().unbindBidirectional(oldKorisnik.passwordProperty() );
                sliderGodinaRodjenja.valueProperty().unbindBidirectional(oldKorisnik.godinaRodjenjaProperty());
            }

            if (newKorisnik == null) {
                fldIme.setText("");
                fldPrezime.setText("");
                fldEmail.setText("");
                fldUsername.setText("");
                fldPassword.setText("");
                fldPasswordRepeat.setText("");
                sliderGodinaRodjenja.setValue(2000);
            }
            else {      //bind na novog trenutnog korisnika
                fldIme.textProperty().bindBidirectional( newKorisnik.imeProperty() );
                fldPrezime.textProperty().bindBidirectional( newKorisnik.prezimeProperty() );
                fldEmail.textProperty().bindBidirectional( newKorisnik.emailProperty() );
                fldUsername.textProperty().bindBidirectional( newKorisnik.usernameProperty() );
                fldPassword.textProperty().bindBidirectional( newKorisnik.passwordProperty() );
                fldPasswordRepeat.setText(fldPassword.getText());
                sliderGodinaRodjenja.valueProperty().bindBidirectional(newKorisnik.godinaRodjenjaProperty());
            }
        });

        cbAdmin.selectedProperty().addListener(new ChangeListener<Boolean>() { //prisluškujemo čekbox
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) {
                if(model.getTrenutniKorisnik()==null) return; //ako niko nije selektovan da se ne krahira
                if(!oldValue){ //ako nije bio čekiran, pa se čekira
                    if(!(model.getTrenutniKorisnik() instanceof Administrator)) {   //i ako ta osoba nije administrator, castaj je u admina
                        int indeks = listKorisnici.getSelectionModel().getSelectedIndex();
                        Korisnik temp = new Administrator(model.getTrenutniKorisnik().getIme(), model.getTrenutniKorisnik().getPrezime(), model.getTrenutniKorisnik().getEmail(), model.getTrenutniKorisnik().getUsername(), model.getTrenutniKorisnik().getPassword());
                        temp.setGodinaRodjenja(model.getTrenutniKorisnik().getGodinaRodjenja()); //izbacujemo pa ubacujemo u listu, ne može drugačije
                        model.getKorisnici().remove(indeks);
                        model.getKorisnici().add(indeks, temp);
                        listKorisnici.getSelectionModel().select(indeks);
                        return;
                    }
                }
                if(model.getTrenutniKorisnik() instanceof Administrator) {  //ako je trenutna osoba administrator
                    if (!newValue) { //i unčekamo joj box, moramo je castati u običnog korisnika
                        Korisnik temp = new Korisnik(model.getTrenutniKorisnik().getIme(), model.getTrenutniKorisnik().getPrezime(), model.getTrenutniKorisnik().getEmail(), model.getTrenutniKorisnik().getUsername(), model.getTrenutniKorisnik().getPassword());
                        temp.setGodinaRodjenja(model.getTrenutniKorisnik().getGodinaRodjenja());
                        int indeks = listKorisnici.getSelectionModel().getSelectedIndex(); //izbacujemo iz liste i ponovo ubacujemo, ne može drugačije
                        model.getKorisnici().remove(indeks);
                        model.getKorisnici().add(indeks, temp);
                        listKorisnici.getSelectionModel().select(indeks);
                    }
                }
            }
        });


        fldIme.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && imePrezimeCheck(newIme)) { //ako je polje uredu
                fldIme.getStyleClass().removeAll("poljeNijeIspravno");
                fldIme.getStyleClass().add("poljeIspravno");    //oboji ga u zeleno
            } else {
                fldIme.getStyleClass().removeAll("poljeIspravno"); //ako nije
                fldIme.getStyleClass().add("poljeNijeIspravno");    //oboji ga u crveno preko ovog add i remove styleclass uklanjamo i stavljamo
            } //određeni css
        });

        fldPrezime.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && imePrezimeCheck(newIme)) {
                fldPrezime.getStyleClass().removeAll("poljeNijeIspravno");
                fldPrezime.getStyleClass().add("poljeIspravno");
            } else {
                fldPrezime.getStyleClass().removeAll("poljeIspravno");
                fldPrezime.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldEmail.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && emailCheck(newIme)) {
                fldEmail.getStyleClass().removeAll("poljeNijeIspravno");
                fldEmail.getStyleClass().add("poljeIspravno");
            } else {
                fldEmail.getStyleClass().removeAll("poljeIspravno");
                fldEmail.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldUsername.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && usernameCheck(newIme)) {
                fldUsername.getStyleClass().removeAll("poljeNijeIspravno");
                fldUsername.getStyleClass().add("poljeIspravno");
            } else {
                fldUsername.getStyleClass().removeAll("poljeIspravno");
                fldUsername.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldPassword.textProperty().addListener((obs, oldIme, newIme) -> {   //password i password repeat su povezani
            Korisnik k;
            if(model.getTrenutniKorisnik() instanceof Administrator){ //ovo radimo jer imamo razlicite checkPassworde koje moramo pozvat u zavisnosti od trenutnog korisnika
                k = new Administrator("neko","treci", "etf@etf", "hehe", newIme);
            }
            else{k = new Korisnik("neko","treci", "etf@etf", "hehe", newIme);}
            if (k.checkPassword() && !newIme.isEmpty() && fldPasswordRepeat.getText().equals(fldPassword.getText())) {
                fldPassword.getStyleClass().removeAll("poljeNijeIspravno");
                fldPassword.getStyleClass().add("poljeIspravno");
                fldPasswordRepeat.getStyleClass().removeAll("poljeNijeIspravno");
                fldPasswordRepeat.getStyleClass().add("poljeIspravno");
            } else {
                fldPassword.getStyleClass().removeAll("poljeIspravno");
                fldPassword.getStyleClass().add("poljeNijeIspravno");
                fldPassword.getStyleClass().removeAll("poljeIspravno");
                fldPassword.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldPasswordRepeat.textProperty().addListener((obs, oldIme, newIme) -> {
            Korisnik k;
            if(model.getTrenutniKorisnik() instanceof Administrator){
                k = new Administrator("neko","treci", "etf@etf", "hehe", newIme);
            }
             else{k = new Korisnik("neko","treci", "etf@etf", "hehe", newIme);}
            if (k.checkPassword() && !newIme.isEmpty() && fldPasswordRepeat.getText().equals(fldPassword.getText())) {//ako repeatPassword ne odgovara trenutnom passwordu, zacrvene se oboje
                fldPasswordRepeat.getStyleClass().removeAll("poljeNijeIspravno");
                fldPasswordRepeat.getStyleClass().add("poljeIspravno");
                fldPassword.getStyleClass().removeAll("poljeNijeIspravno");
                fldPassword.getStyleClass().add("poljeIspravno");
            } else {
                fldPassword.getStyleClass().removeAll("poljeIspravno");
                fldPassword.getStyleClass().add("poljeNijeIspravno");
                fldPasswordRepeat.getStyleClass().removeAll("poljeIspravno");
                fldPasswordRepeat.getStyleClass().add("poljeNijeIspravno");
            }
        });


        btnDodaj.setText("Dodaj");
        btnObrisi.setText("Obriši");
        btnKraj.setText("Kraj");
        btnDodaj.getStyleClass().add("btnDodajSlika");  //dodajemo slike
        btnKraj.getStyleClass().add("btnKrajSlika");
        btnObrisi.getStyleClass().add("btnObrisiSlika");

    }

    public boolean imePrezimeCheck(String ime)
    {
        if(ime.length()<3) return false;
        return ime.matches("^[\\p{L}\\s’\\-ČčĆćŽžŠšĐđ]+$");  //regex
    }

    public boolean emailCheck(String email)
    {
        return email.matches("^[a-zA-Z0-9_!#$%&’*+/=?`{|}~^.-]+@[a-zA-Z0-9.-]+$");
    }

    public boolean usernameCheck(String user)
    {
        if(user.length()>16) return false;
        return user.matches("^[a-zA-Z_$][a-zA-Z_$0-9]*$");
    }



    public void dodajAction(ActionEvent actionEvent) { //dodaje novog korisnika na kraj liste, i selektuje ga odnosno on postaje trenutni korisnik
        model.getKorisnici().add(new Korisnik("", "", "", "", ""));
        listKorisnici.getSelectionModel().selectLast();
    }

    public void obrisiAction(ActionEvent event) //briše selektovanog korisnika iz liste korisnika
    {
        if(model.getKorisnici().size()==0) {
            return;
        }
        int temp = listKorisnici.getSelectionModel().getSelectedIndex();
        model.getKorisnici().remove(temp);
        listKorisnici.getSelectionModel().select(temp); //sljedeceg koji zauzima njegov indeks selektuje
    }

    public static String generatePassword() {  //Generiše random password
        SecureRandom random = new SecureRandom();
         String ALPHA_CAPS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
         String ALPHA = "abcdefghijklmnopqrstuvwxyz";
        String NUMERIC = "0123456789";
         String SPECIAL_CHARS = "!@#$%^&*_=+-/";
        String result = "";

        int index = random.nextInt(ALPHA.length());
        result += ALPHA.charAt(index);
        index=random.nextInt(ALPHA_CAPS.length());
        result+=ALPHA_CAPS.charAt(index);
        index=random.nextInt(NUMERIC.length());
        result+=NUMERIC.charAt(index);
        index=random.nextInt(SPECIAL_CHARS.length());
        result+=SPECIAL_CHARS.charAt(index);

        for(int i=0; i<4; i++)
        {
            Random r = new Random();
            int ind= r.nextInt((3 - 0) + 1);
            switch(ind) {
                case 0: {
                    int br = random.nextInt(ALPHA.length());
                    result += ALPHA.charAt(br);
                    break;
                }
                case 1: {
                    int br = random.nextInt(ALPHA_CAPS.length());
                    result += ALPHA_CAPS.charAt(br);
                    break;
                }
                case 2: {
                    int br = random.nextInt(NUMERIC.length());
                    result += NUMERIC.charAt(br);
                    break;
                }
                case 3: {
                    int br = random.nextInt(SPECIAL_CHARS.length());
                    result += SPECIAL_CHARS.charAt(br);
                    break;
                }
            }
        }
        return result;
    }


    public void generisiAction(ActionEvent event) //generiše username npr hhamzic
    {
        Korisnik k = model.getTrenutniKorisnik();
        String tempIme=k.getIme().toLowerCase().replace('ć','c').replace('š','s').replace('č','c').replace('đ','d').replace('ž','z');;
        String tempPrezime=k.getPrezime().toLowerCase().replace('ć','c').replace('š','s').replace('č','c').replace('đ','d').replace('ž','z');
        String s = "";
        if(tempIme.isEmpty()) //kad je novi korisnik prazan ne smijemo uraditi charAt(indeks), bacit će exception!
        {
            model.getTrenutniKorisnik().setUsername(s);
        }
        else {
            s=s+tempIme.charAt(0)+tempPrezime;
        }
        String pass=generatePassword(); //generišemo random password
        model.getTrenutniKorisnik().setUsername(s);
        model.getTrenutniKorisnik().setPassword(pass);
        fldPasswordRepeat.setText(model.getTrenutniKorisnik().getPassword());
        Alert alert = new Alert(Alert.AlertType.INFORMATION);   //iskače information box koji nam prikazuje password
        alert.setTitle("Informacije");
        alert.setHeaderText("Vaš password je:");
        alert.setContentText(pass);
        alert.showAndWait();
    }

    public void krajAction(ActionEvent actionEvent) {
        System.exit(0);
    }
}
