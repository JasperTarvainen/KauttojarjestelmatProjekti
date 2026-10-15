#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Käsittelee yhden syötteen kerrallaan ja lukee sen rivikerrallaan loppuun.*/
static void grep_function(FILE *fp, const char *term)
{
    char *line = NULL;
    size_t cap = 0;

    while (getline(&line, &cap, fp) != -1)
    {
        if (strstr(line, term) != NULL)
        {
            printf("%s", line);
        }
    }
    free(line);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    /*Tarkistetaan, että käyttäjä on syöttänyt tarpeeksi argumentteja*/
    {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    const char *term = argv[1];

    /*Jos tiedostoja ei ole annettu, luetaan syötteestä*/
    if (argc == 2)
    {
        grep_function(stdin, term);
        return 0;
    }

    /*jos syötteitä enemmän kuin 2, luetaan tiedostoista.*/
    for (int i = 2; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        }
        grep_function(fp, term);
        fclose(fp);
    }
    return 0;
}