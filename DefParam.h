#ifndef DEF_PARAM 
#define DEF_PARAM
// Definition de nos parametres

#include <vector>
#include <string>

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
    float vie = 0;
    int niveau = 0;  
    int nb_defenseurs = 0;
    float vie_premier_defenseur = 0;
};

struct data_troupes_de_guerre{
    float vie = 0;
    int niveau = 0;
    int degats = 0;
    int soins = 0;
};

struct data_joueur{
    std::string nomj; 
    int ressources = 10; // ok
    int nb_travailleurs = 0; // ok
    data_batiment base; 
    data_batiment forteresse;  // ok
    data_batiment ecole_magie; // ok
    std::vector<data_troupes_de_guerre> listesoldats; // ok
    std::vector<data_troupes_de_guerre> listemagiciens; // ok
};

struct data{
    data_joueur j1;
    data_joueur j2;
    std::string texteinfo = "debut de la partie";
    int tour_joueur = 1;
};

#endif