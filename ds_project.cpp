#include<iostream>
#include<fstream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<iomanip>
#include<stack>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include"GetStations.h"
#define Degree 3

using namespace std;

template <typename T>
class heapNode
{
public:
    T d;
    int sno;
    heapNode *p,*l,*r;
    heapNode(T x,int xy,heapNode *y=NULL)
    {
        d=x;
        sno=xy;
        p=y;
        l=r=NULL;
    }
};
template <typename U>
class minheap
{
    heapNode <U>*r;
    int s;
public:
    minheap()
    {
        r==NULL;
        s=0;
    }
    void inserth(U x,int y)
    {
        int f=0,e=0;
        bool b;
        if(s==0)
        {
            r=new heapNode<U>(x,y,NULL);
            s++;
        }
        else
        {
            heapNode <U>*a[s];
            a[0]=r;
            while(f<=e)
            {
                if(a[f]->l)
                    {
                        a[2*f+1]=a[f]->l;
                        e=2*f+1;
                    }
                else
                    {
                        b=0;
                        break;
                    }
                if(a[f]->r)
                    {
                        a[2*f+2]=a[f]->r;
                        e=1*f+2;
                    }
                else
                    {
                        b=1;
                        break;
                    }
                f++;
            }
            if(!b)
            {
                a[f]->l=new heapNode<U>(x,y,a[f]);
                s++;
                heapify_up(a[f]->l);
            }
            else
            {
                a[f]->r=new heapNode<U>(x,y,a[f]);
                s++;
                heapify_up(a[f]->r);
            }
        }
    }
    int deleteh()
    {
        int v;
        heapNode <U>*n;
        if(s==1)
        {
            n=r;
            v=r->sno;
            s--;
            r=NULL;
            delete n;
            return v;
        }
            int f=0,e=0;
            bool b;
            heapNode <U>*a[s];
            a[0]=r;
            v=a[0]->sno;
            while(f<=e)
            {
                if(a[f]->l)
                    {
                        a[2*f+1]=a[f]->l;
                        e=2*f+1;
                    }
                if(a[f]->r)
                    {
                        a[2*f+2]=a[f]->r;
                        e=2*f+2;
                    }
                f++;
            }
            f--;
            a[0]->d=a[f]->d;
           if(f%2==1)
                {
                    n=a[f]->p->l;
                    a[f]->p->l=NULL;
                    delete n;
                }
            else
                {
                    n=a[f]->p->r;
                    a[f]->p->r=NULL;
                    delete n;
                }
            s--;
            heapify_down(r);
            return v;
    }
    void heapify_up(heapNode<U> *n)
    {
        if(n->p==NULL || n->p->d < n->d)
            return;
        else
        {
            U x;
            int y;
            x=n->p->d;
            y=n->p->sno;
            n->p->d=n->d;
            n->p->sno=n->sno;
            n->d=x;
            n->sno=y;
            heapify_up(n->p);
        }
    }
    void heapify_down(heapNode<U> *n)
    {
        if((n->l==NULL && n->r==NULL))
            return;
        else if(n->l!=NULL  &&  n->l->d < n->d && n->r!=NULL && n->l->d < n->r->d)
        {
            U x;
            int y;
            x=n->l->d;
            y=n->l->sno;
            n->l->d=n->d;
            n->l->sno=n->sno;
            n->d=x;
            n->sno=y;
            heapify_down(n->l);
        }
        else if(n->r!=NULL && n->r->d < n->d)
        {
            U x;
            int y;
            x=n->r->d;
            y=n->r->sno;
            n->r->d=n->d;
            n->r->sno=n->sno;
            n->d=x;
            n->sno=y;
            heapify_down(n->r);
        }
    }
    heapNode<U> *getroot()
    {
        return r;
    }
    int getrootdata()
    {
        return r->sno;
    }
    void inorder(heapNode<U> *n)
    {
        if(n==NULL)
            return;
        inorder(n->l);
        cout<<n->d<<"   "<<n->sno<<endl;
        inorder(n->r);
    }
};
template <typename S>
class maxheap
{
    heapNode <S>*r;
    int s;
public:
    maxheap()
    {
        r==NULL;
        s=0;
    }
    void inserth(S x,int y)
    {
        int f=0,e=0;
        bool b;
        if(s==0)
        {
            r=new heapNode<S>(x,y,NULL);
            s++;
        }
        else
        {
            heapNode <S>*a[s];
            a[0]=r;
            while(f<=e)
            {
                if(a[f]->l)
                    {
                        a[2*f+1]=a[f]->l;
                        e=2*f+1;
                    }
                else
                    {
                        b=0;
                        break;
                    }
                if(a[f]->r)
                    {
                        a[2*f+2]=a[f]->r;
                        e=1*f+2;
                    }
                else
                    {
                        b=1;
                        break;
                    }
                f++;
            }
            if(!b)
            {
                a[f]->l=new heapNode<S>(x,y,a[f]);
                s++;
                heapify_up(a[f]->l);
            }
            else
            {
                a[f]->r=new heapNode<S>(x,y,a[f]);
                s++;
                heapify_up(a[f]->r);
            }
        }
    }
    int deleteh()
    {
        int v;
        heapNode <S>*n;
        if(s==1)
        {
            n=r;
            v=r->sno;
            s--;
            r=NULL;
            delete n;
            return v;
        }
            int f=0,e=0;
            bool b;
            heapNode <S>*a[s];
            a[0]=r;
            v=a[0]->sno;
            while(f<=e)
            {
                if(a[f]->l)
                    {
                        a[2*f+1]=a[f]->l;
                        e=2*f+1;
                    }
                if(a[f]->r)
                    {
                        a[2*f+2]=a[f]->r;
                        e=2*f+2;
                    }
                f++;
            }
            f--;
            a[0]->d=a[f]->d;
           if(f%2==1)
                {
                    n=a[f]->p->l;
                    a[f]->p->l=NULL;
                    delete n;
                }
            else
                {
                    n=a[f]->p->r;
                    a[f]->p->r=NULL;
                    delete n;
                }
            s--;
            heapify_down(r);
            return v;
    }
    void heapify_up(heapNode<S> *n)
    {
        if(n->p==NULL || n->p->d > n->d)
            return;
        else
        {
            S x;
            int y;
            x=n->p->d;
            y=n->p->sno;
            n->p->d=n->d;
            n->p->sno=n->sno;
            n->d=x;
            n->sno=y;
            heapify_up(n->p);
        }
    }
    void heapify_down(heapNode<S> *n)
    {
        if((n->l==NULL && n->r==NULL))
            return;
        else if(n->l!=NULL  &&  n->l->d > n->d && n->r!=NULL && n->l->d > n->r->d)
        {
            S x;
            int y;
            x=n->l->d;
            y=n->l->sno;
            n->l->d=n->d;
            n->l->sno=n->sno;
            n->d=x;
            n->sno=y;
            heapify_down(n->l);
        }
        else if(n->r!=NULL && n->r->d > n->d)
        {
            S x;
            int y;
            x=n->r->d;
            y=n->r->sno;
            n->r->d=n->d;
            n->r->sno=n->sno;
            n->d=x;
            n->sno=y;
            heapify_down(n->r);
        }
    }
    heapNode<S> *getroot()
    {
        return r;
    }
    int getrootdata()
    {
        return r->sno;
    }
    void inorder(heapNode<S> *n)
    {
        if(n==NULL)
            return;
        inorder(n->l);
        cout<<n->d<<"   "<<n->sno<<endl;
        inorder(n->r);
    }
};


