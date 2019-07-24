#include <iostream>

using namespace std;

struct nod{int key;nod *stg;nod *drp;} *root=NULL;

struct nod *predecesor(struct nod *q)
{
    nod *p=q->stg;
    while(p->drp!=NULL)
        p=p->drp;
    return p;
}

void SRD(struct nod *q)
{
   if(q!=NULL)
   {
        SRD(q->stg);
        cout<<q->key<<" ";
        SRD(q->drp);
   }
}

void insert_val(int x)
{
    nod *q=new nod;
    q->key=x;
    q->stg=NULL;
    q->drp=NULL;
    if(root==NULL)
        root=q;
    else
    {
        nod *p=root;
        int k=0;
        while(k==0)
        {
            if(q->key<=p->key)
            {
                if (p->stg==NULL)
                {
                    k=1;
                    p->stg=q;
                }
                else p=p->stg;
            }
            else
            {
                if(p->drp==NULL)
                {
                    k=1;
                    p->drp=q;
                }
                else p=p->drp;
            }
        }
    }
}

bool searchh(int x)
{
    nod *p=root;
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

int maxim()
{
    nod *p=root;
    while(p->drp!=NULL)
        p=p->drp;
    return p->key;
}

struct nod * stergere(int x,struct nod *q)
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
        insert_val(x);
    }
    SRD(root);
    cout<<"Maximul este: "<<maxim()<<endl;
    cout<<"Introduceti valoarea cautata: ";cin>>x;
    if(searchh(x))
        cout<<"Valoarea a fost gasita."<<endl;
    else
        cout<<"Valoarea nu a fost gasita."<<endl;
    cout<<"Introduceti valoarea pe care vreti sa o stergeti: ";
    cin>>x;
    root=stergere(x,root);
    SRD(root);
    return 0;
}
