#include <iostream>
#include <cstring>

using namespace std;

class Oferta
{
    char destinatie[100]; ///pentru locatiile formate din mai multe cuvinte, spatiile vor fi inlocuite cu "_"
    float pret; /// in euro
    int locuridisponibile; ///locuri disponibile, maximul pestru oferta respectiva
public:

    Oferta(){}; ///pt a putea initializa obiecte de tip oferta

    Oferta(char *destinatie_, float pret_, int locuridisponibile_) ///constructor de initializare
    {
        strcpy(destinatie, destinatie_);
        pret = pret_;
        locuridisponibile = locuridisponibile_;
    }

    Oferta(const Oferta *oferta) ///constructor de copiere
    {
        strcpy(destinatie, oferta->destinatie);
        pret=oferta->pret;
        locuridisponibile=oferta->locuridisponibile;
    };

    const char *getDestinatie() const
    {
        return destinatie;
    }

    void setDestinatie(char destinatie_[])
    {
        strcpy(Oferta::destinatie, destinatie_);
    }

    float getPret() const
    {
        return pret;
    }

    void setPret(float pret_)
    {
        Oferta::pret = pret_;
    }

    int getLocuriDisponibile() const
    {
        return locuridisponibile;
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

    virtual ~Oferta(){} ///destructor, se apeleaza odata cu destructorul de la agentie de turism

};

class Agentie_de_turism
{
    char nume[25];
    int nr_oferte=0;
    Oferta **oferta=new Oferta*[20];
public:

    Agentie_de_turism(){}; ///pt a putea initializa obiecte de tip Agentie_de_turism

    Agentie_de_turism(char *nume_, int nr_oferte_) ///constructor de initializare
    {
        strcpy(nume, nume_);
        nr_oferte=nr_oferte_;
    }

    Agentie_de_turism(const Agentie_de_turism &agentie) ///constructor de copiere
    {
        strcpy(nume, agentie.nume);
        nr_oferte=agentie.nr_oferte;
    }

    const char *getNume() const {
        return nume;
    }

    void setNume(char nume_[25])
    {
        strcpy(nume, nume_);
    }

    int getNrOferte() const {
        return nr_oferte;
    }

    void setNrOferte(int nrOferte) {
        nr_oferte = nrOferte;
    }

    void afisare_agentie()
    {
        cout<<"Numele agentiei este: "<<nume<<endl;
        cout<<"Numarul ofertelor din agentie este: "<<nr_oferte;
    }

    Oferta **getOferta() const;

    void setOferta(Oferta **oferta);

    friend ostream &operator<<(ostream &out, const Agentie_de_turism &agentie);

    friend istream &operator>>(istream &in, Agentie_de_turism &agentie);

    friend class Oferta;

    Agentie_de_turism operator+=(Oferta *oferta_)
    {
        nr_oferte++;
        Oferta *off=new Oferta(oferta_);
        oferta[nr_oferte-1]=off;

        return *this;
    }

    void citest_agentie()
    {
        char n[25];
        int nr_of;
        cin>>n>>nr_of;
        strcpy(nume, n);
        nr_oferte=nr_of;
    }
    void cauta_oferta(char destinatie[], Oferta a[], int n)
    {
        cout<<"Destinatia cautata este: "<<destinatie<<endl;
        int ok=0;
        for(int i=0;i<n;i++)
            if(strcmp(destinatie, a[i].getDestinatie())==0)
            {
                ok++;
                cout<<"Optiunea cu numarul "<<ok<<" este: "<<endl;
                cout<<"Pretul pentru destinatia cautata este: "<<a[i].getPret()<<" euro "<<endl;
                cout<<"Locurile disponibile pentru locatia cautata sunt:"<<a[i].getLocuriDisponibile()<<endl<<endl;
            }
        if(ok==0)
            cout<<"Nu exista oferte pentru destinatia cautata!"<<endl;
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
            cout<<"Nu exista oferte pentru destinatia si pretul cautata, deci nu a fost nimic sters!"<<endl;
        else
        {
            cout<<"Ofertele cu destinatia si pretul cerut au fost sterse!"<<endl;
        }

    }

    Agentie_de_turism& operator=(const Agentie_de_turism &rhs) {

        cout<<"Apel operator=\n";

        if(this!=&rhs) // in op= sau in setName ar trebui sa existe acest check
            strcpy(this->nume,rhs.nume);

        this->nr_oferte = rhs.nr_oferte;

        return *this;
    }

