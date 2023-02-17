Am rezolvat Task-urile 1 si 2
Pentru fiecare dintre acestea am folosit functii precum: read_bmp, write_bmp, overlap_bmp. 
La Task-ul 1, incep cu citirea din fisier a datelor pentru structuri. Apoi ma duc pe bitul in care matrica de pixeli incepe. Apoi aloc memorie cu ajutorul pointerului bmp_data si continui citirea. Apoi, m-am folosit de functia write_bmp pentru a obtine fisierul de tip bmp. Aici, inloc sa citesc, am scris in imaginea din output. 
La Task-ul 2, aflu ce fisier trebuie citit, alaturi de coordonatele y si x. Apoi citesc datele imaginii. Ambele bmp-uri sunt inversate si continui mai apoi in overlay_bmp. Aici pornesc de la pozitia x si y din imaginea in care vom suprapune celelalte fisiere. Dupa care, pentru fiecare bit, preiau culorile din imaginea de suprapus (r,g,b) si le pun peste bitul imaginii principale. Apoi, voi inversa imaginea din nou si se va ajunge la output-ul dorit.
La quit, eliberez memoria din heap. 
