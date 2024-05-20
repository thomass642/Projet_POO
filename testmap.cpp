#include "testmap.hpp"

Tour tourjeu = SOLDATS;

Action action = NONE_ACTION;

Choice choice = OUI;

// choix (1 attaquer, 0 defendre, 2 soigner)
int choix = -1;


// permet de tester si les valeurs change à partir de la boucle de l'interface graph
void changeVillage2(data* donnees) {
    
    // Change les valeurs de village2
    donnees->j2.base.vie = 0.5;
    std::cout << donnees->j2.base.vie << std::endl;
    
}

void changesold2avant(data* donnees) {
    
    // Change les valeurs
    donnees->j2.sold_select -= 1;
    std::cout << donnees->j2.sold_select << std::endl;
    
}
void changesold2apres(data* donnees) {
    
    // Change les valeurs
    donnees->j2.sold_select += 1;
    std::cout << donnees->j2.sold_select << std::endl;
    
}
void changemag2avant(data* donnees) {
    
    // Change les valeurs
    donnees->j2.mag_select -= 1;
    std::cout << donnees->j2.mag_select << std::endl;
    
}
void changemag2apres(data* donnees) {
    
    // Change les valeurs
    donnees->j2.mag_select += 1;
    std::cout << donnees->j2.mag_select << std::endl;
    
}

void changesold1avant(data* donnees) {
    
    // Change les valeurs
    donnees->j1.sold_select -= 1;
    std::cout << donnees->j1.sold_select << std::endl;
    
}
void changesold1apres(data* donnees) {
    
    // Change les valeurs
    donnees->j1.sold_select += 1;
    std::cout << donnees->j1.sold_select << std::endl;
    
}
void changemag1avant(data* donnees) {
    
    // Change les valeurs
    donnees->j1.mag_select -= 1;
    std::cout << donnees->j1.mag_select << std::endl;
    
}
void changemag1apres(data* donnees) {
    
    // Change les valeurs
    donnees->j1.mag_select += 1;
    std::cout << donnees->j1.mag_select << std::endl;
    
}

// METTRE DES FLECHE AUTOUR DU SOLDAT POUR SELECTIONNER CELUI A ATTAQUER

