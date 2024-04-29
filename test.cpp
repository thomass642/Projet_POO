#include <iostream>
#include "troupe.hpp"

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

    return 0;
}