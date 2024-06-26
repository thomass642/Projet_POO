#include "troupe.hpp"

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
            if (joueur_courant == 1){
                DONNEES.j1.base.vie = batiment->getvie();
            }else{ 
                DONNEES.j2.base.vie = batiment->getvie();
            }
        }
    }

    else if (batiment->getbatiment() == "Forteresse") {
        if (batiment->getvie() > batiment->getniveau() * FACTO_VIE_FORTERESSE) {
            batiment->setvie(batiment->getvie()+ _niveau * FACTO_VIE_FORTERESSE);
        }
        if (joueur_courant == 1){
            DONNEES.j1.forteresse.vie = batiment->getvie();
        }else{ 
            DONNEES.j2.forteresse.vie = batiment->getvie();
        }
    }

    else if (batiment->getbatiment() == "Ecole de magie") {
        if (batiment->getvie() > batiment->getniveau() * FACTO_VIE_ECOLE_MAGIE) {
            batiment->setvie(batiment->getvie()+ _niveau * FACTO_VIE_ECOLE_MAGIE);
        }
        if (joueur_courant == 1){
            DONNEES.j1.ecole_magie.vie = batiment->getvie();
        }else{ 
            DONNEES.j2.ecole_magie.vie = batiment->getvie();
        }
    }

    else {
        std::cout << "Mauvais type de batiment" << std::endl;
    }

}

void Travailleur::ameliorer_batiment(Batiment* batiment){ // On ameliore un batiment
    batiment->setniveau(batiment->getniveau() + 1);
    batiment->setvie(batiment->getvie() + 200);
    if (joueur_courant == 1){
        if (batiment->getbatiment() == "Base"){
            DONNEES.j1.base.niveau = batiment->getniveau();
            DONNEES.j1.base.vie = batiment->getvie();
        } else if (batiment->getbatiment() == "Forteresse"){
            DONNEES.j1.forteresse.niveau = batiment->getniveau();
            DONNEES.j1.forteresse.vie = batiment->getvie();
        } else{
            DONNEES.j1.ecole_magie.niveau = batiment->getniveau();
            DONNEES.j1.ecole_magie.vie = batiment->getvie();
        }
    }else{ 
        if (batiment->getbatiment() == "Base"){
            DONNEES.j2.base.niveau = batiment->getniveau();
            DONNEES.j2.base.vie = batiment->getvie();
        } else if (batiment->getbatiment() == "Forteresse"){
            DONNEES.j2.forteresse.niveau = batiment->getniveau();
            DONNEES.j2.forteresse.vie = batiment->getvie();
        } else{
            DONNEES.j2.ecole_magie.niveau = batiment->getniveau();
            DONNEES.j2.ecole_magie.vie = batiment->getvie();
        }
    }
}

