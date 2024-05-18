#include "batiment.hpp"
#include "DefParam.hpp"

// ----------------------------------------------------------------

Troupe* Batiment::former_troupes(){ Troupe* troupe = new Troupe(0); return troupe;} // On forme une troupe à partir des ressources du joueur


void Batiment::se_fait_attaquer(int degats){ // Le batiment perd de la vie, a moins qu'il soit défendu. Dans ce cas c'est un défenseur qui prend les dégats
    if (_defenseurs.size() == 0){
        _vie -= degats;
        
        std::cout << "La " << _type_batiment << " n'a pas de defenseur et a subi " << degats << ". Il lui reste " << _vie << " points de vie..." << std::endl;
        DONNEES.texteinfo = "La " + _type_batiment + " n'a pas de defenseur et a subi " + std::to_string(degats) + ". Il lui reste " + std::to_string(_vie) +" points de vie...";
    } else {
        int vie_apres_degats = _defenseurs[0]->se_fait_attaquer(degats); // Défenseur mort si degats <= 0
        std::cout << "Le defenseur a subi " << degats << " degats.. Il lui reste donc " << vie_apres_degats << "points de vie..." << std::endl; 
        while (vie_apres_degats <=0){ // Tant que les degats infliges excedent les degats du defenseur courant
            _defenseurs.erase(_defenseurs.begin()); // On supprime le defenseur courant (car mort)
            if (_defenseurs.size() == 0){ // S'il n'y a plus de defenseur le batiment est attaque
                std::cout << "Le dernier defenseur est mort et le batiment encaisse " << -vie_apres_degats << ".Il lui reste " << _vie << " points de vie..." << std::endl;
                _vie -= -vie_apres_degats;
                break;
            } else {
                std::cout << "Le deuxieme defenseur a subi " << -vie_apres_degats << " degats..";
                vie_apres_degats = _defenseurs[0]->se_fait_attaquer(-vie_apres_degats);
                std::cout <<" Il lui reste donc " << vie_apres_degats << "points de vie..." << std::endl; 
            }
        }
    }

    if (_vie > 0){
        std::cout << "La " << _type_batiment << " a tenu bon face a l'attaque. Il lui reste " << _vie << " points de vie." << std::endl;  
        DONNEES.texteinfo = "La " + _type_batiment + " a tenu bon face a l'attaque. Il lui reste " + std::to_string(_vie) + " points de vie.";  
    } else{
        std::cout << "La " << _type_batiment << " a ete detruite..." << std::endl;
        DONNEES.texteinfo = "La " + _type_batiment + " a ete detruite...";
        _niveau = 0;
    }

    if (joueur_courant == 1){
        if (_type_batiment == "Base"){
            DONNEES.j1.base.vie = _vie;
            DONNEES.j1.base.niveau = _niveau;
            DONNEES.j1.base.nb_defenseurs = _defenseurs.size();
            if (_defenseurs.size() != 0){
                DONNEES.j1.base.vie_premier_defenseur = _defenseurs[0]->getvie();    
            } else {
                DONNEES.j1.base.vie_premier_defenseur = 0;
            }
        } else if (_type_batiment == "Forteresse"){
            DONNEES.j1.forteresse.vie = _vie;
            DONNEES.j1.forteresse.niveau = _niveau;
            DONNEES.j1.forteresse.nb_defenseurs = _defenseurs.size();
            if (_defenseurs.size() != 0){
                DONNEES.j1.forteresse.vie_premier_defenseur = _defenseurs[0]->getvie();    
            } else {
                DONNEES.j1.forteresse.vie_premier_defenseur = 0;
            }
        } else{
            DONNEES.j1.ecole_magie.vie = _vie;
            DONNEES.j1.ecole_magie.niveau = _niveau;
            DONNEES.j1.ecole_magie.nb_defenseurs = _defenseurs.size();
            if (_defenseurs.size() != 0){
                DONNEES.j1.ecole_magie.vie_premier_defenseur = _defenseurs[0]->getvie();    
            } else {
                DONNEES.j1.ecole_magie.vie_premier_defenseur = 0;
            }
        }
    }else{ 
        if (_type_batiment == "Base"){
            DONNEES.j2.base.vie = _vie;
            DONNEES.j2.base.niveau = _niveau;
            DONNEES.j2.base.nb_defenseurs = _defenseurs.size();
            if (_defenseurs.size() != 0){
                DONNEES.j2.base.vie_premier_defenseur = _defenseurs[0]->getvie();    
            } else {
                DONNEES.j2.base.vie_premier_defenseur = 0;
            }
        } else if (_type_batiment == "Forteresse"){
            DONNEES.j2.forteresse.vie = _vie;
            DONNEES.j2.forteresse.niveau = _niveau;
            DONNEES.j2.forteresse.nb_defenseurs = _defenseurs.size();
            if (_defenseurs.size() != 0){
                DONNEES.j2.forteresse.vie_premier_defenseur = _defenseurs[0]->getvie();    
            } else {
                DONNEES.j2.forteresse.vie_premier_defenseur = 0;
            }
        } else{
            DONNEES.j2.ecole_magie.vie = _vie;
            DONNEES.j2.ecole_magie.niveau = _niveau;
            DONNEES.j2.ecole_magie.nb_defenseurs = _defenseurs.size();
            if (_defenseurs.size() != 0){
                DONNEES.j2.ecole_magie.vie_premier_defenseur = _defenseurs[0]->getvie();    
            } else {
                DONNEES.j2.ecole_magie.vie_premier_defenseur = 0;
            }
        }
    }
}

