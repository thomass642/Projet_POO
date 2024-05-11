#include "troupe.hpp"
#include "DefParam.h"

// ----------------------------------------------------------------
// TROUPE

Troupe::Troupe(int niv){
    _niveau = niv;
}

// ----------------------------------------------------------------
// TRAVAILLEUR

std::string Travailleur::get_infos(){
    return "\n!!!!!!!!!!!!!!!!!!!!!!!!!!\nTravailleur de niveau " + std::to_string(getniveau()) + "!\n!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
}


int Travailleur::chercher_ressources(){ // Renvoie le nombre de ressources collectées (en fonction de son niveau)
    int nb_ressources = 0;
    nb_ressources = _niveau * FACTO_RESSOURCES ;
    std::cout << "Le nombre de ressources collectees est de " << nb_ressources << std::endl ;
    return nb_ressources;
}

void Travailleur::reparer_batiment(int ressources, Batiment* batiment){ // Répare un batiment en fonction des ressources du joueur
    batiment->setvie(batiment->getvie() + ressources * FACTO_REPAR);

    if (batiment->getbatiment() == "Base") {
        if (batiment->getvie() > batiment->getniveau() * FACTO_VIE_BASE) {
            batiment->setvie(batiment->getniveau() * FACTO_VIE_BASE);
        }
    }

    else if (batiment->getbatiment() == "Forteresse") {
        if (batiment->getvie() > batiment->getniveau() * FACTO_VIE_FORTERESSE) {
            batiment->setvie(batiment->getvie()+ _niveau * FACTO_VIE_FORTERESSE);
        }
    }

    else if (batiment->getbatiment() == "Ecole de magie") {
        if (batiment->getvie() > batiment->getniveau() * FACTO_VIE_ECOLE_MAGIE) {
            batiment->setvie(batiment->getvie()+ _niveau * FACTO_VIE_ECOLE_MAGIE);
        }
    }

    else {
        std::cout << "Mauvais type de batiment" << std::endl;
    }

}

void Travailleur::ameliorer_batiment(Batiment* batiment){ // On ameliore un batiment
    batiment->setniveau(batiment->getniveau() + 1);
    batiment->setvie(batiment->getvie() + 200);
}

void Travailleur::agir(Joueur& joueur, Joueur& deuxieme_joueur){
    int action; // Commande du joueur
    std::cout << *this << std::endl << "Veuillez saisir une action :\n\t1 : Chercher des ressources\n\t2 : Reparer un batiment\n\t3 : Ameliorer / Construire un batiment\n\tAutre chose : Passer son tour\n";
    action = joueur.get_action(0,4);
    switch (action){
    case 1: // Chercher des ressources
        joueur.recuperer_ressources(chercher_ressources());
        break;
    
    case 2: // Reparer un batiment
        std::cout << "Reparation d'un batiment:\nVeuillez saisir un batiment :\n\t1 : Base\n\t2 : Forteresse\n\t3 : Ecole De Magie\n\tAutre chose : Annuler\n";
        action = joueur.get_action(0,3);
        
        switch (action){
        case 1: // Reparer Base
            std::cout << "Reparation de la Base" << std::endl;
            std::cout << "Veuillez saisir le nombre de ressources a utiliser:\n\t";
            action = joueur.get_action(0,20);
            reparer_batiment(action, joueur.get_batiment(0));
            joueur.recuperer_ressources(-action); // On perd le nombre de ressources utilisées
            break;
        
        case 2: // Reparer Forteresse
            std::cout << "Reparation de la Forteresse" << std::endl;
            std::cout << "Veuillez saisir le nombre de ressources a utiliser:\n\t";
            action = joueur.get_action(0,20);
            reparer_batiment(action, joueur.get_batiment(1));
            joueur.recuperer_ressources(-action); // On perd le nombre de ressources utilisées
            break;

        case 3: // Reparer Ecole de Magie
            std::cout << "Reparation de l'Ecole de Magie" << std::endl;
            std::cout << "Veuillez saisir le nombre de ressources a utiliser:\n\t";
            action = joueur.get_action(0,20);
            reparer_batiment(action, joueur.get_batiment(2));
            joueur.recuperer_ressources(-action); // On perd le nombre de ressources utilisées
            break;

        default: // Annuler
            std::cout << "Annulation de la reparation" << std::endl;
            this->agir(joueur, deuxieme_joueur);
            break;
        }
        break;

    case 3: // Ameliorer un batiment
        std::cout << "Amelioration / Construction d'un batiment (" << joueur.get_ressources() << "):\nVeuillez saisir un batiment :\n\t1 : Base (" << joueur.cout_amelioration(0) << ")\n\t2 : Forteresse (" << joueur.cout_amelioration(1) << ")\n\t3 : Ecole De Magie (" << joueur.cout_amelioration(2) << ")\n\tAutre chose : Annuler\n";
        action = joueur.get_action(0,3);
        switch (action){
        case 1: // Ameliorer Base
            if (joueur.get_ressources() >= joueur.cout_amelioration(0)){
                std::cout << "Amelioration de la Base" << std::endl;
                joueur.recuperer_ressources(-joueur.cout_amelioration(0));
                ameliorer_batiment(joueur.get_batiment(0));
            } else {
                std::cout << "Cout trop eleve pour l'amelioration de la Base\n";
                this->agir(joueur, deuxieme_joueur);
            }
            break;
        
        case 2: // Ameliorer Forteresse
            if (joueur.get_ressources() >= joueur.cout_amelioration(1)){
                std::cout << "Amelioration de la Forteresse" << std::endl;
                joueur.recuperer_ressources(-joueur.cout_amelioration(1));
                ameliorer_batiment(joueur.get_batiment(1));
            } else {
                std::cout << "Cout trop eleve pour l'amelioration de la Forteresse\n";
                this->agir(joueur, deuxieme_joueur);
            }
            break;

        case 3: // Ameliorer Ecole de Magie
            if (joueur.get_ressources() >= joueur.cout_amelioration(2)){
                std::cout << "Amelioration de l'Ecole de Magie" << std::endl;
                joueur.recuperer_ressources(-joueur.cout_amelioration(2));
                ameliorer_batiment(joueur.get_batiment(2));
            } else {
                std::cout << "Cout trop eleve pour l'amelioration de l ecole de magie\n";
                this->agir(joueur, deuxieme_joueur);
            }
            break;

        default: // Annuler
            std::cout << "Annulation de l'amelioration" << std::endl;
            this->agir(joueur, deuxieme_joueur);
            break;
        }
        break;

    default: // Passer son tour
        break;
    }
}

