Pozdrav. 

Ovim txt fajlom bih želio samo da naglasim ideju koja stoji iza zadatka.
Razmišljajući imao sam par ideja kako se ovo može izvesti i od njih svih mi se najmanje 
svidjela ona u kojoj se sve "rješava u boardu" i pomislio sam da bi bilo super kada bi svaka figura
imala "svijest" odnosno "znala" gdje stoje figure oko nje, to jest da bi bilo ekstra kada bi svaka figura
znala na kojoj ploči igra i koji potez smije napraviti a koji ne!

I onda sam skontao da je optimalno rješenje da u Boardu kao glavni atribut imam kolekciju figura odnosno tačnije
HashMapu figura, i to sa key vrijednošću ChessPiece a value vrijednošću Boolean odnosno da li je aktivna ili neaktivna(pojedena ili ne)
a da u apstraktnoj klasi imam referencu na HashMapu kao privatni atribut i setter tog atributa.

Naime ideja je da se iz Boarda prije igranja npr it.getKey().move(position) // it.getKey() bi vratio npr nekog pijuna
da ja tome pijunu postavim njegovu referencu na hashmapu na kojoj treba da odigra potez, i samim time u klasi Pawn se provjerava
da li je potez legalan(npr da li ima figura u tom pravcu, da li je to polje uopšte unutar ploče) itd...

Te ako je na poziciji "position" bila neka figura i ako je taj potez legalan za našeg gore spomenutog pijuna(odnosno
pijun je provjerio da li smije/može otići na to polje, uzimajući u obzir trenutno stanje figura na ploči), onda se figura koja je
prije bila na toj poziciji jednostavno ukloni iz hashMape metodom remove().

Smatram da je ovaj način implementacije iznimno efikasan izveden preko HashMape jer ne trebamo pamtiti indekse, nikakvu matricu i tako
dalje.

Srdačan pozdrav, Huso.


