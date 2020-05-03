package ba.unsa.etf.rpr;

import java.util.Map;

public abstract class ChessPiece {
    public enum Color{
        BLACK, WHITE;
    }
    private String pozicija;
    private Color boja;
    private Map<ChessPiece, Boolean> f; //privatna referenca preko koje ce svaka figura znati na kojoj ploci igra i bit ce
                                        //svjesna figura preko sebe jer ce ova referenca pokazivati na hashmapu tog Boarda na kom figura igra
    public ChessPiece(String pozicija, Color boja)
    {

        if(pozicija.isEmpty() || !Character.isLetter(pozicija.charAt(0)) || !Character.isDigit(pozicija.charAt(1))) throw new IllegalArgumentException();
        if ((!(pozicija.charAt(0)>='A' && pozicija.charAt(0)<='H') || (pozicija.charAt(0)>='a' && pozicija.charAt(0)<='h')) || !(pozicija.charAt(1)>='1' && pozicija.charAt(1)<='8')){
            throw new IllegalArgumentException();
        }
        this.pozicija=pozicija;
        this.boja=boja;
    }

    /*ovako je ostvarena komunikacija između ploče i figura, tako što se prije svakog odigranog poteza, izvedenim klasama iz ChessPiece
    pošalje referenca na ploču na kojoj igraju! - tako figure postaju svjesna jedna druge*/

    void setPloca(Map<ChessPiece, Boolean> mapa) {
        this.f=mapa;
    }
    Map<ChessPiece, Boolean> getPloca(){
        return this.f;
    }

    void setPosition(String pozicija){
            this.pozicija=pozicija;
    }

    void setBoja(Color boja){
        this.boja=boja;
    }

    public String getPosition() {
        return this.pozicija;
    }
    public Color getColor() {
        return this.boja;
    }
    public abstract void move(String position) throws IllegalChessMoveException;
    boolean imaFigura(String pos, ChessPiece.Color boja) //package private da bi se izbjeglo bespotrebno multipliciranje u svim klasama
    {                                                    //samo zato da bi ovo bilo private u njima a ista je funkcija u svim klasama
        Map<ChessPiece, Boolean> mapa = this.getPloca();    //zato se nalazi u apstraktnoj
        if(mapa==null) return false;
        for(Map.Entry<ChessPiece, Boolean> it : mapa.entrySet())    //provjerava da li u smjeru kretanja figure ima neka druga figura na tom polju
        {                                                       //na osnovu ove funkcije se prekida bespotreba pretraga u nekim smjerovima
            if(it.getKey().getPosition().equals(pos) && (it.getKey().getColor()==boja || it.getKey().getColor()!=boja)) return true;
        }
        return false;
    }
    boolean jel_unutra(String pos) //također kao i za metodu imaFigura, zbog bespotrebnog multipliciranja stavljena je kao package-private
    {                               //u apstraktnoj klasi, te je zajednicka za sve funkcije. Provjerava da li je poslana pozicija unutar
        if(!Character.isLetter(pos.charAt(0)) || !Character.isDigit(pos.charAt(1))) return false;       //šahovske ploče
        if (!(pos.charAt(0)>='A' && pos.charAt(0)<='H') || !(pos.charAt(1)>='1' && pos.charAt(1)<='8')) return false;
        return true;
    }

}
