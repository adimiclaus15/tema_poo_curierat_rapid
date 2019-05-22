#ifndef VEHICUL_H_INCLUDED
#define VEHICUL_H_INCLUDED

#include "comanda.h"
#include <bits/stdc++.h>
using namespace std;

class Vehicul
{
protected:
    double capacitate;
    bool frigorific;
    int strategie;
    double masa_curenta;
    double viteza;
    bool miscare;
    pair <double,double> pozitie;
    int tip_livrare;
    double timer;
    vector <Comanda> v;
public:
    Vehicul()
    {
        capacitate=0;
        frigorific=0;
        strategie=0;
        masa_curenta=0;
        viteza=0;
        miscare=0;
        pozitie.first=0;
        pozitie.second=0;
        tip_livrare=0;
        timer=0;
    }
    Vehicul(double x,double y,double cap,int tip,double t)
    {
        pozitie.first=x;
        pozitie.second=y;
        capacitate=cap;
        masa_curenta=0;
        tip_livrare=tip;
        timer=t;
    }
    Vehicul(const Vehicul & ob)
    {
        capacitate=ob.capacitate;
        frigorific=ob.frigorific;
        strategie=ob.strategie;
        masa_curenta=ob.masa_curenta;
        viteza=ob.viteza;
        miscare=ob.miscare;
        pozitie=ob.pozitie;
        tip_livrare=ob.tip_livrare;
        timer=ob.timer;
        v=ob.v;
    }
    Vehicul & operator = (const Vehicul &ob)
    {
        if(this!=&ob)
        {
            capacitate=ob.capacitate;
            frigorific=ob.frigorific;
            strategie=ob.strategie;
            masa_curenta=ob.masa_curenta;
            viteza=ob.viteza;
            miscare=ob.miscare;
            pozitie=ob.pozitie;
            tip_livrare=ob.tip_livrare;
            timer=ob.timer;
            v=ob.v;
        }
        return *this;
    }
    double getcapacitate()
    {
        return capacitate;
    }
    double getmasa_curenta()
    {
        return masa_curenta;
    }
    double DistantaManhattan(double,double);
    double DistantaEuclidiana(double,double);
    double Distanta(double,double);
    double Timp(double,double);
    double TimpDeLivrare(Comanda,const double);
    void AdaugaComanda(Comanda);
    void ActualizeazaTimp(double);
};
double Vehicul::DistantaManhattan(double x,double y)
{
    return abs(pozitie.first-x)+abs(pozitie.second-y);
}
double Vehicul::DistantaEuclidiana(double x,double y)
{
    return sqrt((pozitie.first-x)*(pozitie.first-x)+(pozitie.second-y)*(pozitie.second-y));
}
double Vehicul::Distanta(double x,double y)
{
    if(miscare==0)
    {
        return DistantaEuclidiana(x,y);
    }
    else
    {
        return DistantaManhattan(x,y);
    }
}
double Vehicul::Timp(double x,double y)
{
    return Distanta(x,y)/viteza;
}