void Travailleur::agir(Joueur& joueur, Joueur& deuxieme_joueur){
    tourjeu = TRAVAILLEURS;
    action = NONE_ACTION;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    int select; // Commande du joueur
    std::cout << *this << std::endl << "Veuillez saisir une action :\n\t1 : Chercher des ressources\n\t2 : Reparer un batiment\n\t3 : Ameliorer / Construire un batiment\n\tAutre chose : Passer son tour\n";
    select = joueur.get_action(0,4);
    switch (select){
    case 1: // Chercher des ressources
        joueur.recuperer_ressources(chercher_ressources());
        break;
    
    case 2: // Reparer un batiment
        std::cout << "Reparation d'un batiment:\nVeuillez saisir un batiment :\n\t1 : Base\n\t2 : Forteresse\n\t3 : Ecole De Magie\n\tAutre chose : Annuler\n";
        DONNEES.texteinfo = "Reparation d'un batiment:\nVeuillez saisir un batiment a reparer";
        select = joueur.get_action(0,3);
        
        switch (select){
        case 1: // Reparer Base
            std::cout << "Reparation de la Base" << std::endl;
            std::cout << "Veuillez saisir le nombre de ressources a utiliser:\n\t";
            select = joueur.get_action(0,20);
            reparer_batiment(select, joueur.get_batiment(0));
            joueur.recuperer_ressources(-select); // On perd le nombre de ressources utilisées
            break;
        
        case 2: // Reparer Forteresse
            std::cout << "Reparation de la Forteresse" << std::endl;
            std::cout << "Veuillez saisir le nombre de ressources a utiliser:\n\t";
            DONNEES.texteinfo = "Veuillez saisir le nombre de ressources a utiliser:";
            select = joueur.get_action(0,20);
            reparer_batiment(select, joueur.get_batiment(1));
            joueur.recuperer_ressources(-select); // On perd le nombre de ressources utilisées
            break;

        case 3: // Reparer Ecole de Magie
            std::cout << "Reparation de l'Ecole de Magie" << std::endl;
            std::cout << "Veuillez saisir le nombre de ressources a utiliser:\n\t";
            select = joueur.get_action(0,20);
            reparer_batiment(select, joueur.get_batiment(2));
            joueur.recuperer_ressources(-select); // On perd le nombre de ressources utilisées
            break;

        default: // Annuler
            std::cout << "Annulation de la reparation" << std::endl;
            this->agir(joueur, deuxieme_joueur);
            break;
        }
        if (joueur_courant == 1){
            DONNEES.j1.ressources = joueur.get_ressources();
        }else{ 
            DONNEES.j2.ressources = joueur.get_ressources();
        }
        break;

    case 3: // Ameliorer un batiment
        tourjeu = TRAVAILLEURS;
        action = CONST_BATIMENTS;
        std::cout << "Amelioration / Construction d'un batiment (" << joueur.get_ressources() << "):\nVeuillez saisir un batiment :\n\t1 : Base (" << joueur.cout_amelioration(0) << ")\n\t2 : Forteresse (" << joueur.cout_amelioration(1) << ")\n\t3 : Ecole De Magie (" << joueur.cout_amelioration(2) << ")\n\tAutre chose : Annuler\n";
        DONNEES.texteinfo = "Amelioration / Construction d'un batiment\n\t1 : Base (" + std::to_string(joueur.cout_amelioration(0)) + ")\n\t2 : Forteresse (" + std::to_string(joueur.cout_amelioration(1)) + ")\n\t3 : Ecole De Magie (" + std::to_string(joueur.cout_amelioration(2)) + ")";
        select = joueur.get_action(0,3);
        switch (select){
        case 1: // Ameliorer Base
            if (joueur.get_ressources() >= joueur.cout_amelioration(0)){
                std::cout << "Amelioration de la Base" << std::endl;
                DONNEES.texteinfo = "Amelioration de la Base";
                joueur.recuperer_ressources(-joueur.cout_amelioration(0));
                ameliorer_batiment(joueur.get_batiment(0));
            } else {
                std::cout << "Cout trop eleve pour l'amelioration de la Base\n";
                DONNEES.texteinfo = "Cout trop eleve pour l'amelioration de la Base\n";
                this->agir(joueur, deuxieme_joueur);
            }
            break;
        
        case 2: // Ameliorer Forteresse
            if (joueur.get_ressources() >= joueur.cout_amelioration(1)){
                std::cout << "Amelioration de la Forteresse" << std::endl;
                DONNEES.texteinfo = "Amelioration de la Forteresse";
                joueur.recuperer_ressources(-joueur.cout_amelioration(1));
                ameliorer_batiment(joueur.get_batiment(1));
            } else {
                std::cout << "Cout trop eleve pour l'amelioration de la Forteresse\n";
                DONNEES.texteinfo = "Cout trop eleve pour l'amelioration de la Forteresse\n";
                this->agir(joueur, deuxieme_joueur);
            }
            break;

        case 3: // Ameliorer Ecole de Magie
            if (joueur.get_ressources() >= joueur.cout_amelioration(2)){
                DONNEES.texteinfo = "Amelioration de l'Ecole de Magie";
                std::cout << "Amelioration de l'Ecole de Magie" << std::endl;
                joueur.recuperer_ressources(-joueur.cout_amelioration(2));
                ameliorer_batiment(joueur.get_batiment(2));
            } else {
                std::cout << "Cout trop eleve pour l'amelioration de l ecole de magie\n";
                DONNEES.texteinfo = "Cout trop eleve pour l'amelioration de l'Ecole de Magie\n";
                this->agir(joueur, deuxieme_joueur);
            }
            break;

        default: // Annuler
            std::cout << "Annulation de l'amelioration" << std::endl;
            this->agir(joueur, deuxieme_joueur);
            break;
        }
        if (joueur_courant == 1){
            DONNEES.j1.ressources = joueur.get_ressources();
        }else{ 
            DONNEES.j2.ressources = joueur.get_ressources();
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
    tourjeu = SOLDATS;
    choix =-1;
    
    int select; // Commande du joueur
    std::cout << *this << std::endl << "Veuillez saisir une select :\n\t1 : Attaquer une troupe\n\t2 : Attaquer un batiment\n\t3 : Defendre un batiment\n\tAutre : Passer son tour\n";
    
    if (joueur_courant == 1){
        DONNEES.j1.select_degats_sold = _niveau * FACTO_ATTAQUE_TROUPE_SOLD;
        DONNEES.j1.select_niveau_sold = _niveau;
        DONNEES.j1.select_vie_sold = _vie;
    } else {
        DONNEES.j2.select_degats_sold = _niveau * FACTO_ATTAQUE_TROUPE_SOLD;
        DONNEES.j2.select_niveau_sold = _niveau;
        DONNEES.j2.select_vie_sold = _vie;
    }

    select = joueur.get_action(0,4);

    switch (select){
    case 0:
        break;
    case 1: // Attaquer une troupe
        std:: cout << "Veuillez choisir une troupe a attaquer:\n";
        DONNEES.texteinfo = "Veuillez choisir une troupe a attaquer:";
        deuxieme_joueur.show_troupes();
        std:: cout << "Veuillez choisir l'index de la troupe a cibler (ou 0 si vous voulez passer votre tour)";
        select = joueur.get_action(0, deuxieme_joueur.get_size_troupes());

        if (select != 0){ // Si le joueur ne souhaite pas passer son tour
            if (select <= deuxieme_joueur.get_size_troupes()){ // Si l'index est valide
                if (deuxieme_joueur.get_troupe(select-1).gettroupe() != "Travailleur"){
                    attaquer_troupe(dynamic_cast<TroupeDeGuerre&>(deuxieme_joueur.get_troupe(select-1)));
                    if (joueur_courant == 2){
                        DONNEES.j1.listesoldats.clear();
                        DONNEES.j1.listemagiciens.clear();
                    }else{ 
                        DONNEES.j2.listesoldats.clear();
                        DONNEES.j2.listemagiciens.clear();
                    }
                    for (int i = 0; i<deuxieme_joueur.get_size_troupes(); i++)
                        if (deuxieme_joueur.get_troupe(i).gettroupe() == "Soldat"){
                            Soldat* copie = dynamic_cast<Soldat*>(&deuxieme_joueur.get_troupe(i));
                            data_troupes_de_guerre sold;
                            sold.vie = copie->getvie();
                            sold.niveau = copie->getniveau();
                            sold.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_SOLD;
                            if (joueur_courant == 2){
                                DONNEES.j1.listesoldats.push_back(sold);
                            }else{ 
                                DONNEES.j2.listesoldats.push_back(sold);
                            }
                            
                        } else if (deuxieme_joueur.get_troupe(i).gettroupe() == "Magicien"){
                            Magicien* copie = dynamic_cast<Magicien*>(&deuxieme_joueur.get_troupe(i));
                            data_troupes_de_guerre mag;
                            mag.vie = copie->getvie();
                            mag.niveau = copie->getniveau();
                            mag.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_MAG;
                            mag.soins = copie->getniveau() * FACTO_SOIN_TROUPE;
                            if (joueur_courant == 2){
                                DONNEES.j1.listesoldats.push_back(mag);
                            }else{ 
                                DONNEES.j2.listesoldats.push_back(mag);
                            }
                        }
            } else {
                std::cout << "On n'attaque pas un villageois !\n";
                DONNEES.texteinfo = "On n'attaque pas un villageois !";
                } 
            } else {
                std::cout << "Mauvais choix d'index ou passage de tour" << std::endl;
            }
        }
        
        break;
    case 2: // Attaquer un batiment
        std::cout << "Veuillez choisir un batiment a attaquer:\n\t0 : Passer son tour\n\t1 : Base\n\t2 : Forteresse\n\t3 : Ecole de Magie\n\tAutre Chose : Annuler\n"; 
        select = joueur.get_action(0,4);
        switch (select){
        case 0: // Passer tour
            break;
        case 1: // Attaquer la base
            if (deuxieme_joueur.get_batiment(0)->getvie() <= 0){
                std::cout << "La base est deja detruite...\n";
                DONNEES.texteinfo = "La base est deja detruite...";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(0)); 
                if (joueur_courant == 2){
                    DONNEES.j1.base.vie = deuxieme_joueur.get_batiment(0)->getvie();
                    DONNEES.j1.base.niveau = deuxieme_joueur.get_batiment(0)->getniveau();
                    DONNEES.j1.base.nb_defenseurs = deuxieme_joueur.get_batiment(0)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(0)->getdefenseurs().size() > 0){
                        DONNEES.j1.base.vie_premier_defenseur = deuxieme_joueur.get_batiment(0)->getdefenseurs()[0]->getvie();
                    }
                }else {
                    DONNEES.j2.base.vie = deuxieme_joueur.get_batiment(0)->getvie();
                    DONNEES.j2.base.niveau = deuxieme_joueur.get_batiment(0)->getniveau();
                    DONNEES.j2.base.nb_defenseurs = deuxieme_joueur.get_batiment(0)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(0)->getdefenseurs().size() > 0){
                        DONNEES.j2.base.vie_premier_defenseur = deuxieme_joueur.get_batiment(0)->getdefenseurs()[0]->getvie();
                    }
                }
            }
            break;
        case 2:
            if (deuxieme_joueur.get_batiment(1)->getvie() <= 0){
                std::cout << "La forteresse est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(1)); 
                if (joueur_courant == 2){
                    DONNEES.j1.forteresse.vie = deuxieme_joueur.get_batiment(1)->getvie();
                    DONNEES.j1.forteresse.niveau = deuxieme_joueur.get_batiment(1)->getniveau();
                    DONNEES.j1.forteresse.nb_defenseurs = deuxieme_joueur.get_batiment(1)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(1)->getdefenseurs().size() > 0){
                        DONNEES.j1.forteresse.vie_premier_defenseur = deuxieme_joueur.get_batiment(1)->getdefenseurs()[0]->getvie();
                    }
                }else {
                    DONNEES.j2.forteresse.vie = deuxieme_joueur.get_batiment(1)->getvie();
                    DONNEES.j2.forteresse.niveau = deuxieme_joueur.get_batiment(1)->getniveau();
                    DONNEES.j2.forteresse.nb_defenseurs = deuxieme_joueur.get_batiment(1)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(1)->getdefenseurs().size() > 0){
                        DONNEES.j2.forteresse.vie_premier_defenseur = deuxieme_joueur.get_batiment(1)->getdefenseurs()[0]->getvie();
                    }
                }
            }
            break;

        case 3:
            if (deuxieme_joueur.get_batiment(2)->getvie() <= 0){
                std::cout << "L ecole de magie est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(2));
                if (joueur_courant == 2){
                    DONNEES.j1.ecole_magie.vie = deuxieme_joueur.get_batiment(2)->getvie();
                    DONNEES.j1.ecole_magie.niveau = deuxieme_joueur.get_batiment(2)->getniveau();
                    DONNEES.j1.ecole_magie.nb_defenseurs = deuxieme_joueur.get_batiment(2)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(2)->getdefenseurs().size() > 0){
                        DONNEES.j1.ecole_magie.vie_premier_defenseur = deuxieme_joueur.get_batiment(2)->getdefenseurs()[0]->getvie();
                    }
                }else {
                    DONNEES.j2.ecole_magie.vie = deuxieme_joueur.get_batiment(2)->getvie();
                    DONNEES.j2.ecole_magie.niveau = deuxieme_joueur.get_batiment(2)->getniveau();
                    DONNEES.j2.ecole_magie.nb_defenseurs = deuxieme_joueur.get_batiment(2)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(2)->getdefenseurs().size() > 0){
                        DONNEES.j2.ecole_magie.vie_premier_defenseur = deuxieme_joueur.get_batiment(2)->getdefenseurs()[0]->getvie();
                    }
                }
            }
            break;

        default:
            agir(joueur, deuxieme_joueur);
            break;
        }
        break;

    case 3: // Defendre un batiment
        choix = 0; 
        std::cout << "Veuillez choisir un batiment a defendre:\n\t1 : Base\n\t2 : Forteresse\n\t3 : Ecole de Magie\n\tAutre Chose : Annuler\n"; 
        select = joueur.get_action(0,3);
        if (select == 1){ // Defendre la Base 
            defendre_batiment(joueur.get_batiment(0));
            if (joueur_courant == 1){
                DONNEES.j1.base.nb_defenseurs = joueur.get_batiment(0)->getdefenseurs().size();
                DONNEES.j1.base.vie_premier_defenseur = joueur.get_batiment(0)->getdefenseurs()[0]->getvie();
            }else {
                DONNEES.j2.base.nb_defenseurs = joueur.get_batiment(0)->getdefenseurs().size();
                DONNEES.j2.base.vie_premier_defenseur = joueur.get_batiment(0)->getdefenseurs()[0]->getvie();
            }
        } else if (select == 2){ // Defendre la Forteresse 
            defendre_batiment(joueur.get_batiment(1));
            if (joueur_courant == 1){
                DONNEES.j1.forteresse.nb_defenseurs = joueur.get_batiment(1)->getdefenseurs().size();
                DONNEES.j1.forteresse.vie_premier_defenseur = joueur.get_batiment(1)->getdefenseurs()[0]->getvie();
            }else {
                DONNEES.j2.forteresse.nb_defenseurs = joueur.get_batiment(1)->getdefenseurs().size();
                DONNEES.j2.forteresse.vie_premier_defenseur = joueur.get_batiment(1)->getdefenseurs()[0]->getvie();
            }
        } else if (select == 3){ // Defendre l'ecole de magie 
            defendre_batiment(joueur.get_batiment(2));
            if (joueur_courant == 1){
                DONNEES.j1.ecole_magie.nb_defenseurs = joueur.get_batiment(2)->getdefenseurs().size();
                DONNEES.j1.ecole_magie.vie_premier_defenseur = joueur.get_batiment(2)->getdefenseurs()[0]->getvie();
            }else {
                DONNEES.j2.ecole_magie.nb_defenseurs = joueur.get_batiment(2)->getdefenseurs().size();
                DONNEES.j2.ecole_magie.vie_premier_defenseur = joueur.get_batiment(2)->getdefenseurs()[0]->getvie();
            }
        } else { // Annulation
            agir(joueur, deuxieme_joueur);
        }
        _type_troupe = "Defend";
        if (joueur_courant == 1){
            DONNEES.j1.select_degats_sold = 0;
            DONNEES.j1.select_niveau_sold = 0;
            DONNEES.j1.select_vie_sold = 0;

        } else {
            DONNEES.j2.select_degats_sold = 0;
            DONNEES.j2.select_niveau_sold = 0;
            DONNEES.j2.select_vie_sold = 0;
        }
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
    tourjeu = MAGICIENS;
    choix = -1;
    int action; // Commande du joueur
    std::cout << *this << std::endl << "Veuillez saisir une action :\n\t1 : Attaquer une troupe\n\t2 : Attaquer un batiment\n\t3 : Soigner une troupe\n\tAutre : Passer son tour\n";
    if (joueur_courant == 1){
        DONNEES.j1.select_degats_mag = _niveau * FACTO_ATTAQUE_TROUPE_MAG;
        DONNEES.j1.select_niveau_mag = _niveau;
        DONNEES.j1.select_vie_mag = _vie;
        DONNEES.j1.select_soins = _niveau * FACTO_SOIN_TROUPE;
    } else {
        DONNEES.j2.select_degats_mag = _niveau * FACTO_ATTAQUE_TROUPE_MAG;
        DONNEES.j2.select_niveau_mag = _niveau;
        DONNEES.j2.select_vie_mag = _vie;
        DONNEES.j2.select_soins = _niveau * FACTO_SOIN_TROUPE;
    }
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
                    if (joueur_courant == 2){
                        DONNEES.j1.listesoldats.clear();
                        DONNEES.j1.listemagiciens.clear();
                    }else{ 
                        DONNEES.j2.listesoldats.clear();
                        DONNEES.j2.listemagiciens.clear();
                    }
                    attaquer_troupe(dynamic_cast<TroupeDeGuerre&>(deuxieme_joueur.get_troupe(action-1)));
                    for (int i = 0; i<deuxieme_joueur.get_size_troupes(); i++)
                        if (deuxieme_joueur.get_troupe(i).gettroupe() == "Soldat"){
                            Soldat* copie = dynamic_cast<Soldat*>(&deuxieme_joueur.get_troupe(i));
                            data_troupes_de_guerre sold;
                            sold.vie = copie->getvie();
                            sold.niveau = copie->getniveau();
                            sold.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_SOLD;
                            if (joueur_courant == 2){
                                DONNEES.j1.listesoldats.push_back(sold);
                            }else{ 
                                DONNEES.j2.listesoldats.push_back(sold);
                            }
                            
                        } else if (deuxieme_joueur.get_troupe(i).gettroupe() == "Magicien"){
                            Magicien* copie = dynamic_cast<Magicien*>(&deuxieme_joueur.get_troupe(i));
                            data_troupes_de_guerre mag;
                            mag.vie = copie->getvie();
                            mag.niveau = copie->getniveau();
                            mag.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_MAG;
                            mag.soins = copie->getniveau() * FACTO_SOIN_TROUPE;
                            if (joueur_courant == 2){
                                DONNEES.j1.listesoldats.push_back(mag);
                            }else{ 
                                DONNEES.j2.listesoldats.push_back(mag);
                            }
                        }
                } else {
                    std::cout << "On n'attaque pas un villageois !\n";
                    DONNEES.texteinfo = "On n'attaque pas un villageois !";
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
                if (joueur_courant == 2){
                    DONNEES.j1.base.vie = deuxieme_joueur.get_batiment(0)->getvie();
                    DONNEES.j1.base.niveau = deuxieme_joueur.get_batiment(0)->getniveau();
                    DONNEES.j1.base.nb_defenseurs = deuxieme_joueur.get_batiment(0)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(0)->getdefenseurs().size() > 0){
                        DONNEES.j1.base.vie_premier_defenseur = deuxieme_joueur.get_batiment(0)->getdefenseurs()[0]->getvie();
                    }
                }else {
                    DONNEES.j2.base.vie = deuxieme_joueur.get_batiment(0)->getvie();
                    DONNEES.j2.base.niveau = deuxieme_joueur.get_batiment(0)->getniveau();
                    DONNEES.j2.base.nb_defenseurs = deuxieme_joueur.get_batiment(0)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(0)->getdefenseurs().size() > 0){
                        DONNEES.j2.base.vie_premier_defenseur = deuxieme_joueur.get_batiment(0)->getdefenseurs()[0]->getvie();
                    }
                }
            }
            break;
        case 2:
            if (deuxieme_joueur.get_batiment(1)->getvie() <= 0){
                std::cout << "La forteresse est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(1)); 
                if (joueur_courant == 2){
                    DONNEES.j1.forteresse.vie = deuxieme_joueur.get_batiment(1)->getvie();
                    DONNEES.j1.forteresse.niveau = deuxieme_joueur.get_batiment(1)->getniveau();
                    DONNEES.j1.forteresse.nb_defenseurs = deuxieme_joueur.get_batiment(1)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(1)->getdefenseurs().size() > 0){
                        DONNEES.j1.forteresse.vie_premier_defenseur = deuxieme_joueur.get_batiment(1)->getdefenseurs()[0]->getvie();
                    }
                }else {
                    DONNEES.j2.forteresse.vie = deuxieme_joueur.get_batiment(1)->getvie();
                    DONNEES.j2.forteresse.niveau = deuxieme_joueur.get_batiment(1)->getniveau();
                    DONNEES.j2.forteresse.nb_defenseurs = deuxieme_joueur.get_batiment(1)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(1)->getdefenseurs().size() > 0){
                        DONNEES.j2.forteresse.vie_premier_defenseur = deuxieme_joueur.get_batiment(1)->getdefenseurs()[0]->getvie();
                    }
                }
            }
            break;

        case 3:
            if (deuxieme_joueur.get_batiment(2)->getvie() <= 0){
                std::cout << "L ecole de magie est deja detruite...\n";
                agir(joueur, deuxieme_joueur);
            } else {
                attaquer_batiment(deuxieme_joueur.get_batiment(2));
                if (joueur_courant == 2){
                    DONNEES.j1.ecole_magie.vie = deuxieme_joueur.get_batiment(2)->getvie();
                    DONNEES.j1.ecole_magie.niveau = deuxieme_joueur.get_batiment(2)->getniveau();
                    DONNEES.j1.ecole_magie.nb_defenseurs = deuxieme_joueur.get_batiment(2)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(2)->getdefenseurs().size() > 0){
                        DONNEES.j1.ecole_magie.vie_premier_defenseur = deuxieme_joueur.get_batiment(2)->getdefenseurs()[0]->getvie();
                    }
                }else {
                    DONNEES.j2.ecole_magie.vie = deuxieme_joueur.get_batiment(2)->getvie();
                    DONNEES.j2.ecole_magie.niveau = deuxieme_joueur.get_batiment(2)->getniveau();
                    DONNEES.j2.ecole_magie.nb_defenseurs = deuxieme_joueur.get_batiment(2)->getdefenseurs().size();
                    if (deuxieme_joueur.get_batiment(2)->getdefenseurs().size() > 0){
                        DONNEES.j2.ecole_magie.vie_premier_defenseur = deuxieme_joueur.get_batiment(2)->getdefenseurs()[0]->getvie();
                    }
                }
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
                    if (joueur_courant == 1){
                        DONNEES.j1.listesoldats.clear();
                        DONNEES.j1.listemagiciens.clear();
                    }else{ 
                        DONNEES.j2.listesoldats.clear();
                        DONNEES.j2.listemagiciens.clear();
                    }
                    for (int i = 0; i<joueur.get_size_troupes(); i++)
                        if (joueur.get_troupe(i).gettroupe() == "Soldat"){
                            Soldat* copie = dynamic_cast<Soldat*>(&joueur.get_troupe(i));
                            data_troupes_de_guerre sold;
                            sold.vie = copie->getvie();
                            sold.niveau = copie->getniveau();
                            sold.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_SOLD;
                            if (joueur_courant == 1){
                                DONNEES.j1.listesoldats.push_back(sold);
                            }else{ 
                                DONNEES.j2.listesoldats.push_back(sold);
                            }
                            
                        } else if (joueur.get_troupe(i).gettroupe() == "Magicien"){
                            Magicien* copie = dynamic_cast<Magicien*>(&joueur.get_troupe(i));
                            data_troupes_de_guerre mag;
                            mag.vie = copie->getvie();
                            mag.niveau = copie->getniveau();
                            mag.degats = copie->getniveau() * FACTO_ATTAQUE_TROUPE_MAG;
                            mag.soins = copie->getniveau() * FACTO_SOIN_TROUPE;
                            if (joueur_courant == 1){
                                DONNEES.j1.listesoldats.push_back(mag);
                            }else{ 
                                DONNEES.j2.listesoldats.push_back(mag);
                            }
                        }
                } else {
                    std::cout << "On ne soigne pas un villageois !\n";
                    DONNEES.texteinfo = "On ne soigne pas un villageois !";
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
