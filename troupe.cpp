#include "troupe.hpp"
#define VIE_MAX_BAT 50
#define VIE_MAX_TROUPE 50

// ----------------------------------------------------------------
// TROUPE

Troupe::Troupe(int niv){
    _niveau = niv;
}

// ----------------------------------------------------------------
// TRAVAILLEUR

int Travailleur::chercher_ressources(){ // Renvoie le nombre de ressources collectées (en fonction de son niveau)
    int nb_ressources = 0;
    nb_ressources = _niveau * 5 ;
    std::cout << "Le nombre de ressources collectees est de " << nb_ressources << std::endl ;
    return nb_ressources;
}

void Travailleur::reparer_batiment(int ressources, Batiment& batiment){ // Répare un batiment en fonction des ressources du joueur
    if (ressources >= _niveau * 5 && batiment.getvie() < VIE_MAX_BAT) {
        batiment.setvie(batiment.getvie()+ _niveau * 2) ;
    }
    else {
        std::cout << "Le batiment a atteint son niveau max ou le nombre de ressources n'est pas suffisant" << std::endl ;
    }
}

// ----------------------------------------------------------------
// TROUPE DE GUERRE

void TroupeDeGuerre::attaquer_batiment(Batiment &batiment){ // On attaque un batiment (dépend du niveau de la troupe)
    std::cout << "Le batiment avait une vie de " << batiment.getvie() << std::endl;
    batiment.setvie(batiment.getvie()+ -(_niveau / 2 * 20)) ;
    
    if (batiment.getvie() <= 0 ){
        batiment.setvie(0) ;
        std::cout << "Le batiment a été detruit." << std::endl;
    }

    else {
        std::cout << "Le batiment a maintenant une vie de " << batiment.getvie() << std::endl;
    }

}

int TroupeDeGuerre::se_fait_attaquer(int degats){ // Renvoie le nombre de vie qu'il lui reste (possible négatif -> surplus dégats)
    return _vie - degats;
}

// ----------------------------------------------------------------
// SOLDAT

Soldat::Soldat(int niveau){
    _type_troupe = "Soldat";
    _niveau = niveau;
    _vie = _niveau/2*60;
    std::cout << "Les soldats ont une vie de " << _vie << std::endl ;
}

void Soldat::attaquer_troupe(TroupeDeGuerre &troupe){ // On attaque une troupe (dépend du niveau de la troupe)
    std::cout << "La troupe adverse avait une vie de " << troupe.getvie() << std::endl;
    troupe.setvie(troupe.getvie() + -(_niveau / 2 * 20));
    
    if (troupe.getvie() <= 0 ){
        troupe.setvie(0);
        std::cout << "La troupe adverse est morte." << std::endl;
    }

    else {
        std::cout << "La troupe adverse a maintenant une vie de " << troupe.getvie() << std::endl;
    }

}

void Soldat::defendre_batiment(Batiment batiment){ // La troupe défend un batiment

}

// ----------------------------------------------------------------
// MAGICIEN

Magicien::Magicien(int niveau){
    _type_troupe = "Magicien";
    _niveau = niveau;
    _vie = _niveau/2*30;
    std::cout << "Les magiciens ont une vie de " << _vie << std::endl;
}
// soins = niveau / 2 * 10
void Magicien::attaquer_troupe(TroupeDeGuerre &troupe){ // On attaque une troupe (dépend du niveau de la troupe)
    std::cout << "La troupe adverse avait une vie de " << troupe.getvie() << std::endl;
    troupe.setvie(troupe.getvie() -(_niveau / 2 * 25));
    
    if (troupe.getvie() <= 0 ){
        troupe.setvie(0);
        std::cout << "La troupe adverse est morte." << std::endl;
    }

    else {
        std::cout << "La troupe adverse a maintenant une vie de " << troupe.getvie() << std::endl;
    }

}

void Magicien::soigner(TroupeDeGuerre &troupe){ // On soigne la troupe en parametre (dépend du niveau du magicien)
    if (troupe.getvie() <= VIE_MAX_TROUPE - _niveau / 2 * 10) {
        troupe.setvie(troupe.getvie()+ _niveau / 2 * 10) ;
    }

    else {
        troupe.setvie(VIE_MAX_TROUPE) ;
    }

    std::cout << "La troupe soignée a maintenant une vie de " << troupe.getvie() << std::endl;
}



// --------------------------------------------------------------
// OPÉRATEUR FLUX

std :: ostream& operator<<(std::ostream& os, const Travailleur& trav){ // Operator de flux Travailleur
    os << "!!!!!!!!!!!!!!!!!!!!!!!!!!\nTravailleur de niveau " << trav.getniveau() << "!" << std::endl<< "!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    return os;
}

std :: ostream& operator<<(std::ostream& os, const Soldat& sold){ // Operator de flux Soldat
    os << "PPPPPPPPPPPPPPPPPPPPPPPPPPPP\nSoldat de niveau " << sold.getniveau() << "!\nVie : " << sold.getvie() << "  /  Degats : " << sold.getniveau() * 1 << std::endl << "PPPPPPPPPPPPPPPPPPPPPPPPPPPP\n";
    return os;
}

std :: ostream& operator<<(std::ostream& os, const Magicien& mag){ // Operator de flux Magicien
    os << "*****************************\nMagicien de niveau " << mag.getniveau() << "!\nVie : " << mag.getvie() << "  /  Degats : " << mag.getniveau() * 1 << "  /  Soins : " << mag.getniveau() * 1<<std::endl << "********************\n";
    return os;
}
