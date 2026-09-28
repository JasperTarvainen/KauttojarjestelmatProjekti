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

    /*Jos ei anneta tiedostoa, luetaan ja käännetään syötteet*/
    FILE *input = stdin;
    FILE *output = stdout;

    /*Tarkistetaan onko liikaa argumentteja*/
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    };

    /*Ensimmäinen on luettava ja toinen palautettava + virheen tarkistus*/
    if (argc >= 2)
        input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }
    if (argc == 3)
        output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
        exit(1);
    }

    struct solmu *alku = NULL;
    char *rivi = NULL;
    size_t koko = 0;

    /* Luetaan rivi kerrallaan ja lisätään listan alkuun */
    while (getline(&rivi, &koko, input) != -1)
    {
        struct solmu *uusi = malloc(sizeof(struct solmu));
        if (uusi == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
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
