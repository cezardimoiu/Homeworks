   _____              _             __  __                                      
  / ____|            | |           |  \/  |                                     
 | |      __ _   ___ | |__    ___  | \  / |  ___  _ __ ___    ___   _ __  _   _ 
 | |     / _` | / __|| '_ \  / _ \ | |\/| | / _ \| '_ ` _ \  / _ \ | '__|| | | |
 | |____| (_| || (__ | | | ||  __/ | |  | ||  __/| | | | | || (_) || |   | |_| |
  \_____|\__,_| \___||_| |_| \___| |_|  |_| \___||_| |_| |_| \___/ |_|    \__, |
                                                                           __/ |
                                                                          |___/ 

DIMOIU CEZAR GABRIEL - 322CB

Aceasta tema presupune aprofundarea conceptului de mostenire implementand mai multe tipuri
de memorii cache. Am implementat cate o clasa pentru fiecare tip de memorie cache, clasele 
implementand interfata Cache.

Obiectele din memoria principala si din memoria cache sunt de tip Subscriptie(Abstract), 
care la randul lor sunt Free, Basic si Premium, fiecare extinzand clasa anterioara.

Metodele din interfata Cache sunt unele destul de basic (adaugare, stergere, cautare obiect
in memorie, returnare index obiect specific).

FIFOCache presupune ca elementul de la inceputul cozii va fi eliminat in cazul in care se face
o accesare, sau nu mai exista spatiu pentru a adauga alt element nou.
Pentru implementarea LRUCache m-am folosit de FIFOCache in sensul in care atunci cand accesam un 
obiect, il scoteam de la locul lui din memorie si il inseram la sfarsitul cozii, elementul cel 
mai nefolosit(ca perioada de timp) sa fie primul in coada.

//TODO BONUS