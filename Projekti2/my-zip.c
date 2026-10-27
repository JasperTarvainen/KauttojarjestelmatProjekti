#include <stdio.h>
#include <stdlib.h>

/*Ohjelmassa käytetyt lähteet: https://www.geeksforgeeks.org/dsa/run-length-encoding/,
https://www.geeksforgeeks.org/c/fwrite-in-c/, */

/*Funktio kirjoittamaan 4-tavuisen int ja 1 tavuisen merkin stdouttiin.*/
static void write(int count, int c)
{
    char ch = (char)c;
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&ch, sizeof(char), 1, stdout);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        /*Jos ei syötetty tiedostoja, tulostetaan ohjea ja poistutaan.*/
        printf("my-zip, file1 [file2 ...]\n");
        exit(1);
    }

    int count = 0;
    int prev = EOF;

    /*Käydään läpi kaikki annetut tiedostot*/
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("my-zip: cannot open file\n");
            exit(1);
        }

        int c;
        /*Käytetään fgetc, jotta voidaan lukea merkki kerrallaan. Varmistetaan myös että c ei ole EOF*/
        while ((c = fgetc(fp)) != EOF)
        {
            if (prev == EOF)
            {
                prev = c;
                count = 1;
            }
            else if (c == prev)
            {
                count++;
            }
            else
            {
                write(count, prev);
                prev = c;
                count = 1;
            }
        }
        fclose(fp);
    }
}