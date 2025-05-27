#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;
FILE *fout;

struct lista
{
    int x, y;
    struct lista *next;
};
typedef struct lista lista;

struct stiva
{
    int generatia;
    lista *headLista;
    struct stiva *next;
};
typedef struct stiva stiva;

struct arbore
{
    lista *head; //head-ul listei fiecarui nod din arbore
    struct arbore *left, *right;
};
typedef struct arbore arbore;

struct graf
{
    int x, y; //retinem in fiecare nod din graf coordonatele din matrice
};
typedef struct graf graf;

void addAtBeginning(lista **head, int x, int y)
{
    // *head , inceputul listei se va modifica
    // x, y,  informatia de stocat
    lista *newNode = (lista *)malloc(sizeof(lista));
    newNode->x = x;
    newNode->y = y;
    newNode->next = *head;
    *head = newNode;
}

void addAtEnd(lista **head, int x, int y)
{
    lista *aux = *head;

    if (*head == NULL)
        addAtBeginning(head, x, y); // daca lista este vida , se modifica adresa de inceput
    else
    { 
        lista *newNode = (lista *)malloc(sizeof(lista));
        newNode->x = x;
        newNode->y = y; // stocheaza informatia nodului nou
        // cat timp nu s-a ajuns la final , se parcurge
        while (aux->next != NULL)
            aux = aux->next;
        // se adauga noul element in lista
        aux->next = newNode;
        newNode->next = NULL; // final lista
    }
}

void push(stiva **top, lista **head, int gen)
{
    stiva *newNode = (stiva *)malloc(sizeof(stiva));
    newNode->generatia = gen;

    lista *copie = NULL;
    lista *elemCurent = *head;

    while (elemCurent != NULL)
    {
        addAtEnd(&copie, elemCurent->x, elemCurent->y);
        elemCurent = elemCurent->next;
    }
    newNode->headLista = copie;
    newNode->next = *top;
    *top = newNode;
}

void calculVecini(char **matrice, int row, int col, int **aux)
{
    int nrVecini = 0, i, j;

    for (j = 1; j < col - 1; j++)
    { // facem verificarea pentru linia 0

        nrVecini = 0;
        if (matrice[0][j - 1] == 'X')
            nrVecini++;
        if (matrice[0][j + 1] == 'X')
            nrVecini++;
        if (matrice[1][j - 1] == 'X')
            nrVecini++;
        if (matrice[1][j] == 'X')
            nrVecini++;
        if (matrice[1][j + 1] == 'X')
            nrVecini++;
        aux[0][j] = nrVecini;
    }

    for (j = 1; j < col - 1; j++)
    { // facem verificarea pentru ultima linie

        nrVecini = 0;
        if (matrice[row - 1][j - 1] == 'X')
            nrVecini++;
        if (matrice[row - 1][j + 1] == 'X')
            nrVecini++;
        if (matrice[row - 2][j - 1] == 'X')
            nrVecini++;
        if (matrice[row - 2][j] == 'X')
            nrVecini++;
        if (matrice[row - 2][j + 1] == 'X')
            nrVecini++;
        aux[row - 1][j] = nrVecini;
    }

    for (i = 1; i < row - 1; i++)
    { // facem verificarea pentru prima coloana
        nrVecini = 0;
        if (matrice[i][1] == 'X')
            nrVecini++;
        if (matrice[i - 1][0] == 'X')
            nrVecini++;
        if (matrice[i - 1][1] == 'X')
            nrVecini++;
        if (matrice[i + 1][0] == 'X')
            nrVecini++;
        if (matrice[i + 1][1] == 'X')
            nrVecini++;
        aux[i][0] = nrVecini;
    }

    for (i = 1; i < row - 1; i++)
    { // facem verificarea pentru ultima coloana
        nrVecini = 0;
        if (matrice[i - 1][col - 1] == 'X')
            nrVecini++;
        if (matrice[i - 1][col - 2] == 'X')
            nrVecini++;
        if (matrice[i][col - 2] == 'X')
            nrVecini++;
        if (matrice[i + 1][col - 2] == 'X')
            nrVecini++;
        if (matrice[i + 1][col - 1] == 'X')
            nrVecini++;
        aux[i][col - 1] = nrVecini;
    }

    // facem verificarea pentru interiorul matricei
    for (i = 1; i < row - 1; i++)
        for (j = 1; j < col - 1; j++)
        {
            nrVecini = 0;

            if (matrice[i][j - 1] == 'X')
                nrVecini++;
            if (matrice[i - 1][j - 1] == 'X')
                nrVecini++;
            if (matrice[i - 1][j] == 'X')
                nrVecini++;
            if (matrice[i - 1][j + 1] == 'X')
                nrVecini++;
            if (matrice[i][j + 1] == 'X')
                nrVecini++;
            if (matrice[i + 1][j + 1] == 'X')
                nrVecini++;
            if (matrice[i + 1][j] == 'X')
                nrVecini++;
            if (matrice[i + 1][j - 1] == 'X')
                nrVecini++;

            aux[i][j] = nrVecini;
        }

    nrVecini = 0;
    // facem verificarea pentru colt stg sus
    if (matrice[0][1] == 'X')
        nrVecini++;
    if (matrice[1][1] == 'X')
        nrVecini++;
    if (matrice[1][0] == 'X')
        nrVecini++;
    aux[0][0] = nrVecini;

    nrVecini = 0;
    // facem verificarea pentru colt dr sus
    if (matrice[0][col - 2] == 'X')
        nrVecini++;
    if (matrice[1][col - 2] == 'X')
        nrVecini++;
    if (matrice[1][col - 1] == 'X')
        nrVecini++;
    aux[0][col - 1] = nrVecini;

    nrVecini = 0;
    // facem verificarea pentru colt stg jos
    if (matrice[row - 2][0] == 'X')
        nrVecini++;
    if (matrice[row - 2][1] == 'X')
        nrVecini++;
    if (matrice[row - 1][1] == 'X')
        nrVecini++;
    aux[row - 1][0] = nrVecini;

    nrVecini = 0;
    // facem verificarea pentru colt dr jos
    if (matrice[row - 2][col - 1] == 'X')
        nrVecini++;
    if (matrice[row - 2][col - 2] == 'X')
        nrVecini++;
    if (matrice[row - 1][col - 2] == 'X')
        nrVecini++;
    aux[row - 1][col - 1] = nrVecini;
}

