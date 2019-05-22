#include <bits/stdc++.h>
//#include "manager.h"
#include "comanda.h"
#include "vehicul.h"
using namespace std;
ifstream f("date.in");
const double zi=86400;
int strategie;
int main()
{
    Vehicul v[3];
    v[0] =  Masina(0, 0, 250, 0, 0,0);
    v[1] =  Duba(50, 50, 1000, 0, 0, 1);
    v[2] =  Scuter(50, 50, 60, 0, 0,0);
    int n,i,j;
    n=3;
    //cout<<v[0].tip_livrare;
    cout<<"Alege o strategie de livrare "<<"\n";
    cin>>strategie;
    for(i=1;i<=n;i++)
    {
        Comanda c;
        f>>c;
       // cout<<c.preluare<<" ";
        for(j=0;j<3;j++)
        {
            v[j].ActualizeazaTimp(c.getpreluare());
        }
        if(strategie==0)
        {
            double minim=zi+1;
            int poz=-1;
            for(j=0;j<3;j++)
            {
                double dist=v[j].Distanta(c.getXstart(),c.getYstart());
                double tmp=v[j].TimpDeLivrare(c,zi);
                //cout<<dist<<" "<<tmp<<"\n";
                if(minim>dist && tmp<=zi)
                {
                    poz=j;
                    minim=dist;
                }
            }
            if(poz!=-1)
            {
                v[poz].AdaugaComanda(c);
            }
            else
            {
                cout<<"Comanda cu id-ul "<<c.getId()<<" "<<"nu poate fi preluata"<<"\n";
            }
        }
        if(strategie==1)
        {
            double minim=zi+1;
            int poz=-1;
            for(j=0;j<3;j++)
            {
                double tmp=v[j].TimpDeLivrare(c,zi);
                if(tmp<minim)
                {
                    minim=tmp;
                    poz=j;
                }
            }
            if(poz!=-1)
            {
                v[poz].AdaugaComanda(c);

            }
            else
            {
                cout<<"Comanda cu id-ul "<<c.getId()<<" "<<"nu poate fi preluata"<<"\n";
            }
        }
        if(strategie==2)
        {
            double maxim=0;
            int poz=-1;
            for(j=0;j<3;j++)
            {
                double d=v[j].getcapacitate()-v[j].getmasa_curenta();
                double tmp=v[j].TimpDeLivrare(c,zi);
                if(d>maxim && tmp<=zi)
                {
                    poz=j;
                    maxim=d;
                }
            }
            if(poz!=-1)
            {
                v[poz].AdaugaComanda(c);

            }
            else
            {
                cout<<"Comanda cu id-ul "<<c.getId()<<" "<<"nu poate fi preluata"<<"\n";
            }
        }
    }
    for(j=0;j<3;j++)
    {
        v[j].ActualizeazaTimp(zi);
    }
    return 0;
}
