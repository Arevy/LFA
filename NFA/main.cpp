
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int q[100], q0, n, m, p, fin[100], t, j, st[100], w;
char cuv[100];
char l[100];


struct nod
{
    int stare;
    nod *urm;
};

nod *d[105][200], *a, *b;


void parcurgere(int state, int p)
{
    if (cuv[p]!='\0')
       {
           if (d[state][cuv[p]]!=NULL)
            {
                nod *c=d[state][cuv[p]];

                while(c->urm)
                {
                    parcurgere(c->stare, p+1);
                    c=c->urm;

                    if ( c==NULL )
                        return;
                }
                parcurgere(c->stare, p+1);
            }
       }
    else st[++j]=state;
}


int main()
{
    ifstream f("nfa_2.txt");

    ofstream g("NFA.out");

    f>>n;
    for(int i=1; i<=n; i++)
        f>>q[i];

    f>>m;
    for(int i=1; i<=m; i++)
        f>>l[i];

    f>>q0;

    f>>p;

    for(int i=1; i<=p; i++)
        f>>fin[i];

    int x, z;
    char y;

    f>>t;

    for(int i=1; i<=t; i++)
    {
        f>>x>>y>>z;
        if(d[x][y]==NULL)
        {
            d[x][y]=new nod;
            d[x][y]->stare=z;
            d[x][y]->urm=NULL;
        }

        else
        {
            a=new nod;
            a->stare=z;
            a->urm=d[x][y];
            d[x][y]=a;
        }
    }

    f>>w;

    for(int i=1; i<=w; i++)
    {
        f>>cuv;
        j=0;
        parcurgere(q0, 0);

        int sem=0;

        for(int i=1; i<=j; i++)
            for(int k=1; k<=p; k++)
                if(st[i]==fin[k]) sem=1;

        if (sem==1) g<<"DA";
            else g<<"NU";

        g<<endl;
    }

return 0;
}
