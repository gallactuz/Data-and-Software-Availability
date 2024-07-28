#include <stdio.h>  // Standard I/O library for reading and writing files
#include <string.h> // String manipulation library
#include <stdlib.h> // Standard library for memory allocation, process control, etc.
#include <math.h>   // Math library for mathematical operations

#define CUTOFF_RADIUS 0.5 // Defines the cutoff radius used for scoring interactions

// Structure that stores information about a line in the PDB file
struct vetor {
  char line[150]; // Array to store a single line from the PDB file
};

// Arrays that store the PDB files
struct vetor L[10000];   // Array to store lines from the first PDB file
struct vetor L2[100000]; // Array to store lines from the second PDB file

char str[9]; // Temporary string used for substring extraction

// Function that converts a substring to a float
float separar(int i, char *string) {
  for (int j = i - 3, k = 0; j < i + 3; j++, k++) // Extracts 6 characters around position i
    str[k] = string[j]; // Copies the characters to the temporary string
  str[8] = '\0';        // Null-terminates the string

  return atof(str); // Converts the extracted substring to a float
}

// Function that converts a substring to an integer
int separarint(int i, char *string) {
  for (int j = i - 2, k = 0; j < i + 2; j++, k++) // Extracts 4 characters around position i
    str[k] = string[j]; // Copies the characters to the temporary string
  str[8] = '\0';        // Null-terminates the string

  return atoi(str); // Converts the extracted substring to an integer
}

