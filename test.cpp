#include <iostream>
#include "troupe.hpp"
#include "batiment.hpp"

int main(){

    Travailleur trava(3);


    std::cout << trava;


    Soldat sold(5);

    std::cout << sold;


    Magicien mag(2);

    std::cout << mag;

    mag.attaquer_troupe(sold);

    std::cout << "ATTAQUE" << std::endl << sold;

    mag.soigner(sold);

    std::cout << "SOIN" << std::endl << sold;

    std::cout << "Creation d'une base" << std::endl; 

    Base base;

    base.setniveau(3);
    std::cout<<base.former_troupes();

    std::cout << "Creation d'une ecole de magie" << std::endl; 

    EcoleDeMagie ec;

    ec.setniveau(5);
    std::cout<<ec.former_troupes();


    return 0;
}