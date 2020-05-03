package ba.unsa.etf.rpr;

import java.lang.reflect.InvocationTargetException;
import java.sql.SQLOutput;
import java.util.HashMap;
import java.util.Map;

public class Board {
    private Map<ChessPiece, Boolean> figure; //mapa svih figura koje igraju na instanci ove ploče

    Board(){            //postavljamo ploču u početni položaj
        figure = new HashMap<ChessPiece, Boolean>();
        for(int i=65; i<=72; i++)
        {
            figure.put(new Pawn((char) i + "2", ChessPiece.Color.WHITE), true);
            figure.put(new Pawn((char) i + "7", ChessPiece.Color.BLACK), true);
        }
        figure.put(new King( "E1", ChessPiece.Color.WHITE), true);
        figure.put(new King( "E8", ChessPiece.Color.BLACK), true);
        figure.put(new Queen( "D1", ChessPiece.Color.WHITE), true);
        figure.put(new Queen( "D8", ChessPiece.Color.BLACK), true);
        figure.put(new Rook( "A1", ChessPiece.Color.WHITE), true);
        figure.put(new Rook( "H1", ChessPiece.Color.WHITE), true);
        figure.put(new Rook( "A8", ChessPiece.Color.BLACK), true);
        figure.put(new Rook( "H8", ChessPiece.Color.BLACK), true);      //setup ploče
        figure.put(new Bishop( "C1", ChessPiece.Color.WHITE), true);
        figure.put(new Bishop( "F1", ChessPiece.Color.WHITE), true);
        figure.put(new Bishop( "C8", ChessPiece.Color.BLACK), true);
        figure.put(new Bishop( "F8", ChessPiece.Color.BLACK), true);
        figure.put(new Knight( "B1", ChessPiece.Color.WHITE), true);
        figure.put(new Knight( "G1", ChessPiece.Color.WHITE), true);
        figure.put(new Knight( "B8", ChessPiece.Color.BLACK), true);
        figure.put(new Knight( "G8", ChessPiece.Color.BLACK), true);
    }
    public Map<ChessPiece, Boolean> getFigure()
    {
        return this.figure;
    }

    public void move(Class type, ChessPiece.Color color, String position) throws IllegalChessMoveException {

        for(Map.Entry<ChessPiece, Boolean> it : figure.entrySet())  //traži se u kolekciji figura ona figura koja odgovara figuri prosljeđenoj kao parametar
        {
            if(it.getKey().getClass() == type  && it.getKey().getColor()==color)
            {
                try {
                    it.getKey().setPloca(figure);           //klasi te figure šaljemo referencu na ploču na kojoj treba da odigra potez
                    Class<ChessPiece> tmp = (Class<ChessPiece>) it.getKey().getClass(); //te ona je tako u mogućnosti provjeriti legalne poteze
                    String temp = it.getKey().getPosition();                           //ovom referencom figure postaju svjesne jedne drugih
                    it.getKey().move(position);
                    if(this.isCheck(color)){            //Ako se figura pomjeri, a ona osoba koja je pomjerila figuru je idalje u šahu
                        figure.remove(it.getKey());         //to je illegal move te moramo vratiti ploču kakva je bila prije tog poteza!
                        figure.put(tmp.getDeclaredConstructor(String.class, ChessPiece.Color.class).newInstance(temp,color), true);
                        break;
                    }
                    return;
                }catch(IllegalChessMoveException | IllegalArgumentException | NoSuchMethodException | IllegalAccessException | InvocationTargetException | InstantiationException ignored) {

                }
            }
        }
        throw new IllegalChessMoveException();   //ako nema ta figura na ploči baca se izuzetak opet!
    }


    public boolean isCheck(ChessPiece.Color color) {    //provjeravamo sve figure koje mogu napasti odnosno kojima je premještanje na kraljevu poziciju
        ChessPiece k=null;                              //legalan potez!
        for(Map.Entry<ChessPiece, Boolean> it: figure.entrySet()) {
            if(it.getKey().getClass()==King.class && it.getKey().getColor()==color)
            {
                k=new King(it.getKey().getPosition(), it.getKey().getColor());
                break;
            }
        }
        for(Map.Entry<ChessPiece, Boolean> it : figure.entrySet())
        {
            if(it.getKey().getColor()!=color)
            {
                try{
                    it.getKey().setPloca(figure);
                    ChessPiece temp=it.getKey();
                    String str=it.getKey().getPosition();
                    ChessPiece.Color c=it.getKey().getColor();    //moramo vratit sve kako je bilo prije pomjeranja
                    it.getKey().move(k.getPosition()); //kralj nece nikad bit pojeden, ne moze null bit
                    Class<ChessPiece> tmp = (Class<ChessPiece>) temp.getClass();
                    figure.remove(temp);
                    try {
                        figure.put(tmp.getDeclaredConstructor(String.class, ChessPiece.Color.class).newInstance(str,c), true);
                    } catch (InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
                        e.printStackTrace();
                        throw new IllegalArgumentException("Nema konstruktora sa dva parametra!");
                    }
                    figure.put(new King(k.getPosition(),k.getColor()),true);
                    return true;
                }catch(IllegalArgumentException | IllegalChessMoveException ignored){
                }
            }
        }
         return false;
    }

    public void move(String oldPosition, String newPosition) throws IllegalChessMoveException{
        boolean ima=false;
        for(Map.Entry<ChessPiece, Boolean> it : figure.entrySet())
        {
            if(it.getKey().getPosition().equals(oldPosition))
            {
                ima=true;
                try
                {
                    this.move(it.getKey().getClass(), it.getKey().getColor(), newPosition);
                    return;
                }catch(IllegalChessMoveException e) {
                    throw new IllegalChessMoveException();
                }catch (IllegalArgumentException e){
                    throw new IllegalArgumentException();
                }
            }
        }
        if(!ima) {
            throw new IllegalArgumentException();   //ako nema ta figura na ploči baca se izuzetak opet!
        }
    }
}
