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

nod *d[300][300], *ma[300][300];
int coada[300];
int contor=1;

int verificare1 ( int nr )
{
    for (int i=1; i<=contor; i++ )
        if ( coada[i] == nr ) return 1;
    return 0;
}



void eliminared(nod *a, int &sem2)
{
    nod *b, *c;

    while(a->urm)
        {
            b=a;
            while(b->urm->urm)
            {
                int sem=1;
                if(a->stare==b->urm->stare)
                {
                    c=b->urm;
                    b->urm=c->urm;
                    delete c;
                    sem2--;
                    sem=0;

                }

                if (b->urm->urm==NULL) break;

                b=b->urm;

            }

            if(b->urm->stare==a->stare)
            {
                c=b->urm;
                b->urm=NULL;
                delete c;
                sem2--;
            }

            if (a->urm)
                a=a->urm;
        }
}

int verificare2 ( int nr, int k, int maxim )
{
    for ( int i=1; i<=contor; i++ )
        for ( int j=1; j<=m; j++ )
            if ( ma[coada[i]][l[j]] && ma[coada[i]][l[j]]->stare> maxim && ma[coada[i]][l[j]]!=ma[nr][l[k]] )
            {
                nod *a=ma[nr][l[k]], *b, *c;

                b=a->urm;
                c=ma[coada[i]][l[j]]->urm;

                int cont1=0, cont2=0;

                while ( b )
                {
                    cont1++;
                    b=b->urm;
                }

                while ( c )
                {
                    cont2++;
                    c=c->urm;
                }

                if ( cont1==cont2 )
                {

                    int sem=1, sem2, sem3=0;

                    b=a->urm;

                    while ( b )
                    {
                        sem2=0;
                        nod *c=ma[coada[i]][l[j]]->urm;

                        while ( c )
                        {
                            if ( b->stare==c->stare )
                            {
                                sem2=1;
                                break;
                            }
                            c=c->urm;
                        }

                        if ( sem2== 0 )
                            break;

                        b=b->urm;
                    }

                    if ( sem2==0 )
                        sem=0;

                    if ( sem )
                        return ma[coada[i]][l[j]]->stare;
                }
            }
    return 0;
}


int finale[200], nr_f;

void st_finale ( int maxim )
{
    for ( int i=1; i<=contor; i++ )
        for( int j=1; j<=m; j++ )
            if ( ma[coada[i]][l[j]] )
            if ( ma[coada[i]][l[j]]->stare<=maxim )
            {
                int ok=1;
                for(int y=1; y<=nr_f; y++)
                    if (finale[y]==ma[coada[i]][l[j]]->stare) ok=0;
                for ( int k=1; k<=p; k++ )
                    if ( ma[coada[i]][l[j]]->stare==fin[k] && ok ) { finale[++nr_f]=fin[k];   break; }
            }
            else
            {
                int ok=1;
                for(int y=1; y<=nr_f; y++)
                    if (finale[y]==ma[coada[i]][l[j]]->stare) ok=0;
                if (ok)
                {
                nod *b=ma[coada[i]][l[j]]->urm;
                while ( b )
                {
                    int k;
                    for ( k=1; k<=p; k++ )
                        if ( b->stare==fin[k] )
                            { finale[++nr_f]=ma[coada[i]][l[j]]->stare;   break; }
                    if ( k<=p ) break;
                    b=b->urm;
                }
                }
            }
    for(int i=1; i<=p; i++)
        if (q0==fin[i]) finale[++nr_f]=q0;
}


