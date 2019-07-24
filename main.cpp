#include <iostream>

using namespace std;

struct nod{int key;nod *stg;nod *drp;int h;} *root=NULL;

int max_int(int a,int b)
{
    if(a>b) return a;
    return b;
}

int inaltime(nod *q)
{
    if(q==NULL) return 0;
    return q->h;
}

struct nod *nod_nou(int x)
{
    nod *q=new nod;
    q->key=x;
    q->stg=NULL;
    q->drp=NULL;
    q->h=1;
    return q;
}

int verif_echil(nod *q)
{
    if(q==NULL) return 0;
    return inaltime(q->stg)-inaltime(q->drp);
}

struct nod *rotire_stg(nod *y)
{
    nod *x=y->drp,*z=x->stg;
    x->stg=y;
    y->drp=z;
    y->h=max_int(inaltime(y->stg),inaltime(y->drp))+1;
    x->h=max_int(inaltime(x->stg),inaltime(x->drp))+1;
    return x;
}

struct nod *rotire_drp(nod *y)
{
    nod *x=y->stg,*z=x->drp;
    x->drp=y;
    y->stg=z;
    y->h=max_int(inaltime(y->stg),inaltime(y->drp))+1;
    x->h=max_int(inaltime(x->stg),inaltime(x->drp))+1;
    return x;
}

struct nod *adaugare(int x,nod *q)
{
    if(q==NULL) return nod_nou(x);
    if(x<q->key) q->stg=adaugare(x,q->stg);
    else if(x>q->key) q->drp=adaugare(x,q->drp);
        else return q;
    q->h=max_int(inaltime(q->stg),inaltime(q->drp))+1;
    int d=verif_echil(q);
    if(d>1 && x<q->stg->key) return rotire_drp(q);
    else if(d<-1 && x>q->drp->key) return rotire_stg(q);
    else if(d>1 && x>q->stg->key)
    {
        q->stg=rotire_stg(q->stg);
        return rotire_drp(q);
    }
    else if(d<-1 && x<q->drp->key)
    {
        q->drp=rotire_drp(q->drp);
        return rotire_stg(q);
    }
    return q;
}

void afis1(nod *q)
{
    if(q!=NULL)
    {
        afis1(q->stg);
        cout<<q->key<<" ";
        afis1(q->drp);
    }
}

void afis2(nod *q)
{
    if(q!=NULL)
    {
        cout<<q->key<<" ";
        afis2(q->stg);
        afis2(q->drp);
    }
}

int maxim()
{
    nod *p=root;
    while(p->drp!=NULL)
        p=p->drp;
    return p->key;
}

bool searchh(nod *q,int x)
{
    nod *p=q;
    while(p!=NULL)
    {
        if(x<p->key)
            p=p->stg;
        else if(x>p->key)
                p=p->drp;
             else return 1;
    }
    return 0;
}

struct nod *predecesor(struct nod *q)
{
    nod *p=q->stg;
    while(p->drp!=NULL)
        p=p->drp;
    return p;
}

struct nod *stergere(int x,nod *q)
{
    if(q==NULL) return q;
    if(x<q->key) q->stg=stergere(x,q->stg);
    else if(x>q->key) q->drp=stergere(x,q->drp);
    else
    {
        nod *t;
        if(q->stg==NULL && q->drp==NULL)
        {
            t=q;
            q=NULL;
            delete t;
        }
        else if(q->stg==NULL)
        {
            t=q->drp;
            *q=*t;
            delete t;
        }
        else if(q->drp==NULL)
        {
            t=q->stg;
            *q=*t;
            delete t;
        }
        else
        {
            t=predecesor(q);
            q->key=t->key;
            q->stg=stergere(t->key,q->stg);
        }
    }
    if(q==NULL) return q;
    q->h=max_int(inaltime(q->stg),inaltime(q->drp))+1;
    int d=verif_echil(q);
    if(d>1 && verif_echil(q->stg)<=0)
        return rotire_drp(q);
    else if(d<-1 && verif_echil(q->drp)>=0)
        return rotire_stg(q);
    else if(d>1 && verif_echil(q->stg)>0)
    {
        q->stg=rotire_stg(q->stg);
        return rotire_drp(q);
    }
    else if(d<-1 && verif_echil(q->drp)<0)
    {
        q->drp=rotire_drp(q->drp);
        return rotire_stg(q);
    }
    return q;
}

int main()
{
    int n,x,i;
    cout<<"Introduceti nr elem arbore: ";cin>>n;
    cout<<"Introduceti elementele arborelui: ";
    for(i=1;i<=n;i++)
    {
        cin>>x;
        root=adaugare(x,root);
    }
    afis1(root);
    cout<<endl;
    afis2(root);
    cout<<endl;
    cout<<"Introduceti valoarea pe care vreti sa o stergeti: ";
    cin>>x;
    root=stergere(x,root);
    afis1(root);
    cout<<endl;
    afis2(root);
    return 0;
}