    ~Agentie_de_turism()
    {
        delete[] oferta; ///destructor
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
        out<<"Destinatia: "<<agentie.getOferta()[i]->getDestinatie()<<endl;
        out<<"Pretul: "<<agentie.getOferta()[i]->getPret()<<endl;
        out<<"Locuri disponibile: "<<agentie.getOferta()[i]->getLocuriDisponibile()<<endl;
        out<<endl;
    }

    return out;
}

istream &operator>>(istream &in, Agentie_de_turism &agentie)
{
    char buf[25];
    in>>buf;
    agentie.setNume(buf);

    return in;
}

Oferta **Agentie_de_turism::getOferta() const
{
    return oferta;
}

void Agentie_de_turism::setOferta(Oferta **oferta)
{
    Agentie_de_turism::oferta=oferta;
}

int main()
{
    Oferta of1; ///contructor de initializare

    Agentie_de_turism ag;

    Oferta* of=new Oferta[100];

    int n;

    bool quit=false;
    do
    {
        cout<<endl;

        cout<<"0.Exit"<<endl;
        cout<<"1.Afisarea constructorul de initializare!"<<endl;
        cout<<"2.Afisarea contructorul de copiere!"<<endl;
        cout<<"3.Afisarea operatorului de atribuire =!"<<endl;
        cout<<"4.Citirea si afisarea n obiecte!"<<endl;
        cout<<"5.Cautarea ofertelor cu o anumita destinatie, din cele n oferte citite la punctul 3!"<<endl;
        cout<<"6.Adaugarea mai multor oferte cu operatorul +=!"<<endl;
        cout<<"7.Stergerea ofertelor cu destinatia Malta si pretul de 400 euro!"<<endl;
        cout<<"8.Supraincarcarea operatorilor >> si <<!"<<endl;
        cout<<"9.Adaugarea unei oferte in vectorul de oferte deja existente"<<endl;

        cout<<endl<<endl;

        int roll;
        cout<<"Introduce un numar de la 1 la 10:";
        cout<<endl;
        cin>>roll;
        switch(roll)
        {
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
                Agentie_de_turism ag4("Ftravel", 4); // Apel constructor

                ag4.afisare_agentie();
                cout<<endl;

                Agentie_de_turism agg4;

                agg4=ag4;

                agg4.afisare_agentie();


                break;
            }
            case 4:
            {
                cout<<"Introduceti o agentie noua(numele+nr de oferte din acea agentie): ";  ///Agentie_de_turism ag1("Veltravel", n);

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
            case 5:
            {
                char destinatie_cautata[100];

                cout<<"Introduceti ce destinatie cautati: ";
                cin>>destinatie_cautata;
                cout<<endl;

                ag.cauta_oferta(destinatie_cautata, of, ag.getNrOferte());

                break;
            }
            case 6:
            {
                Agentie_de_turism agentii;

                agentii.setNume("TTravel");

                agentii+=new Oferta("Argentina", 400, 1);
                agentii+=new Oferta("Malta", 400, 3);

                cout<<endl;
                cout<<agentii;

                break;
            }
            case 7:
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
            case 8:
            {
                Agentie_de_turism ag1;

                cout<<"Introduceti un nume de agentie: "<<endl;
                cin>>ag1;

                ag1+=new Oferta("Argentina", 400, 1);
                ag1+=new Oferta("Malta", 400, 3);
                ag1+=new Oferta("Ungaria", 500, 2);

                cout<<ag1;
                break;
            }
            case 9:
            {
                ///adaugarea unei oferte in vectorul de oferte deja existente
                Oferta oferta_de_adaugat;

                ag.setNrOferte(ag.getNrOferte()+1);
                cout<<ag.getNrOferte()<<endl;

                int p=ag.getNrOferte();

                of[p-1].setDestinatie("Franta");
                of[p-1].setPret(800);
                of[p-1].setLocuridisponibile(1);


                for(int i=0;i<ag.getNrOferte();i++)
                {
                    cout<<"Oferta cu numarul "<<i+1<<" este: "<<endl;
                    of[i].afisare_oferta();
                }

                break;
            }
            default:
            {
                cout<<"Nu ai introdus un numar intre 1 si 9!";
                break;
            }
            case 0:
                quit=true;
        }
    }while(!quit);

    delete[] of;

    return 0;
}