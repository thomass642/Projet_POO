#include "joueur.hpp"

class Jeu{
    private:
        Joueur* _joueur1;
        Joueur* _joueur2;
    public:
        Jeu(std::string joueur1, std::string joueur2); // Définition des joueurs (ou IA)
        void run();
};