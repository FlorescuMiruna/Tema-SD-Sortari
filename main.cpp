#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

ifstream f ("sortari.in");
ofstream g ("sortari.out");

///Bubble Sort
void BubbleSort(long long v[],int n)
{

    bool sortat = 0;
    int i;
    while(sortat == 0)
    {
        sortat = 1;

        for(i=0; i<n-1; i++)
            if(v[i]>v[i+1])
            {
                swap(v[i],v[i+1]);
                sortat = 0;
            }


    }


}


///Count Sort
void CountSort(long long v[], int &n )
{

    int maxim = 0,l=0;
    for(int i=0; i<n; i++)
    {
        if(v[i]>maxim)
            maxim = v[i];
    }


    int ap[maxim];
    for(int i=0; i<=maxim; i++)
        ap[i]=0;
    for(int i=0; i<n; i++)
        ap[v[i]]++;


    for(int i=1; i<=maxim; i++)
        for(int j=1; j<=ap[i]; j++)
            v[l++]=i;
    n=l;


}

///Quick Sort

int functie(long long v[],int st,int dr)
{

    int pivot = v[dr];
    int i = st-1;
    for(int j=st; j<=dr; j++)
    {
        if(v[j]<pivot)
        {
            i++;
            swap(v[i],v[j]);
        }

    }
    swap(v[i+1],v[dr]);
    int  poz = i+1;
    return poz;
}
void QuickSort(long long v[],int st,int dr)
{
    int poz;


    if(st<dr)
    {

        poz=functie(v,st,dr);
        QuickSort(v,st,poz-1);
        QuickSort(v,poz+1,dr);
    }
}




///Merge Sort

void merge(long long *v,int st, int dr,int mijloc)
{
    int temp[dr-st+1];
    int i=st, j = mijloc+1,k=0;
    while(i<= mijloc and j<=dr)
    {
        if(v[i]<=v[j])
        {
            temp[k++] = v[i];
            i++;
        }
        else
        {
            temp[k++] = v[j];
            j++;
        }

    }
    while(i<=mijloc)
    {
        temp[k++] = v[i];
        i++;
    }
    while(j<=dr)
    {
        temp[k++] = v[j];
        j++;
    }
    for(i=st; i<=dr; i++)
        v[i] = temp[i-st];

}
void mergeSort(long long v[],int st,int dr)
{
    if(st<dr)
    {
        int mijloc = (st+dr)/2;
        mergeSort(v,st,mijloc);
        mergeSort(v,mijloc+1,dr);
        merge(v,st,dr,mijloc);
    }
}

///Radix Sort
int get_maxim(long long v[], int n)
{
    int maxim = v[0];
    for(int i=0; i<n; i++)
        if(v[i]>maxim)
            maxim=v[i];
    return maxim;
}
void counting_sort(long long v[],int n,int putere)
{
    int x=10,ap[10];
    long long temp[n];
    for(int i=0; i<x; i++)
        ap[i]=0;

    for(int i=0; i<n; i++)
        ap[(v[i]/putere)%10]++;

    for(int i=1; i<x; i++)
        ap[i]+=ap[i-1];

    for(int i=n-1; i>=0; i--)
    {
        temp[ap[(v[i]/putere)%10]-1]=v[i];
        ap[(v[i]/putere)%10]--;
    }
    for(int i=0; i<n; i++)
        v[i]=temp[i];
}
void RadixSort(long long v[],int n)
{
    int maxim;
    maxim=get_maxim(v,n);
    for(int putere=1; maxim/putere>0; putere*=10)
        counting_sort(v,n,putere);
}




int verif_sortare(long long v[],int n)
{
    int ok=1;
    for(int i=0; i<n-1; i++)
        if(v[i]>v[i+1])
        {
            ok=0;
            break;
        }
    return ok;
}

void copiere(long long v[],long long w[],int n)
{
    for(int i=0; i<n; i++)
        v[i] = w[i];
}
void Afis(int n,long long v[])
{
    for(int i=0; i<n; i++)

        g<<v[i]<<" ";

    g<<endl<<endl;
}
int n,i,x,p,numar_teste;
bool oprire;
float time_req;
long long maxim;
long long v[10000000],w[10000000];
int main()
{

    f>>numar_teste;
    for(int j=0; j<numar_teste; j++)
    {

        f>>n>>maxim;
        g<<"Pentru "<<n<<" numere, care nu depasesc "<<maxim<<" timpii de executie sunt:\n";

        for(i=0; i<n; i++)
        {
            v[i]=rand()%maxim+(maxim/10);
        }


        copiere(w,v,n);
        time_req = clock();
        sort(w,w+n);
        time_req = clock()-time_req;
        if(verif_sortare(w,n)==1)
            g<<"Sort dureaza: "<<time_req/CLOCKS_PER_SEC<<'\n';
        else
            g<<"Nu este sortat.\n";



        if(n>50000)
            g<<"Bubble Sort dureaza prea mult.\n";
        else
        {
            copiere(w,v,n);
            time_req = clock();
            BubbleSort(w,n);
            time_req = clock()-time_req;
            if(verif_sortare(w,n)==1)
                g<<"Bubble Sort dureaza: "<<time_req/CLOCKS_PER_SEC<<'\n';
            else
                g<<"Nu este sortat.\n";

        }


        if(maxim>25000)
            g<<"Count sort nu merge.\n";
        else
        {
            copiere(w,v,n);
            time_req = clock();
            CountSort(w,n);
            time_req = clock()-time_req;


            if(verif_sortare(w,n)==1)
                g<<"Count Sort dureaza: "<<time_req/CLOCKS_PER_SEC<<'\n';
            else
                g<<"Nu este sortat.\n";
        }



        copiere(w,v,n);
        time_req = clock();
        QuickSort(w,0,n-1);
        time_req = clock()-time_req;
        if(verif_sortare(w,n)==1)
            g<<"Quick Sort dureaza: "<<time_req/CLOCKS_PER_SEC<<'\n';
        else
            g<<"Nu este sortat.\n";




        if(n>500000)
            g<<"Merge Sort nu merge pentru atatea numere.\n";
        else
        {
            copiere(w,v,n);
            time_req = clock();
            mergeSort(w,0,n-1);
            time_req = clock()-time_req;
            if(verif_sortare(w,n)==1)
                g<<"Merge Sort dureaza: "<<time_req/CLOCKS_PER_SEC<<'\n';
            else
                g<<"Nu este sortat.\n";

        }



        if(n>200000)
            g<<"Radix Sort nu merge pentru atatea numere.\n";
        else
        {
            copiere(w,v,n);
            time_req = clock();
            RadixSort(w,n);
            time_req = clock()-time_req;
            if(verif_sortare(w,n)==1)
                g<<"Radix Sort dureaza: "<<time_req/CLOCKS_PER_SEC<<'\n';
            else
                g<<"Nu este sortat.\n";

        }

        g<<"\n";


    }

    return 0;
}