void gameB(char **matrice, int **aux, int row, int col, arbore *root, int test)
{
    //functia gameB implementeaza regulile noi
    int i, j;

    for( i = 0; i < row; i++)
        for(j = 0; j < col; j++)
        {
            if((matrice[i][j] == '+' ) && (aux[i][j] == 2)) //noile reguli ale jocului
               {
                matrice[i][j] = 'X';
                addAtEnd(&root->head, i, j); //adaugam coordonatele la finalul listei
               }
        }
}

void game(char **matrice, int **aux, int row, int col, stiva *head, arbore *root, int test)
{ //functia game aplica regulile clasice ale jocului game of life
    int i, j;

    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
        { // verificam daca respectiva casuta este vie/moarta si aplicam regulile jocului
            if (matrice[i][j] == '+')
                if (aux[i][j] == 3)
                {
                    if( test == 2)
                        addAtEnd(&head->headLista, i, j); //adauga la finalul listei coordonatele casutei modificate
                    if( test == 3)
                        addAtEnd (&root->head, i, j); //adauga la finalul listei coordonatele casutei modificate
                    
                    matrice[i][j] = 'X';
                }
            if (matrice[i][j] == 'X')
                if (aux[i][j] < 2)
                {
                    if( test == 2)
                        addAtEnd(&head->headLista, i, j);
                    if( test == 3)
                        addAtEnd (&root->head, i, j);
                    matrice[i][j] = '+';
                }
                else if (aux[i][j] > 3)
                {
                    if( test == 2)
                        addAtEnd(&head->headLista, i, j);
                    if( test == 3)
                        addAtEnd (&root->head, i, j);
                    matrice[i][j] = '+';
                }
        }
}

void printStiva(stiva *top)
{
    // afisare recursiva pentru ca listele sa fie in ordine crescatoare
    if (top == NULL)
        return;
    else
    {
        printStiva(top->next);
        fprintf(fout, "%d", top->generatia);
        lista *nodCurent = top->headLista;

        while (nodCurent != NULL)
        {
            fprintf(fout, " %d %d", nodCurent->x, nodCurent->y);
            nodCurent = nodCurent->next;
        }
        fprintf(fout, "\n");
    }
}