// ----------------------------------------------------------------
// TROUPE DE GUERRE

void TroupeDeGuerre::attaquer_batiment(Batiment *batiment){ // On attaque un batiment (dépend du niveau de la troupe)
    batiment->se_fait_attaquer(_niveau * FACTO_ATTAQUE_BAT);
}

int TroupeDeGuerre::se_fait_attaquer(int degats){ // Renvoie le nombre de vie qu'il lui reste (possible négatif -> surplus dégats)
    _vie -= degats;
    return _vie;
}

// ----------------------------------------------------------------
// SOLDAT

Soldat::Soldat(int niveau){
    _type_troupe = "Soldat";
    _niveau = niveau;
    _vie = _niveau * FACTO_VIE_SOLDAT;
    std::cout << "Les soldats ont une vie de " << _vie << std::endl ;
}

std::string Soldat::get_infos(){
    return "\nPPPPPPPPPPPPPPPPPPPPPPPPPPPP\nSoldat de niveau " + std::to_string(getniveau()) + "!\nVie : " + std::to_string(getvie()) + "/" + std::to_string(getniveau()*FACTO_VIE_SOLDAT) + " //  Degats : " + std::to_string(getniveau() * FACTO_ATTAQUE_TROUPE_SOLD) + "\nPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n";
}

void Soldat::attaquer_troupe(TroupeDeGuerre &troupe){ // On attaque une troupe (dépend du niveau de la troupe)
    std::cout << "La troupe adverse avait une vie de " << troupe.getvie() << std::endl;
    troupe.setvie(troupe.getvie() + -(_niveau* FACTO_ATTAQUE_TROUPE_SOLD));
    
    if (troupe.getvie() <= 0 ){
        troupe.setvie(0);
        std::cout << "La troupe adverse est morte." << std::endl;
    }

    else {
        std::cout << "La troupe adverse a maintenant une vie de " << troupe.getvie() << std::endl;
    }

}

void Soldat::defendre_batiment(Batiment* batiment){ // La troupe défend un batiment
    batiment->se_fait_defendre(this);
}


