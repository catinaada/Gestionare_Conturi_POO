#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include <windows.h>

using namespace std;

/*
*  Gestiune conturi bancare pt persoane fizice de la nivelul unei filiale bancare
*/


void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


class Cont {
private:
    string tipCont;
    string iban;
    double* listaOperatii;
    int nrOperatii;
    double sold;

public:
    // Constructori
    Cont() : tipCont("cont bancar"), iban("RO33BTRLRONCRT6060197701"), listaOperatii(nullptr), nrOperatii(0), sold(0.0) {}

    Cont(const string tc, const string iban)
        : tipCont(tc), iban(iban), listaOperatii(nullptr), nrOperatii(0), sold(0) {}


    Cont(const string tc, const string iban, double sold)
        : tipCont(tc), iban(iban), listaOperatii(nullptr), nrOperatii(0), sold(sold) {}

    Cont(const string tc, const string iban, const double* listaOperatii, int nrOperatii, double sold)
        : tipCont(tc), iban(iban), nrOperatii(nrOperatii), sold(sold) {
        if (nrOperatii > 0) {
            this->listaOperatii = new double[nrOperatii];
            for (int i = 0; i < nrOperatii; i++) {
                this->listaOperatii[i] = listaOperatii[i];
            }
        }
        else {
            this->listaOperatii = nullptr;
            this->nrOperatii = 0;
        }
    }

    Cont(const Cont& c) : tipCont(c.tipCont), iban(c.iban), nrOperatii(c.nrOperatii), sold(c.sold) {
        if (nrOperatii > 0) {
            listaOperatii = new double[nrOperatii];
            for (int i = 0; i < nrOperatii; i++) {
                listaOperatii[i] = c.listaOperatii[i];
            }
        }
        else {
            this->nrOperatii = 0;
            this->listaOperatii = nullptr;
        }
    }

    Cont& operator=(const Cont& c) {
        if (this != &c) {
            if (this->listaOperatii != nullptr)
                delete[] listaOperatii;
            this->tipCont = c.tipCont;
            this->iban = c.iban;
            this->sold = c.sold;
            this->nrOperatii = c.nrOperatii;
            if (this->nrOperatii > 0) {
                listaOperatii = new double[nrOperatii];
                for (int i = 0; i < nrOperatii; i++) {
                    listaOperatii[i] = c.listaOperatii[i];
                }
            }
            else {
                this->listaOperatii = nullptr;
                this->nrOperatii = 0;

            }
        }
        return *this;
    }

    ~Cont() {
        if (this->listaOperatii != nullptr)
            delete[] listaOperatii;
    }


    string getTipCont()  {
        return this->tipCont;
    }

    void setTipCont( string tc) {
        if (tc.length() > 1)
            this->tipCont = tc;
    }

    string getIban()  {
        return this->iban;
    }

    void setIban(const string& i) {
        if (i.length() >=24) 
            iban = i;
        else
            cout<<("IBAN-ul este invalid");
    }

    double getSold()  {
        return this->sold;
    }

    void setSold(double s) {
        this->sold = s > 0 ? s : 0;
    }

    int getNrOperatii()  {
        return nrOperatii;
    }

    double* getOperatii()  {
        if (listaOperatii != nullptr) {
            double* copie = new double[nrOperatii];
            for (int i = 0; i < nrOperatii; i++) {
                copie[i] = listaOperatii[i];
            }
            return copie;
        }
        return nullptr;
    }

    void setOperatii(const double* listaOperatii, int nrOperatii) {
        delete[] this->listaOperatii;
        if (nrOperatii > 0) {
            this->nrOperatii = nrOperatii;
            this->listaOperatii = new double[this->nrOperatii];
            for (int i = 0; i < this->nrOperatii; i++) {
                this->listaOperatii[i] = listaOperatii[i];
            }
        }
        else {
            this->nrOperatii = 0;
            this->listaOperatii = nullptr;
        }
    }


    bool operator==( Cont c) {
        if (this->getIban() == c.iban)
            return true;
        else return false;

    }

