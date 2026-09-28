#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct solmu
{
    char *rivi;
    struct solmu *seuraava;
};

int main(int argc, char *argv[])
{

    FILE *input = stdin;
    FILE *output = stdout;

    /*Ensimmäinen on luettava ja toinen palautettava*/
    if (argc >= 2)
        input = fopen(argv[1], "r");
    if (argc >= 3)
        output = fopen(argv[2], "w");

    struct solmu *alku = NULL;
    char *rivi = NULL;
    size_t koko = 0;

    /* Luetaan rivi kerrallaan ja lisätään listan alkuun */
    while (getline(&rivi, &koko, input) != -1)
    {
        struct solmu *uusi = malloc(sizeof(struct solmu));
        uusi->rivi = rivi;
        uusi->seuraava = alku;
        alku = uusi;

        rivi = NULL;
        koko = 0;
    }

    /* Tulostetaan käänteisessä järjestyksessä */
    while (alku != NULL)
    {
        fprintf(output, "%s", alku->rivi);
        alku = alku->seuraava;
    }

    fclose(input);
    fclose(output);

    return 0;
}