void Soldat::agir(Joueur& joueur, Joueur& deuxieme_joueur){ // Méthode d'action. On copie le joueur en parametre 
    int action; // Commande du joueur
    std::cout << *this << std::endl << "Veuillez saisir une action :\n\t1 : Attaquer une troupe\n\t2 : Attaquer un batiment\n\t3 : Defendre un batiment\n\tAutre : Passer son tour\n";
    action = joueur.get_action(0,4);
    switch (action){
    case 0:
        break;
    case 1: // Attaquer une troupe
        std:: cout << "Veuillez choisir une troupe a attaquer:\n";
        deuxieme_joueur.show_troupes();
        std:: cout << "Veuillez choisir l'index de la troupe a cibler (ou 0 si vous voulez passer votre tour)";
        action = joueur.get_action(0, deuxieme_joueur.get_size_troupes());

        if (action != 0){ // Si le joueur ne souhaite pas passer son tour
            if (action <= deuxieme_joueur.get_size_troupes()){ // Si l'index est valide
                if (deuxieme_joueur.get_troupe(action-1).gettroupe() != "Travailleur"){
                    attaquer_troupe(dynamic_cast<TroupeDeGuerre&>(deuxieme_joueur.get_troupe(action-1)));
                } else {
                    std::cout << "On n'attaque pas un villageois !\n";
                } 
            } else {
                std::cout << "Mauvais choix d'index" << std::endl;
            }
        }
        
        break;
    case 2: // Attaquer un batiment
        std::cout << "Veuillez choisir un batiment a attaquer:\n\t0 : Passer son tour\n\t1 : Base\n\t2 : Forteresse\n\t3 : Ecole de Magie\n\tAutre Chose : Annuler\n"; 
        action = joueur.get_action(0,4);
        switch (action){
        case 0: // Passer tour
            break;
        case 1: // Attaquer la base
            if (deuxieme_joueur.get_batiment(0)->getvie() <= 0){
                std::cout << "La base est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(0)); 
            }
            break;
        case 2:
            if (deuxieme_joueur.get_batiment(1)->getvie() <= 0){
                std::cout << "La forteresse est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(1)); 
            }
            break;

        case 3:
            if (deuxieme_joueur.get_batiment(2)->getvie() <= 0){
                std::cout << "L ecole de magie est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(2));
            }
            break;

        default:
            agir(joueur, deuxieme_joueur);
            break;
        }
        break;

    case 3: // Defendre un batiment 
        std::cout << "Veuillez choisir un batiment a defendre:\n\t1 : Base\n\t2 : Forteresse\n\t3 : Ecole de Magie\n\tAutre Chose : Annuler\n"; 
        action = joueur.get_action(0,3);
        if (action == 1){ // Defendre la Base 
            defendre_batiment(joueur.get_batiment(0));
        } else if (action == 2){ // Defendre la Forteresse 
            defendre_batiment(joueur.get_batiment(1));
        } else if (action == 3){ // Defendre l'ecole de magie 
            defendre_batiment(joueur.get_batiment(2));
        } else { // Annulation
            agir(joueur, deuxieme_joueur);
        }
        _type_troupe = "Defend";
        break;

    default:
        agir(joueur, deuxieme_joueur);
        break;
    }
}

// ----------------------------------------------------------------
// MAGICIEN

Magicien::Magicien(int niveau){
    _type_troupe = "Magicien";
    _niveau = niveau;
    _vie = _niveau * FACTO_VIE_MAGICIEN;
    std::cout << "Les magiciens ont une vie de " << _vie << std::endl;
}

std::string Magicien::get_infos(){
    return "\n*****************************\nMagicien de niveau " + std::to_string(getniveau()) + "!\nVie : " + std::to_string(getvie()) + "/" + std::to_string(getniveau()*FACTO_VIE_MAGICIEN) + "  //  Degats : " + std::to_string(getniveau() * FACTO_ATTAQUE_TROUPE_MAG) + "  //  Soins : " + std::to_string(getniveau() * FACTO_SOIN_TROUPE) + "\n********************\n";
}

void Magicien::attaquer_troupe(TroupeDeGuerre &troupe){ // On attaque une troupe (dépend du niveau de la troupe)
    std::cout << "La troupe adverse avait une vie de " << troupe.getvie() << std::endl;
    troupe.setvie(troupe.getvie() -(_niveau * FACTO_ATTAQUE_TROUPE_MAG));
    
    if (troupe.getvie() <= 0 ){
        troupe.setvie(0);
        std::cout << "La troupe adverse est morte." << std::endl;
    }

    else {
        std::cout << "La troupe adverse a maintenant une vie de " << troupe.getvie() << std::endl;
    }

}

void Magicien::soigner(TroupeDeGuerre &troupe){ // On soigne la troupe en parametre (dépend du niveau du magicien)
    troupe.setvie(troupe.getvie()+ _niveau * FACTO_SOIN_TROUPE) ;
    if (troupe.gettroupe() == "Soldat") {
        if (troupe.getvie() > troupe.getniveau() * FACTO_VIE_SOLDAT) {
            troupe.setvie(troupe.getniveau()*FACTO_VIE_SOLDAT);
        }
    } else if (troupe.gettroupe() == "Magicien") {
        if (troupe.getvie() > troupe.getniveau() * FACTO_VIE_MAGICIEN) {
            troupe.setvie(troupe.getniveau()*FACTO_VIE_MAGICIEN);
        }
    } else{
        std::cout << "Mauvais choix de type de troupe" << std::endl;
    }
    
    std::cout << "La troupe soignée a maintenant une vie de " << troupe.getvie() << std::endl;
}