    bool operator!=( Cont c) {
        if (this->getIban() != c.iban)
            return true;
        else return false;
    }

    void addTranzactie(double tranzactie)
    {
        double* listanoua = new double[++nrOperatii];
        for (int i = 0; i < nrOperatii - 1; i++) {
            listanoua[i] = listaOperatii[i];
        }
        listanoua[nrOperatii - 1] = tranzactie;

        delete[] listaOperatii;
        listaOperatii = listanoua;
        this->sold += tranzactie;

    }

    virtual void afisareCont() const {
        setConsoleColor(0x0A);
        cout << " --> ";
        cout << "Tip cont: " << tipCont << "\n"
            << "IBAN: " << iban << "\n"
            << "Sold: " << sold << "\n"
            << "Numar operatii: " << nrOperatii << "\n";
        for (int i = 0; i < nrOperatii; i++) {
            cout << "Operatie " << i + 1 << ": " << listaOperatii[i] << "\n";
        }
        setConsoleColor(0x07);

    }

    friend ostream& operator<<(ostream& ost, Cont& c) {
        ost << c.tipCont << " " << c.iban << " " << c.sold << " " << c.nrOperatii << " : ";
        if (c.listaOperatii != nullptr && c.nrOperatii > 0)
            for (int i = 0; i < c.nrOperatii; i++) {
                ost << c.listaOperatii[i] << ", ";
            }
        else ost << "nimic" << endl;

        return ost;
    }

    friend istream& operator>>(istream& ist, Cont& c) {
        cout << "Tip cont= ";
        ist >> c.tipCont;
        cout << "Iban= ";
        ist >> c.iban;
        cout << "Sold= ";
        ist >> c.sold;
        cout << "Numar de operatii= ";
        ist >> c.nrOperatii;
        if (c.listaOperatii != nullptr) {
            delete[] c.listaOperatii;
        }
        if (c.nrOperatii > 0) {
            c.listaOperatii = new double[c.nrOperatii];
            for (int i = 0; i < c.nrOperatii; i++) {
                ist >> c.listaOperatii[i];
            }
        }
        else
        {
            c.nrOperatii = 0;
            c.listaOperatii = nullptr;
        }
        return ist;
    }

    friend ifstream& operator>>(ifstream& ist, Cont& c) {
        getline(ist, c.tipCont);
        getline(ist, c.iban);
        ist >> c.sold;
        ist >> c.nrOperatii;
        delete[] c.listaOperatii;
        c.listaOperatii = new double[c.nrOperatii];
        for (int i = 0; i < c.nrOperatii; i++) {
            ist >> c.listaOperatii[i];
        }
        return ist;
    }

};


class ContEconomii : public Cont {
private:
    double dobanda;
    string scopEconomie;


public:

    ContEconomii()
        : Cont("cont economii", "RO49AAAA1B31007593840000"), dobanda(0.0), scopEconomie("Necunoscut") {}



    ContEconomii( string tc,  string iban, double* listaOperatii = nullptr, int nrOperatii = 0, double sold = 0.0, double dobanda = 0.0,  string scopEconomie = "Necunoscut")
        : Cont(tc, iban, listaOperatii, nrOperatii, sold), dobanda(dobanda), scopEconomie(scopEconomie) {}

    ContEconomii( string tc,  string iban, double sold, double dobanda,  string scopEconomie)
        : Cont(tc, iban, sold), dobanda(dobanda), scopEconomie(scopEconomie) {}

    ContEconomii(const ContEconomii& c) : Cont(c), dobanda(c.dobanda), scopEconomie(c.scopEconomie) {}

    ContEconomii& operator=(const ContEconomii& c) {
        if (this != &c) {
            Cont::operator=(c);
            dobanda = c.dobanda;
            scopEconomie = c.scopEconomie;
        }
        return *this;
    }
   
    ~ContEconomii() {}


    void setDobanda(double d) {
        dobanda = (d > 0) ? d : 0;
    }

    double getDobanda()  {
        return dobanda;
    }

    string getScopEconomie()  {
        return scopEconomie;
    }

