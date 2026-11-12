#include <iomanip>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// ======================= CLASSE MÈRE (ABSTRAITE) =======================
class Employe {
protected:
    string matricule;
    string nom;
    string prenom;
    double salaireBase;

public:
    Employe(const string& mat, const string& n, const string& p, double sb)
        : matricule(mat), nom(n), prenom(p), salaireBase(sb) {}

    virtual ~Employe() = default;  // destructeur virtuel indispensable

    // Méthodes virtuelles pures -> classe abstraite
    virtual double calculerSalaire() const = 0;
    virtual string getCategorie() const = 0;

    // Méthode virtuelle redéfinissable
    virtual void afficher() const {
        cout << "Categorie  : " << getCategorie() << "\n"
             << "Matricule  : " << matricule << "\n"
             << "Nom        : " << nom << "\n"
             << "Prenom     : " << prenom << "\n"
             << "Salaire de base : " << fixed << setprecision(2) << salaireBase << "\n";
    }

    string getMatricule() const { return matricule; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    double getSalaireBase() const { return salaireBase; }
};

// ======================= CLASSE DÉRIVÉE : ENSEIGNANT =======================
class Enseignant : public Employe {
private:
    double indemniteEnseignement;
    double indemniteRecherche;

public:
    Enseignant(const string& mat, const string& n, const string& p, double sb,
               double indEns, double indRech)
        : Employe(mat, n, p, sb),
          indemniteEnseignement(indEns), indemniteRecherche(indRech) {}

    double calculerSalaire() const override {
        return salaireBase + indemniteEnseignement + indemniteRecherche;
    }

    string getCategorie() const override { return "Enseignant"; }

    void afficher() const override {
        Employe::afficher();
        cout << "Indemnite d'enseignement : " << indemniteEnseignement << "\n"
             << "Indemnite de recherche   : " << indemniteRecherche << "\n"
             << "SALAIRE TOTAL : " << calculerSalaire() << "\n";
    }
};

// ======================= CLASSE DÉRIVÉE : AGENT ADMINISTRATIF =======================
class AgentAdministratif : public Employe {
private:
    double primeRendement;
    double primeResponsabilite;

public:
    AgentAdministratif(const string& mat, const string& n, const string& p, double sb,
                       double pRend, double pResp)
        : Employe(mat, n, p, sb),
          primeRendement(pRend), primeResponsabilite(pResp) {}

    double calculerSalaire() const override {
        return salaireBase + primeRendement + primeResponsabilite;
    }

    string getCategorie() const override { return "Agent administratif"; }

    void afficher() const override {
        Employe::afficher();
        cout << "Prime de rendement      : " << primeRendement << "\n"
             << "Prime de responsabilite : " << primeResponsabilite << "\n"
             << "SALAIRE TOTAL : " << calculerSalaire() << "\n";
    }
};

// ======================= CLASSE DÉRIVÉE : TECHNICIEN =======================
class Technicien : public Employe {
private:
    double primeRisque;
    double primeTechnique;

public:
    Technicien(const string& mat, const string& n, const string& p, double sb,
               double pRisque, double pTech)
        : Employe(mat, n, p, sb),
          primeRisque(pRisque), primeTechnique(pTech) {}

    double calculerSalaire() const override {
        return salaireBase + primeRisque + primeTechnique;
    }

    string getCategorie() const override { return "Technicien"; }

    void afficher() const override {
        Employe::afficher();
        cout << "Prime de risque    : " << primeRisque << "\n"
             << "Prime technique    : " << primeTechnique << "\n"
             << "SALAIRE TOTAL : " << calculerSalaire() << "\n";
    }
};

// ======================= PROGRAMME PRINCIPAL =======================
int main() {
    // Collection polymorphe : pointeurs vers la classe mère
    vector<unique_ptr<Employe>> personnel;

    personnel.push_back(make_unique<Enseignant>("ENS001", "Diallo", "Amadou", 300000, 80000, 50000));
    personnel.push_back(make_unique<Enseignant>("ENS002", "Traore", "Fatoumata", 350000, 90000, 60000));
    personnel.push_back(make_unique<AgentAdministratif>("ADM001", "Kone", "Issouf", 200000, 30000, 25000));
    personnel.push_back(make_unique<Technicien>("TEC001", "Ouedraogo", "Salif", 180000, 20000, 35000));

    cout << "===== LISTE DU PERSONNEL UNIVERSITAIRE =====\n\n";

    double masseSalariale = 0;
    for (const auto& e : personnel) {
        e->afficher();                       // liaison dynamique
        masseSalariale += e->calculerSalaire();
        cout << "--------------------------------------------\n";
    }

    cout << "\nMasse salariale totale : " << masseSalariale << "\n";
    return 0;
}