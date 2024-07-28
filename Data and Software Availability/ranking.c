#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Define a structure to hold a line of text
struct vetor {
    char line[150];
};

// Define a structure to hold information about an amino acid
struct amino {
    char nome[150];
    int pos;
    int rotamero;
    int pontos;
};

// Array to hold the lines read from the file
struct vetor L[10000];

// Array to hold amino acid information
struct amino L2[100000];
int NL2; // Number of elements in L2
int Number_aminacids=18;

char str[9]; // Buffer for temporary string manipulations

// Function to insert or update amino acid information in L2
void insere(char *nome, int pos, int pontos, int rotamero) {
    int ok = 0;

    // If L2 is empty, add the new amino acid
    if (NL2 == 0) {
        strcpy(L2[NL2].nome, nome);
        L2[NL2].pos = pos;
        L2[NL2].pontos = pontos;
        L2[NL2].rotamero = rotamero;
        NL2++;
    } else {
        ok = 0;
        // Check if the amino acid already exists
        for (int k = 0; k < NL2; k++) {
            if (strcmp(L2[k].nome, nome) == 0) {
                // Update if the new points are greater
                if (L2[k].pontos < pontos) {
                    L2[k].pontos = pontos;
                    L2[k].rotamero = rotamero;
                }
                ok = 1;
            }
        }

        // If not found, add it as a new entry
        if (ok == 0) {
            strcpy(L2[NL2].nome, nome);
            L2[NL2].pos = pos;
            L2[NL2].pontos = pontos;
            L2[NL2].rotamero = rotamero;
            NL2++;
        }

        // Sort L2 in descending order of points
        for (int j = 0; j < NL2; j++) {
            for (int k = j + 1; k < NL2; k++) {
                if (L2[j].pontos < L2[k].pontos) {
                    char nome2[20];
                    int posaux, pontosaux, rotameroaux;
                    strcpy(nome2, L2[j].nome);
                    strcpy(L2[j].nome, L2[k].nome);
                    strcpy(L2[k].nome, nome2);

                    posaux = L2[j].pos;
                    L2[j].pos = L2[k].pos;
                    L2[k].pos = posaux;

                    rotameroaux = L2[j].rotamero;
                    L2[j].rotamero = L2[k].rotamero;
                    L2[k].rotamero = rotameroaux;

                    pontosaux = L2[j].pontos;
                    L2[j].pontos = L2[k].pontos;
                    L2[k].pontos = pontosaux;
                }
            }
        }
    }
}

// Function to extract a floating-point number from a substring
float separar(int i, char *string) {
    for (int j = i - 3, k = 0; j < i + 3; j++, k++)
        str[k] = string[j];
    str[8] = '\0'; // Null-terminate the string
    return atof(str);
}

// Function to extract an integer from a substring
int separarint(int i, char *string) {
    for (int j = i - 2, k = 0; j < i + 2; j++, k++)
        str[k] = string[j];
    str[8] = '\0'; // Null-terminate the string
    return atoi(str);
}

// Main function
int main(int argc, char *argv[]) {
    FILE *fp;

    int Na1 = 0, Na2 = 0, i, j;

    // Array of positions to check
    int POS[] = {
        2, 4, 6, 8, 13, 15, 17, 19, 42, 44, 46, 49, 51, 53, 55
    };

    // Open the input file for reading
    fp = fopen(argv[1], "r");   /* ASCII file for reading */
    if (!fp) {
        printf("Error opening the file");
        return 1;
    }

    // Read lines from the input file
    while (fgets(L[Na1].line, sizeof(L[Na1].line), fp)) { /* tsin is FILE* input */
        if (L[Na1].line[0] == 'E' || L[Na1].line[0] == ' ') break;
        Na1++;
    }

    fclose(fp);

    int K;

    // Open the output file for writing
    fp = fopen("ranking.dat", "w");   /* ASCII file for writing */
    if (!fp) {
        printf("Error opening the file");
        return 1;
    }

    // Process each position
    for (K = 0; K < 15; K++) {
        NL2 = 0;
        for (i = 0; i < Na1; i++) {
            char string[1000];
            strcpy(string, L[i].line);

            // Tokenize the line and extract data
            char* token = strtok(string, " ");
            int cont = 1;
            int posicao;
            char amino[4];
            int points;
            int rotameros;

            while (token != NULL) { 
                if (cont == 2)
                    strcpy(amino, token);
                if (cont == 4)
                    posicao = atoi(token); 
                if (cont == 6)
                    points = atoi(token);
                if (cont == 8)
                    rotameros = atoi(token);
                
                token = strtok(NULL, " "); 
                cont++;
            } 

            // Insert amino acid information if the position matches
            if (posicao == POS[K])
                insere(amino, posicao, points, rotameros);
        }

        // Write the results to the output file
        for (int j = 0; j < Number_aminacids; j++)
            fprintf(fp, "%d %s %d %d %d\n", j + 1, L2[j].nome, L2[j].pos, L2[j].pontos, L2[j].rotamero);
    }

    fclose(fp);
    return 0;
}