    void setScopEconomie( string scop) {
        if (scop.length() > 2) {
            scopEconomie = scop;
        }
    }

    // Calcul dobanda zilnica
    void calculDobandaZi(double& dz)  {
        dz = getSold() * dobanda * 1 / 360;
    }

    void afisareCont() const override {
        setConsoleColor(0x0A);
        Cont::afisareCont();
        cout << ", Dobanda= " << dobanda << ", Scop Economie= " << scopEconomie << "\n";
        setConsoleColor(0x07);

    }

    friend ostream& operator<<(ostream& ost, ContEconomii& ce) {
        ost << (Cont&)ce;
        ost << " " << ce.dobanda << " " << ce.scopEconomie;
        return ost;
    }

    friend istream& operator>>(istream& ist, ContEconomii& ce) {
        ist >> (Cont&)ce;
        cout << "Dobanda= ";
        ist >> ce.dobanda;
        cout << "Scop Economie= ";
        ist >> ce.scopEconomie;
        return ist;
    }

};


class Persoana {
private:
    string nume;
    string prenume;
    string cnp;
    string adresa; 

public:
    Persoana() : nume("Necunoscut"), prenume("Necunoscut"), cnp("0000000000000"), adresa("Necunoscut") {}

    Persoana( string nume,  string prenume,  string cnp,  string adresa)
        : nume(nume), prenume(prenume), cnp(cnp), adresa(adresa) {}

    string getNume()  {
        return nume;
    }

    void setNume( string nume) {
        this->nume = nume;
    }

    string getPrenume()  {
        return prenume;
    }

    void setPrenume( string prenume) {
        this->prenume = prenume;
    }

    string getCNP()  {
        return cnp;
    }

    void setCNP( string cnp) {
        this->cnp = cnp;
    }

    string getAdresa()  {
        return adresa;
    }

    void setAdresa( string adresa) {
        this->adresa = adresa;
    }

    virtual void afisarePersoana()  {
    
        cout << "Nume: " << nume << ", Prenume: " << prenume << ", CNP: " << cnp << ", Adresa: " << adresa << endl;
    }

    friend ostream& operator<<(ostream& ost, Persoana& p) {

        ost << p.nume << " " << p.prenume << " " << p.cnp <<" " << p.adresa << " \n ";
        return ost;
    }



};


class Client : public Persoana {
private:
    Cont* conturi;   
    int nrConturi;   

public:
    Client() : Persoana(), conturi(nullptr), nrConturi(0) {}

    Client( string nume,  string prenume,  string cnp,  string adresa)
        : Persoana(nume, prenume, cnp, adresa), conturi(nullptr), nrConturi(0) {}

    Client( string nume,  string prenume,  string cnp,  string adresa, const Cont* conturi, int nrConturi)
        : Persoana(nume, prenume, cnp, adresa), nrConturi(nrConturi) {
        if (nrConturi > 0) {
            this->conturi = new Cont[nrConturi];
            for (int i = 0; i < nrConturi; ++i) {
                this->conturi[i] = conturi[i];
            }
        }
        else {
            this->nrConturi = 0;
            this->conturi = nullptr;
        }
    }

    Client(const Client& c) : Persoana(c) {
        nrConturi = c.nrConturi;
        if (nrConturi > 0) {
            conturi = new Cont[nrConturi];
            for (int i = 0; i < nrConturi; ++i) {
                conturi[i] = c.conturi[i];
            }
        }
        else {
            this->nrConturi = 0;
            this->conturi = nullptr;
        }
    }

    Client& operator=(const Client& c) {
        if (this != &c) {
            Persoana::operator=(c);

            delete[] conturi;

            nrConturi = c.nrConturi;
            if (nrConturi > 0) {
                conturi = new Cont[nrConturi];
                for (int i = 0; i < nrConturi; ++i) {
                    conturi[i] = c.conturi[i];
                }
            }
            else {
                this->conturi = nullptr;
                nrConturi = 0;
            }
        }
        return *this;
    }

    ~Client() {
        if (conturi != nullptr)
            delete[] conturi;
    }

