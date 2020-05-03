package ba.unsa.etf.rpr;

import java.util.Map;

public class Rook extends ChessPiece {
    public Rook(String pozicija, Color boja) {
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
        //Rook dio
        int granicaZaJ=8;
        int ioffset = super.getPosition().charAt(1)-48;     //početna pozicija
        int jot = super.getPosition().charAt(0)-64;

        /*Provjeravamo kretanje topa u svim smjerovima!*/

        for(int kt=jot+1; kt<=granicaZaJ; kt++)  //horizontala desno
        {
            int t = kt + 64;
            char temp = (char)t;
            String pom = temp + Integer.toString(ioffset);
            if(jel_unutra(pom) && this.imaFigura(pom, super.getColor()) && !pom.equals(pos)) break; //ima figura desno na horizontali pa ne mozemo desno
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


        for(int kt = jot-1; kt>0 ; kt--)  //horizontala lijevo
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


        for(int i = ioffset+1; i<10; i++) //vertikala iznad
        {
            String pom = super.getPosition().charAt(0) + Integer.toString(i);
            if (jel_unutra(pom) && this.imaFigura(pom, super.getColor()) && !pom.equals(pos)) break; //ima figura iznad na vertikali pa ne mozemo iznad
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
            if (jel_unutra(pom) && this.imaFigura(pom, super.getColor()) && !pom.equals(pos)) break; //ima figura ispod na vertikali pa ne mozemo ispod
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

        throw new IllegalChessMoveException();
    }
}
