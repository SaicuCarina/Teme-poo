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
        cout<<"Numele agentiei este: "<<endl;
        cout<<nume<<" si "<<"numarul ofertelor din agentie este: "<<nr_oferte;
    }

    const Oferta *getOferta() const {
        return oferta;
    }

    ~Agentie_de_turism() {} ///destructor

    friend ostream &operator<<(ostream &out, const Agentie_de_turism &agentie);

    friend istream &operator>>(istream &in, Agentie_de_turism &agentie);

    void operator+=(Oferta oferta_)
    {
        nr_oferte++;
        oferta[nr_oferte-1]=oferta_;
    }

    friend class Oferta;

    void citest_agentie()
    {
        char n[25];
        int nr_of;
        Oferta off[100];
        cin>>n>>nr_of;
        strcpy(nume, n);
        nr_oferte=nr_of;

        ///for(int i=0;i<nr_of;i++)
            ///off[i].citeste_oferta();
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


    void sterge_oferta(char destinatie[], float pret, Oferta a[], int &n)
    {
        int ok=0;
        for(int i=0;i<n;i++)
            if(strcmp(destinatie, a[i].getDestinatie())==0 && pret==a[i].getPret())
            {
                ok++;
                for(int j=i+1;j<n;j++)
                    a[j-1]=a[j];
                Oferta a_nou[n-1];
                for(int j=0;j<n-1;j++)
                    a_nou[j]=a[j];
                n=n-1;
               a=a_nou;
            }
        if(ok==0)
            cout<<"Nu exista oferte pentru destinatia si pretul cautata, deci nu a fost nimic sters!";
        else
            cout<<"Ofertele cu destinatia si pretul cerut au fost sterse!";

    }
};

ostream &operator<<(ostream &out, const Agentie_de_turism &agentie)
{
    if(!agentie.nume)
    {
        out<<"Nu a fost initializata!"<<endl;
        return out;
    }
    out<<"Numele agentiei este: "<<agentie.nume<<", iar numarul de oferte din aceasta agentie este: "<<agentie.nr_oferte<<endl;
    for(int i=0;i<agentie.getNrOferte();i++)
    {
        out<<"Destinatia: "<<agentie.getOferta()[i].getDestinatie()<<endl;
        out<<"Pretul: "<<agentie.getOferta()[i].getPret()<<endl;
        out<<"Locuri disponibile: "<<agentie.getOferta()[i].getLocuriDisponibile()<<endl;
        out<<endl;
    }

    return out;
//    out<<"Numele agentiei este: "<<agentie.getNume()<<endl;
//    out<<"Numarul ofertelor este: "<<agentie.getNrOferte()<<endl;
//    for(int i=0;i<agentie.getNrOferte();i++)
//    {
//        cout<<"Destinatia: "<<agentie.getOferta()[i].getDestinatie()<<endl;
//        cout<<"Pretul: "<<agentie.getOferta()[i].getPret()<<endl;
//        cout<<"Locuri disponibile: "<<agentie.getOferta()[i].getLocuriDisponibile()<<endl;
//    }
}

istream &operator>>(istream &in, Agentie_de_turism &agentie)
{
    char buf[100];
    in>>buf;
    agentie.setNume(buf);

    in>>agentie.nr_oferte;

    return in;

//    cout<<endl<<"Numele Agentiei este: ";
//    in>>agentie.getNume();
//    cout<<endl;
//    cout<<"Numarul de oferte din agentie: ";
//    in>>agentie.getNrOferte();
    return in;
}
int main()
{
    Oferta of1; ///constructor de initializare

    Agentie_de_turism ag;

    Oferta of[100];
    int n;

    //Agentie_de_turism agentii;

    bool quit=false;
    do
    {
        cout<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"1.Afisare constructorul de initializare!"<<endl;
        cout<<"2.Afiseaza contructorul de copiere!"<<endl;
        cout<<"3.Citeste si afiseaza n obiecte!"<<endl;
        cout<<"4.Cauta o oferta cu destinatia Malta, din cele n oferte citite la punctul 3!"<<endl;
        cout<<"5.Adaugarea mai multor oferte cu operatorul +=!"<<endl;
        cout<<"6.Stergerea unei oferte dupa destinatie si pret!"<<endl;
        cout<<"7.Supraincarcarea operatorilor >> si <<!"<<endl;
        cout<<endl<<endl;

        int roll;
        cout<<"Introduce un numar de la 1 la 7:";
        cin>>roll;
        switch(roll)
        {
            case 0:
                quit=true;
            case 1:
            {
                cout<<"Constructorul de initializare are vlaorile: "<<endl;

                of1.setDestinatie("Malta");
                of1.setPret(400);
                of1.setLocuridisponibile(3);

                of1.afisare_oferta();
                cout<<endl;

                break;
            }
            case 2:
            {
                Oferta of2(of1); ///constructor de copiere
                cout<<"Constructorul de copiere are vlaorile: "<<endl;

                of2.afisare_oferta();
                cout<<endl;

                break;
            }
            case 3:
            {
                cout<<"Introdu o agentie noua(numele+nr de oferte din acea agentie): ";
                ///Agentie_de_turism ag1("Veltravel", n);
                ag.citest_agentie();
                ag.afisare_agentie();
                cout<<endl<<endl;


                cout<<"Cele "<<ag.getNrOferte()<<" oferte din agentia "<<ag.getNume()<<" sunt: "<<endl;
                for(int i=0;i<ag.getNrOferte();i++)
                {
                    cout<<i+1<<": ";
                    of[i].citire_oferta();
                }
                for(int i=0;i<ag.getNrOferte();i++)
                {
                    cout<<"Oferta cu numarul "<<i+1<<" este: "<<endl;
                    of[i].afisare_oferta();
                }

                break;
            }
            case 4:
            {
                ag.cauta_oferta("Malta", of, ag.getNrOferte());
                break;
            }
            case 5:
            {
                Agentie_de_turism agentii;
                agentii.setNume("TTravel");
                agentii+=Oferta("Argentina", 400, 1);
                agentii+=Oferta("Malta", 400, 3);
                cout<<endl;
                cout<<agentii;
                break;
            }
            case 6:
            {
                int m=ag.getNrOferte();
                ag.sterge_oferta("Malta", 400, of, m);
                ag.setNrOferte(m);
                for(int i=0;i<ag.getNrOferte();i++)
                {
                    cout<<"Oferta cu numarul "<<i+1<<" este: "<<endl;
                    of[i].afisare_oferta();
                }
                break;
            }
            case 7:
            {
                Agentie_de_turism ag1;
                cin>>ag1;
//                Oferta off[100];
//                for(int i=0;i<ag1.getNrOferte();i++)
//                    off->citire_oferta();
                cout<<ag1;
                break;
            }
            default:
            {
                cout<<"Nu ai introdus un numar intre 1 si 7!";
                break;
            }
        }
    }while(!quit);

    return 0;
}