    Cont* getConturi()  {
        return conturi;
    }

    void setConturi(Cont* conturi, int nrConturi) {
        delete[] this->conturi;
        this->nrConturi = nrConturi;
        if (nrConturi > 0) {
            this->conturi = new Cont[nrConturi];
            for (int i = 0; i < nrConturi; ++i) {
                this->conturi[i] = conturi[i];
            }
        }
        else {
            this->conturi = nullptr;
        }
    }

    int getNrConturi()  {
        return nrConturi;
    }

    void addCont(Cont cont)
    {
        Cont* listanoua = new Cont[++nrConturi];
        for (int i = 0; i < nrConturi - 1; i++) {
            listanoua[i] = conturi[i];
        }
        listanoua[nrConturi - 1] = cont;

        delete[] conturi;
        conturi = listanoua;
    }

    void stergeCont( Cont& cont) {
        if (nrConturi <= 0) return;

        Cont* vcontvechi = conturi;
        conturi = new Cont[nrConturi - 1];
        int index = 0;

        for (int i = 0; i < nrConturi; ++i) {
            if (vcontvechi[i] != cont) {
                conturi[index++] = vcontvechi[i];
            }
        }

        delete[] vcontvechi;
        nrConturi--;
    }

    double calculTotalDisponibil()  {
        double suma = 0;
        for (int i = 0; i < nrConturi; ++i) {
            suma += conturi[i].getSold();
        }
        return suma;
    }

    void transfer(const Cont& cont1, const Cont& cont2, double suma) {
        bool cont1Gasit = false, cont2Gasit = false;

        for (int i = 0; i < nrConturi; ++i) {
            if (conturi[i] == cont1) {
                cont1Gasit = true;
                for (int j = 0; j < nrConturi; ++j) {
                    if (conturi[j] == cont2) {
                        cont2Gasit = true;
                        if (conturi[i].getSold() >= suma) {
                            conturi[i].addTranzactie(-suma);
                            conturi[j].addTranzactie(suma);
                            cout << "Transfer aprobat" << endl;
                        }
                        else {
                            cout << "Sold insuficient pentru aceasta tranzactie" << endl;
                        }
                        break;
                    }
                }
                break;
            }
        }

        if (!cont1Gasit || !cont2Gasit) {
            cout << "Cont/uri inexistent/e" << endl;
        }
    }

    void depune( Cont cont, double suma) {
        if (suma <= 0) {
            cout << "Suma de depus trebuie sa fie pozitiva" << endl;
            return;
        }

        for (int i = 0; i < nrConturi; ++i) {
            if (conturi[i] == cont) {
                conturi[i].addTranzactie(suma);
                cout << "Adaugare "<<suma<<" la contul "<<cont.getTipCont() << endl;

                return;
            }
        }

        cout << "Contul nu a fost gasit" << endl;
    }

    void retrage( Cont cont, double suma) {
        if (suma <= 0) {
            cout << "Suma de retras trebuie sa fie pozitiva" << endl;
            return;
        }

        for (int i = 0; i < nrConturi; ++i) {
            if (conturi[i] == cont) {
                if (suma <= conturi[i].getSold()) {
                    conturi[i].addTranzactie(-suma);
                    cout << "Retragere " << suma << " la contul " << cont.getTipCont() << endl;

                }
                else {
                    cout << "Suma este mai mare decat soldul" << endl;
                }
                return;
            }
        }

        cout << "Contul nu a fost gasit" << endl;
    }

    bool operator==( Client p)  {
        return this->getCNP() == p.getCNP();
    }

    bool operator!=( Client p)  {
        return !(*this == p);
    }

    void afisarePersoana()  override{

        Persoana::afisarePersoana();

        cout << ", Nr Conturi= " << nrConturi << " :\n";
        for (int i = 0; i < nrConturi; ++i) {
            conturi[i].afisareCont();
        }
    }

    friend ostream& operator<<(ostream& ost, Client& p) {
        ost << (Persoana&)p;
        ost << p.nrConturi << " :\n ";
        for (int i = 0; i < p.nrConturi; i++)
            ost << p.conturi[i] << "\n";
        return ost;
    }

};