struct avl_node
{
    double data;
    string s_name;
    int s_no;
    struct avl_node *left;
    struct avl_node *right;
};

class avlTree
{
    public:
        avl_node **arr;
        int Size;
        int height(avl_node *);
        int diff(avl_node *);
        avl_node *rr_rotation(avl_node *);
        avl_node *ll_rotation(avl_node *);
        avl_node *lr_rotation(avl_node *);
        avl_node *rl_rotation(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert_av(avl_node *, double ,string,int);
        void display(avl_node *, int);
        void inorder(avl_node *);
        void range(double start,double endi,avl_node*,int pres);
        void inorderIterative(avl_node*);
        avlTree()
        {
            Size=0;
        }
};

class state
{
    public:
    int sno;
    string name;
    string capital;
    int population;
    float growth;
    int area;
    int density;
    int sex_ratio;
    float literacy;
    string maj_rel;
    float hindu;
    float muslim;
    float christ;
    float sikh;
    float budh;
    float jain;
    float others;
    float atheist;
    void out()
    {
        cout<<"State Number\t\t\t | "<<sno<<endl;
        cout<<"Name of State\t\t\t | "<<name<<endl;
        cout<<"Capital of State\t\t | "<<capital<<endl;
        cout<<"Population of State\t\t | "<<population<<endl;
        cout<<"Growth of State\t\t\t | "<<growth<<endl;
        cout<<"Area of State\t\t\t | "<<area<<endl;
        cout<<"Density of State\t\t | "<<density<<endl;
        cout<<"Sex Ratio of State\t\t | "<<sex_ratio<<endl;
        cout<<"Literacy of State\t\t | "<<literacy<<endl;
        cout<<"Majority Religion of State\t | "<<maj_rel<<endl;
        cout<<"Hindu Percentage of State\t | "<<hindu<<endl;
        cout<<"Muslim Percentage of State\t | "<<muslim<<endl;
        cout<<"Christian Percentage of State\t | "<<christ<<endl;
        cout<<"Sikh Percentage of State\t | "<<sikh<<endl;
        cout<<"Budh Percentage of State\t | "<<budh<<endl;
        cout<<"Jain Percentage of State\t | "<<jain<<endl;
        cout<<"Others Percentage of State\t | "<<others<<endl;
        cout<<"Atheist Percentage of State\t | "<<atheist<<endl;
    }

};
class BTreeNode
{
public:
    state *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;
    BTreeNode(int _t, bool _leaf);
    void insertTreeNonFull(state k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    void stateNames();
    state *searchTree(int k);
    void stateCapitals();
    friend class BTree;
    void traverse_and_put(avl_node*&,avlTree&);
    void traverse_and_put_area(avl_node*&rt,avlTree &av_tree);
    void traverse_and_put_literacy(avl_node*&rt,avlTree &av_tree);
};

class BTree
{
public:
    BTreeNode *root;
    int t;
    BTree(int x)
    {
        root = NULL;
        t = x;
    }

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    void stateNames()
    {
        if (root != NULL)
            root->stateNames();
    }

    state* searchTree(int k)
    {
        return (root == NULL)? NULL : root->searchTree(k);
    }
    void traverse_and_put(avl_node*&rt,avlTree &av_tree)
    {
        root->traverse_and_put(rt,av_tree);
    }
    void traverse_and_put_area(avl_node*&rt,avlTree &av_tree)
    {
        root->traverse_and_put_area(rt,av_tree);
    }

