#ifndef DEF_PARAM 
#define DEF_PARAM
// Definition de nos parametres
#include <string>
#include <vector>

#define FACTO_VIE_BASE 300
#define FACTO_VIE_FORTERESSE 200
#define FACTO_VIE_ECOLE_MAGIE 100
#define NIVEAU_MAX_BAT 5

#define NIVEAU_MAX_TROUPE 5

#define FACTO_RESSOURCES 5
#define FACTO_ATTAQUE_BAT 20

#define FACTO_VIE_SOLDAT 60
#define FACTO_ATTAQUE_TROUPE_SOLD 20

#define FACTO_VIE_MAGICIEN 30
#define FACTO_ATTAQUE_TROUPE_MAG 25

#define FACTO_SOIN_TROUPE 10

#define FACTO_REPAR 1/4

#define FACTO_COUT_BASE 2
#define FACTO_COUT_FORT 3
#define FACTO_COUT_ECOLE 4

#define FACTO_AMELIO_BASE 30
#define FACTO_AMELIO_FORT 10
#define FACTO_AMELIO_ECOLE 10



struct data_batiment{
    int vie ;
    int niveau; 
    int nb_defenseurs;
    int vie_premier_defenseur;
};

struct data_troupes_de_guerre{
    int vie;
    int niveau;
    int degats;
    int soins;
};

struct data_joueur{
    std::string nomj;
    int ressources = 10;
    int nb_travailleurs = 0;
    data_batiment base;
    data_batiment forteresse; 
    data_batiment ecole_magie;
    std::vector<data_troupes_de_guerre> listesoldats;
    std::vector<data_troupes_de_guerre> listemagiciens;
};


struct data{
    data_joueur j1;
    data_joueur j2;
    std::string texteinfo = "debut !";
    int tour_joueur = 1;

};

#endif