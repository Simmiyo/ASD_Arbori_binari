#include <iostream>
#include <queue>

using namespace std;

struct nod{int key;nod *stg;nod *drp;} *root=NULL;

void adaugare(int x)
{
    nod *q=new nod;
    q->key=x;
    q->drp=NULL;
    q->stg=NULL;
    if(root==NULL)
        root=q;
    else
    {
        nod *p=root;
        queue <struct nod *> coada;
        coada.push(p);
        int k=0;
        while(k==0)
        {
            if(p->stg==NULL)
                {
                    p->stg=q;
                    k=1;
                }
            else if(p->drp==NULL)
                    {
                        p->drp=q;
                        k=1;
                    }
            else
            {
                coada.push(p->stg);
                coada.push(p->drp);
                coada.pop();
                p=coada.front();
            }
        }
    }
}

void RSD(struct nod *q)
{
    if(q!=NULL)
    {
        cout<<q->key<<" ";
        RSD(q->stg);
        RSD(q->drp);
    }
}

void SDR(struct nod *q)
{
    if(q!=NULL)
    {
        SDR(q->stg);
        SDR(q->drp);
        cout<<q->key<<" ";
    }
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

int main()
{
    int i,x,n;
    cout<<"Introduceti nr de elem ce vor fi adaugate: "; cin>>n;
    cout<<"Introduceti valorile in arbore: ";
    for(i=1;i<=n;i++)
    {
        cin>>x;
        adaugare(x);
    }
    cout<<endl;
    RSD(root);
    cout<<endl;
    SDR(root);
    cout<<endl;
    SRD(root);
    cout<<endl;
    return 0;
}
