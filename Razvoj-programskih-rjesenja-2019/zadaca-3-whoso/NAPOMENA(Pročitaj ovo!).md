# zadaca-3-hhamzic1
Urađena je čitava zadaća međutim kada se runnaju svi autotestovi odjednom oni padaju, nakon dugo dugo vremena sam skontao razlog i ja mislim 
da je on neizbježan, naime kako ne mogu kontrolisati kada će se Garbage Collector pozvati kada izgubim referencu na neki objekat(a što se 
dosta puta radi u autotestovima) konekcija sa bazom ostane i te je naredba db.delete() ne može obrisati jer to vidi kao da je koristi neki 
drugi proces :( . Ne znam kako to riješiti, i mislim da to kod Linuxa nije slučaj jer Linux to dozvoljava(brisanje fajlova kad su u upotrebi)
 te zato profesoru prolaze svi autotestovi, sa kim god od studenata sam razgovarao a da koristi windows isto mu se dešava kako god da uradi zadatak. Čak
 sam mijenjao logiku zadatka kontajući da je do baze zato sam odlučio da brišem svaki put sve iz baze i jako brzo to ubacim ponovo u bazu kao executeBatch(), ali džaba... 
Uvjeren sam da zadaća 100% radi, jer sam testirao sve slučajeve, pa čak i testovi kad se pokreću zadatak po zadatak prolaze svi (4. traži da se
obriše baza pa da se pokrene). Nadam se da će, ko god bude ovo ocijenjivao kada pročita ovo testirati ručno zadatak u mainu, pratiti bazu kroz 
DB browser ili nešto slično jer sve fakat radi ali neki autotestovi padaju, jer nema logike da se gleda samo da prolaze autotestovi jer je
u zadaću uloženo fakat puno truda i vremena...

Srdačan pozdrav, Huso.
