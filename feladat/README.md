# Párhuzamos algoritmusok féléves beadandó feladat leírása
## 1. Monte Carlo Tree Search (MCTS)
A Monte Carlo Tree Search (MCTS) egy döntéshozatali algoritmus, 
amelyet gyakran alkalmaznak játékokban és szimulációs problémákban. 
A módszer iteratív módon bővíti a döntési fát, és minden lépésnél véletlenszerű szimulációkat futtat, 
hogy meghatározza a legjobb következő lépést. Párhuzamos verziója a szimulációkat több szálon futtatja, 
így jelentősen felgyorsítva a keresési folyamatot. 
A párhuzamos MCTS a döntési fát több szálon párhuzamosan építi és optimalizálja, 
ezáltal hatékonyabbá válik a számítási erőforrások kihasználása.

## 2. Perline noise
A Perlin Noise egy matematikai függvény, 
amely folyamatos, zökkenőmentes véletlenszerű értékek generálására szolgál, 
és különösen hasznos a számítógépes grafika, játékok és szimulációk terén. 
A párhuzamos Perlin Noise generálás során a különböző részproblémák 
(például a zajértékek kiszámítása) párhuzamosan kerülnek végrehajtásra, 
így gyorsítva a zajminták előállítását, 
és lehetővé téve nagyobb felbontású és összetettebb zajstruktúrák generálását valós időben.

## 3. Prímszám keresés (Eratosthenészi szita párhuzamosítva)
Az Eratosthenészi szita egy klasszikus algoritmus a prímszámok meghatározására egy adott számig. 
A párhuzamosított változatában a szita algoritmus egyes szakaszait több szálon hajtják végre, 
így a számok kipróbálása és a többszörös osztók kiszűrése gyorsabban történik. 
A párhuzamosítás révén a különböző tartományokban történő szitálás párhuzamosítható, 
csökkentve a végrehajtási időt, különösen nagy számok esetében.