    void traverse_and_put_literacy(avl_node*&rt,avlTree &av_tree)
    {
        root->traverse_and_put_literacy(rt,av_tree);
    }
    void stateCapitals()
    {
        if (root != NULL)
            root->stateCapitals();
    }
    void insertTree(state k);
};

class vertex;

class adj
{
public:
    adj*next;
    vertex*ptr;
    double wt;
    adj(vertex*x,double w)
    {
        next=NULL;
        ptr=x;
        wt=w;
    }
};

class vertex
{
public:
    vertex*down;
    int key;
    string airport_name;
    string city;
    string state;
    string type;
    adj*head;
    bool visited;
    vertex(int al,string an,string c,string st,string tp)
    {
        key=al;
        head=NULL;
        down=NULL;
        visited=false;
        airport_name=an;
        type=tp;
        city=c;
        state=st;
    }

};
int tot_airports;
void add_to_adj(vertex*t1,vertex*t2,double w)
{
    if(t1->head==NULL)
    {
        t1->head=new adj(t2,w);
    }
    else
    {
        adj*temp=t1->head;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=new adj(t2,w);
    }
}

void add_node(vertex*f,int c1,int c2,double w)
{
    vertex*temp=f;
    vertex*t1,*t2;
    t1=NULL;
    t2=NULL;
    adj*temp2;
    while(temp!=NULL)
    {
        if(temp->key==c1)
            t1=temp;
        if(temp->key==c2)
            t2=temp;
        temp=temp->down;
    }
    add_to_adj(t1,t2,w);
    //add_to_adj(t2,t1);directed
}

void vis_reset(vertex*f)
{
    while(f!=NULL)
    {
        f->visited=false;
        f=f->down;
    }
}

void bft(vertex*f)
{
    vertex*q[tot_airports];
    int fr=0,bk=1;
    q[0]=f;
    f->visited=true;
    while(fr!=bk)
    {
        cout<<q[fr]->key<<"  "<<q[fr]->airport_name<<" "<<q[fr]->city<<endl;
        adj*temp=q[fr]->head;
        fr++;
        while(temp!=NULL)
        {
            if(!(temp->ptr->visited))
            {
                q[bk++]=temp->ptr;
                temp->ptr->visited=true;
            }
            temp=temp->next;
        }
    }
    cout<<endl<<endl;
    vis_reset(f);
}

void show_all_airports(vertex*t)
{
    string s1,s2,s3,s4;
    while(t!=NULL)
    {
        cout<<setw(2)<<setfill(' ')<<t->key<<" ";
        s1=t->state;
        s2=t->airport_name;
        s3=t->city;
        s4=t->type;
        s1.resize(26,' ');
        s2.resize(50,' ');
        s3.resize(15,' ');
        s4.resize(15,' ');
        cout<<s2<<" "<<s3<<" "<<s1;
        if(t->head==NULL)
            cout<<"NO CONNECTIVITY ";
        cout<<endl;
        t=t->down;
    }
}

double time_dif(int a,int b)
{
    int bm,am,ah,bh;
    double dm,dh;
    bm=b%100;
    am=a%100;
    bh=b/100;
    ah=a/100;
    dm=(bm-am);
    dh=(bh-ah);
    if(dm<0)
    {
        dm=60-dm;
        dh=dh-1;
    }
    if(dh<0)
    {
        dh=24-dh;
    }
    double diff;
    diff=dh+dm/60;
    return diff;
}

void shortest_path(vertex*strt,vertex*fr,vertex*to)
{
    double dist[tot_airports+1];
    bool vis[tot_airports+1];
    string path[tot_airports+1];
    for(int i=1;i<=tot_airports;i++)
    {
        vis[i]=false;
        dist[i]=-1;
        path[i]=fr->airport_name;
    }
    vertex*temp=fr;
    double d_from_src=0;
    int tot=tot_airports;
    adj*temp2;
    while(tot--)
    {
        temp2=temp->head;
        vis[temp->key]=true;
        while(temp2!=NULL)
        {
            if((dist[temp2->ptr->key]==-1)||(dist[temp2->ptr->key]>(d_from_src+temp2->wt)))
            {
                dist[temp2->ptr->key]=d_from_src+temp2->wt;
                path[temp2->ptr->key]=path[temp->key]+" -> "+temp2->ptr->airport_name;
            }
            if(temp2->ptr==to)
            {
                cout<<"\n\nThe total time taken is :"<<dist[temp2->ptr->key]<<endl;
                cout<<"The path is :\n"<<path[temp2->ptr->key]<<endl<<endl;
                return;
            }
            temp2=temp2->next;
        }

        bool first=true;
        double s_dist;
        int s_j=1;
        for(int j=1;j<=tot_airports;j++)
        {
            if(dist[j]==-1||vis[j])
                continue;
            if(first)
            {
                first=false;
                s_dist=dist[j];
                s_j=j;
                continue;
            }
            if(dist[j]<s_dist)
            {
                s_j=j;
                s_dist=dist[j];
            }
        }
        vertex*temp3=strt;
        int s_j2=s_j;
        while(temp3!=NULL)
        {
            if(temp3->key==s_j2)
                break;
            temp3=temp3->down;
        }
        temp=temp3;
        d_from_src=dist[s_j2];
    }
}

void route(vertex * f,int a1,int a2)
{
    vertex *fr,*to;
    vertex* f2=f;
    while(f!=NULL)
    {
        if(f->key==a1)
            fr=f;
        if(f->key==a2)
            to=f;
        f=f->down;
    }
    shortest_path(f2,fr,to);
}



int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}


int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}


avl_node *avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}


avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}

avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}


avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}


avl_node *avlTree::insert_av(avl_node *root, double value,string sname,int sno)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        root->s_name=sname;
        root->s_no=sno;
        Size++;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert_av(root->left, value,sname,sno);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insert_av(root->right, value,sname,sno);
        root = balance (root);
    }
    return root;
}



BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    keys = new state[2*t-1];
    C = new BTreeNode *[2*t];
    n = 0;
}

void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
        keys[i].out();
        cout<<endl;
    }
    if (leaf == false)
        C[i]->traverse();

}

void BTreeNode::stateNames()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->stateNames();
        cout<<keys[i].sno<<"\t"<<keys[i].name;
        cout<<endl;
    }
    if (leaf == false)
        C[i]->stateNames();

}

void BTreeNode::stateCapitals()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->stateCapitals();
        string xy=keys[i].name;
        xy.resize(30,' ');
        cout<<setw(2)<<setfill('0')<<keys[i].sno<<"\t"<<xy<<"\t"<<keys[i].capital;
        cout<<endl;
    }
    if (leaf == false)
        C[i]->stateCapitals();

}

state *BTreeNode::searchTree(int k)
{
    int i = 0;
    while (i < n && k > keys[i].sno)
        i++;
    if (keys[i].sno == k)
        return this->keys+i;
    if (leaf == true)
        return NULL;
    return C[i]->searchTree(k);
}

void BTree::insertTree(state k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2*t-1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0].sno < k.sno)
                i++;
            s->C[i]->insertTreeNonFull(k);
            root = s;
        }
        else
            root->insertTreeNonFull(k);
    }
}