void Magicien::agir(Joueur& joueur, Joueur& deuxieme_joueur){ // Méthode d'action. On copie le joueur en parametre 
    int action; // Commande du joueur
    std::cout << *this << std::endl << "Veuillez saisir une action :\n\t1 : Attaquer une troupe\n\t2 : Attaquer un batiment\n\t3 : Soigner une troupe\n\tAutre : Passer son tour\n";
    action = joueur.get_action(0,3);
    switch (action){
    case 0:
        break;
    case 1: // Attaquer une troupe
        std:: cout << "Veuillez choisir une troupe a attaquer:\n";
        deuxieme_joueur.show_troupes();
        std:: cout << "Veuillez choisir l'index de la troupe a cibler (ou 0 si vous voulez passer votre tour)";
        action = joueur.get_action(0,deuxieme_joueur.get_size_troupes());

        if (action != 0){ // Si le joueur ne souhaite pas passer son tour
            if (action <= deuxieme_joueur.get_size_troupes()){ // Si l'index est valide
                if (deuxieme_joueur.get_troupe(action-1).gettroupe() != "Travailleur"){
                    attaquer_troupe(dynamic_cast<TroupeDeGuerre&>(deuxieme_joueur.get_troupe(action-1)));
                } else {
                    std::cout << "On n'attaque pas un villageois !\n";
                } 
            } else {
                std::cout << "Mauvais choix d'index" << std::endl;
            }
        }
        
        break;
    case 2: // Attaquer un batiment
        std::cout << "Veuillez choisir un batiment a attaquer:\n\t0 : Passer son tour\n\t1 : Base\n\t2 : Forteresse\n\t3 : Ecole de Magie\n\tAutre Chose : Annuler\n"; 
        action = joueur.get_action(0,4);
        switch (action){
        case 0: // Passer tour
            break;
        case 1: // Attaquer la base
            if (deuxieme_joueur.get_batiment(0)->getvie() <= 0){
                std::cout << "La base est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(0)); 
            }
            break;
        case 2:
            if (deuxieme_joueur.get_batiment(1)->getvie() <= 0){
                std::cout << "La forteresse est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(1)); 
            }
            break;

        case 3:
            if (deuxieme_joueur.get_batiment(2)->getvie() <= 0){
                std::cout << "L ecole de magie est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(2));
            }
            break;

        default:
            agir(joueur, deuxieme_joueur);
            break;
        }
        break;

    case 3: // Soigner une troupe 
        std:: cout << "Veuillez choisir une troupe a soigner:\n";
        joueur.show_troupes();
        std:: cout << "Veuillez choisir l'index de la troupe a cibler (ou 0 si vous voulez passer votre tour)";
        action = joueur.get_action(0, joueur.get_size_troupes());

        if (action != 0){ // Si le joueur ne souhaite pas passer son tour
            if (action <= joueur.get_size_troupes()){ // Si l'index est valide
                if (joueur.get_troupe(action-1).gettroupe() != "Travailleur"){
                    soigner(dynamic_cast<TroupeDeGuerre&>(joueur.get_troupe(action-1)));
                } else {
                    std::cout << "On ne soigne pas un villageois !\n";
                } 
            } else {
                std::cout << "Mauvais choix d'index" << std::endl;
            }
        }
        
        break;

    default:
        agir(joueur, deuxieme_joueur);
        break;
    }
}

// --------------------------------------------------------------
// OPÉRATEUR FLUX

std :: ostream& operator<<(std::ostream& os , const Troupe& troupe){os << "VIRTUAL" ; return os ;} // Operator de flux Troupe


std :: ostream& operator<<(std::ostream& os, const Travailleur& trav){ // Operator de flux Travailleur
    os << "!!!!!!!!!!!!!!!!!!!!!!!!!!\nTravailleur de niveau " << trav.getniveau() << "!" << std::endl<< "!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    return os;
}

std :: ostream& operator<<(std::ostream& os, const Soldat& sold){ // Operator de flux Soldat
    os << "PPPPPPPPPPPPPPPPPPPPPPPPPPPP\nSoldat de niveau " << sold.getniveau() << "!\nVie : " << sold.getvie() << "/" << sold.getniveau()*FACTO_VIE_SOLDAT << "  //  Degats : " << sold.getniveau() * FACTO_ATTAQUE_TROUPE_SOLD << std::endl << "PPPPPPPPPPPPPPPPPPPPPPPPPPPP\n";
    return os;
}

std :: ostream& operator<<(std::ostream& os, const Magicien& mag){ // Operator de flux Magicien
    os << "*****************************\nMagicien de niveau " << mag.getniveau() << "!\nVie : " << mag.getvie() << "/" << mag.getniveau()*FACTO_VIE_MAGICIEN << "  //  Degats : " << mag.getniveau() * FACTO_ATTAQUE_TROUPE_MAG << "  /  Soins : " << mag.getniveau() * FACTO_SOIN_TROUPE <<std::endl << "********************\n";
    return os;
}
