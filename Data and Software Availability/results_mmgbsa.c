#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Define a structure to hold a line of text
struct vetor {
    char line[100];
};

// Declare arrays of structures to hold lines from files
struct vetor L[100000];
struct vetor L2[100000];

// String buffer for extracting substrings
char str[8];

// Function to extract a float value from a specific part of a string
float separar(int i, char *string) {
    // Extract a substring from the input string
    for (int j = i - 3, k = 0; j < i + 3; j++, k++)
        str[k] = string[j];
    str[7] = '\0'; // Null-terminate the string

    // Convert the substring to a float and return it
    return atof(str);
}

// Function to compare two lines for sorting
int compare_lines(const void *a, const void *b) {
    // Convert void pointers to char pointers
    const char *line_a = *(const char **)a;
    const char *line_b = *(const char **)b;

    // Extract the energy values from the end of each line
    float energy_a, energy_b;
    
    // Ensure we read the correct amount of space (8 chars) to account for '\n' or spaces after float
    sscanf(line_a + strlen(line_a) - 9, "%f", &energy_a);
    sscanf(line_b + strlen(line_b) - 9, "%f", &energy_b);

    // Compare the energy values
    if (energy_a < energy_b) return -1;
    if (energy_a > energy_b) return 1;
    return 0;
}

// Function to sort the file
void sort_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file for reading\n");
        return;
    }

    // Read all lines into memory
    char *lines[10000];
    int count = 0;
    while (1) {
        lines[count] = (char*)malloc(256);
        if (fgets(lines[count], 256, fp) == NULL) break;
        count++;
    }
    fclose(fp);

    // Sort the lines
    qsort(lines, count, sizeof(char *), compare_lines);

    // Write sorted lines back to file
    fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file for writing\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fputs(lines[i], fp);
        free(lines[i]); // Free the allocated memory
    }
    fclose(fp);
}

int main() {
    FILE *fp;
    // Open the results file for appending
    fp = fopen("Population_classification.dat", "a+");
    fclose(fp); // Close the file after opening

    char c;
    for (int pop = 1; pop <= 12; pop++) {

        int i = 0;
        int N2 = 0;

        char nome_arquivo[50];
        // Create the file name based on the current population index
        sprintf(nome_arquivo, "pasta%d/antibody.pdb", pop);
        printf("%s\n", nome_arquivo);

        // Open the pdb file for reading
        fp = fopen(nome_arquivo, "r");
        if (!fp) {
            // Print an error message if the file cannot be opened
            printf("Error opening file");
            return 1;
        }

        // Read lines from the pdb file into the L array
        while (fgets(L[i].line, sizeof(L[i].line), fp)) {
            i++;
        }

        fclose(fp); // Close the pdb file

        // Create the file name for the results file
        sprintf(nome_arquivo, "pasta%d/FINAL_RESULTS_MMPBSA.dat", pop);
        // Open the results file for reading
        fp = fopen(nome_arquivo, "r");
        if (!fp) {
            // Print an error message if the file cannot be opened
            printf("Error opening file");
            return 1;
        }

        // Read lines from the results file into the L2 array
        while (fgets(L2[N2].line, sizeof(L2[N2].line), fp)) {
            N2++;
        }

        fclose(fp); // Close the results file

        // Open the results_mmgbsa.dat file for appending
        fp = fopen("Population_classification.dat", "a+");
        int vet[] = {2, 4, 6, 8, 13, 15, 17, 19, 42, 44, 46, 49, 51, 53, 55};
        // Loop through the predefined values
        for (int j = 0; j < 15; j++) {
            // Loop through the lines read from the pdb file
            for (int k = 0; k < i; k++) {
                int valor = separar(25, L[k].line);
                // If the extracted value matches one of the predefined values
                if (valor == vet[j]) {
                    // Write the line to the results file
                    fprintf(fp, "%c%c%c %d ", L[k].line[17], L[k].line[18], L[k].line[19], vet[j]);
                    k = i; // Exit the inner loop
                }
            }
        }
        // Write the final float value to the results file
        fprintf(fp, "%.3f \n", separar(30, L2[87].line));

        fclose(fp); // Close the results_mmgbsa.dat file
    }
    
       sort_file("Population_classification.dat");

    return 0;
}