void BTreeNode::insertTreeNonFull(state k)
{
    int i = n-1;
    if (leaf == true)
    {
        while (i >= 0 && keys[i].sno > k.sno)
        {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1]=k;
        n = n+1;
    }
    else
    {
        while (i >= 0 && keys[i].sno > k.sno)
            i--;
        if (C[i+1]->n == 2*t-1)
        {
            splitChild(i+1, C[i+1]);
            if (keys[i+1].sno < k.sno)
                i++;
        }
        C[i+1]->insertTreeNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
    y->n = t - 1;
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
    C[i+1] = z;
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];
    n = n + 1;
}

void BTreeNode::traverse_and_put(avl_node*&rt,avlTree &av_tree)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse_and_put(rt,av_tree);
        rt=av_tree.insert_av(rt,keys[i].population,keys[i].name,keys[i].sno);
    }
    if (leaf == false)
        C[i]->traverse_and_put(rt,av_tree);
}

avl_node* take_from_btree(BTree bt,avl_node *rt,avlTree &av_tree)
{
    bt.traverse_and_put(rt,av_tree);
    return rt;
}

void BTreeNode::traverse_and_put_area(avl_node*&rt,avlTree &av_tree)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse_and_put_area(rt,av_tree);
        rt=av_tree.insert_av(rt,keys[i].area,keys[i].name,keys[i].sno);
    }
    if (leaf == false)
        C[i]->traverse_and_put_area(rt,av_tree);
}

avl_node* take_from_btree_area(BTree bt,avl_node *rt,avlTree &av_tree)
{
    bt.traverse_and_put_area(rt,av_tree);
    return rt;
}

//literacy:
void BTreeNode::traverse_and_put_literacy(avl_node*&rt,avlTree &av_tree)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse_and_put_literacy(rt,av_tree);
        rt=av_tree.insert_av(rt,keys[i].literacy,keys[i].name,keys[i].sno);
    }
    if (leaf == false)
        C[i]->traverse_and_put_literacy(rt,av_tree);
}

avl_node* take_from_btree_literacy(BTree bt,avl_node *rt,avlTree &av_tree)
{
    bt.traverse_and_put_literacy(rt,av_tree);
    return rt;
}

void inorder(avl_node*rt,int p)
{
    if(rt==NULL)
        return;
    inorder(rt->left,p);
    cout<<fixed<<setprecision(p)<<rt->data<<" "<<rt->s_name<<endl;
    inorder(rt->right,p);
}

void air_lines()//MAIN AIRLINE FUNCTION
{
    ifstream fl;
    fl.open("air_p.txt");
    if(!fl)
        cout<<"Couldnt open\n";
    vertex*f,*temp;
    string s1,s2,s3,s4;
    bool first=true;
    int ii=1;
    while(fl>>s1)
    {
        fl>>s2>>s3>>s4;
        if(first)
        {
            first=false;
            f=new vertex(ii,s2,s3,s1,s4);
            temp=f;
            ii++;
            continue;
        }
        temp->down=new vertex(ii,s2,s3,s1,s4);
        temp=temp->down;
        ii++;
    }
    tot_airports=ii-1;
    fl.close();
    fstream fl2;
    fl2.open("27000.txt");
    string s,d;
    int fr,to;
    while(fl2>>s)
    {
        fl2>>d;
        fl2>>fr>>to;
        vertex*t1,*t2;
        int a1,a2;
        a1=a2=true;
        vertex *temp=f;
        a1=a2=0;
        double td=time_dif(fr,to);
        while(temp!=NULL)
        {
            if(s==temp->city)
                a1=temp->key;
            if(d==temp->city)
                a2=temp->key;
            temp=temp->down;
        }
        if(a1&&a2)
            add_node(f,a1,a2,td);
    }
    fl2.close();
    AA:cout<<"Enter:\n1: To show all airports and their info\n2: Shortest route(min time taken) b/w 2 airports\n3: To return to main\n\n->";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        cout<<"All the airports are :\n\n";
        show_all_airports(f);
        getch();
        goto AA;
    }
    else if(choice==2)
    {
        cout<<"\n\nEnter the source (airport no.) and destination (airport no.):\n->";
        int src,dest;
        cin>>src;
        cout<<"->";
        cin>>dest;
        route(f,src,dest);
        getch();
        goto AA;
    }
    else
        return;
}

void avlTree::inorderIterative(avl_node* root)
{
    int i =0;
    arr = new avl_node*[Size];
    if(root==NULL)
        return;
    stack<avl_node*>s;
    avl_node* temp = root;
    while(!s.empty() || temp!=NULL)
    {
        if(temp)
        {
            s.push(temp);
            temp = temp->left;
        }
        else
        {
            temp = s.top();
            s.pop();
            arr[i++] = temp;
            temp = temp->right;
        }
    }
}

void avlTree::range(double s,double e,avl_node*root,int p)
{
    inorderIterative(root);
    int i=0;
    while(arr[i]->data <=s)
        i++;
    while(i<Size&&arr[i]->data<=e)
    {
        cout<<fixed<<setprecision(p)<<arr[i]->data<<" "<<arr[i]->s_name<<endl;
        i++;
    }
}