void freeLista(lista *head)
{
    while (head != NULL)
    {
        lista *temp = head;
        head = head->next;
        free(temp);
    }
}

char **copiazaMatrice (char **matrice, int row, int col)
{//functie clasica de copierea unei matrici, folosita la task 3
    char **copie = (char**)malloc( row * sizeof(char*));

    for(int i = 0; i < row; i++)
    {
        copie[i] = (char*)malloc(col * sizeof(char));
        for(int j = 0; j < col; j++)
            copie[i][j] = matrice[i][j];
    }

    return copie;
}

void freeMatrice(char** matrice, int row)
{
    //elibereaza memoria din matricea de tip char

    for (int i = 0; i < row; i++)
        free(matrice[i]);
    free(matrice);
}

void freeArbore(arbore* nod) 
{
    //daca am ajuns la final
    if (nod == NULL)
        return;

    freeLista(nod->head);  // eliberam lista
    //apelam recursiv pe stanga si apoi pe dreapta
    freeArbore(nod->left);  
    freeArbore(nod->right); 

    free(nod);  // eliberam nodul 
}

void creareArbore(arbore *nodCurent, char **matrice, int **aux, int row, int col, int k)
{
    //functia nu doar creeaza pe rand fiecare nod al arborelui, dar aplica regulile jocului si apoi afiseaza matricile

    //daca am ajuns la final
    if (k == 0 || nodCurent == NULL)
        return;
    
    // pt noua regula = partea stanga a arborelui
    char **matriceStanga = copiazaMatrice(matrice, row, col);

    nodCurent->left = (arbore *)malloc(sizeof(arbore));
    nodCurent->left->head = NULL;
    nodCurent->left->left = NULL;
    nodCurent->left->right = NULL;

    calculVecini(matriceStanga, row, col, aux);
    gameB(matriceStanga, aux, row, col, nodCurent->left, 3);
    //la fiecare apel recursiv, matricea pe stanga este afisata
    for (int i = 0; i < row; i++) 
    {
        for (int j = 0; j < col; j++)
            fprintf(fout, "%c", matriceStanga[i][j]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    
    //apelam recursiv pe stanga si eliberam memoria matricei copiate
    creareArbore(nodCurent->left, matriceStanga, aux, row, col, k - 1);
    freeMatrice(matriceStanga, row);


    // pt regula normala = partea dreapta a arborelui
    char **matriceDreapta = copiazaMatrice(matrice, row, col);

    nodCurent->right = (arbore *)malloc(sizeof(arbore));
    nodCurent->right->head = NULL;
    nodCurent->right->left = NULL;
    nodCurent->right->right = NULL;

    calculVecini(matriceDreapta, row, col, aux);
    game(matriceDreapta, aux, row, col, NULL, nodCurent->right, 3);
    //la fiecare apel recursiv, matricea pe dreapta este afisata
    for (int i = 0; i < row; i++) 
    {
        for (int j = 0; j < col; j++)
            fprintf(fout, "%c", matriceDreapta[i][j]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");

    //apelam recursiv pe dreapta si eliberam memoria matricei copiate 
    creareArbore(nodCurent->right, matriceDreapta, aux, row, col, k - 1);
    freeMatrice(matriceDreapta, row);
}

int noduriVecine(graf a, graf b)
{
    if( (abs(a.x - b.x) <= 1) && (abs(a.x - b.x) != 0) ) //daca diferenta e mai mica sau egala cu 1 inseamna ca se afla la maxim o casuta distanta => sunt vecine
        if( (abs(a.y - b.y) <= 1) && (abs(a.y - b.y) != 0))
            return 1;
    
    return 0;
}

int main(int argc, const char *argv[])
{
    int row, col, i, j, k, t;
    // row = nr de linii
    // col = nr de coloane
    stiva *nodStiva = NULL; // nodStiva = top-ul stivei
    lista *nodLista = NULL; // nodLista = head-ul listei
    arbore *nodArbore = NULL; // nodArbore = root-ul arborelui

    if (argc < 3)
        return 1;
    fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Nu s-a putut deschide fisierul");
        return 0;
    }
    fout = fopen(argv[2], "w");
    if (fout == NULL)
    {
        printf("Nu s-a putut deschide fisierul");
        return 0;
    }

    
    fscanf(fin, "%d", &t); //citim numarul task-ului
    fscanf(fin, "%d %d", &row, &col); //citim nr de linii si coloane
    fscanf(fin, "%d", &k); //citim nr de generatii
    int **aux; // aux e folosita pentru a stoca numarul de vecini egali cu X ai matricei
    char **matrice; // = matricea initiala


    // alocam dinamic spatiul din matrice
    matrice = (char **)malloc(row * sizeof(char *));
    for (i = 0; i < row; i++)
        matrice[i] = (char *)malloc(col * sizeof(char));

    // citim matricea initiala
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            fscanf(fin, " %c", &matrice[i][j]);

    fclose(fin);

    //alocam dinamic spatiul din matricea aux = matricea de vecini
    aux = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        aux[i] = (int *)malloc(col * sizeof(int));


    //facem un prim nod al arborelui folosit doar in task-ul 3
    nodArbore = ( arbore *) malloc ( sizeof ( arbore ));
    nodArbore -> head = NULL;
    nodArbore -> left = NULL;
    nodArbore -> right = NULL;

    if (t == 1)
    {
        // afisam matricea initiala
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
                fprintf(fout, "%c", matrice[i][j]);
            fprintf(fout, "\n");
        }
        fprintf(fout, "\n");

        while (k)
        {
            calculVecini(matrice, row, col, aux);
            game(matrice, aux, row, col, nodStiva, nodArbore->right, 1); //chiar daca apelam nodStiva si nodArbore si t este egal cu 1, ele nu vor fi afectate deoarece verificam in game care este numarul task-ului, si aceste noduri vor fi folosite doar pentru task2 si task3

            // afisam fiecare matrice noua generata
            for (i = 0; i < row; i++)
            {
                for (j = 0; j < col; j++)
                    fprintf(fout, "%c", matrice[i][j]);
                fprintf(fout, "\n");
            }
            fprintf(fout, "\n");

            k--; //scadem nr generatiilor
        }
    }
    else if (t == 2)
    {
        int cnt = 1;
        while (cnt <= k) // k = nr de generatii
        {
            push(&nodStiva, &nodLista, cnt);
            calculVecini(matrice, row, col, aux);
            game(matrice, aux, row, col, nodStiva, nodArbore->right, 2);

            cnt++;
        }

        // afisam stiva
        printStiva(nodStiva);
    }
    else if (t == 3 || t == 4)
    {
        //afisam matricea initiala
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
                fprintf(fout, "%c", matrice[i][j]);
            fprintf(fout, "\n");
        }
        fprintf(fout, "\n");

        creareArbore(nodArbore, matrice, aux, row, col, k);

        if( t == 4)
        {//nu e complet
            graf *noduriGraf = NULL; //retinem toate coordonatele celulelor vii din matrice
            noduriGraf = (graf *)malloc(row * col * sizeof(graf));

            int n = 0; //nr de elemnte din vectorul noduriGraf

            for(i = 0; i < row; i++)
                for(j = 0; j < col; j++)
                    if(matrice[i][j] == 'X')
                    {
                        noduriGraf[n].x = i;
                        noduriGraf[n].y = j;
                        n++;
                    }

            int **matriceAdiacenta = NULL;
            matriceAdiacenta = (int **)malloc(row * sizeof(int *));
            for (i = 0; i < row; i++)
                matriceAdiacenta[i] = (int *)malloc(col * sizeof(int));

            for(i = 0; i < row; i++)
                    for(j = 0; j < col; j++)
                        if(noduriVecine(noduriGraf[i], noduriGraf[j]) == 1)
                            if(i != j)
                                matriceAdiacenta[i][j] = 1;
        }
    }


    // eliberam memoria pentru matrici si stiva
    for (i = 0; i < row; i++)
    {
        free(matrice[i]);
        free(aux[i]);
    }

    while (nodStiva != NULL)
    {
        stiva *temp = nodStiva;
        freeLista(nodStiva->headLista);
        nodStiva = nodStiva->next;
        free(temp);
    }

    freeArbore(nodArbore);
    free(matrice);
    free(aux);
    fclose(fout);

    return 0;
}