class Banca {
private:
    const int id_banca;
    string denumire;
    Client* persoane;
    int nr_persoane;
    static int nrTotalBanci;

public:

    Banca(const int id, string d, Client* p, int nr_p) :id_banca(id) {
        denumire = d;
        nr_persoane = nr_p;
        if (nr_p > 0)
        {
            persoane = new Client[nr_persoane];
            for (int i = 0; i < nr_persoane; i++) {
                persoane[i] = p[i];
            }
        }
        else {
            persoane = nullptr;
            nr_persoane = 0;
        }
        ++nrTotalBanci;
    }

    Banca(const int id, Client* p, int nr_p) :id_banca(id) {
        nr_persoane = nr_p;
        if (nr_p > 0)
        {
            persoane = new Client[nr_persoane];
            for (int i = 0; i < nr_persoane; i++) {
                persoane[i] = p[i];
            }
        }
        else {
            persoane = nullptr;
            nr_persoane = 0;
        }
        ++nrTotalBanci;

    }


    Banca(const Banca& b) :id_banca(b.id_banca) {

        denumire = b.denumire;
        nr_persoane = b.nr_persoane;
        nrTotalBanci++;
        if (nr_persoane > 0)
        {
            persoane = new Client[nr_persoane];
            for (int i = 0; i < nr_persoane; i++) {
                persoane[i] = b.persoane[i];
            }
        }
        else {
            persoane = nullptr;
            nr_persoane = 0;
        }
        ++nrTotalBanci;

    }

    Banca& operator=(const Banca& b) {
        if (this != &b) {
            if (persoane != nullptr)
                delete[] persoane;
            denumire = b.denumire;
            nr_persoane = b.nr_persoane;
            if (nr_persoane > 0)
            {
                persoane = new Client[nr_persoane];
                for (int i = 0; i < nr_persoane; i++) {
                    persoane[i] = b.persoane[i];
                }
            }
            else {
                persoane = nullptr;
                nr_persoane = 0;
            }
        }
        return *this;
    }

    static int getNrTotalBanci() {
        return nrTotalBanci;
    }

    static void setNrTotalBanci(int nrTotalBanci) {
        if (nrTotalBanci > 0) {
            Banca::nrTotalBanci = nrTotalBanci;
        }
        else Banca::nrTotalBanci = 0;
    }

    string getDenumire() {
        return denumire;
    }

    void setDenumire(string den) {
        if (den.length() >=2)
            denumire = den;
    }

    Client* getPersoane() {
        if (persoane != nullptr) {
            Client* copie = new Client[nr_persoane];
            for (int i = 0; i < nr_persoane; i++) {
                copie[i] = persoane[i];
            }
            return copie;
        }
         return nullptr;
    }

    int getNrPersoane() {
        return nr_persoane;
    }

    void setListaPersoane(Client* p, int nr) {
        delete[] persoane;
        nr_persoane = nr;
        if (nr > 0)
        {
            persoane = new Client[nr];
            for (int i = 0; i < nr; i++) {
                persoane[i] = p[i];
            }
        }
        else {
            nr_persoane = 0;
            persoane = nullptr;
        }
    }

    void stergeClient(Client p) {
        if (nr_persoane > 0) {
            Client* vpers = persoane;
            persoane = new Client[nr_persoane - 1];
            int j = 0;
            for (int i = 0; i < nr_persoane; ++i) {
                if (vpers[i] != p) {
                    persoane[j++] = vpers[i];
                }
            }
            nr_persoane--;
            delete[] vpers;
        }

    }

    void addClient(Client pers)
    {
        Client* listanoua = new Client[nr_persoane + 1];
        for (int i = 0; i < nr_persoane; ++i) {
            listanoua[i] = persoane[i];
        }
        listanoua[nr_persoane] = pers;
        ++nr_persoane;
        delete[] persoane;
        persoane = listanoua;
    }
    
   

    

