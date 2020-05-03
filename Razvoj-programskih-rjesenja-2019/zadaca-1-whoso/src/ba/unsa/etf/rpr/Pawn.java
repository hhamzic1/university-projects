package ba.unsa.etf.rpr;

import java.util.Map;

public class Pawn extends ChessPiece{
    public Pawn(String pozicija, Color boja) {
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
        Color temper = super.getColor();

        /*Kretanje pijuna zavisi od njegove boje pa imamo dva slučaja kao i 4 moguće opcije koje pijun može odigrati, testiraju se sve*/
        switch(temper)
        {
            case WHITE:
                int ioffset=super.getPosition().charAt(1)-48;
                int joffset=super.getPosition().charAt(0)-64;
                boolean iznad=false;
                //gore
                int t=joffset+64;
                char temp=(char)t;
                String pom = temp + Integer.toString(ioffset+1);
                if(jel_unutra(pom) && !this.imaFigura(pom, this.getColor()) && pom.equals(pos))
                {
                    super.setPosition(pos);
                    return;
                }

                //gore - lijevo
                t=joffset-1+64;
                temp=(char)t;
                pom=temp+Integer.toString(ioffset+1);
                if(jel_unutra(pom) && !this.imaFigura(pom,this.getColor()) && pom.equals(pos))
                {
                    throw new IllegalChessMoveException();
                }
                else if(jel_unutra(pom) && this.imaFigura(pom,this.getColor()) && pom.equals(pos))
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
                    super.setPosition(pos);
                    return;
                }

                    //gore-desno
                t=joffset+1+64;
                temp=(char)t;
                pom=temp+Integer.toString(ioffset+1);
                if(jel_unutra(pom) && !this.imaFigura(pom,this.getColor()) && pom.equals(pos))
                {
                    throw new IllegalChessMoveException();
                }
                else if(jel_unutra(pom) && this.imaFigura(pom,this.getColor()) && pom.equals(pos))
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
                    super.setPosition(pos);
                    return;
                }

                //za dva - otvaranje
                t=joffset+64;
                temp=(char)t;
                pom=temp+Integer.toString(ioffset+1);
                String pom2=temp+Integer.toString(ioffset+2);
                if(jel_unutra(pom) && !this.imaFigura(pom,this.getColor()) && !pom.equals(pos))
                {
                    if(jel_unutra(pom2) && pom2.equals(pos) && !this.imaFigura(pom2,this.getColor()) && ioffset==2) {
                        super.setPosition(pos);
                        return;
                    }
                }
                throw new IllegalChessMoveException();

            case BLACK:
                int ioffset2=super.getPosition().charAt(1)-48;
                int joffset2=super.getPosition().charAt(0)-64;

                //dole
                int t2=joffset2+64;
                char temp2=(char)t2;
                String pom3 = temp2 + Integer.toString(ioffset2-1);
                if(jel_unutra(pom3) && !this.imaFigura(pom3,this.getColor()) && pom3.equals(pos))
                {
                    super.setPosition(pos);
                    return;
                }

                //dole - lijevo
                t2=joffset2-1+64;
                temp=(char)t2;
                pom=temp+Integer.toString(ioffset2-1);
                if(jel_unutra(pom) && !this.imaFigura(pom,this.getColor())&& pom.equals(pos))
                {
                    throw new IllegalChessMoveException();
                }
                else if(jel_unutra(pom) && this.imaFigura(pom,this.getColor()) && pom.equals(pos))
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
                    super.setPosition(pos);
                    return;
                }

                //dole-desno
                t2=joffset2+1+64;
                temp=(char)t2;
                pom=temp+Integer.toString(ioffset2-1);
                if(jel_unutra(pom) && !this.imaFigura(pom,this.getColor()) && pom.equals(pos))
                {
                    throw new IllegalChessMoveException();
                }
                else if(jel_unutra(pom) && this.imaFigura(pom,this.getColor()) && pom.equals(pos))
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
                    super.setPosition(pos);
                    return;
                }

                //za dva - otvaranje
                t2=joffset2+64;
                temp=(char)t2;
                pom=temp+Integer.toString(ioffset2-1);
                String pom4=temp+Integer.toString(ioffset2-2);
                if(jel_unutra(pom) && !this.imaFigura(pom,this.getColor()) && !pom.equals(pos))
                {
                    if(jel_unutra(pom4) && pom4.equals(pos) && ioffset2==7) {
                        super.setPosition(pos);
                        return;
                    }
                }
                throw new IllegalChessMoveException();

        }


    }
}
