#include <iostream>
#include <cstring>

using namespace std;

class Oferta
{
    char destinatie[100]; ///pentru locatiile formate din mai multe cuvinte, spatiile vor fi inlocuite cu "_"
    float pret; /// in euro
    int locuridisponibile; ///locuri disponibile, maximul pestru oferta respectiva
public:

    Oferta(){};

    Oferta(char *destinatie_, float pret_, int locuridisponibile_) ///constructor de initializare
    {
        strcpy(destinatie, destinatie_);
        pret = pret_;
        locuridisponibile = locuridisponibile_;
    }

    Oferta(const Oferta &oferta) ///constructor de copiere
    {
        strcpy(destinatie, oferta.destinatie);
        pret=oferta.pret;
        locuridisponibile=oferta.locuridisponibile;
    };

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

    void setDestinatie(char destinatie_[])
    {
        strcpy(Oferta::destinatie, destinatie_);
    }

    void setPret(float pret_)
    {
        Oferta::pret = pret_;
    }

    void setLocuridisponibile(int locuridisponibile_)
    {
        Oferta::locuridisponibile = locuridisponibile_;
    }

    void citire_oferta()
    {
        char d[100];
        float p;
        int l;
        cin>>d>>p>>l;
        strcpy(destinatie, d);
        pret=p;
        locuridisponibile=l;
    }
    void afisare_oferta() {
        cout<<"Destinatia: "<<destinatie<<endl;
        cout<<"Pretul: "<<pret<<" euro "<<endl;
        cout<<"Locurile disponibile pentru aceasta oferta: "<<locuridisponibile<<endl;
        cout<<endl;
    }
//    bool operator==(const Oferta &comp) const{
//        return destinatie==comp.destinatie && pret==comp.pret && locuridisponibile==comp.locuridisponibile;
//    }

    virtual ~Oferta(){} ///destructor, se apeleaza odata cu destructorul de la agentie de turism

};


class Agentie_de_turism
{
    char nume[25];
    int nr_oferte=0;
    Oferta oferta[1000];
public:

    Agentie_de_turism(){};

    Agentie_de_turism(char *nume_, int nr_oferte_) ///constructor de initializare
    {
        strcpy(nume, nume_);
        nr_oferte=nr_oferte_;
    }

    void cauta_oferta(char destinatie[], Oferta a[], int n)
    {
        int ok=0;
        for(int i=0;i<n;i++)
            if(strcmp(destinatie, a[i].getDestinatie())==0)
            {
                ok++;
                cout<<"Pretul pentru destinatia cautata este: "<<a[i].getPret()<<" euro "<<endl;
                cout<<"Locurile disponibile pentru locatia cautata sunt:"<<a[i].getLocuriDisponibile()<<endl<<endl;
            }
        if(ok==0)
            cout<<"Nu exista oferte pentru destinatia cautata!";
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

    void afisare_agentie()
    {
        cout<<"Numele agentiei este: "<<nume<<", "<<"numarul ofertelor din agentie este: "<<nr_oferte;
    }

    const Oferta *getOferta() const {
        return oferta;
    }

    ~Agentie_de_turism() {} ///destructor

//    friend ostream &operator<<(ostream &out, const Agentie_de_turism &agentie);

//    friend istream &operator>>(istream &in, Agentie_de_turism &agentie);

    void operator+=(Oferta oferta_)
    {
        nr_oferte++;
        oferta[nr_oferte-1]=oferta_;
    }

    friend class Oferta;
};

ostream &operator<<(ostream &out, const Agentie_de_turism &agentie)
{
    out<<"Numele agentiei este: "<<agentie.getNume()<<endl;
    out<<"Numarul ofertelor este: "<<agentie.getNrOferte()<<endl;
    for(int i=0;i<agentie.getNrOferte();i++)
    {
        cout<<"Destinatia: "<<agentie.getOferta()[i].getDestinatie()<<endl;
        cout<<"Pretul: "<<agentie.getOferta()[i].getPret()<<endl;
        cout<<"Locuri disponibile: "<<agentie.getOferta()[i].getLocuriDisponibile()<<endl;
    }
    return out;
}


int main()
{
    Oferta of1; ///constructor de initializare
    Oferta of[100];

    int n;

    Agentie_de_turism agentii;


    int roll;
    cout<<"Introduce un numar de la 1 la 6:";
    cin >> roll;
    switch(roll)
    {

        case 1:
        {
            cout<<"Afiseava contructorul de initializare!"<<endl;

            of1.setDestinatie("Malta");
            of1.setPret(400);
            of1.setLocuridisponibile(3);

            of1.afisare_oferta();
            cout<<endl;

            break;
        }
        case 2:
        {
            cout<<"Afiseaza contructorul de copiere!"<<endl;

            Oferta x(of1); ///constructor de copiere
            cout<<"Constructorul de copiere are vlaorile:"<<endl;

            x.afisare_oferta();
            cout<<endl;

            break;
        }
        case 3:
        {
            cout<<"Citeste si afiseaza n obiecte"<<endl;

            cout<<"Introduceti un numar de oferte:";
            cin>>n;

            Agentie_de_turism ag1("Veltravel", n);
            ag1.afisare_agentie();
            cout<<endl<<endl;

            cout<<"Cele "<<ag1.getNrOferte()<<" oferte din agentia "<<ag1.getNume()<<" sunt: "<<endl;
            for(int i=0;i<ag1.getNrOferte();i++)
            {
                cout<<i+1<<": ";
                of[i].citire_oferta();
            }
            for(int i=0;i<ag1.getNrOferte();i++)
            {
                cout<<"Oferta cu numarul "<<i+1<<" este: "<<endl;
                of[i].afisare_oferta();
            }
            break;
        }
        case 4:
        {
            cout<<"Cauta o oferta dupa o anumita destinatie!"<<endl;

            agentii.cauta_oferta("Malta", of, n);
            break;
        }
        case 5:
        {
            cout<<"Adaugarea mai multor oferte cu operatorul +=!";
            agentii+=Oferta("Argentina", 400, 1);
            agentii+=Oferta("Malta", 400, 3);
            cout<<endl;
            cout<<agentii;
            break;
        }
        case 6:
            break;

        default:
            cout<<"Nu ai introdus un numar intre 1 si 6!";
    }
    return 0;
}
