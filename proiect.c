#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;
FILE *fout;

struct lista{
    int x, y;
    struct lista* next;
};
typedef struct lista lista;

struct stiva {
    int generatia;
    lista* headLista;
    struct stiva* next;
};
typedef struct stiva stiva;

void addAtBeginning ( lista ** head , int x, int y)
{
// *head , inceputul listei se va modifica
// x, y,  informatia de stocat
lista * newNode = ( lista *) malloc ( sizeof ( lista ));
    newNode -> x = x;
    newNode -> y = y;
    newNode -> next = * head ;
    * head = newNode ;
}


void addAtEnd ( lista ** head , int x, int y){
    lista * aux = * head ;
    lista * newNode = ( lista *) malloc ( sizeof ( lista ));
    newNode -> x = x;
    newNode -> y = y;         // stocheaza informatia nodului nou
   
    if (* head == NULL ) addAtBeginning (&* head , x, y);  // daca lista este vida , se modifica adresa de inceput
    else { // cat timp nu s-a ajuns la final , se parcurge
        while (aux -> next != NULL ) aux = aux -> next ;
             // se adauga noul element in lista
        aux -> next = newNode ;
        newNode -> next = NULL ; // final lista
    }
}


void push ( stiva **top , lista **head, int gen) {
    stiva * newNode =( stiva *) malloc ( sizeof ( stiva ));
    newNode -> generatia = gen;

    lista *copie = NULL;
    lista *elemCurent = *head;

    while(elemCurent != NULL)
    {
        addAtEnd(&copie, elemCurent -> x, elemCurent -> y);
        elemCurent = elemCurent -> next;
    }
    newNode ->headLista = *head;
    newNode -> next = *top;
    *top = newNode ;
}


void calculVecini(char **matrice, int row, int col, int **aux)
{
    int nrVecini = 0, i, j;

    for(j = 1; j < col - 1; j++)
    {//facem verificarea pentru linia 0 

        nrVecini = 0;
        if(matrice[0][j-1] == 'X')
            nrVecini++;
        if(matrice[0][j+1] == 'X')
            nrVecini++;
        if(matrice[1][j-1] == 'X')
            nrVecini++;
        if(matrice[1][j] == 'X')
            nrVecini++;
        if(matrice[1][j+1] == 'X')
            nrVecini++;
        aux[0][j] = nrVecini;
    }

    for(j = 1; j < col - 1; j++)
    {//facem verificarea pentru ultima linie

        nrVecini = 0;
        if(matrice[row-1][j-1] == 'X')
            nrVecini++;
        if(matrice[row-1][j+1] == 'X')
            nrVecini++;
        if(matrice[row-2][j-1] == 'X')
            nrVecini++;
        if(matrice[row-2][j] == 'X')
            nrVecini++;
        if(matrice[row-2][j+1] == 'X')
            nrVecini++;
        aux[row-1][j] = nrVecini;
    }

    for(i = 1; i < row - 1; i++)
    {//facem verificarea pentru prima coloana
        nrVecini = 0;
        if(matrice[i][1] == 'X')
            nrVecini++;
        if(matrice[i-1][0] == 'X')
            nrVecini++;
        if(matrice[i-1][1] == 'X')
            nrVecini++;
        if(matrice[i+1][0] == 'X')
            nrVecini++;
        if(matrice[i+1][1] == 'X')
            nrVecini++;
        aux[i][0] = nrVecini;
    }

    for(i = 1; i < row - 1; i++)
    {//facem verificarea pentru ultima coloana
        nrVecini = 0;
        if(matrice[i-1][col-1] == 'X')
            nrVecini++;
        if(matrice[i-1][col-2] == 'X')
            nrVecini++;
        if(matrice[i][col-2] == 'X')
            nrVecini++;
        if(matrice[i+1][col-2] == 'X')
            nrVecini++;
        if(matrice[i+1][col-1] == 'X')
            nrVecini++;
        aux[i][col-1] = nrVecini;
    }


    // facem verificarea pentru interiorul matricei
    for( i = 1; i < row - 1; i++)
        for( j = 1; j < col - 1; j++)
            {
                nrVecini = 0;

                if(matrice[i][j-1] == 'X')
                    nrVecini++;
                if(matrice[i-1][j-1] == 'X')
                    nrVecini++;
                if(matrice[i-1][j] == 'X')
                    nrVecini++;
                if(matrice[i-1][j+1] == 'X')
                    nrVecini++;
                if(matrice[i][j+1] == 'X')
                    nrVecini++;
                if(matrice[i+1][j+1] == 'X')
                    nrVecini++;
                if(matrice[i+1][j] == 'X')
                    nrVecini++;
                if(matrice[i+1][j-1] == 'X')
                    nrVecini++;

                aux[i][j] = nrVecini;
            }

        nrVecini = 0;
        //facem verificarea pentru colt stg sus
        if(matrice[0][1] == 'X')
            nrVecini++;
        if(matrice[1][1] == 'X')
            nrVecini++;
        if(matrice[1][0] == 'X')
            nrVecini++;
        aux[0][0] = nrVecini;

        nrVecini = 0;
        //facem verificarea pentru colt dr sus
        if(matrice[0][col-2] == 'X')
            nrVecini++;
        if(matrice[1][col-2] == 'X')
            nrVecini++;
        if(matrice[1][col-1] == 'X')
            nrVecini++;
        aux[0][col-1] = nrVecini;

        nrVecini = 0;
        //facem verificarea pentru colt stg jos
        if(matrice[row-2][0] == 'X')
            nrVecini++;
        if(matrice[row-2][1] == 'X')
            nrVecini++;
        if(matrice[row-1][1] == 'X')
            nrVecini++;
        aux[row-1][0] = nrVecini;

        nrVecini = 0;
        //facem verificarea pentru colt dr jos
        if(matrice[row-2][col-1] == 'X')
            nrVecini++;
        if(matrice[row-2][col-2] == 'X')
            nrVecini++;
        if(matrice[row-1][col-2] == 'X')
            nrVecini++;
        aux[row-1][col-1] = nrVecini;

}