void Batiment::se_fait_defendre(Soldat* troupe){ // Le batiment se fait défendre par un défenseur
    _defenseurs.push_back(troupe);
    std::cout << "Le batiment se fait defendre par " << *troupe << "!" << std::endl;
    DONNEES.texteinfo = "Le batiment se fait defendre !";
}

void Batiment::se_fait_reparer(int reparation){ // reparation du batiment
    int vie_avant_rep = _vie;
    _vie += reparation;
    if (joueur_courant == 1){
        if (_type_batiment == "Base"){
            DONNEES.j1.base.vie = _vie;
        } else if (_type_batiment == "Forteresse"){
            DONNEES.j1.forteresse.vie = _vie;
        } else{
            DONNEES.j1.ecole_magie.vie = _vie;
        }
    }else{ 
        if (_type_batiment == "Base"){
            DONNEES.j2.base.vie = _vie;
        } else if (_type_batiment == "Forteresse"){
            DONNEES.j2.forteresse.vie = _vie;
        } else{
            DONNEES.j2.ecole_magie.vie = _vie;
        }
    }
}

// ----------------------------------------------------------------
// BASE

Base::Base(){ // Constructeur base
    _niveau = 1;
    _vie = FACTO_VIE_BASE;
    _type_batiment = "Base";
}

Travailleur* Base::former_troupes(){ // Renvoie un travailleur 
    Travailleur* travailleur = new Travailleur(_niveau);
    std:: cout << "La base de niveau " << _niveau << " a forme un travailleur de niveau " << _niveau << " !" << std::endl; 
    DONNEES.texteinfo = "La base de niveau " + std::to_string(_niveau) + " a forme un travailleur de niveau " + std::to_string(_niveau) + " !"; 
    if (joueur_courant == 1){
        DONNEES.j1.nb_travailleurs += 1;
    } else {
        DONNEES.j2.nb_travailleurs += 1;
    }
    return travailleur;
}

int Base::cout_amelioration(){
    if (_niveau == 0 or _niveau == NIVEAU_MAX_BAT){
        return 10000;
    } else {
        return _niveau * FACTO_AMELIO_BASE;
    }
}


// ----------------------------------------------------------------
// FORTERESSE

Forteresse::Forteresse(){ // Constructeur forteresse
    _vie = 0;
    _niveau = 0;
    _type_batiment = "Forteresse";
}

Soldat* Forteresse::former_troupes(){ // Renvoie un soldat
    Soldat* soldat = new Soldat(_niveau);
    data_troupes_de_guerre sold;
    sold.degats = _niveau*FACTO_ATTAQUE_TROUPE_SOLD;
    sold.niveau = _niveau;
    sold.vie = _niveau * FACTO_VIE_SOLDAT;

    if(joueur_courant == 1){
        DONNEES.j1.listesoldats.push_back(sold);
    } else{
        DONNEES.j2.listesoldats.push_back(sold);
    }

    std:: cout << "La forteresse de niveau " << _niveau << " a forme un soldat de niveau " << _niveau << " !" << std::endl; 
    DONNEES.texteinfo = "La forteresse de niveau " + std::to_string(_niveau) + " a forme un soldat de niveau " + std::to_string(_niveau) + " !"; 
    return soldat;
}

int Forteresse::cout_amelioration(){
    if (_niveau == NIVEAU_MAX_BAT){
        return 10000;
    } else {
        return (_niveau+1) * FACTO_AMELIO_FORT;
    }
}

// ----------------------------------------------------------------
// ECOLE DE MAGIE

EcoleDeMagie::EcoleDeMagie(){ // Constructeur forteresse
    _vie = 0;
    _niveau = 0;
    _type_batiment = "Ecole de Magie";
}

Magicien* EcoleDeMagie::former_troupes(){ // Renvoie un magicien 
    Magicien* magicien = new Magicien(_niveau);
    data_troupes_de_guerre mag;
    mag.degats = _niveau*FACTO_ATTAQUE_TROUPE_MAG;
    mag.niveau = _niveau;
    mag.vie = _niveau * FACTO_VIE_MAGICIEN;

    if(joueur_courant == 1){
        DONNEES.j1.listemagiciens.push_back(mag);
    } else{
        DONNEES.j2.listemagiciens.push_back(mag);
    }
    std:: cout << "L'Ecole de Magie de niveau " << _niveau << " a forme un magicien de niveau " << _niveau << " !" << std::endl; 
    DONNEES.texteinfo = "L'Ecole de Magie de niveau " + std::to_string(_niveau) + " a forme un magicien de niveau " + std::to_string(_niveau) + " !" ; 
    return magicien;
}

int EcoleDeMagie::cout_amelioration(){
    if (_niveau == NIVEAU_MAX_BAT){
        return 10000;
    } else {
        return (_niveau+1) * FACTO_AMELIO_ECOLE;
    }
}

// ----------------------------------------------------------------
// Affichage

std :: ostream& operator<<(std::ostream& os, Batiment& batiment){ // Operator de flux Batiment
    os << batiment.getbatiment() << ": Niveau " << batiment.getniveau() << " Vie " << batiment.getvie() << std::endl << "Liste de defenseurs :\n";
    for (TroupeDeGuerre* defenseur : batiment.getdefenseurs()){
        os <<  *dynamic_cast<Soldat*>(defenseur);
    }
    os << "--" << std::endl;
    return os;
}