void transformare()
{
    int nr=0, maxim;

    for ( int i=1; i<=n; i++ )
        if ( q[i] > nr ) nr=q[i];

    maxim=nr;

    nr++;

    coada[1]=q0;
    int h=1;

    for ( int i=1; i<=m; i++ )
    {
        if ( d[q0][l[i]]!=NULL )
        {
            ma[q0][l[i]]=new nod;
            ma[q0][l[i]]->urm=NULL;
            ma[q0][l[i]]->stare=d[q0][l[i]]->stare;

            if ( d[q0][l[i]]->urm!=NULL )
            {
                nod *e=d[q0][l[i]]->urm;
                while(e)
                {
                    nod *b=new nod;
                    b->stare=e->stare;
                    b->urm=ma[q0][l[i]];
                    ma[q0][l[i]]=b;
                    e=e->urm;
                }
                nod *b=new nod;
                b->stare=nr;
                b->urm=ma[q0][l[i]];
                ma[q0][l[i]]=b;
                nr++;
            }
        }
    }

    while(h<=contor)
    {
        for ( int i=1; i<=m; i++ )
            if ( ma[coada[h]][l[i]] )
            {
                int nr3=ma[coada[h]][l[i]]->stare;

                if ( verificare1 ( nr3 )==0 )
                {

                coada[++contor]=nr3;

                if(nr3<=maxim)
                {
                    for(int j=1; j<=m; j++)
                    {
                        if(d[nr3][l[j]])
                        {
                            nod *e=d[nr3][l[j]];
                            ma[nr3][l[j]]=new nod;
                            ma[nr3][l[j]]->urm=NULL;
                            ma[nr3][l[j]]->stare=e->stare;

                            if(e->urm)
                            {
                                e=e->urm;

                                while(e)
                                {
                                    nod *b=new nod;
                                    b->stare=e->stare;
                                    b->urm=ma[nr3][l[j]];
                                    ma[nr3][l[j]]=b;
                                    e=e->urm;
                                }

                                nod *b=new nod;
                                b->stare=nr;
                                b->urm=ma[nr3][l[j]];
                                ma[nr3][l[j]]=b;
                                nr++;

                                if ( verificare2( nr3, j, maxim ) )
                                    {ma[nr3][l[j]]->stare=verificare2( nr3, j, maxim ); nr--;}

                            }
                        }
                    }
                }
                else
                {
                    for(int j=1; j<=m; j++)
                    {
                        int sem=0;
                        nod *f=ma[coada[h]][l[i]]->urm;
                        if(d[f->stare][l[j]])
                        {
                            nod *e=d[f->stare][l[j]];
                            ma[nr3][l[j]]=new nod;
                            ma[nr3][l[j]]->urm=NULL;
                            ma[nr3][l[j]]->stare=e->stare;
                            e=e->urm;
                            sem++;

                            while(e)
                            {
                                nod *b=new nod;
                                b->stare=e->stare;
                                b->urm=ma[nr3][l[j]];
                                ma[nr3][l[j]]=b;
                                e=e->urm;
                                sem++;
                            }
                        }

                        f=f->urm;

                        while(f)
                        {
                            if(d[f->stare][l[j]])
                            {
                                nod *e=d[f->stare][l[j]];

                                if(ma[nr3][l[j]]==NULL)
                                {
                                    ma[nr3][l[j]]=new nod;
                                    ma[nr3][l[j]]->urm=NULL;
                                    ma[nr3][l[j]]->stare=e->stare;
                                    e=e->urm;
                                    sem++;
                                }

                                while(e)
                                {
                                    nod *b=new nod;
                                    b->stare=e->stare;
                                    b->urm=ma[nr3][l[j]];
                                    ma[nr3][l[j]]=b;
                                    e=e->urm;
                                    sem++;
                                }
                            }
                            f=f->urm;
                        }
                        if (sem>=2)
                            eliminared(ma[nr3][l[j]], sem);

                        if(sem>=2)
                        {
                            nod *b=new nod;
                            b->stare=nr++;
                            b->urm=ma[nr3][l[j]];
                            ma[nr3][l[j]]=b;

                            if ( verificare2( nr3, j, maxim ) )
                                {ma[nr3][l[j]]->stare=verificare2( nr3, j, maxim ); nr--;}
                        }
                    }
                }
                }
            }
        h++;
    }
    st_finale(maxim);
}

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


                    if(c == NULL)
                    return;
                }
                parcurgere(c->stare, p+1);
            }
       }
    else st[++j]=state;
}


int parcurgere_DFA(int q, int p)
{
    if ( cuv[p]!='\0' )
        {if ( ma[q][cuv[p]] )
            parcurgere_DFA ( ma[q][cuv[p]]->stare, p+1 );}
    else return q;
}


int main()
{
    ifstream f("date.txt");

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

    nod *a, *b;

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
    transformare();

/*
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
            if(d[q[i]][l[j]])
            {
                cout<<q[i]<<" "<<l[j]<<" : ";
                nod *a=d[q[i]][l[j]];
                while(a)
                {
                    cout<<a->stare<<" ";
                    a=a->urm;
                }
                cout<<endl;
            }
    }


    for(int i=1; i<=w; i++)
    {
        f>>cuv;
        j=0;

        parcurgere(q0, 0);

        int sem=0;

        for(int i=1; i<=j; i++)
            for(int k=1; k<=p; k++)
                if(st[i]==fin[k]) sem=1;

        if (sem==1) g<<"DA\t";
            else g<<"NU\t";

        int sta=parcurgere_DFA(q0, 0);

        sem=0;

        for ( int i=1; i<=nr_f; i++ )
            if ( finale[i]==sta )
                {sem=1 ; break; }

        if ( sem ) g<<"DA\t";
            else g<<"NU\t";

        g<<endl;
    }
*/
    int nr_t=0;

    for(int i=1; i<=contor; i++)
       {
           for(int j=1; j<=m; j++)
            if(ma[coada[i]][l[j]]!=NULL)
                {
                    cout<<coada[i]<<l[j]<<":"<<ma[coada[i]][l[j]]->stare<<" ";
                    cout<<endl;
                    nr_t++;
                }
       }


    g<<contor<<endl;
    for ( int i=1; i<=contor; i++)
        g<<coada[i]<<" ";
    g<<endl;

    g<<m<<endl;
    for ( int i=1; i<=m; i++)
        g<<l[i]<<" ";

    g<<endl;

    g<<q0<<endl;

    g<<nr_f<<endl;

    for( int i=1; i<=nr_f; i++)
        g<<finale[i]<<" ";

    g<<endl;

    g<<nr_t<<endl;

    for(int i=1; i<=contor; i++)
       {
           for(int j=1; j<=m; j++)
            if(ma[coada[i]][l[j]]!=NULL)
                {
                    g<<coada[i]<<" "<<l[j]<<" "<<ma[coada[i]][l[j]]->stare;
                    g<<endl;
                }
       }


return 0;
}
