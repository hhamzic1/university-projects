package ba.unsa.etf.rpr;

import java.util.Arrays;
import java.util.Map;

public class King extends ChessPiece {
    public King(String pozicija, Color boja){
        super(pozicija, boja);
    }

    public String getPosition() {
        return super.getPosition();
    }

    public Color getColor() {
        return super.getColor();
    }

    @Override
    public void move(String position) throws IllegalChessMoveException
    {
        Map<ChessPiece, Boolean> mapa = this.getPloca();
        String pos = position.toUpperCase();
        if(pos.isEmpty() || !Character.isLetter(pos.charAt(0)) || !Character.isDigit(pos.charAt(1))) throw new IllegalArgumentException();
        if(!jel_unutra(pos)) throw new IllegalArgumentException();
        int granicaZaI=super.getPosition().charAt(1)-49+3;
        int granicaZaJ=super.getPosition().charAt(0) - 65+3;

        for(int ioffset = super.getPosition().charAt(1)-49; ioffset<granicaZaI; ioffset++)
        {
            for(int joffset = super.getPosition().charAt(0) - 65; joffset<granicaZaJ; joffset++)
            {
                int t = joffset+64;
                char temp = (char)t;
                String pom = temp + Integer.toString(ioffset);
                if(pom.equals(pos) && this.imaFigura(pom, super.getColor()) && jel_unutra(pom))              //iteracije oko kralja za +-1 polje
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
                    super.setPosition(pom);
                    return;
                }
                if(pom.equals(pos) && !this.imaFigura(pom, super.getColor()) && jel_unutra(pom))              //iteracije oko kralja za +-1 polje
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
                    super.setPosition(pom);
                    return;
                }
            }
        }
        throw new IllegalChessMoveException();
    }
}
