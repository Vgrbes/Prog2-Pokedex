#ifndef HEADER_H
#define HEADER_H

#include "datatype.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajpokemona(const char* const);
void* ucitajPokemone(const char* const);
void ispisiSvePokemone(const POKEMON* const);
void* pretraziPokemone(POKEMON* const);
int izlazIzPrograma(POKEMON*);
void brisanjePokemona(POKEMON* const, const char* const);


/*
int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajPusku(const char* const);
void* ucitajPuske(const char* const);
void ispisiSve(const PUSKA*);
void ispisiSortirano(const PUSKA*);
void* pretraziPuske(PUSKA* const);
void azurirajPusku(PUSKA*, const char* const);
void brisanjePuske(PUSKA* const, const char* const);
*/



#endif