double Vehicul::TimpDeLivrare(Comanda c,const double tmax)
{

    if(c.masa+masa_curenta>capacitate)
    {
        return tmax+1;
    }
    if(c.rece==1 && frigorific==0)
    {
        return tmax+1;
    }
    Vehicul a=*this;
    double tmp=a.timer;
        if(tip_livrare==0)
        {
            c.masa=666013;
            a.v.push_back(c);
            sort(a.v.begin(),a.v.end());
            while(a.v.size()>0)
            {
                Comanda b=a.v.back();
                //cout<<b.tip<<" ";
                if(b.taken==0)
                {
                    a.timer=a.timer+Timp(b.start.first,b.start.second);
                    a.timer=ceil(a.timer);
                    a.pozitie.first=b.start.first;
                    a.pozitie.second=b.start.second;
                    a.v.back().taken=1;
                    if(c.tip==0)
                    {
                        a.v.back().livrare+=a.timer;
                    }
                }
                else
                {
                    a.timer=a.timer+Timp(b.start.first,b.start.second);
                    a.timer=ceil(a.timer);
                    a.pozitie.first=b.finish.first;
                    a.pozitie.second=b.finish.second;
                    a.v.pop_back();
                    if(c.masa==666013)
                    {
                       tmp=a.timer;
                    }
                    if(b.tip==0 || b.tip==1)
                    {
                        if(a.timer>b.livrare)
                        {
                            return tmax+1;
                        }
                    }
                    if(a.timer>tmax)
                    {
                        return tmax+1;
                    }
                }
            }
            return tmp;
        }
        if(tip_livrare==1)
        {
            c.masa=666013;
            a.v.push_back(c);
            while(a.v.size()>0)
            {
                double minim=1e9;
                int poz=-1,i;
                for(i=0;i<a.v.size();i++)
                {
                    if(a.v[i].taken==1)
                    {
                        if(minim>Distanta(a.v[i].finish.first,a.v[i].finish.second))
                        {
                            poz=i;
                            minim=Distanta(a.v[i].finish.first,a.v[i].finish.second);
                        }
                    }
                    else
                    {
                        if(minim>Distanta(a.v[i].start.first,a.v[i].start.second))
                        {
                            poz=i;
                            minim=Distanta(a.v[i].start.first,a.v[i].start.second);
                        }
                    }
                }
                for(i=poz;i<a.v.size()-1;i++)
                {
                    swap(a.v[i],a.v[i+1]);
                }
                Comanda b=a.v.back();
                if(b.taken==0)
                {
                    a.timer=a.timer+Timp(b.start.first,b.start.second);
                    a.timer=ceil(a.timer);
                    a.pozitie.first=b.start.first;
                    a.pozitie.second=b.start.second;
                    a.v.back().taken=1;
                    if(c.tip==0)
                    {
                        a.v.back().livrare+=a.timer;
                    }
                }
                else
                {
                    a.timer=a.timer+Timp(b.start.first,b.start.second);
                    a.timer=ceil(a.timer);
                    a.pozitie.first=b.finish.first;
                    a.pozitie.second=b.finish.second;
                     a.v.pop_back();
                    if(c.masa==666013)
                    {
                       tmp=a.timer;
                    }
                    if(b.tip==0 || b.tip==1)
                    {
                        if(a.timer>b.livrare)
                        {
                            return tmax+1;
                        }
                    }
                    if(a.timer>tmax)
                    {
                        return tmax+1;
                    }
                }
            }
            return tmp;
        }
        if(tip_livrare==2)
        {
            while(a.v.size()>0)
            {
                Comanda b=a.v.back();
                a.v.pop_back();
                if(b.taken==0)
                {
                    a.timer=a.timer+Timp(b.start.first,b.start.second);
                    a.timer=ceil(a.timer);
                    b.taken=1;
                    a.pozitie=b.start;
                }
                if(b.taken==1)
                {
                    a.timer=a.timer+Timp(b.finish.first,b.finish.second);
                    a.timer=ceil(a.timer);
                    a.pozitie=b.finish;
                }
            }
            a.timer=a.timer+Timp(c.start.first,c.start.second);
            a.timer=ceil(a.timer);
            a.pozitie=c.start;
            a.timer=a.timer+Timp(c.finish.first,c.finish.second);
            a.timer=ceil(a.timer);
            if(c.tip==0 || c.tip==1)
            {
                if(a.timer>c.livrare)
                {
                    return tmax+1;
                }
            }
            if(a.timer>tmax)
            {
                return tmax+1;
            }
            return a.timer;
        }
}

void Vehicul::AdaugaComanda(Comanda c)
{
    masa_curenta=c.masa;
    v.push_back(c);
    double minim=1e9;
    int poz=-1,i;
    if(tip_livrare==0)
    {
        sort(v.begin(),v.end());
    }
    if(tip_livrare==1)
    {
        for(i=0;i<v.size();i++)
        {
            if(v[i].taken==1)
            {
                if(minim>Distanta(c.finish.first,c.finish.second))
                {
                    poz=i;
                    minim=Distanta(c.finish.first,c.finish.second);
                }
            }
            else
            {
                if(minim>Distanta(c.start.first,c.start.second))
                {
                    poz=i;
                    minim=Distanta(c.start.first,c.start.second);
                }
            }
        }
        for(i=poz;i<v.size()-1;i++)
        {
            swap(v[i],v[i+1]);
        }
    }
    if(tip_livrare==2)
    {
        for(i=v.size()-1;i>=1;i--)
        {
            swap(v[i],v[i-1]);
        }
    }
}

