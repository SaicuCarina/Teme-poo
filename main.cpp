#include <iostream>
#include <string.h>

using namespace std;

class Oferta
{
    char destinatie[100]; ///pentru locatiile formate din mai multe cuvinte, spatiile vor fi inlocuite cu "_"
    float pret; /// in lei
    int locuridisponibile; ///locuri disponibile, maximul pestru oferta respectiva
public:
    Oferta(){}; ///constructor de initializare
    Oferta(char *destinatie_, float pret_, int locuridisponibile_) ///constructor de initializare
    {
        strcpy(destinatie, destinatie_);
        pret=pret_;
        locuridisponibile=locuridisponibile_;
    }

    virtual ~Oferta(){} ///destructor

    const char *getDestinatie() const
    {
        return destinatie;
    }

    float getPret() const
    {
        return pret;
    }

    int getLocuriDisponibile() const
    {
        return locuridisponibile;
    }

    void setDestinatie(char destinatie[])
    {
        strcpy(Oferta::destinatie, destinatie);
    }

    void setPret(float pret)
    {
        Oferta::pret = pret;
    }

    void setLocuridisponibile(int locuridisponibile)
    {
        Oferta::locuridisponibile = locuridisponibile;
    }


    void citire()
    {

        char d[100];
        float p;
        int l;
        cin>>d>>p>>l;
        strcpy(destinatie, d);
        pret=p;
        locuridisponibile=l;
    }
    void afisare() {
        cout << destinatie << " " << pret << " " << locuridisponibile << "\n";
    }

};

class Agentie_de_turism
{
    char nume[25];
    int nr_oferte=0;
    Oferta o[1000];
public:
    Agentie_de_turism(char *nume_, int nr_oferte_) ///constructor de initializare
    {
        strcpy(nume, nume_);
        nr_oferte=nr_oferte_;
    }
    Agentie_de_turism(const Agentie_de_turism &agentie) ///constructor de copiere
    {
        strcpy(nume, agentie.nume);
        nr_oferte=agentie.nr_oferte;
    };

    Agentie_de_turism() {};

    int cauta_oferta(char destinatie[], int pret, Oferta a[], int n)
    {
        for(int i=0;i<n;i++)
            if(strcmp(destinatie, a[i].getDestinatie())==0 and pret==a[i].getPret())
                return i;
        return -1;
    }

    const char *getNume() const {
        return nume;
    }

    int getNrOferte() const {
        return nr_oferte;
    }

    void setNume(char nume_[25])
    {
        strcpy(nume, nume_);
    }

    void setNrOferte(int nrOferte) {
        nr_oferte = nrOferte;
    }

    void afisare()
    {
        cout<<nume<<" "<<nr_oferte;
    }
    virtual ~Agentie_de_turism() {} ///destructor

    friend ostream &operator<<(ostream &out, const Agentie_de_turism &agentie);

    friend istream &operator>>(istream &in, Agentie_de_turism &agentie);

    bool operator==(const Agentie_de_turism &comp) const{
        return nume==comp.nume && nr_oferte==comp.nr_oferte;
    }

    void operator+=(Oferta oferta_)
    {
        nr_oferte++;
        o[nr_oferte-1]=oferta_;
    }
};
/*
ostream &operator<<(ostream &out, const Agentie_de_turism &agentieDeTurism)
{

}

istream &operator>>(istream &in, Agentie_de_turism &agentieDeTurism)
{

}
*/
int main()
{
    Oferta x; ///constructor de initializare

    x.setDestinatie("Malta");
    x.setPret(1000);
    x.setLocuridisponibile(2);

    cout<<"Constructorul de initializare are valorile:"<<endl;
    x.afisare();
    cout<<endl;

    Oferta y(x); ///constructor de copiere
    cout<<"Constructorul de copiere are vlaorile:"<<endl;
    y.afisare();
    cout<<endl;

    Oferta z; ///constructor de atribuire
    z=x;

    cout<<"Constructorul de atribuire are valoarea:"<<endl;
    z.afisare();
    cout<<endl;

    int n;
    cout<<"Numarul de oferte disponibile in agentie este: ";
    cin>>n;
    Oferta a[n+1];
    cout<<endl;
    cout<<"Aceste oferte sunt: "<<endl;
    for(int i=0;i<n;i++)
        a[i].citire();
    cout<<endl;
    cout<<"Ofertele introduse in sistem sunt:"<<endl;
    for(int i=0;i<n;i++)
        a[i].afisare();

    Agentie_de_turism agentie;

    int cauta=0;

    cauta=agentie.cauta_oferta("Malta", 400, a, n);

    cout<<"Oferta cautata este:";
    a[cauta].afisare();
    cout<<endl;
    cout<<"Pozitia unde a fost gasita este:"<<endl;
    cout<<cauta;
    return 0;
}
