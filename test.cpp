#include <iostream>
#include "troupe.hpp"
#include "batiment.hpp"
#include "joueur.hpp"
#include "jeu.hpp"

int main(){

    Joueur j1("Thomas");
    Joueur j2("Manpreet");

    Jeu jeu("Thomas", "Manpreet");  
    jeu.run();

    return 0;
}