package ba.unsa.etf.rpr.t7;

import javafx.beans.property.SimpleStringProperty;
import javafx.scene.image.Image;

public class Korisnik {
    private SimpleStringProperty ime, prezime, email, username, password;
    private Image avatar;
    private String putanjaAvatar;

    public Korisnik(String ime, String prezime, String email, String username, String password) {
        this.ime = new SimpleStringProperty(ime);
        this.prezime = new SimpleStringProperty(prezime);
        this.email = new SimpleStringProperty(email);
        this.username = new SimpleStringProperty(username);
        this.password = new SimpleStringProperty(password);
    }

    public Image getAvatar() {
        return avatar;
    }

    public String getPutanjaAvatar() {
        return putanjaAvatar;
    }

    public void setPutanjaAvatar(String putanjaAvatar) {
        this.putanjaAvatar = putanjaAvatar;
    }

    public void setAvatar(Image avatar) {
        this.avatar = avatar;
    }

    @Override
    public String toString() {
        return prezime.get() + " " + ime.get();
    }

    public String getIme() {
        return ime.get();
    }

    public SimpleStringProperty imeProperty() {
        return ime;
    }

    public void setIme(String ime) {
        this.ime.set(ime);
    }

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


    public void setSlika(String s) {
        this.setPutanjaAvatar(s);
    }

    public String getSlika() {
        return getPutanjaAvatar();
    }
}
