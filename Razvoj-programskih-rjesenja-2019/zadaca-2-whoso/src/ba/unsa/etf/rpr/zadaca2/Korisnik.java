package ba.unsa.etf.rpr.zadaca2;

import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;

public class Korisnik { //korisnik ima sve property-e
    private SimpleStringProperty ime, prezime, email, username, password;
    private SimpleIntegerProperty godinaRodjenja;
    private SimpleBooleanProperty jelAdmin=new SimpleBooleanProperty(false);

    public Korisnik(String ime, String prezime, String email, String username, String password) {
        this.ime = new SimpleStringProperty(ime);
        this.prezime = new SimpleStringProperty(prezime);
        this.email = new SimpleStringProperty(email);
        this.username = new SimpleStringProperty(username);
        this.password = new SimpleStringProperty(password);
        this.godinaRodjenja = new SimpleIntegerProperty(2000);
        if(this instanceof Administrator)
        {
            jelAdmin.setValue(true);
        }
    }

    @Override
    public String toString() {
        return prezime.get() + " " + ime.get();
    } //toString kako bi se mogao ispisati na ListView

    public String getIme() {
        return ime.get();
    }

    public SimpleStringProperty imeProperty() {
        return ime;
    }

    public SimpleIntegerProperty godinaRodjenjaProperty() { return godinaRodjenja; }

    public void setGodinaRodjenja(int grodjenja){
        this.godinaRodjenja.set(grodjenja);
    }
    public int getGodinaRodjenja(){ return godinaRodjenja.getValue(); }

    public void setIme(String ime) {
        this.ime.set(ime);
    }

    public SimpleBooleanProperty jelAdminProperty(){ return this.jelAdmin;}

    public String getPrezime() {
        return prezime.get();
    }

    public SimpleStringProperty prezimeProperty() {
        return prezime;
    }

    public void setPrezime(String prezime) {
        this.prezime.set(prezime);
    }

    public String getEmail() {
        return email.get();
    }

    public SimpleStringProperty emailProperty() {
        return email;
    }

    public void setEmail(String email) {
        this.email.set(email);
    }

    public String getUsername() {
        return username.get();
    }

    public SimpleStringProperty usernameProperty() {
        return username;
    }

    public void setUsername(String username) {
        this.username.set(username);
    }

    public String getPassword() {
        return password.get();
    }

    public SimpleStringProperty passwordProperty() {
        return password;
    }

    public void setPassword(String password) {
        this.password.set(password);
    }

    @Override
    public boolean equals(Object obj) { //overajd equalsa kako bi provjerili da li su dva korisnika jednaka
        if(obj instanceof Korisnik) {
            if(((Korisnik) obj).getEmail().equals(this.getEmail()) && ((Korisnik) obj).getUsername().equals(this.getUsername()) && ((Korisnik) obj).getIme().equals(this.getIme())
            && ((Korisnik) obj).getPrezime().equals(this.getPrezime()) && ((Korisnik) obj).getPassword().equals(this.getPassword())){
                return true;
            }
        }
        return false;
    }

    public boolean checkPassword() //provjeri password za obicnog korisnika(mora sadrzavati veliko i malo slovo kao i broj)
    {
        return this.getPassword() != null && this.getPassword().length() >= 3
            && this.getPassword().matches(".*\\p{Ll}+.*")
            && this.getPassword().matches(".*\\p{Lu}+.*")
            && this.getPassword().matches(".*\\d+.*");
    }
}
