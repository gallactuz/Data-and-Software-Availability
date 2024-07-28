#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_LEN 100

// Structure to hold a line of text
struct vetor {
    char line[200];
};

// Arrays to hold lines from files
struct vetor L[100000];
struct vetor L2[100000];

// Function to perform mutation
void realizar_mutacao(char *sequencia, char *res_novo) {
    int k = 0;
    // Adjust k if the new residue (res_novo) has a length of 5
    if (strlen(res_novo) == 5)
        k = 1;

    // Iterate through the sequence to find a place to apply the mutation
    for (int i = 0; i < strlen(sequencia) - 1; i++) {
        // Check if the last two characters of the new residue match the position in the sequence
        if (res_novo[4 - k] == sequencia[i] && res_novo[5 - k] == sequencia[i + 1]) {
            // Replace the residue at the indicated position
            sequencia[i + 1] = res_novo[5 - k];
            sequencia[i] = res_novo[4 - k];
            sequencia[i - 1] = res_novo[3 - k];
            sequencia[i - 2] = res_novo[2 - k];
            sequencia[i - 3] = res_novo[1 - k];
            sequencia[i - 4] = res_novo[0 - k];
        }
    }
}

// Function to extract a float value from a specific part of the string
float separar(int i, char *string) {
    char str[10];
    // Extract 6 characters from the string around position i
    for (int j = i - 3, k = 0; j < i + 3; j++, k++)
        str[k] = string[j];
    str[7] = '\0'; // Null-terminate the string
    return atof(str); // Convert the string to a float
}

// Function to compare if two strings are equal
int igual(char *str1, char *str2) {
    int ok = 1;
    for (int i = 0; i < 100; i++)
        if (str1[i] != str2[i])
            ok = 0;
    return ok;
}

// Function to check if a string exists in an array of structures
int verifica(struct vetor *Li, int N, char *str) {
    int ok = 0;
    for (int i = 0; i < N; i++) {
        if (igual(str, Li[i].line) == 1)
            ok = 1;
    }
    return ok;
}

int main() {
    FILE *fp;
    char c;
    int i = 0;
    int N2 = 0;

    // Open the file for reading
    fp = fopen("Population_classification.dat", "r"); // ASCII file for reading
    if (!fp) {
        printf("Error opening file\n"); // Error message if the file cannot be opened
        return 1;
    }


    // Read lines from the file into the L array
    while (fgets(L[i].line, sizeof(L[i].line), fp)) {
        L[i].line[101] = '\0'; // Ensure null-termination
        i++;
    }

    fclose(fp);

    // Open a file for writing
    fp = fopen("crossing_over.dat", "w");
    int corte = 51;
    char m;
    char str1[200], str2[200];

    // Perform crossing over and mutations
  for (int j = 0; j < 12; j = j + 2) {

    strcpy(str1, L[j].line);
    strcpy(str2, L[j + 1].line);

    for (int l = 0; l < corte; l++) {
      str2[l] = L[j].line[l];
      str1[l] = L[j + 1].line[l];

    }
    //crossing two beta strands
    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 0; l < 24; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }

      for (int l = 72; l < 100; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }

    }
    //crossing four beta strands
    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 5; l < 9; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
      for (int l = 17; l < 21; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
      for (int l = 30; l < 35; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
      for (int l = 44; l < 48; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
      for (int l = 58; l < 62; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
      for (int l = 72; l < 76; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
      for (int l = 86; l < 90; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }

    }
    //crossing single residues
    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 50; l < 58; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 59; l < 63; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 64; l < 71; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 71; l < 78; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 78; l < 85; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 85; l < 92; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }
    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 92; l < 99; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 0; l < 4; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 4; l < 10; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 10; l < 16; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 16; l < 22; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 22; l < 29; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 29; l < 36; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 36; l < 43; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    if (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {

      for (int l = 43; l < 50; l++) {
        char c = str2[l];
        str2[l] = str1[l];
        str1[l] = c;

      }
    }

    // Check for valid permutations and prompt for mutations if necessary
    while (verifica(L, i, str1) == 1 || verifica(L, i, str2) == 1) {
      printf("Copy error: no effective permutation\n%s\n%s\n", str1, str2);
      if (verifica(L, i, str1) == 1) {
        printf("Insert mutation\n%s\n", str1);
        char res_novo[MAX_LEN];
        printf("Enter the new residue (e.g., GLU 55): ");
        scanf("%[^\n]%*c", res_novo); // Read until newline and remove newline
        // Apply the mutation
        realizar_mutacao(str1, res_novo);
      }
      if (verifica(L, i, str2) == 1) {
        printf("Insert mutation\n%s\n", str2);
        char res_novo[MAX_LEN];
        printf("Enter the new residue (e.g., GLU 55): ");
        scanf("%[^\n]%*c", res_novo); // Read until newline and remove newline
        // Apply the mutation
        realizar_mutacao(str2, res_novo);
      }

    }

    strcpy(L2[j].line, str1);
    strcpy(L2[j + 1].line, str2);

  }

  for (int j = 0; j < 12; j++)
    fprintf(fp, "%d  %s\n", j + 1, L2[j].line);

  fclose(fp);
  return 0;
}
