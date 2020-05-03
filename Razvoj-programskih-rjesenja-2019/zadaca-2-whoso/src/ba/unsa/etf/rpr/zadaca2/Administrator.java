package ba.unsa.etf.rpr.zadaca2;

import javafx.beans.property.SimpleBooleanProperty;

public class Administrator extends Korisnik { //nasljeđuje klasu Korisnik, i ima overajdovan checkPassword
    public Administrator(String ime, String prezime, String email, String username, String password) {
        super(ime, prezime, email, username, password);
    }

    @Override
    public boolean checkPassword(){ //overajd zato jer administrator mora sadrzavati i neki specijalan karakter u šifri
        return this.getPassword()!=null && this.getPassword().length()>=4
                && this.getPassword().matches(".*\\p{Ll}+.*") //bilo koji znak lower
                && this.getPassword().matches(".*\\p{Lu}+.*") //bilo koji znak upper
                && this.getPassword().matches(".*\\d+.*")   //broj
                && !this.getPassword().matches("[a-zA-Z0-9 ]*");    //ako ne sadrži specijalan znak, bit će true
    }
}