void game ( char **matrice, int **aux, int row, int col, stiva *head)
{
    int i, j;

    for(i = 0; i < row; i++)
        for(j = 0; j < col; j++)
            {//verificam daca respectiva casuta este vie/moarta si aplicam regulile jocului
                if(matrice[i][j] == '+')
                    if(aux[i][j] == 3)
                    {
                        addAtEnd(&head -> headLista, i, j);  
                        matrice[i][j] = 'X';
                    }
                if(matrice[i][j] == 'X')
                    if(aux[i][j] < 2)
                    {
                        addAtEnd(&head -> headLista, i, j); 
                         matrice[i][j] = '+';
                    }
                    else if(aux[i][j] > 3)
                    {
                        addAtEnd(&head -> headLista, i, j); 
                        matrice[i][j] = '+';
                    }
            }
}

void printStiva(stiva* top) {
    //afisare recursiva pentru ca listele sa fie in ordine crescatoare
    if (top == NULL)
        return;
    else{
        printStiva(top ->next);
        fprintf(fout, "%d: ", top -> generatia);
        lista *nodCurent = top -> headLista;

        while(nodCurent != NULL)
        {
            fprintf(fout, "(%d %d); ", nodCurent -> x, nodCurent -> y);
            nodCurent = nodCurent -> next;
        }

        fprintf(fout, "\n");

    }
}

int main (int argc, const char* argv[])
{
    int row, col, i, j, k, t;
    //row = nr de linii 
    //col = nr de coloane
    stiva *nodStiva = NULL; //nodStiva = top-ul stivei
    lista *nodLista = NULL; //nodLista = head-ul listei

    if(argc < 3)
    return 1;

    fin = fopen(argv[1], "r");
    if(fin == NULL)
    {
        printf("Nu s-a putut deschide fisierul");
        return 0;
    }

    fout = fopen(argv[2], "w");
    if(fout == NULL)
    {
        printf("Nu s-a putut deschide fisierul");
        return 0;
    }

    fscanf(fin, "%d", &t);
    fscanf(fin, "%d %d", &row, &col);
    fscanf(fin, "%d", &k);
    int **aux; // aux e folosita pentru a stoca numarul de vecini egali cu X ai matricei
    char **matrice;
    
    //alocam dinamic spatiul din matrice
    matrice = (char**)malloc(row * sizeof(char *));
    for( i = 0; i < row; i++)
        matrice[i] = (char *)malloc( col * sizeof(char));

    // Introduceti matricea 
    for( i = 0; i < row; i++)
        for( j = 0; j < col; j++)
            fscanf(fin, " %c", &matrice[i][j]);
    
    fclose(fin);

    aux = (int**)malloc(row * sizeof(int *));
    for( i = 0; i < row; i++)
        aux[i] = (int *)malloc(col * sizeof(int));
 
    int cnt = 1;
    while(cnt <= k)
        {
            push(&nodStiva, &nodLista, cnt);
            calculVecini(matrice, row, col, aux);
            game(matrice, aux, row, col, nodStiva);

            cnt++;
        }
   
     //afisam stiva
           printStiva(nodStiva);

    //eliberam memoria pentru matrici si stiva de liste
    for( i = 0; i < row; i++)
        {
            free(matrice[i]);
            free(aux[i]);
        }

    free(matrice);
    free(aux);
    while (nodStiva != NULL) 
    {
        stiva* temp = nodStiva;
        freeLista(nodStiva->headLista); 
        nodStiva = nodStiva->next;
        free(temp);
    }
   // fclose(fin);
    fclose(fout);

    return 0;
}