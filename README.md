# gameoflife-proiect
TASK 1:
Aplica regulile clasice ale jocului, care pornind de la o matrice obtine urmatoarele k generatii
Am folosit o functie calculVecini care calculeaza intr-o matrice aux numarul vecinilor vii ai unei casute
Apoi cu functia game, aplic regulile jocului in functie de numarul de vecini din aux, modific matricea
In main, folosesc un while care merge de la 1 pana la generatia k, apelez mereu calculVecini si game, iar apoi afisez fiecare matrice obtinuta 

Task 2:
Folosesc acelasi principiu doar ca de data asta retinem doar coordonatele casutelor care se modifica la fiecare generatie intr-o stiva de liste pentru eficienta
Ma folosesc tot de un while care merge de la cnt = 1 (generatia) pana la k.
Dau push generatiei in stiva de liste
Apoi am modificat functia game, ca doar pt acest task sa dea push coordonatelor in lista (asta daca gaseste o casuta care se modifica), dar in acelasi timp, folosesc functia ca la task 1 si modific matricea pe parcurs

Bonus:
Dandu-se continutul unei stive pt k generatii, si matricea corespunzatoare generatiei k, aflam matricea initiala
Citim intr-un while: numarul generatiei, apoi perechile de coordonate, si adaugam in stiva de liste pe parcurs
Stiva este construita cu generatiile crescator de sus in jos, pentru ca am folosit functia addAtEnd
Am creat o functie aflareMatrice, care este apelata recursiv, si parcurge pe rand fiecare lista, iar pentru coordonatele din lista modifica acea casuta

Task 3:
Stocam generatiile din gameoflife cu regulile clasice pe dreapta, si cele cu regulile modificate pe stanga fiecarui nod din arbore
Am creat o functie creareArbore care creeaza un nod al arborelui, pe partea stanga calculeaza vecinii cu functia de la task1, apeleaza o noua functie numita gameB care aplica noile reguli gameoflife si adauga la finalul listei coordonatele casutelor care se modifica. La final apelam recursiv pentru partea stanga a arborelui.
Analog pentru copiii din dreapta ai fiecarui nod, doar ca aplica regulile clasice

