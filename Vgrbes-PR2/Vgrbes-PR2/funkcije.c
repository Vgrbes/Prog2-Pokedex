#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "header.h"

static int brojPokemona = 0;

void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "wb");

	if (fp == NULL) {
		perror("Kreiranje datoteke pokemoni.bin");
		exit(EXIT_FAILURE);
	}

	fwrite(&brojPokemona, sizeof(int), 1, fp);

	printf("Kreirana datoteka pokemoni.bin\n\n");
	fclose(fp);

}

void dodajpokemona(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje pokemona u datoteku pokemoni.bin");
		exit(EXIT_FAILURE);
	}

	//citamo prvi red datoteke i zapisujemo broj clanova u varijablu brojPokemona
	fread(&brojPokemona, sizeof(int), 1, fp);
	printf("Broj pokemona: %d\n\n", brojPokemona);

	POKEMON temp = { 0 };
	temp.id = brojPokemona;
	getchar();

	printf("Unesite ime pokemona: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite tip pokemona: ");
	scanf("%24[^\n]", temp.tip);
	getchar();


	//pomicemo se na kraj datoteke i zapisujemo tamo
	fseek(fp, sizeof(POKEMON) * brojPokemona, SEEK_CUR);
	fwrite(&temp, sizeof(POKEMON), 1, fp);
	printf("Novi pokemon dodan.\n\n");

	// povratak na pocetak datoteke
	rewind(fp);
	brojPokemona++;

	// zapis novog broja pokemona
	fwrite(&brojPokemona, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajPokemone(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje pokemona iz pokemoni.bin");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojPokemona, sizeof(int), 1, fp);
	printf("Broj pokemona: %d\n", brojPokemona);

	POKEMON* poljePokemona = (POKEMON*)calloc(brojPokemona, sizeof(POKEMON));

	if (poljePokemona == NULL) {
		perror("Zauzimanje memorije za pokemone");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljePokemona, sizeof(POKEMON), brojPokemona, fp);

	printf("Svi pokemoni uspjesno ucitani.\n\n");

	return poljePokemona;
}

void ispisiSvePokemone(const POKEMON* const polje) {

	if (polje == NULL) {
		printf("Polje pokemona prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojPokemona; i++) {
		printf("Pokemon broj %d\tID: %d\tIme: %s\ttip: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->tip);
	}
}

void* pretraziPokemone(POKEMON* const polje) {

	if (polje == NULL) {
		printf("Polje pokemona prazno\n");
		return;
	}

	int i;

	int trazeniId;

	printf("Unesite ID pokemona kojeg trazite: \n");
	scanf("%d", &trazeniId);

	// ako nademo pokemona vracamo cijeli element polja s trazenim id-em
	for (i = 0; i < brojPokemona; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("Pokemon pronaden.\n");

			return (polje + i);
		}
	}

	// vracamo NULL u slucaju da ne nademo nijednog clana s tim id
	return NULL;
}


int izlazIzPrograma(POKEMON* polje) {

	if (remove("pokemoni.bin") == 0)
		printf("Datoteka uspjesno obrisana \n");
	else
		printf("datoteku je nemoguce obrisati \n");
	free(polje);

	return 0;
}

void brisanjePokemona(POKEMON* const polje, const char* const dat) {

	if (brojPokemona == 0) {
		printf("Polje pokemona prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje pokemona");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID pokemona kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojPokemona) {
			printf("Pokemon s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojPokemona);

	POKEMON* pomocnoPolje = (POKEMON*)calloc(brojPokemona - 1, sizeof(POKEMON));

	int counter = 0;

	for (i = 0; i < brojPokemona; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + counter) = *(polje + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(POKEMON), 1, fp);
			counter++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Puska je uspjesno obrisana\n");
}