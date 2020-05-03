package ba.unsa.etf.rpr;

import java.util.Map;

public class Knight extends ChessPiece {
    public Knight(String pozicija, Color boja) {
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

        //provjera boje i odmah eliminacija ako je polje na kojem konj stoji iste boje kao i ono na koje treba doskocit!
        int slovo = position.charAt(0) - 64;
        int broj = position.charAt(1)-48;
        Color tempor = Color.WHITE;
        if((slovo + broj)%2==0) tempor=Color.BLACK;
        int slovo1= super.getPosition().charAt(0) - 64;
        int broj1= super.getPosition().charAt(1) - 48;
        Color tempor1= Color.WHITE;
        if((slovo1 + broj1)%2==0) tempor1=Color.BLACK;
        if(tempor==tempor1) throw new IllegalChessMoveException(); //konj može skočiti samo na kontra boju!


        //eliminacija kocki uz konja
        int granicaZaI=super.getPosition().charAt(1)-49+3;
        int granicaZaJ=super.getPosition().charAt(0) - 65+3;

        for(int ioffset = super.getPosition().charAt(1)-49; ioffset<granicaZaI; ioffset++)
        {
            for(int joffset = super.getPosition().charAt(0) - 65; joffset<granicaZaJ; joffset++)
            {
                int t = joffset+64;
                char temp = (char)t;
                String pom = temp + Integer.toString(ioffset);
                if(pom.equals(pos)  && jel_unutra(pom))              //iteracije oko kralja za +-1 polje
                {
                    throw new IllegalChessMoveException();
                }
            }
        }

        //  provjera polja udaljenih za 2 oko konja

        granicaZaI = super.getPosition().charAt(1)-50+5;
        granicaZaJ = super.getPosition().charAt(0) - 66+5;
        for(int ioffset = super.getPosition().charAt(1)-50; ioffset<granicaZaI; ioffset++)
        {
            for(int joffset = super.getPosition().charAt(0) - 66; joffset<granicaZaJ; joffset++)
            {
                int t = joffset+64;
                char temp = (char)t;
                String pom = temp + Integer.toString(ioffset);
                if(jel_unutra(pom) && pom.equals(pos))
                {
                    if(mapa!=null){
                            for(Map.Entry<ChessPiece, Boolean> it : mapa.entrySet()) {
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
