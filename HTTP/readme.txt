Dimoiu Cezar Gabriel - 322CB

Tema3- HTTP

Am implementat un client care sa realizeze cereri de tip GET si POST.
Pentru a folosi datele din raspunsul servelului, am utilizat JSON-C.
Pentru a completa cererile m-am folosit si de functiile de la laborator.

Mi-am facut o structura in care sa salvez campurile primite de la server
si pe care le folosesc pentru rezolvarea urmatoarelor taskuri.

Am facut o functie pentru fiecare task, pentru a fi mai usor de citit.
In fiecare din aceste functii (task1, task2, task3, task4) doar completez
cererea de GET/POST in mod corespunzator, si o trimit la server, apoi intorc
mesajul primit de la server, si il afisez in main.

Am realizat si o functie ajutatoare pentru preluarea cookie-urilor din 
mesajul primit de la server.

Am incercat pe cat posibil sa eliberez toata memoria folosita si sa nu 
existe leak-uri de memorie.
