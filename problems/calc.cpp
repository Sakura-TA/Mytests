#include<iostream>
using namespace std;
long double sav[50];
long double c(int n)
{
    return sav[n]?:sav[n]=(n<3?n:c(n-1)+c(n-2));

}

int main()
{
    int n;
    while(1) cin>>n,cout<<c(n);
}
