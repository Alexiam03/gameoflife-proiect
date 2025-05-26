#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input;
FILE *output;

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

void freeLista(lista *head)
{
    while (head != NULL)
    {
        lista *temp = head;
        head = head->next;
        free(temp);
    }
}

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

void printStiva(stiva *top)
{
    // afisare recursiva pentru ca listele sa fie in ordine crescatoare
    if (top == NULL)
        return;
    else
    {
        printStiva(top->next);
        fprintf(output, "%d", top->generatia);
        lista *nodCurent = top->headLista;

        while (nodCurent != NULL)
        {
            fprintf(output, " %d %d", nodCurent->x, nodCurent->y);
            nodCurent = nodCurent->next;
        }
        fprintf(output, "\n");
    }
}

void freeMatrice(char** matrice, int row)
{
    //elibereaza memoria din matricea de tip char

    for (int i = 0; i < row; i++)
        free(matrice[i]);
    free(matrice);
}

void aflareMatrice(char **matrice, int row, int col, stiva *head)
{
     if (head == NULL)
        return;

    //apelam recursiv
    aflareMatrice(matrice, row, col, head->next);

    
    lista *element = head->headLista;
    while (element != NULL) 
    {
        int x = element->x;
        int y = element->y;

        if (x >= 0 && x < row && y >= 0 && y < col && matrice[x][y] != '\0') //verificam sa nu depaseasca parametrii maximi
        {
            //aplicam modificarile pt casuta de coordonate (x, y)
            if (matrice[x][y] == '+')
                matrice[x][y] = 'X';
            else if (matrice[x][y] == 'X')
                matrice[x][y] = '+';
        }

        element = element->next;
    }
}

int main(int argc, const char *argv[])
{
    int row, col, i, j, k, t;
    // row = nr de linii
    // col = nr de coloane
    stiva *nodStiva = NULL; // nodStiva = top-ul stivei
    lista *nodLista = NULL; // nodLista = head-ul listei

    if (argc < 3)
        return 1;
    input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Nu s-a putut deschide fisierul");
        return 0;
    }
    output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Nu s-a putut deschide fisierul");
        return 0;
    }

    fscanf(input, "%d", &k); //citim nr de generatii
    fscanf(input, "%d %d", &row, &col); //citim nr de linii si coloane
    char **matrice; // = matricea de la generatia k
    int g, x, y; //g va fi numarul generatiei iar x si y coordonatele


    // alocam dinamic spatiul din matrice
    matrice = (char **)malloc(row * sizeof(char *));
    for (i = 0; i < row; i++)
        matrice[i] = (char *)malloc(col * sizeof(char));

    // citim matricea de la generatia k
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            fscanf(input, " %c", &matrice[i][j]);

    // cat timp citim o generatie
    while (fscanf(input, "%d", &g) == 1) 
    {
        //cream un nod nou de tip stiva pt generatia curenta
        stiva *nodNou = (stiva *)malloc(sizeof(stiva));
        nodNou->generatia = g;
        nodNou -> headLista = NULL;
        //legam noul nod la stiva -> ultimul citit va fi primul in stiva
        nodNou->next = nodStiva;
        nodStiva = nodNou;

        int c;
        //citim perechile x y de pe linie
        do {
            if (fscanf(input, "%d %d", &x, &y) != 2)
                break;
            addAtEnd(&nodNou->headLista, x, y); //adaugam in stiva de liste coordonatele

            do {
                c = fgetc(input);
            } while (c == '\r'); //sarim peste newline

            if (c != EOF && c != '\n') //daca am citit cumva un caracter care nu era newline sau final de fisier, il punem inapoi
                ungetc(c, input);

        } while (c != '\n' && c != EOF);
    }

    fclose(input);
    aflareMatrice(matrice, row, col, nodStiva);

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            fprintf(output, "%c", matrice[i][j]);
        fprintf(output, "\n");
    }
        


    // eliberam memoria pentru matrici si stiva
    for (i = 0; i < row; i++)
        free(matrice[i]);

    while (nodStiva != NULL)
    {
        stiva *temp = nodStiva;
        freeLista(nodStiva->headLista);
        nodStiva = nodStiva->next;
        free(temp);
    }
    free(matrice);
    fclose(output);

    return 0;
}