void insertPopu(BTreeNode *a,minheap<int>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertPopu(a->C[i],b);
        b->inserth(a->keys[i].population,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertPopu(a->C[i],b);
}
int minpopu(BTree *a)
{
    minheap<int> h1;
    if(a!=NULL)
    {
    insertPopu(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertPopux(BTreeNode *a,maxheap<int>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertPopux(a->C[i],b);
        b->inserth(a->keys[i].population,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertPopux(a->C[i],b);
}
int maxpopu(BTree *a)
{
    maxheap<int> h1;
    if(a!=NULL)
    {
    insertPopux(a->root,&h1);
    }
    return h1.getroot()->sno;
}


void insertArea(BTreeNode *a,minheap<float>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertArea(a->C[i],b);
        b->inserth(a->keys[i].area,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertArea(a->C[i],b);
}
int minarea(BTree *a)
{
    minheap<float> h1;
    if(a!=NULL)
    {
    insertArea(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertAreax(BTreeNode *a,maxheap<float>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertAreax(a->C[i],b);
        b->inserth(a->keys[i].area,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertAreax(a->C[i],b);
}
int maxarea(BTree *a)
{
    maxheap<float> h1;
    if(a!=NULL)
    {
    insertAreax(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertLite(BTreeNode *a,minheap<float>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertLite(a->C[i],b);
        b->inserth(a->keys[i].literacy,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertLite(a->C[i],b);
}
int minlite(BTree *a)
{
    minheap<float> h1;
    if(a!=NULL)
    {
    insertLite(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertLitex(BTreeNode *a,maxheap<float>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertLitex(a->C[i],b);
        b->inserth(a->keys[i].literacy,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertLitex(a->C[i],b);
}
int maxlite(BTree *a)
{
    maxheap<float> h1;
    if(a!=NULL)
    {
    insertLitex(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertDense(BTreeNode *a,minheap<int>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertDense(a->C[i],b);
        b->inserth(a->keys[i].density,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertDense(a->C[i],b);
}
int mindense(BTree *a)
{
    minheap<int> h1;
    if(a!=NULL)
    {
    insertDense(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertDensex(BTreeNode *a,maxheap<int>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertDensex(a->C[i],b);
        b->inserth(a->keys[i].density,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertDensex(a->C[i],b);
}
int maxdense(BTree *a)
{
    maxheap<int> h1;
    if(a!=NULL)
    {
    insertDensex(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertSex(BTreeNode *a,minheap<int>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertSex(a->C[i],b);
        b->inserth(a->keys[i].sex_ratio,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertSex(a->C[i],b);
}
int minsex(BTree *a)
{
    minheap<int> h1;
    if(a!=NULL)
    {
    insertSex(a->root,&h1);
    }
    return h1.getroot()->sno;
}

void insertSexx(BTreeNode *a,maxheap<int>* b)
{
int i;
    for (i = 0; i < a->n; i++)
    {
        if (a->leaf == false)
            insertSexx(a->C[i],b);
        b->inserth(a->keys[i].sex_ratio,a->keys[i].sno);
    }
    if (a->leaf == false)
        insertSexx(a->C[i],b);
}
int maxsex(BTree *a)
{
    maxheap<int> h1;
    if(a!=NULL)
    {
    insertSexx(a->root,&h1);
    }
    return h1.getroot()->sno;
}

typedef struct Time
{
    int hour;
    int min;
}Time;
typedef struct DB
{
    int count;
    struct train *start;
}database;
typedef struct train
{
    struct train *next;
    struct station *start;
    char tNo[6];
    char tName[40];
    int NOS;
    int dist;
    char week[8];
    Time late;
}train;
typedef struct station
{
    struct station *next;
    short sNo;//nth station from source
    char sName[30];
    char sCode[6];
    Time arr;
    Time dep;
    int dist;//distance from source
}station;
database*initDB()
{
    database*h=(database*)malloc(sizeof(database));
    h->start=NULL;
    h->count=0;
    return h;
}
train*initTrain()
{
    train * t=(train*)malloc(sizeof(train));
    t->next=NULL;
    t->dist=0;
    t->NOS=0;
    strcpy(t->tNo,"\0");
    strcpy(t->tName,"\0");
    t->start=NULL;
    strcpy(t->week,"0000000\0");
    return t;
}
station *createStationNode()
{
    station*s=(station*)malloc(sizeof(station));
    s->next=NULL;
    s->arr.hour=0;
    s->arr.min=0;
    s->dep.hour=0;
    s->dep.min=0;
    s->dist=0;
    strcpy(s->sCode,"\0");
    s->sNo=0;
    strcpy(s->sName,"\0");
    return s;
}
train*loadTrain(train*t,char tempNo[])
{
    char tFile[17]="Trains/";
    strcpy(t->tNo,tempNo);
    strcat(tFile,tempNo);
    strcat(tFile,".txt");
    FILE*fp=fopen(tFile,"r");
    fscanf(fp,"%s",t->tName);
    fscanf(fp,"%d",&(t->NOS));
    fscanf(fp,"%s",t->week);
    station *currs,*s;
    while(!feof(fp))
    {
        s=createStationNode();
        fscanf(fp,"%d",&(s->sNo));
        fscanf(fp,"%s",s->sCode);
        fscanf(fp,"%s",s->sName);
        fscanf(fp,"%d",&(s->arr.hour));
        char c;
        fscanf(fp,"%c",&c);
        fscanf(fp,"%d",&(s->arr.min));
        fscanf(fp,"%d",&(s->dep.hour));
        fscanf(fp,"%c",&c);
        fscanf(fp,"%d",&(s->dep.min));
        fscanf(fp,"%d",&(s->dist));
        if(t->start==NULL)
        {
            t->start=s;
            currs=s;
        }
        else
        {
            currs->next=s;
            currs=s;
        }
    }
    fclose(fp);
    return t;
}
database*loadDB(database*h)
{
    FILE*TNOS=fopen("TrainNos.txt","r");
    char tempNo[10];
    train*currt,*t;
    while(!feof(TNOS))
    {
        fscanf(TNOS,"%s",tempNo);
        t=initTrain();
        t=loadTrain(t,tempNo);
        if(h->start==NULL)
        {
            h->start=t;
            currt=t;
        }
        else
        {
            currt->next=t;
            currt=t;
        }
    }
    return h;
}
Time getCurrentTime()
{
    time_t t;
    Time currentTime;
    time(&t);
    char c[20];
    strcpy(c,ctime(&t));
    currentTime.hour=(c[11]-48)*10+(c[12]-48);
    currentTime.min=(c[14]-48)*10+(c[15]-48);
    return currentTime;
}
void display(database *h)
{
    train *t=h->start;
    while(t!=NULL)
    {
        printf("Train info :\n%s %s\nNo of stations-%d\n\n",t->tName,t->tNo,t->NOS);
        station*s=t->start;
        while(s!=NULL)
        {
            printf("%2d| %20s |%4s |",s->sNo,s->sName,s->sCode);
            printf("ARR-%02d:%02d | DEP-%02d:%02d | ",s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
            printf("Dist-%4d|\n",s->dist);
            s=s->next;
        }
        t=t->next;
        printf("\n\n\n");
    }
}

void printTrains(database*h)
{
    train*t=h->start;
    while(t!=NULL)
    {
        printf("%25s %s\n",t->tName,t->tNo);
        t=t->next;
    }
}
void displayTrain(database *h)
{
    GT:printf("\nChoose the train to see schedule :\n\n");
    Sleep(600);
    printTrains(h);
    char tr[6];
    printf("->");
    scanf("%s",tr);
    train *t=h->start;
    int i=0;
    while(t!=NULL)
    {
        if(strcmp(t->tNo,tr)==0)
        {
            i=1;
            break;
        }
        t=t->next;
    }
    if(i==0)
    {
        printf("\nNo such train. Please Re-enter your choice.\n");
        goto GT;
    }
    printf("Train info :\n%s %s\nNo of stations-%d\n\n",t->tName,t->tNo,t->NOS);
    station*s=t->start;
    while(s!=NULL)
    {
        printf("%2d| %20s |%4s |",s->sNo,s->sName,s->sCode);
        printf("ARR-%02d:%02d | DEP-%02d:%02d | ",s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
        printf("Dist-%4d|\n",s->dist);
        s=s->next;
    }
    printf("\n\n\n");
}
int timeComp(Time t1,Time t2)
{
    int a=t1.hour*60+t1.min;
    int b=t2.hour*60+t2.min;
    if(a>b)
        return 1;
    else if(a<b)
        return -1;
    else
        return 0;
}
Time timeDifference(Time t1,Time t2)//t1 is larger
{
    Time d;
    if(t1.hour==t2.hour)
    {
        d.hour=0;
        d.min=t1.min-t2.min;
        return d;
    }
    else if(t1.min>=t2.min)
    {
        d.min=t1.min-t2.min;
        d.hour=t1.hour-t2.hour;
        return d;
    }
    else
    {
        d.hour=t1.hour-t2.hour-1;
        d.min=60-(t2.min-t1.min);
        return d;
    }
}

void liveStation(database*h)
{
    printf("Choose the station and enter the Station code:\n\n");
    //display all stations here
    printf("->");
    char a[5],c[6];
    scanf("%s",a);
    printf("\nEnter the time for which you want to see live status(in HH:MM format):\n->");
    scanf("%s",c);
    Time b,ct;
    ct=getCurrentTime();
    b.hour=(c[0]-48)*10+(c[1]-48);
    b.min=(c[3]-48)*10+(c[4]-48);
    train*t=h->start;
    int i=0;
    while(t!=NULL)
    {
        station*s=t->start;
        while(s!=NULL)
        {
            if(strcmp(s->sCode,a)==0&&timeComp(s->dep,ct)>=1)
            {
                Time d=timeDifference(s->dep,ct);
                if(timeComp(b,d)>=0)
                {
                    i=1;
                    printf("%25s %s\n Arr- %02d:%02d Dep- %2d:%2d\n\n",t->tName,t->tNo,s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
                    break;
                }
            }
            s=s->next;
        }
        t=t->next;
    }
    if(i==0)
        printf("No trains in the provided time.\n");
}
void trainBetweenStations(database *h)
{
    train *t=h->start;
    char from[5],to[5];
    int i;
    printf("\nFROM:\t");
    scanf("%s",from);
    printf("TO:\t");
    scanf("%s",to);
    int u=0;
    while(t!=NULL)
    {
        i=0;
        station*s=t->start,*s1;
        while(s!=NULL)
        {
            if(!strcmp(s->sCode,from))
            {
                i++;
                s1=s;
            }
            if(!strcmp(s->sCode,to))
            {
                    if(!i)
                        break;
                    u=1;
                    printf("\n\n\nTrain info :\n%s %s\nNo of stations in between-%d\n",t->tName,t->tNo,((s->sNo)-(s1->sNo)));
                    printf("%s\tArrival: %02d:%02d\tDeparture: %02d:%02d\n",s1->sName,s1->arr.hour,s1->arr.min,s1->dep.hour,s1->dep.min);
                    printf("%s\tArrival: %02d:%02d\tDeparture: %02d:%02d\n\n",s->sName,s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
            }
            s=s->next;
        }
        t=t->next;
    }
    if(u==0)
    {
        printf("No trains found.\n\n\n");
        return;
    }
}
void showSpecialTrains(database*h)
{
    int i=0;
    train*t=h->start;
    while(t!=NULL)
    {
        if(t->tNo[0]=='0')
        {
            printf("%25s %s\n",t->tName,t->tNo);
            i=1;
        }
        t=t->next;
    }
    if(i==0)
        printf("No special train at the moment.\n\n");
}
void admin_lateTrain(database*h)
{
    printf("Choose the Train No. to update Late Status :\n");
    Sleep(1000);
    printTrains(h);
    char tNo[6];
    G:printf("\nEnter Train No. :\n->");
    scanf("%s",tNo);
    train*t=h->start;
    int i=0;
    while(t!=NULL)
    {
        if(strcmp(t->tNo,tNo)==0)
         {
             i=1;
            break;
         }
         t=t->next;
    }
    if(i==0)
    {
        printf("Invalid Code. Please Enter again.\n");
        goto G;
    }
    station*s=t->start;
    printf("Enter the time for which the train is late (in HH:MM format) : ");
    char tm1[6];
    scanf("%s",tm1);
    Time tm;
    tm.hour=(tm1[0]-48)*10+(tm1[1]-48);
    tm.min=(tm1[3]-48)*10+(tm1[4]-48);
    while(s!=NULL)
    {
        if((s->arr.min+tm.min)>=60)
        {
            s->arr.min=s->arr.min+tm.min-60;
            s->arr.hour=s->arr.hour+tm.hour+1;
        }
        else
        {
            s->arr.min=s->arr.min+tm.min;
            s->arr.hour=s->arr.hour+tm.hour;
        }
        if((s->dep.min+tm.min)>=60)
        {
            s->dep.min=s->dep.min+tm.min-60;
            s->dep.hour=s->dep.hour+tm.hour+1;
        }
        else
        {
            s->dep.min=s->dep.min+tm.min;
            s->dep.hour=s->dep.hour+tm.hour;
        }
        s->arr.hour=s->arr.hour%24;
        s->dep.hour=s->dep.hour%24;
        s=s->next;
    }
    printf("The updated schedule is :\n");
    s=t->start;
    while(s!=NULL)
    {
        printf("%2d| %20s |%4s |",s->sNo,s->sName,s->sCode);
        printf("ARR-%02d:%02d | DEP-%02d:%02d | ",s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
        printf("Dist-%4d|\n",s->dist);
        s=s->next;
    }
    Sleep(2000);
}
void admin_cancelTrain(database*h)
{
    g:printf("Choose the train to cancel :\n\n");
    train *t=h->start;
    printTrains(h);
    printf("\n\nEnter choice :\n->");
    char tr[6];
    scanf("%s",tr);
    int i=0;
    while(t!=NULL)
    {
        if(strcmp(t->tNo,tr)==0)
        {
            i=1;
            break;
        }
        t=t->next;
    }
    if(i==0)
    {
        printf("Invalid choice. Please re-enter.\n");
        goto g;
    }
    train*temp=h->start;
    while(temp!=NULL)
    {
        if(temp->next==t)
        {
            temp->next=t->next;
            free(t);
        }
        temp=temp->next;
    }
    printf("The revised list of trains is :\n");
    Sleep(1000);
    printTrains(h);
    Sleep(1000);
    printf("\n\n");
}

void admin(database*h)
{
    int j=1;
    G:
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t     Username : ");
    char uname[30];
    char pw[20];
    scanf("%s",uname);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t    Username : %s\n",uname);
    printf("\t\t\t    Password : ");
    int i=0;
    char c;
    while(1)
    {
        c=getch();
        if(c==8)
        {
            printf("\b \b");
            i--;
            continue;
        }
        if(c==13)
            break;
        pw[i++]=c;
        printf("*");
    }
    pw[i]='\0';
    if(strcmp("jiit62",uname)!=0||strcmp("sdflab",pw)!=0)
    {
        if(j==3)
        {
            printf("\n\nWrong input 3 times. Login failed.\n");
            Sleep(100);
            return;
        }
        printf("\n\nWrong username or password. Please re-enter.\n");
        j++;
        Sleep(200);
        goto G;
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t  Login Successful!!!\n\n\n\n\n\n\n\n\n\n\n\n\n");
    Sleep(750);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    int choice=1;
    while(choice)
    {
        printf("Enter your choice : \n1: Change train LATE status\n2: Cancel a train\n0: Return to Main Menu\n\n->");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            {
                admin_lateTrain(h);
                break;
            }
        case 2:
            {
                admin_cancelTrain(h);
                break;
            }
        default:
            break;
        }
    }
}

void trains()
{
    database *h=initDB();
    h=loadDB(h);
    int ch=1;
    while(ch!=0 )
    {
        printf("\n\n\nEnter your choice\n");
        printf("1: Display all trains\n2: Show Special Trains\n3: Display train schedule\n4: Display everything\n5: Train Between Stations\n6: Live Station\n7: Show all stations\n8: Admin Login\n0: Go back to main program\n->");
        scanf("%d",&ch);
        switch(ch)
        {
            case 0:
            {
                return;
                break;
            }
            case 1:
                {
                    printTrains(h);
                    break;
                }
            case 2:
                {
                    showSpecialTrains(h);
                    break;
                }
            case 3:
                {
                    displayTrain(h);
                    break;
                }
            case 4:
                {
                    display(h);
                    break;
                }
            case 5:
                {
                    trainBetweenStations(h);
                    break;
                }
            case 6:
                {
                    liveStation(h);
                    break;
                }
            case 7:
                {
                    printAllStations();
                    break;
                }
            case 8:
                {
                    admin(h);
                    break;
                }
            default :
                {
                    break;
                }
        }
    }
}


int main()
{
    cout<<"\n+-------------------------------- Welcome to S.A.Z.A. : Indian Demographics System ----------------------------------+\n\n\n";
    BTree t(Degree);
    state a;
    fstream stateFile;
    stateFile.open("states.txt");
    if(stateFile.fail())
        cout<<"Sorry! File Not Found.";
    while(!stateFile.eof())
    {
        stateFile>>a.sno;
        stateFile>>a.name;
        stateFile>>a.capital;
        stateFile>>a.population;
        stateFile>>a.growth;
        stateFile>>a.area;
        stateFile>>a.density;
        stateFile>>a.sex_ratio;
        stateFile>>a.literacy;
        stateFile>>a.maj_rel;
        stateFile>>a.hindu;
        stateFile>>a.muslim;
        stateFile>>a.christ;
        stateFile>>a.sikh;
        stateFile>>a.budh;
        stateFile>>a.jain;
        stateFile>>a.others;
        stateFile>>a.atheist;
        t.insertTree(a);
    }
    stateFile.close();
    state *b=NULL;

    int i=0;
    int num_states=35;
    int population[num_states];
    int density[num_states];
    int Ratio[num_states];
    string Rank[num_states],name[num_states];
    avlTree av_pop,av_area,av_literacy;
    avl_node *pop=NULL,*area=NULL,*literacy=NULL;
    pop=take_from_btree(t,pop,av_pop);
    area=take_from_btree_area(t,area,av_area);
    literacy=take_from_btree_literacy(t,literacy,av_literacy);

    int choice,x=1,fr,to;
    while(x)
    {
        cout<<"                         1. Trains and their information."<<endl
            <<"                         2. Airports and their connectivity."<<endl
            <<"                         3. Maximum Population."<<endl
            <<"                         4. Minimum Population."<<endl
            <<"                         5. Maximum Area."<<endl
            <<"                         6. Minimum Area."<<endl
            <<"                         7. Maximum Literacy Rate."<<endl
            <<"                         8. Minimum Literacy Rate."<<endl
            <<"                         9. Maximum Sex Ratio."<<endl
            <<"                         10.Minimum Sex Ratio."<<endl
            <<"                         11.Find Your State."<<endl
            <<"                         12.Minimum Density."<<endl
            <<"                         13.Maximum Density."<<endl
            <<"                         14.Population Range."<<endl
            <<"                         15.Area Range."<<endl
            <<"                         16.Literacy Range."<<endl
            <<"                         17.Sorted Population."<<endl
            <<"                         18.Sorted Literacy."<<endl
            <<"                         19.Sorted Area."<<endl
            <<"                         20.States and their Capitals."<<endl
            <<"                         21.Statewise Religious Data."<<endl
            <<"                         22.Display All States."<<endl
            <<"                         Any other to exit."<<endl;
            cout<<endl<<"Enter Your Choice :\t";
            cin>>choice;
            cout<<endl<<endl<<endl;
            switch(choice)
            {
                case 1:
                    trains();
                    break;
                case 2:
                    air_lines();
                    break;
               case 3:
                    cout<<endl<<"Maximum Population State : "<<endl<<endl;
                    b=t.searchTree(maxpopu(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Population of State\t\t | "<<b->population<<endl;
                    cout<<endl;
                    break;
                case 4:
                    cout<<endl<<"Minimum Population State : "<<endl<<endl;
                    b=t.searchTree(minpopu(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Population of State\t\t | "<<b->population<<endl;
                    cout<<endl;
                    break;
                case 5:
                    cout<<endl<<"Minimum Area State : "<<endl<<endl;
                    b=t.searchTree(minarea(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Area of State\t\t\t | "<<b->area<<endl;
                    cout<<endl;
                    break;
                case 6:
                    cout<<endl<<"Maximum Area State : "<<endl<<endl;
                    b=t.searchTree(maxarea(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Area of State\t\t\t | "<<b->area<<endl;
                    cout<<endl;
                    break;
                case 7:
                    cout<<endl<<"Minimum Literacy State : "<<endl<<endl;
                    b=t.searchTree(minlite(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Literacy of State\t\t | "<<b->literacy<<endl;
                    cout<<endl;
                    break;
                case 8:
                    cout<<endl<<"Maximum Literacy State : "<<endl<<endl;
                    b=t.searchTree(maxlite(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Literacy of State\t\t | "<<b->literacy<<endl;
                    cout<<endl;
                    break;
                case 9:
                    cout<<endl<<"Minimum Sex Ratio State : "<<endl<<endl;
                    b=t.searchTree(minsex(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Sex Ratio of State\t\t | "<<b->sex_ratio<<endl;
                    cout<<endl;
                    break;
                case 10:
                    cout<<endl<<"Maximum Sex Ratio State : "<<endl<<endl;
                    b=t.searchTree(maxsex(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Sex Ratio of State\t\t | "<<b->sex_ratio<<endl;
                    cout<<endl;
                    break;
                case 11:
                    cout<<"State Directory : "<<endl<<endl;
                    t.stateNames();
                    cout<<"Enter State Number : \t";
                    cin>>x;
                    b=t.searchTree(x);
                    b->out();
                    break;
                case 12:
                    cout<<endl<<"Minimum Density State : "<<endl<<endl;
                    b=t.searchTree(mindense(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Density of State\t\t | "<<b->density<<endl;
                    cout<<endl;
                    break;
                case 13:
                    cout<<endl<<"Maximum Density State : "<<endl<<endl;
                    b=t.searchTree(maxdense(&t));
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Density of State\t\t | "<<b->density<<endl;
                    cout<<endl;
                    break;
                case 14:
                    fr,to;
                    cout<<"Enter the range of population:\n->";
                    cin>>fr;
                    cout<<"->";
                    cin>>to;
                    av_pop.range(fr,to,pop,0);
                    break;

                case 15:
                    fr,to;
                    cout<<"Enter the range of area:\n->";
                    cin>>fr;
                    cout<<"->";
                    cin>>to;
                    av_area.range(fr,to,area,0);
                    break;

                case 16:
                    fr,to;
                    cout<<"Enter the range of literacy:\n->";
                    cin>>fr;
                    cout<<"->";
                    cin>>to;
                    av_literacy.range(fr,to,literacy,2);
                    break;

                case 17:
                    cout<<"\n\nPopulation\n\n";
                    inorder(pop,0);
                    break;
                case 18:
                    cout<<"\n\nLiteracy\n\n";
                    inorder(literacy,2);
                    break;
                case 19:
                    cout<<"\n\nArea\n\n";
                    inorder(area,0);
                    break;
                case 20:
                    cout<<endl<<"States and their Capitals : "<<endl<<endl;
                    t.stateCapitals();
                    break;
                case 21:
                    cout<<"State Directory : "<<endl<<endl;
                    t.stateNames();
                    cout<<"Enter State Number : \t";
                    cin>>x;
                    b=t.searchTree(x);
                    cout<<endl;
                    cout<<"Name of State\t\t\t | "<<b->name<<endl;
                    cout<<"Majority Religion of State\t | "<<b->maj_rel<<endl;
                    cout<<"Hindu Percentage of State\t | "<<b->hindu<<endl;
                    cout<<"Muslim Percentage of State\t | "<<b->muslim<<endl;
                    cout<<"Christian Percentage of State\t | "<<b->christ<<endl;
                    cout<<"Sikh Percentage of State\t | "<<b->sikh<<endl;
                    cout<<"Budh Percentage of State\t | "<<b->budh<<endl;
                    cout<<"Jain Percentage of State\t | "<<b->jain<<endl;
                    cout<<"Others Percentage of State\t | "<<b->others<<endl;
                    cout<<"Atheist Percentage of State\t | "<<b->atheist<<endl;
                    cout<<endl;
                    break;
                case 22:
                    t.traverse();;
                    break;
            default:
                x=0;
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tExiting...\n\n\n\n\n\n\n\n\n\n\n\n\n\n ";
                break;
            }
            getch();
            cout<<endl<<"-----------------------------------------------------------------------------------------------------------"<<endl<<endl;
    }
    return 0;
}
