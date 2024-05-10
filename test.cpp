#include <iostream>
#include "troupe.hpp"
#include "batiment.hpp"
#include "joueur.hpp"

int main(){

    Joueur j1("Thomas");
    Joueur j2("Manpreet");

    j1.jouer(j2);
    j1.jouer(j2);

    // std::cout << j1 << std::endl << "Autre joueur : \n" << j2;


    // std::vector<Batiment*> _village;

    // Base* bat = new Base;

    // _village.push_back(bat);

    // std::cout << _village[0]->former_troupes()->get_infos();


    // std::vector<Troupe*> _troupes;
    

    // _troupes.push_back(_village[0]->former_troupes());
    // _troupes.push_back(bat->former_troupes());


    // std::cout << _troupes[0]->get_infos();
    // std::cout << _troupes[1]->get_infos();


    ///////////////// TOUT CA FONCTIONNE SANS LE VILLAGE

    return 0;
}