// Main function
int main(int argc, char *argv[]) {
  FILE *fp; // File pointer for reading and writing files

  int Na1 = 0, Na2 = 0; // Counters for the number of lines in each PDB file

  fp = fopen(argv[1], "r"); // Opens the first PDB file for reading
  if (!fp) {
    printf("Error opening file %s\n", argv[1]); // Error message if the file cannot be opened
    return 1;
  }

  char line[150] = ""; // Initialize the line buffer to 0 ('\0')

  while (fgets(L[Na1].line, sizeof(line), fp)) { // Reads each line from the file into the array L
    if (L[Na1].line[0] == 'E' || L[Na1].line[0] == ' ') // Stops reading if the line starts with 'E' or is blank
      break;
    Na1++; // Increment the line counter
  }

  fclose(fp); // Closes the first PDB file

  fp = fopen(argv[2], "r"); // Opens the second PDB file for reading
  if (!fp) {
    printf("Error opening file %s\n", argv[2]); // Error message if the file cannot be opened

    return 1;
  }

  char line2[150] = ""; // Initialize the line buffer to 0 ('\0')

  while (fgets(L2[Na2].line, sizeof(line2), fp)) { // Reads each line from the file into the array L2
    if (L2[Na2].line[0] == 'E' || L2[Na2].line[0] == ' ') // Stops reading if the line starts with 'E' or is blank
      break;
    Na2++; // Increment the line counter
  }

  fclose(fp); // Closes the second PDB file

  // Opens the output file for appending scores
  fp = fopen("score.dat", "a");
  if (!fp) {
    printf("Error opening file\n"); // Error message if the file cannot be opened

    return 1;
  }

  int posicao = atoi(argv[3]), pos, k, pontos = 0, Nres = 0; // Variables for the position, score, and residue count

  for (pos = 0; pos < Na1; pos++) { // Iterates over each line in the first PDB file
    if (separarint(25, L[pos].line) == posicao && L[pos].line[77] != 'H') { // Checks if the line corresponds to the specified position and is not a hydrogen atom

      Nres++; // Increments the residue count
      for (k = 0; k < Na2; k++) { // Iterates over each line in the second PDB file

        float x1, y1, z1, px, py, pz; // Variables for coordinates

        // Extracts the coordinates from the current line of the second PDB file
        x1 = separar(34, L2[k].line);
        y1 = separar(42, L2[k].line);
        z1 = separar(51, L2[k].line);

        // Extracts the coordinates from the current line of the first PDB file
        px = separar(34, L[pos].line);
        py = separar(42, L[pos].line);
        pz = separar(51, L[pos].line);

        // Calculates the distance between the points and checks if it falls within the cutoff radius
        if (sqrt(pow(x1 - px, 2) + pow(y1 - py, 2) + pow(z1 - pz, 2)) >= .00 && sqrt(pow(x1 - px, 2) + pow(y1 - py, 2) + pow(z1 - pz, 2)) < CUTOFF_RADIUS) {

          // Updates the score based on the atom types and specific conditions
          if (L2[k].line[77] == 'C' && L[pos].line[77] == 'C') pontos += 17; // Carbon-Carbon interaction
          if (L2[k].line[77] == 'C' && L[pos].line[77] == 'N') pontos -= 95; // Carbon-Nitrogen interaction
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'C') pontos -= 95; // Nitrogen-Carbon interaction
          if (L2[k].line[77] == 'C' && L[pos].line[77] == 'O') pontos -= 95; // Carbon-Oxygen interaction
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'C') pontos -= 95; // Oxygen-Carbon interaction
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'O') pontos -= 95; // Oxygen-Oxygen interaction
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'N') pontos -= 95; // Nitrogen-Nitrogen interaction
          if (L2[k].line[77] == 'H' && L[pos].line[77] == 'N' && L[pos].line[17] == 'H' && L[pos].line[18] == 'I' && L[pos].line[19] == 'S') pontos += 150; // Specific interactions involving histidine
          if (L2[k].line[77] == 'H' && L[pos].line[77] == 'O' && L[pos].line[17] == 'A' && L[pos].line[18] == 'S' && L[pos].line[19] == 'N') pontos += 150; // Specific interactions involving asparagine
          if (L2[k].line[77] == 'H' && L[pos].line[77] == 'O' && L[pos].line[17] == 'G' && L[pos].line[18] == 'L' && L[pos].line[19] == 'N') pontos += 150; // Specific interactions involving glutamine
          if (L2[k].line[77] == 'H' && L[pos].line[77] == 'O' && L[pos].line[17] == 'G' && L[pos].line[18] == 'L' && L[pos].line[19] == 'U') pontos += 150; // Specific interactions involving glutamic acid
          if (L2[k].line[77] == 'H' && L[pos].line[77] == 'O' && L[pos].line[17] == 'A' && L[pos].line[18] == 'S' && L[pos].line[19] == 'P') pontos += 150; // Specific interactions involving aspartic acid
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'O' && L[pos].line[17] == 'S' && L[pos].line[18] == 'E' && L[pos].line[19] == 'R') pontos += 150; // Specific interactions involving serine
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'O' && L[pos].line[17] == 'T' && L[pos].line[18] == 'Y' && L[pos].line[19] == 'R') pontos += 150; // Specific interactions involving tyrosine
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'N' && L[pos].line[17] == 'T' && L[pos].line[18] == 'R' && L[pos].line[19] == 'P') pontos += 150; // Specific interactions involving tryptophan
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'N' && L[pos].line[17] == 'A' && L[pos].line[18] == 'S' && L[pos].line[19] == 'N') pontos += 150; // Specific interactions involving asparagine
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'N' && L[pos].line[17] == 'G' && L[pos].line[18] == 'L' && L[pos].line[19] == 'N') pontos += 150; // Specific interactions involving glutamine
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'N' && L[pos].line[17] == 'A' && L[pos].line[18] == 'R' && L[pos].line[19] == 'G') pontos += 150; // Specific interactions involving arginine
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'N' && L[pos].line[17] == 'H' && L[pos].line[18] == 'I' && L[pos].line[19] == 'S') pontos += 150; // Specific interactions involving histidine
          if (L2[k].line[77] == 'O' && L[pos].line[77] == 'N' && L[pos].line[17] == 'L' && L[pos].line[18] == 'Y' && L[pos].line[19] == 'S') pontos += 150; // Specific interactions involving lysine
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'O' && L[pos].line[17] == 'S' && L[pos].line[18] == 'E' && L[pos].line[19] == 'R') pontos += 150; // Specific interactions involving serine
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'O' && L[pos].line[17] == 'T' && L[pos].line[18] == 'Y' && L[pos].line[19] == 'R') pontos += 150; // Specific interactions involving tyrosine
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'N' && L[pos].line[17] == 'T' && L[pos].line[18] == 'R' && L[pos].line[19] == 'P') pontos += 150; // Specific interactions involving tryptophan
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'N' && L[pos].line[17] == 'A' && L[pos].line[18] == 'S' && L[pos].line[19] == 'N') pontos += 150; // Specific interactions involving asparagine
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'N' && L[pos].line[17] == 'G' && L[pos].line[18] == 'L' && L[pos].line[19] == 'N') pontos += 150; // Specific interactions involving glutamine
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'N' && L[pos].line[17] == 'A' && L[pos].line[18] == 'R' && L[pos].line[19] == 'G') pontos += 150; // Specific interactions involving arginine
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'N' && L[pos].line[17] == 'H' && L[pos].line[18] == 'I' && L[pos].line[19] == 'S') pontos += 150; // Specific interactions involving histidine
          if (L2[k].line[77] == 'N' && L[pos].line[77] == 'N' && L[pos].line[17] == 'L' && L[pos].line[18] == 'Y' && L[pos].line[19] == 'S') pontos += 150; // Specific interactions involving lysine
        }
      }
    }
  }

  // Prints the number of residues and the score information
  printf(">>>>>>>>>>>%d\n", Nres); // Prints the number of residues
  printf("Resid= %s pos= %d score= %d  rotamer %d\n", argv[5], posicao, (pontos) / Nres, atoi(argv[4])); // Prints the residue, position, score, and rotamer
  fprintf(fp, "Resid=  %s pos=  %d   score=   %d    rotamer   %d  \n", argv[5], posicao, (pontos) / Nres, atoi(argv[4])); // Writes the information to the output file

  fclose(fp); // Closes the output file

  return 0; // Returns 0 to indicate successful execution
}

