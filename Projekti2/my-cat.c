#include <stdio.h>
#include <stdlib.h>

/*Ohjelmassa on käytettä seuraavia lähteitä: https://www.geeksforgeeks.org/c/build-your-own-cat-command-in-c-for-linux/, https://stackoverflow.com/questions/46982380/c-programming-reading-multiple-files-technique*/

/*Parametreinä argc on argumenttien määrä ja argv merkkijonotaulukko*/
int main(int argc, char *argv[])
{
    char buffer[1024];

    /*Aloitetaan indeksistä 1, jos ei annettu syötteenä yhtään tiedostoa, silmukka ei suoridu kertaakaan (i < argc)*/
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("my-cat: cannot open file\n");
            exit(1);
        }
        /*Lukee tiedostosta rivin kerrallaan puskuriin buffer, jo toistuu niin kauan kunnes tiedosto loppuu.*/
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            /*Tulostaa jokaisen rivin*/
            printf("%s", buffer);
        }
        fclose(fp);
    }
    return 0;
}