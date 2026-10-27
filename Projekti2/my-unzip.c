#include <stdio.h>
#include <stdlib.h>
/*Ohjelmassa käytetyt lähteet: https://www.geeksforgeeks.org/c/fread-function-in-c/ */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        /*Jos ei syötetty tiedostoja, tulostetaan ohje ja poistutaan.*/
        printf("my-unzip, file1 [file2 ...]\n");
        exit(1);
    }

    /*Käydään läpi kaikki annetut tiedostot*/
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("my-unzip: cannot open file\n");
            exit(1);
        }

        int count;
        char c;

        /*Käytetään fread funktiota lukemiseen ja tulostetaan purettu ulostulo*/

        while (fread(&count, sizeof(int), 1, fp) == 1 && fread(&c, sizeof(char), 1, fp) == 1)
        {
            for (int j = 0; j < count; j++)
            {
                putchar(c);
            }
        }
    }
}