    void deschidereCont(Client p, Cont c) {
        bool found = false;
        for (int i = 0; i < nr_persoane; i++) {
            if (persoane[i] == p)
            {
                found = true;
                persoane[i].addCont(c);
                break;
            }
        }
        if (!found) {
            addClient(p);
            persoane[nr_persoane - 1].addCont(c);
        }
    }

 
    void inchidereCont(Client p, const Cont c) {
        for (int i = 0; i < nr_persoane; ++i) {
            if (this->persoane[i] == p) {
                for (int j = 0; j < persoane[i].getNrConturi(); ++j) {
                    if (persoane[i].getConturi()[j] == c) {
                        persoane[i].stergeCont(persoane[i].getConturi()[j]);
                        if (persoane[i].getNrConturi() == 0) {
                            stergeClient(persoane[i]);
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    void transfer(string idClient1,  string ibanCont1, string idClient2,  string ibanCont2, double suma) {
        Client* client1 = nullptr;
        Client* client2 = nullptr;

        for (int i = 0; i < nr_persoane; ++i) {
            if (persoane[i].getCNP() == idClient1) {
                client1 = &persoane[i];
            }
            if (persoane[i].getCNP() == idClient2) {
                client2 = &persoane[i];
            }
        }

        if (client1 == nullptr) {
            cout << "Clientul cu ID-ul " << idClient1 << " nu a fost gasit." << endl;
            return;
        }
        if (client2 == nullptr) {
            cout << "Clientul cu ID-ul " << idClient2 << " nu a fost gasit." << endl;
            return;
        }

        Cont* cont1 = nullptr;
        Cont* cont2 = nullptr;

        for (int i = 0; i < client1->getNrConturi(); ++i) {
            if (client1->getConturi()[i].getIban() == ibanCont1) {
                cont1 = &client1->getConturi()[i];
                break;
            }
        }
        for (int i = 0; i < client2->getNrConturi(); ++i) {
            if (client2->getConturi()[i].getIban() == ibanCont2) {
                cont2 = &client2->getConturi()[i];
                break;
            }
        }

        if (cont1 == nullptr) {
            cout << "Contul cu IBAN-ul " << ibanCont1 << " nu a fost gasit pentru clientul " << idClient1 << "." << endl;
            return;
        }
        if (cont2 == nullptr) {
            cout << "Contul cu IBAN-ul " << ibanCont2 << " nu a fost gasit pentru clientul " << idClient2 << "." << endl;
            return;
        }

        if (cont1->getSold() >= suma) {
            cont1->addTranzactie(-suma);
            cont2->addTranzactie(suma);
            cout << "Transferul de " << suma << " RON de la contul " << ibanCont1 << " la contul " << ibanCont2 << " a fost efectuat cu succes." << endl;
        }
        else {
            cout << "Sold insuficient in contul " << ibanCont1 << "." << endl;
        }
    }

    


    void afisareBanca() {
        cout << "Denumire Banca= " << denumire << ", Nr Persoane " << nr_persoane << " :\n";
        for (int i = 0; i < nr_persoane; i++)
        {
            setConsoleColor(0x0E);
            cout << i+1 << " :\n ";
            persoane[i].afisarePersoana();
        }
        setConsoleColor(0x07);


    }

    ~Banca() {
        if (persoane != nullptr)
            delete[] persoane;
        --nrTotalBanci;
    }

    friend ostream& operator<<(ostream& ost, Banca& b) {
        ost << b.denumire << " " << b.nr_persoane << " :\n";
        for (int i = 0; i < b.nr_persoane; i++)
            ost << b.persoane[i] << "\n";

        return ost;
    }

    void actualizareDateClient(string cnp, string nume, string prenume, string adresa) {
        for (int i = 0; i < nr_persoane; i++)  {
            if (persoane[i].getCNP() == cnp) {
                persoane[i].setNume(nume);
                persoane[i].setPrenume(prenume);
                persoane[i].setAdresa(adresa);
                cout << "Datele clientului cu CNP-ul " << cnp << " au fost actualizate cu succes." <<endl;
            }
        }
    }

    void depunere(string cnp, string iban, double suma) {
        for (int i = 0; i < nr_persoane; i++) {
            if (persoane[i].getCNP() == cnp) {
                bool contGasit = false;
                for (int j = 0; j < persoane[i].getNrConturi(); j++) {
                    if (persoane[i].getConturi()[j].getIban() == iban) {
                        persoane[i].depune(*persoane[i].getConturi(), suma);
                        contGasit = true;
                        break;
                    }
                }
                if (!contGasit) {
                    cout << "Contul cu IBAN-ul " << iban << " nu a fost gasit pentru clientul cu CNP-ul " << cnp << "." << endl;
                }
                return;  
            }
        }
        cout << "Clientul cu CNP-ul " << cnp << " nu a fost gasit." << endl;
    }

    void retragere(string cnp, string iban, double suma) {
        for (int i = 0; i < nr_persoane; i++) {
            if (persoane[i].getCNP() == cnp) {
                bool contGasit = false;
                for (int j = 0; j < persoane[i].getNrConturi(); j++) {
                    if (persoane[i].getConturi()[j].getIban() == iban) {
                        persoane[i].retrage(*persoane[i].getConturi(), suma);
                        contGasit = true;
                        break;
                    }
                }
                if (!contGasit) {
                    cout << "Contul cu IBAN-ul " << iban << " nu a fost gasit pentru clientul cu CNP-ul " << cnp << "." << endl;
                }
                return;
            }
        }
        cout << "Clientul cu CNP-ul " << cnp << " nu a fost gasit." << endl;
    }


 
};

int Banca::nrTotalBanci = 0;



int main() {

    //Testare functionalitati clase

    double operatiiCont1[] = { 100.0, -50.0, 200.0 };
    Cont contCurent("cont curent", "RO12AAAA1234567890123456",  operatiiCont1, 3, 1000.0 );

    ContEconomii contEconomii("cont economii", "RO34BBBB9876543210987654", 2000.0, 0.05, "Economii pentru vacanta");

    Persoana persoana1("Ion", "Popescu", "1234567890123", "Strada Mare nr. 10");

    Cont conturiClient[] = { contCurent, contEconomii };
    Client client("Ion", "Popescu", "1234567890123", "Strada Mare nr. 10", conturiClient, 2);
   
    cout << "Adaugare 500.0 la contul curent al clientului...\n";
    client.depune(contCurent, 500.0);

    cout << "Retragere 200.0 din contul economii al clientului...\n";
    client.retrage(contEconomii, 200.0);

    cout << "Transfer 300.0 din contul curent in contul economii...\n";
    client.transfer(contCurent, contEconomii, 300.0);
    cout << endl;

    //La nivel de banca

    Client clientiBanca[] = { client };
    Banca banca(1, "Banca BCR", clientiBanca, 1);

    cout << endl;

    cout << "Informatii actualizate despre banca:\n";
    banca.afisareBanca();
    
    Client client2("Dima", "Andrei", "1474114741477", "Str. I.L. Caragiale, nr. 8");

    Cont cont2;
    client2.addCont(cont2);
    client2.afisarePersoana();
    banca.addClient(client2);
    

   cout << "Informatii actualizate despre banca, dupa adaugare client nou:\n";
   banca.afisareBanca();
   
   banca.transfer(client.getCNP(), contCurent.getIban(), client2.getCNP(), cont2.getIban(),50);
   
   banca.actualizareDateClient(client2.getCNP(), client2.getNume(), client2.getPrenume(), "Aleea CFR, nr. 6");


   banca.afisareBanca();
   
   cout << endl;
   banca.transfer(client.getCNP(), contEconomii.getIban(), client.getCNP(), contCurent.getIban(), 50);
   banca.depunere(client2.getCNP(), cont2.getIban(), 40);
   banca.retragere(client2.getCNP(), cont2.getIban(), 20);
   banca.afisareBanca();

   cout << "\nInchiderea contului de economii...\n";
   banca.inchidereCont(client, contEconomii); 

   banca.afisareBanca();

    return 0;
}