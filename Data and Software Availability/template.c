#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Structure to hold a line of text from the file
struct vetor {
  char line[100];
};

// Array to hold lines from the file
struct vetor L[100000];

// Temporary string to hold part of a line
char str[9];

// Function to extract a float value from a specific position in a string
float separar(int i, char * string) {

  // Extract a substring from the position i-3 to i+3
  for (int j = i - 3, k = 0; j < i + 3; j++, k++)
    str[k] = string[j];
  str[8] = '\0'; // Null-terminate the string

  return atof(str); // Convert the substring to a float

}

// Function to remove a character from a specific position in a line
void remover(int pos, int l) {
  int i;
  for (i = l; i < strlen(L[pos].line); i++) {
    L[pos].line[i] = L[pos].line[i + 1]; // Shift characters to the left
  }
}

int main() {
  FILE * fp;
  char c;
  int i = 0;

  // Initialize min and max values for coordinates
  float minx = 1000;
  float maxx = -1000;

  float miny = 1000;
  float maxy = -1000;

  float minz = 1000;
  float maxz = -1000;

  // Open the input file for reading
  fp = fopen("antigen.pdb", "r"); /* ASCII file for reading */
  if (!fp) {
    printf("Error opening the file");
    return 1;
  }

  // Read lines from the input file
  while (fgets(L[i].line, sizeof(L[i].line), fp)) {
    i++;
  }

  // Variables to keep track of min and max values for x, y, and z
  int conta;
  for (conta = 0; conta < i - 1; conta++) {

    // Update min and max values for x, y, and z
    if (minx > separar(34, L[conta].line)) {
      minx = separar(34, L[conta].line);
    }
    if (maxx < separar(34, L[conta].line)) {
      maxx = separar(34, L[conta].line);
    }

    if (miny > separar(42, L[conta].line)) {
      miny = separar(42, L[conta].line);
    }
    if (maxy < separar(42, L[conta].line)) {
      maxy = separar(42, L[conta].line);
    }

    if (minz > separar(50, L[conta].line)) {
      minz = separar(50, L[conta].line);
    }
    if (maxz < separar(50, L[conta].line)) {
      maxz = separar(50, L[conta].line);
    }
  }

  // Print the min and max values for x, y, and z
  printf("X min %f max %f\n", minx, maxx);
  printf("Y min %f max %f\n", miny, maxy);
  printf("Z min %f max %f\n", minz, maxz);

  // Open the output file for writing
  fp = fopen("antigen_template.pdb", "w");
  if (!fp) {
    printf("Error opening the file");
    return 1;
  }

  int cont = 0;

  char str[10];
  str[9] = '\0'; // Null-terminate the string

  float px, py, pz;

  // Generate new coordinates within the bounding box
  for (px = minx - 1; px < maxx + 1; px = px + 0.5) {
    for (py = miny - 1; py < maxy+1; py = py + 0.5) {
      for (pz = minz - 1; pz < maxz+1; pz = pz + 0.5) {

        int ok = 1;
        int ok2 = 0;
        int k = 0;
        char atm = 'C';
        while (k < i - 1) {

          float x1, y1, z1;

          x1 = separar(34, L[k].line);
          y1 = separar(42, L[k].line);
          z1 = separar(50, L[k].line);

          // Check if the point is within 3.0 units of any existing point
          if (sqrt(pow(x1 - px, 2) + pow(y1 - py, 2) + pow(z1 - pz, 2)) < 3.0) {
            ok = 0;
          }

          // Check if the point is within a certain range and determine atom type
          if (sqrt(pow(x1 - px, 2) + pow(y1 - py, 2) + pow(z1 - pz, 2)) >= 3.0 && sqrt(pow(x1 - px, 2) + pow(y1 - py, 2) + pow(z1 - pz, 2)) < 3.40) {
            ok2 = 1;
            if (L[k].line[77] == 'S') atm = 'S';
            if (L[k].line[77] == 'O') atm = 'O';
            if (L[k].line[77] == 'O' && L[k].line[17] == 'S' && L[k].line[18] == 'E' && L[k].line[19] == 'R') atm = 'H';
            if (L[k].line[77] == 'O' && L[k].line[17] == 'T' && L[k].line[18] == 'Y' && L[k].line[19] == 'R') atm = 'H';
            if (L[k].line[77] == 'N') atm = 'N';
            if (L[k].line[77] == 'N' && L[k].line[17] == 'T' && L[k].line[18] == 'R' && L[k].line[19] == 'P') atm = 'H';
            if (L[k].line[77] == 'N' && L[k].line[17] == 'A' && L[k].line[18] == 'S' && L[k].line[19] == 'N') atm = 'H';
            if (L[k].line[77] == 'N' && L[k].line[17] == 'G' && L[k].line[18] == 'L' && L[k].line[19] == 'N') atm = 'H';
            if (L[k].line[77] == 'N' && L[k].line[17] == 'A' && L[k].line[18] == 'R' && L[k].line[19] == 'G') atm = 'H';
            if (L[k].line[77] == 'N' && L[k].line[17] == 'H' && L[k].line[18] == 'I' && L[k].line[19] == 'S') atm = 'H';
            if (L[k].line[77] == 'N' && L[k].line[17] == 'L' && L[k].line[18] == 'Y' && L[k].line[19] == 'S') atm = 'H';
          }

          k++;
        }

        // Write the atom to the output file if it meets the criteria
        if (ok == 1 && ok2 == 1) {
          if (atm == 'C') {
            char sinalx = ' ';
            if (px < 0) sinalx = '-';
            char sinaly = ' ';
            if (py < 0) sinaly = '-';
            char sinalz = ' ';
            if (pz < 0) sinalz = '-';

            char espacox[2];
            espacox[0] = ' ';
            espacox[1] = '\0';
            if (fabs(px) >= 10) espacox[0] = '\0';

            char espacoy[2];
            espacoy[0] = ' ';
            espacoy[1] = '\0';
            if (fabs(py) >= 10) espacoy[0] = '\0';

            char espacoz[2];
            espacoz[0] = ' ';
            espacoz[1] = '\0';
            if (fabs(pz) >= 10) espacoz[0] = '\0';

            fprintf(fp, "ATOM    465  C   MOL A  60     %s%c%.3f %s%c%.3f %s%c%.3f  1.00 15.28           C\n", espacox, sinalx, fabs(px), espacoy, sinaly, fabs(py), espacoz, sinalz, fabs(pz));
          }

          if (atm == 'N') {
            char sinalx = ' ';
            if (px < 0) sinalx = '-';
            char sinaly = ' ';
            if (py < 0) sinaly = '-';
            char sinalz = ' ';
            if (pz < 0) sinalz = '-';

            char espacox[2];
            espacox[0] = ' ';
            espacox[1] = '\0';
            if (fabs(px) >= 10) espacox[0] = '\0';

            char espacoy[2];
            espacoy[0] = ' ';
            espacoy[1] = '\0';
            if (fabs(py) >= 10) espacoy[0] = '\0';

            char espacoz[2];
            espacoz[0] = ' ';
            espacoz[1] = '\0';
            if (fabs(pz) >= 10) espacoz[0] = '\0';

            fprintf(fp, "ATOM    465  N   MOL A  60     %s%c%.3f %s%c%.3f %s%c%.3f  1.00 15.28           N\n", espacox, sinalx, fabs(px), espacoy, sinaly, fabs(py), espacoz, sinalz, fabs(pz));
          }

          if (atm == 'H') {
            char sinalx = ' ';
            if (px < 0) sinalx = '-';
            char sinaly = ' ';
            if (py < 0) sinaly = '-';
            char sinalz = ' ';
            if (pz < 0) sinalz = '-';

            char espacox[2];
            espacox[0] = ' ';
            espacox[1] = '\0';
            if (fabs(px) >= 10) espacox[0] = '\0';

            char espacoy[2];
            espacoy[0] = ' ';
            espacoy[1] = '\0';
            if (fabs(py) >= 10) espacoy[0] = '\0';

            char espacoz[2];
            espacoz[0] = ' ';
            espacoz[1] = '\0';
            if (fabs(pz) >= 10) espacoz[0] = '\0';

            fprintf(fp, "ATOM    465  H   MOL A  60     %s%c%.3f %s%c%.3f %s%c%.3f  1.00 15.28           H\n", espacox, sinalx, fabs(px), espacoy, sinaly, fabs(py), espacoz, sinalz, fabs(pz));
          }

          if (atm == 'O') {
            char sinalx = ' ';
            if (px < 0) sinalx = '-';
            char sinaly = ' ';
            if (py < 0) sinaly = '-';
            char sinalz = ' ';
            if (pz < 0) sinalz = '-';

            char espacox[2];
            espacox[0] = ' ';
            espacox[1] = '\0';
            if (fabs(px) >= 10) espacox[0] = '\0';

            char espacoy[2];
            espacoy[0] = ' ';
            espacoy[1] = '\0';
            if (fabs(py) >= 10) espacoy[0] = '\0';

            char espacoz[2];
            espacoz[0] = ' ';
            espacoz[1] = '\0';
            if (fabs(pz) >= 10) espacoz[0] = '\0';

            fprintf(fp, "ATOM    465  O   MOL A  60     %s%c%.3f %s%c%.3f %s%c%.3f  1.00 15.28           O\n", espacox, sinalx, fabs(px), espacoy, sinaly, fabs(py), espacoz, sinalz, fabs(pz));
          }
        }
      }
    }
  }

  // Write the END line to the output file
  fprintf(fp, "END\n");

  // Close the output file
  fclose(fp);
  return 0;
}

