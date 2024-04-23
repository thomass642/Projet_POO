#include "troupe.hpp"


// ----------------------------------------------------------------
// TROUPE

Troupe::Troupe(int niv){
    _niveau = niv;
}

// ----------------------------------------------------------------
// TRAVAILLEUR

int Travailleur::chercher_ressources(){ // Renvoie le nombre de ressources collectées (en fonction de son niveau)

}

void Travailleur::reparer_batiment(int ressources){ // Répare un batiment en fonction des ressources du joueur

}

// ----------------------------------------------------------------
// TROUPE DE GUERRE

void TroupeDeGuerre::attaquer_troupe(Troupe &troupe){ // On attaque une troupe (dépend du niveau de la troupe)

}

void TroupeDeGuerre::attaquer_batiment(Batiment &batiment){ // On attaque un batiment (dépend du niveau de la troupe)

}

// ----------------------------------------------------------------
// SOLDAT

Soldat::Soldat(int niveau) : Troupe(niveau){
    _vie = _niveau/2*60;
}

void Soldat::defendre_batiment(Batiment batiment){ // La troupe défend un batiment

}

// ----------------------------------------------------------------
// MAGICIEN

Magicien::Magicien(int niveau) : Troupe(niveau){
    _vie = _niveau/2*30;
}

void Magicien::soigner(Troupe &troupe){ // On soigne la troupe en parametre (dépend du niveau du magicien)

}