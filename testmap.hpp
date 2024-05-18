#ifndef TEST_MAP
#define TEST_MAP

#include <iostream>
#include <thread>
#include <chrono>
#include "data.hpp"
#include "DefParam.hpp"


enum Tour{
    TRAVAILLEURS,
    SOLDATS,
    MAGICIENS,
    NONE
};

// data_batiment village1 = {0.8,1,0,0};
// data_batiment forteresse1 = {0.5,1,2,0.5};
// data_batiment magie1 = {0.6,2,1,0.75};

// data_troupes_de_guerre sol1 = {0.5,1,5,0};
// data_troupes_de_guerre sol11 = {0.75,3,15,0};
// data_troupes_de_guerre mag1 = {1,2,3,5};

// data_joueur jou1 = {"Manpreet",10,5,village1,forteresse1,magie1,{sol1,sol11},{mag1},0,0,0,0,0,0,0,0,0};

// data_batiment village2 = {1,1,0,0};
// data_batiment forteresse2 = {0.7,3,2,0.5};
// data_batiment magie2 = {0.5,2,0,0.75};

// data_troupes_de_guerre sol2 = {1,1,5,0};
// data_troupes_de_guerre sol22 = {0.5,3,5,0};
// data_troupes_de_guerre sol222 = {0,1,1,0};
// data_troupes_de_guerre mag2 = {1,3,15,0};
// data_troupes_de_guerre mag22 = {0.5,2,3,5};

// data_joueur jou2 = {"Thomas",15,6,village2,forteresse2,magie2,{sol2,sol22,sol222},{mag2,mag22},0,0,0.3,0,0,0,0,0,0};

// data DONNEES = {jou1,jou2,"debut",2};

extern Tour tourjeu;

// choix (1 attaquer, 0 defendre, 2 soigner)
extern int choix;


// permet de tester si les valeurs change à partir de la boucle de l'interface graph
void changeVillage2(data* donnees) ;

void changesold2avant(data* donnees) ;

void changesold2apres(data* donnees) ;

void changemag2avant(data* donnees) ;

void changemag2apres(data* donnees) ;

void changesold1avant(data* donnees) ;

void changesold1apres(data* donnees);

void changemag1avant(data* donnees);

void changemag1apres(data* donnees) ;

// METTRE DES FLECHE AUTOUR DU SOLDAT POUR SELECTIONNER CELUI A ATTAQUER


#endif