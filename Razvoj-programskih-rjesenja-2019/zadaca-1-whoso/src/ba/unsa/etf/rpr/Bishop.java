package ba.unsa.etf.rpr;

import java.util.Map;

public class Bishop extends ChessPiece{
    public Bishop(String pozicija, Color boja) {
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
            if(jel_unutra(temp2) && this.imaFigura(temp2, super.getColor()) && !temp2.equals(pos)) break; //ako u smjeru provjere ima neka figura a ta pozicija
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
            int l2= joffset + j + 64;
            char t2 = (char)l2;
            String temp2 =  t2 + Integer.toString(i-j-k);
            if(jel_unutra(temp2) && this.imaFigura(temp2, super.getColor()) && !temp2.equals(pos)) break; //ako u smjeru provjere ima neka figura a ta pozicija
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
        throw new IllegalChessMoveException();
    }
}
