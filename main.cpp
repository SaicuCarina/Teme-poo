#include <iostream>
#include <string.h>

using namespace std;

class Oferta
{
    char destinatie[100]; ///pentru locatiile formate din mai multe cuvinte, spatiile vor fi inlocuite cu "_"
    float pret; /// in lei
    int locuridisponibile; ///locuri disponibile, maximul pestru oferta respectiva
public:
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
    Oferta b[1000];
public:
    int cauta_oferta(char destinatie[], int pret, Oferta a[], int n)
    {
        for(int i=0;i<n;i++)
            if(strcmp(destinatie, a[i].getDestinatie())==0 and pret==a[i].getPret())
                return i;
        return -1;
    }

    void setOferte(Oferta a[],int n)
    {
        for(int i=0;i<n;i++)
            b[i]=a[i];
    }


};
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

    Oferta *c=agentie.getB();
    return 0;
}