void Vehicul::ActualizeazaTimp(double t)
{
    if(v.size()==0)
    {
        timer=t;
        return ;
    }
    if(tip_livrare==0)
    {
        sort(v.begin(),v.end());
        while(v.size()>0)
        {
            Comanda b=v.back();
            double tmp=timer;
            if(b.taken==0)
            {
                tmp=tmp+Timp(b.start.first,b.start.second);
                tmp=ceil(tmp);
                if(tmp<=t)
                {
                    timer=tmp;
                    v.back().taken=1;
                    if(b.tip==0)
                    {
                        v.back().livrare=v.back().livrare+tmp;
                    }
                    cout<<"Comanda cu id-ul "<<b.id<<" a fost preluata la secunda "<<tmp<<"\n";
                }
                else
                {
                    break;
                }
            }
            else
            {
                tmp=tmp+Timp(b.finish.first,b.finish.second);
                tmp=ceil(tmp);
                if(tmp<=t)
                {
                    timer=tmp;
                    v.pop_back();
                    masa_curenta=masa_curenta-b.masa;
                    cout<<"Comanda cu id-ul "<<b.id<<" a fost livrata la secunda "<<tmp<<"\n";
                }
                else
                {
                    break;
                }
            }
        }
    }
    if(tip_livrare==1)
    {
        while(v.size()>0)
        {
            double minim=1e9;
            int poz=-1,i;
            for(i=0;i<v.size();i++)
            {
                if(v[i].taken==1)
                {
                    if(minim>Distanta(v[i].finish.first,v[i].finish.second))
                    {
                        poz=i;
                        minim=Distanta(v[i].finish.first,v[i].finish.second);
                    }
                }
                else
                {
                    if(minim>Distanta(v[i].start.first,v[i].start.second))
                    {
                        poz=i;
                        minim=Distanta(v[i].start.first,v[i].start.second);
                    }
                }
            }
            for(i=poz;i<v.size()-1;i++)
            {
                swap(v[i],v[i+1]);
            }
            Comanda b=v.back();
            double tmp=timer;
            if(b.taken==0)
            {
                tmp=tmp+Timp(b.start.first,b.start.second);
                tmp=ceil(tmp);
                if(tmp<=t)
                {
                    timer=tmp;
                    v.back().taken=1;
                    if(b.tip==0)
                    {
                        v.back().livrare=v.back().livrare+tmp;
                    }
                    cout<<"Comanda cu id-ul "<<b.id<<" a fost preluata la secunda "<<tmp<<"\n";
                }
                else
                {
                    break;
                }
            }
            else
            {
                tmp=tmp+Timp(b.finish.first,b.finish.second);
                tmp=ceil(tmp);
                if(tmp<=t)
                {
                    timer=tmp;
                    v.pop_back();
                    masa_curenta=masa_curenta-b.masa;
                    cout<<"Comanda cu id-ul "<<b.id<<" a fost livrata la secunda "<<tmp<<"\n";
                }
                else
                {
                    break;
                }
            }
        }
    }
    if(tip_livrare==2)
    {
        while(v.size()>0)
        {
            Comanda b=v.back();
            double tmp=timer;
            if(b.taken==0)
            {
                tmp=tmp+Timp(b.start.first,b.start.second);
                tmp=ceil(tmp);
                if(tmp<=t)
                {
                    timer=tmp;
                    v.back().taken=1;
                    if(b.tip==0)
                    {
                        v.back().livrare=v.back().livrare+tmp;
                    }
                    cout<<"Comanda cu id-ul "<<b.id<<" a fost preluata la secunda "<<tmp<<"\n";
                }
                else
                {
                    break;
                }
            }
            else
            {
                tmp=tmp+Timp(b.finish.first,b.finish.second);
                tmp=ceil(tmp);
                if(tmp<=t)
                {
                    timer=tmp;
                    v.pop_back();
                    masa_curenta=masa_curenta-b.masa;
                    cout<<"Comanda cu id-ul "<<b.id<<" a fost livrata la secunda "<<tmp<<"\n";
                }
                else
                {
                    break;
                }
            }
        }
    }
}

class Duba:public Vehicul
{
public:
    Duba():Vehicul()
    {
        viteza=10;
    }
    Duba(double x,double y,double cap,int tip,double t,bool f):Vehicul(x,y,cap,tip,t)
    {
        frigorific=f;
        viteza=10;
        miscare=1;
    }
};

class Masina:public Vehicul
{
public:
    Masina():Vehicul()
    {
        viteza=20;
    }
    Masina(double x,double y,double cap,int tip,double t,bool f):Vehicul(x,y,cap,tip,t)
    {
        frigorific=f;
        viteza=20;
        miscare=1;
    }
};

class Scuter:public Vehicul
{
public:
    Scuter():Vehicul()
    {
        viteza=5;
    }
    Scuter(double x,double y,double cap,int tip,double t,bool f):Vehicul(x,y,cap,tip,t)
    {
        frigorific=f;
        viteza=5;
        miscare=1;
    }
};
#endif // VEHICUL_H_INCLUDED
