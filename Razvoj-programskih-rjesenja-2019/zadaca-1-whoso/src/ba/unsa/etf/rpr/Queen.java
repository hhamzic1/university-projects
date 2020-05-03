package ba.unsa.etf.rpr;

import java.util.Map;

public class Queen extends ChessPiece {
    public Queen(String pozicija, Color boja) {
        super(pozicija, boja);
    }

    public String getPosition() {
        return super.getPosition();
    }

    public Color getColor() {
        return super.getColor();
    }

    @Override
    public void move(String position) throws IllegalChessMoveException {
        Map<ChessPiece, Boolean> mapa = this.getPloca();
        String pos = position.toUpperCase();
        if(pos.isEmpty() || !Character.isLetter(pos.charAt(0)) || !Character.isDigit(pos.charAt(1))) throw new IllegalArgumentException();
        if(!jel_unutra(pos)) throw new IllegalArgumentException();

        /*Dama = Bishop + Rook pa je dijelimo na Bishop provjeru i Rook provjeru*/

        //Bishop dio
        int joffset = super.getPosition().charAt(0) - 64;
        int j=1;
        int k=1;
        for(int i=super.getPosition().charAt(1) - 48 + 1; i<20; i++) {
            int l1 = joffset + j + 64;
            char t1 = (char) l1;
            String temp1 = t1 + Integer.toString(i);
            if(jel_unutra(temp1) && this.imaFigura(temp1, super.getColor()) && !temp1.equals(pos)) break; //ako u smjeru provjere ima neka figura a ta pozicija
            if (jel_unutra(temp1) && temp1.equals(pos))              //nije ona na koju ide kraljica breaka se provjera u tom smjeru
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }
            j++;
            k++;
        }
        j=1;
        k=1;
        for(int i=super.getPosition().charAt(1) - 48 + 1; i<20; i++) {
            int l2 = joffset - j + 64;
            char t2 = (char) l2;
            String temp2 = t2 + Integer.toString(i - j - k);
            if(jel_unutra(temp2) && this.imaFigura(temp2,super.getColor()) && !temp2.equals(pos)) break; //ako u smjeru provjere ima neka figura a ta pozicija
            if (jel_unutra(temp2) && temp2.equals(pos))              //nije ona na koju ide kraljica breaka se provjera u tom smjeru
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }
            j++;
            k++;
        }

        j=1;
        k=1;
        for(int i=super.getPosition().charAt(1) - 48 + 1; i<20; i++) {
            int l1 = joffset - j + 64;
            char t1 = (char) l1;
            String temp1 = t1 + Integer.toString(i);
            if(jel_unutra(temp1) && this.imaFigura(temp1,super.getColor()) && !temp1.equals(pos)) break; //ako u smjeru provjere ima neka figura a ta pozicija
            if (jel_unutra(temp1) && temp1.equals(pos))              //nije ona na koju ide kraljica breaka se provjera u tom smjeru
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }
            j++;
            k++;
        }

        j=1;
        k=1;
        for(int i=super.getPosition().charAt(1) - 48 + 1; i<20; i++) {
            int l2= joffset + j + 64;
            char t2 = (char)l2;
            String temp2 =  t2 + Integer.toString(i-j-k);
            if(jel_unutra(temp2) && this.imaFigura(temp2,super.getColor()) && !temp2.equals(pos)) break; //ako u smjeru provjere ima neka figura iste boje a ta pozicija
            if (jel_unutra(temp2) && temp2.equals(pos))              //nije ona na koju ide kraljica breaka se provjera u tom smjeru
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }
            j++;
            k++;
        }

        //Rook dio
        int granicaZaJ=8;
        int ioffset = super.getPosition().charAt(1)-48;
        int jot = super.getPosition().charAt(0)-64;

        //mora se provjerit prvo desno pa lijevo od te pozicije

        for(int kt=joffset+1; kt<=granicaZaJ; kt++)  //horizontala desno
        {
            int t = kt + 64;
            char temp = (char)t;
            String pom = temp + Integer.toString(ioffset);
            if(jel_unutra(pom) && this.imaFigura(pom,super.getColor()) && !pom.equals(pos)) break; //ima figura desno na horizontali pa ne mozemo desno
            if(pom.equals(pos) && jel_unutra(pom))              //horizontala desno
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }
        }


        for(int kt = joffset-1; kt>=0 ; kt--)  //horizontala lijevo
        {
            int t = kt + 64;
            char temp = (char)t;
            String pom = temp + Integer.toString(ioffset);
            if(jel_unutra(pom) && this.imaFigura(pom, super.getColor()) && !pom.equals(pos)) break; //ima figura lijevo na horizontali pa ne mozemo lijevo
            if(pom.equals(pos) && jel_unutra(pom))
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }

        }


        for(int i = ioffset+1; i<10; i++) //vertikala gore
        {
            String pom = super.getPosition().charAt(0) + Integer.toString(i);
            if (jel_unutra(pom) && this.imaFigura(pom,super.getColor()) && !pom.equals(pos)) break; //ima figura iznad na vertikali pa ne mozemo iznad
            if (pom.equals(pos) && jel_unutra(pom))
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }
        }

        for(int i = ioffset-1; i>=0; i--) //vertikala ispod
        {
            String pom = super.getPosition().charAt(0) + Integer.toString(i);
            if (jel_unutra(pom) && !pom.equals(pos) && this.imaFigura(pom,super.getColor())) break; //ima figura ispod na vertikali pa ne mozemo ispod
            if (pom.equals(pos) && jel_unutra(pom))
            {
                if(mapa!=null) {
                    for (Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
                        if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() != this.getColor()) {
                            mapa.remove(it.getKey());
                            break;                                  //provjera da li na naskocnom polju ima neka figura na ploci
                        }                                           //ako je figura razlicite boje uklanja se sa ploce
                        else if (it.getKey().getPosition().equals(pos) && it.getKey().getColor() == this.getColor()) {
                            throw new IllegalChessMoveException();              //a ako je iste boje baca se exception
                        }
                    }
                }
                super.setPosition(pos);               //nakon eventualnog uklanjaja figure sa naskocne pozicije
                return;                         //postavlja se ova figura na tu poziciju.
            }
        }

        throw new IllegalChessMoveException(); //ovo se baca ako ne moze data figura zbog stanja na ploci napraviti taj potez
        // ili polje nije validno!
    }
}
