package ba.unsa.etf.rpr;

import java.util.Scanner;

public class Program {
     public static void main(String[] args) {
         int i = 0;
         boolean check = false;
         Scanner ulaz = new Scanner(System.in);
         Board b = new Board();
         while (true) {
             ChessPiece.Color farba = ChessPiece.Color.WHITE;
             if (i % 2 == 0) {
                 farba = ChessPiece.Color.WHITE;
                 System.out.printf("White move: ");
             } else if (i % 2 != 0) {
                 farba = ChessPiece.Color.BLACK;
                 System.out.printf("Black move: ");
             }
             String s = ulaz.nextLine();
             //svi moguci bad inputi u jednom ifu
             if(s.length()>3 || (s.length()==1 && s.charAt(0)!='X') || s.length()<1 ||(s.length() == 2 && (!(s.charAt(0) >= 'a' && s.charAt(0) <= 'h') || !(s.charAt(1) >= '1' && s.charAt(1) <= '8'))) || (s.length() == 3 && (!(s.charAt(1) >= 'a' && s.charAt(1) <= 'h') || !(s.charAt(2) >= '1' && s.charAt(2) <= '8'))) || (s.length() == 3 && (s.charAt(0) != 'K' && s.charAt(0) != 'Q' && s.charAt(0) != 'B' && s.charAt(0) != 'P' && s.charAt(0) != 'R' && s.charAt(0) != 'N')) || (s.length() == 3 && (!Character.isLetter(s.charAt(0)) || Character.isLowerCase(s.charAt(0)) || !Character.isLowerCase(s.charAt(1)) || !Character.isDigit(s.charAt(2)))))
             {
                 System.out.printf("Illegal move\n");
                 continue;
             }
             if (s.length() == 1 && s.charAt(0) == 'X' && i % 2 == 0) {
                 System.out.printf("White surrender!\n");
                 return;
             } else if (s.length() == 1 && s.charAt(0) == 'X' && i % 2 != 0) {
                 System.out.printf("Black surrender!\n");
                 return;
             }

             String pom = s.toUpperCase();
             char c = 0;
             int j = 0;
             String temp = "";
             if (s.length() == 3) {
                 c = s.charAt(0);
                 j = (int) pom.charAt(2) - 48;
                 temp = pom.charAt(1) + Integer.toString(j);
             } else if (s.length() == 2) {
                 c = 'P';
                 j = (int) pom.charAt(1) - 48;
                 temp = pom.charAt(0) + Integer.toString(j);
             }
             slucaj: switch (c) {
                 case 'K':
                     try {
                         b.move(King.class, farba, temp);
                         break slucaj;
                     } catch (IllegalChessMoveException e) {
                         System.out.printf("Illegal move\n");
                         continue;
                     }
                 case 'Q':
                     try {
                         b.move(Queen.class, farba, temp);
                         break slucaj;
                     } catch (IllegalChessMoveException e) {
                         System.out.printf("Illegal move\n");
                         continue;
                     }
                 case 'R':
                     try {
                         b.move(Rook.class, farba, temp);
                         break slucaj;
                     } catch (IllegalChessMoveException e) {
                         System.out.printf("Illegal move\n");
                         continue;
                     }
                 case 'B':
                     try {
                         b.move(Bishop.class, farba, temp);
                         break slucaj;
                     } catch (IllegalChessMoveException e) {
                         System.out.printf("Illegal move\n");
                         continue;
                     }
                 case 'N':
                     try {
                         b.move(Knight.class, farba, temp);
                         break slucaj;
                     } catch (IllegalChessMoveException e) {
                         System.out.printf("Illegal move\n");
                         continue;
                     }
                 case 'P':
                     try {
                         b.move(Pawn.class, farba, temp);
                         break slucaj;
                     } catch (IllegalChessMoveException e) {
                         System.out.printf("Illegal move\n");
                         continue;
                     }
                 default:
                     System.out.printf("Illegal move\n");
                     continue;
             }
             if (i % 2 == 0 && !b.isCheck(ChessPiece.Color.WHITE)) {
                 if (b.isCheck(ChessPiece.Color.BLACK)) {
                         System.out.printf("CHECK!!!\n");
                     }
                 }
              else if (i % 2 != 0 && !b.isCheck(ChessPiece.Color.BLACK )) {
                 if (b.isCheck(ChessPiece.Color.WHITE)){
                         System.out.printf("CHECK!!!\n");
                    }
                }
                i++;
            }
        }
     }


