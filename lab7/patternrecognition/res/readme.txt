/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150		27 ms        7 ms
    200		75 ms	     43 ms
    300		241 ms	     60 ms
    400		526 ms	     72 ms
    800		4038 ms	     280 ms
   1600		32398 ms     1090 ms
   3200		64796 ms     4562 ms
   6400		140800 ms    19563 ms
  12800         307200 ms     84919 ms


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:O(n^4) 4 nestlade loopar 

Sortering: O(n^2logn) nestlade loopar + count
