#include <iostream>

//#include <conio.h>

using namespace std;
void AllocteVM(int * , int, int * , int);
void min_heapify(int * , int, int);

//Allocating Virtual Machine to particular Host
void AllocateVM(int * Host, int nhost, int * Vm, int nvm) {
  int max = 10;
  int i, j, k;
  int min;
  int allochost[nvm];
  int newallochost[nvm];
  for (i = 1; i <= nvm; i++) {
    allochost[i] = 0;
    newallochost[i] = 0;
  }

  //sort(Vm,nvm);
  for (i = 1; i <= nvm; i++) {
    min = Host[1];
    if (min + Vm[i] <= max) {
      allochost[i] = min;
      newallochost[i] = min + Vm[i];
      Host[1] = min + Vm[i];
      min_heapify(Host, 1, nhost);
    }

  }

  for (i = 1; i <= nvm; i++) {
    cout << i << " Vm is allocated to Host with ";
    cout << "previous utili=" << allochost[i] << " and new util=" << newallochost[i];
    cout << "\n";

  }
}

void min_heapify(int * a, int i, int n) {
  int j, temp;
  temp = a[i];
  j = 2 * i;
  while (j <= n) {
    if (j < n && a[j + 1] < a[j])
      j = j + 1;
    if (temp < a[j])
      break;
    else if (temp >= a[j]) {
      a[j / 2] = a[j];
      j = 2 * j;
    }
  }
  a[j / 2] = temp;
  return;
}

void build_minheap(int * a, int n) {
  int i;
  for (i = n / 2; i >= 1; i--) {
    min_heapify(a, i, n);
  }
}

int main() {
  int nhost, nvm, i, x;
  
  //Testing with 5 hosts and 5 VMs
  
  //Hosts with utilization info
  int a[] = {
    2,
    5,
    7,
    4,
    3
  };
  
  //VMs with utilization info
  int b[] = {
    5,
    4,
    3,
    2,
    1
  };
  int Host[20];
  int Vm[20];
  nhost = nvm = 5;

  for (i = 0; i < nhost; i++)
    Host[i + 1] = a[i];

  for (i = 0; i < nvm; i++)
    Vm[i + 1] = b[i];
  /* cout<<"enter no of Hosts\n";
   cin>>nhost;
   cout<<"\n";
   cout<<"ENter number of VM ";
   cin>>nvm;
   cout <<"\n";
   
   for (i = 1; i<=nhost; i++)
   {
       cout<<"enter host Utilization "<<(i)<<endl;
       cin>>Host[i];
   }
   for (i = 1; i<=nvm; i++)
   {
       cout<<"enter VM Utilization "<<(i)<<endl;
       cin>>Vm[i];
   }
   */
  build_minheap(Host, nhost);
  AllocateVM(Host, nhost, Vm, nvm);
//  getch();
}
