#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "datatype.h"
#include "header.h"

static int brojPokemona = 0;

int izbornik(const char* const ime) {

	printf("\t\t************************************\n\n");
	printf("\t\tOdaberite jednu od ponudenih opcija: \n\n");
	printf("\t\t************************************\n\n");

	printf("\t\tOpcija 1: Kreiranje datoteke!\n");
	printf("\t\tOpcija 2: Dodavanje pokemona!\n");
	printf("\t\tOpcija 3: Ucitaj sve pokemone!\n");
	printf("\t\tOpcija 4: Ispisi podatke o svim pokemonima!\n");
	printf("\t\tOpcija 5: Pretrazivanje pokemona po ID-u!\n");
	printf("\t\tOpcija 6: Brisanje Pokemona!\n\n");
	printf("\t\tOpcija 7: Izlaz iz programa!\n\n");
	printf("\t\t************************************\n\n");

	int odgovor = 0;

	static POKEMON* poljePokemona = NULL;
	static POKEMON* pronadeniPokemon = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) {
	case 1:
		kreiranjeDatoteke(ime);
		break;
	case 2:
		dodajpokemona(ime);
		break;
	case 3:
		if (poljePokemona != NULL) {
			free(poljePokemona);
			poljePokemona = NULL;
		}

		poljePokemona = (POKEMON*)ucitajPokemone(ime);

		if (poljePokemona == NULL) {
			exit(EXIT_FAILURE);
		}
		break;
	case 4:
		ispisiSvePokemone(poljePokemona);
		break;
	case 5:
		pronadeniPokemon = (POKEMON*)pretraziPokemone(poljePokemona);

		if (pronadeniPokemon != NULL) {
			printf("ID: %d\n", pronadeniPokemon->id);
			printf("Ime: %s\n", pronadeniPokemon->ime);
			printf("Tip: %s\n", pronadeniPokemon->tip);
		}
		else {
			printf("Ne postoji pokemon s tim ID-em.\n");
		}

		break;
	case 6:
		if (poljePokemona != NULL) {
			free(poljePokemona);
			poljePokemona = NULL;
		}

		poljePokemona = (POKEMON*)ucitajPokemone(ime);

		brisanjePokemona(poljePokemona, ime);
		break;
	default:
		free(poljePokemona);
		poljePokemona = NULL;
		odgovor = 0;
	}

	return odgovor;
}