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

int TroupeDeGuerre::se_fait_attaquer(int degats){ // Renvoie le nombre de vie qu'il lui reste (possible négatif -> surplus dégats)

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

// --------------------------------------------------------------
// OPÉRATEUR FLUX

std :: ostream& operator<<(std::ostream&, const Travailleur& trav){ // Operator de flux Travailleur
    os << "Travailleur de niveau " << _niveau << "!";
    return os;
}

std :: ostream& operator<<(std::ostream&, const Soldat& sold){ // Operator de flux Soldat
    os << "Soldat de niveau " << _niveau << "!\nVie : " << _vie << "  /  Degats : " << _niveau * truc << std::endl;
    return os;
}

std :: ostream& operator<<(std::ostream&, const Magicien& mag){ // Operator de flux Magicien
    os << "Soldat de niveau " << _niveau << "!\nVie : " << _vie << "  /  Degats : " << _niveau * truc << "  /  Soins : " << _niveau*truc<<std::endl;
    return os;
}
