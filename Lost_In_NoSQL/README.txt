
$$\       $$$$$$\   $$$$$$\ $$$$$$$$\       $$$$$$\ $$\   $$\ 
$$ |     $$  __$$\ $$  __$$\\__$$  __|      \_$$  _|$$$\  $$ |
$$ |     $$ /  $$ |$$ /  \__|  $$ |           $$ |  $$$$\ $$ |
$$ |     $$ |  $$ |\$$$$$$\    $$ |           $$ |  $$ $$\$$ |
$$ |     $$ |  $$ | \____$$\   $$ |           $$ |  $$ \$$$$ |
$$ |     $$ |  $$ |$$\   $$ |  $$ |           $$ |  $$ |\$$$ |
$$$$$$$$\ $$$$$$  |\$$$$$$  |  $$ |         $$$$$$\ $$ | \$$ |
\________|\______/  \______/   \__|         \______|\__|  \__|
                                                              
                                                              
                                                              

	   /$$   /$$            /$$$$$$   /$$$$$$  /$$      
	  | $$$ | $$           /$$__  $$ /$$__  $$| $$      
	  | $$$$| $$  /$$$$$$ | $$  \__/| $$  \ $$| $$      
	  | $$ $$ $$ /$$__  $$|  $$$$$$ | $$  | $$| $$      
	  | $$  $$$$| $$  \ $$ \____  $$| $$  | $$| $$      		
	  | $$\  $$$| $$  | $$ /$$  \ $$| $$/$$ $$| $$      
	  | $$ \  $$|  $$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$$
	  |__/  \__/ \______/  \______/  \____ $$$|________/
	                                      \__/          
                                                  
                                                  
DIMOIU CEZAR GABRIEL - 322CB

Scopul temei este acela de a simula o baza de date NoSQL.
Am folosit o clasa pentru baza de date, o clasa pentru noduri
si alta clasa pentru entitatile din noduri.
Baza de date este practic un arraylist de noduri, fiecare nod
fiind la randul lui un arraylist de instante ale entitatior.

In entityList mi-am salvat toate entitatile create, iar cand am nevoie de numele atributelor, le iau din entityList

Am implementat urmatoarele functii in mainclass:
	# createDatabase - creaza baza de date 
	# createEntity - creaza o entitate si o pune in arraylist
	# objectEntity - creaza o instanta a entitatii si o returneaza
	# inserEntity - pentru fiecare RF(factor de replicare) o sa am un nod.
		Calculez RF-ul maxim. Daca baza de date e goala, creez "RF" noduri, 
		in caz contrar parcurg baza de date si adaug instanta corespunzator.
	# deleteEntity - caut in baza de date(dupa nume si cheia primara) 
		instanta si daca o gasesc, o elimin din baza de date. Daca nu o gasesc, afisez un mesaj.
	# void getEntity - asemanator ca la deleteEntity(cautare in baza de 
		date). Cand gasesc instanta in baza de date, o afisez impreuna cu toate atributele pe care le are.
	# Entity getEntity - imi cauta in entityList entitatea cu numele "nume" 
		si o returneaza daca o gaseste
	# dec - imi formateaza corspunzator textul ("#.##")
	# print - iterez prin arraylist-uri si afisez numele atributului (din entityList) + atributul (din database)
	# update - TODO


Pentru celelalte clase functiile folosite sunt destul de basic: getteri, setteri, size of a list, remove element.
