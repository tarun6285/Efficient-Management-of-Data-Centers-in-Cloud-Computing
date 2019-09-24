#include<iostream>
#include<conio.h>
#include<stdlib.h>

#define VM_size 3

using namespace std;

int alloc_host[VM_size + 1];
int newalloc_host[VM_size + 1];

class Host {
  int util;
  int id;
  int allocated_vm;
  int newutil;
  public:
    void get_input(void);
	void show_output(int);
  friend void build_minheap(Host hostob[], int nhost);
  friend void min_heapify(Host hostob[], int i, int nhost);
  friend void AllocateVM(Host hostob[], int nhost, int vm_util[], int nvm, int alloc_host_id[]);
  //friend void show_minheap(Host hostob[],int nhost);
};

void Host::get_input(void) {
  allocated_vm = -999;
  cout << "Host Id" << "\n";
  cin >> id;
  cout << "\n" << "Host Utilization" << "\n";
  cin >> util;
  newutil = util;
}

void Host::show_output(int i) {
  //cout<<"Host "<<i+1<<" has utilization "<<util <<"\n";
  cout<<"\n"<<"Host with id "<<id <<"newutil "<<newutil<<"\n";
  cout<<"\n"<<"Host with id "<<id <<"newutil= "<<newutil<<"\n";
}

void build_minheap(Host hostob[], int nhost) {

  for (int i = nhost / 2; i >= 1; i--) {
    min_heapify(hostob, i, nhost);
  }
}

void min_heapify(Host hostob[], int i, int nhost) {
  int temp, temp_id;
  int j;
  temp = hostob[i].newutil;
  temp_id = hostob[i].id;
  j = 2 * i;
  while (j <= nhost) {
    if (j < nhost && hostob[j + 1].newutil < hostob[j].newutil)
      j = j + 1;
    if (temp < hostob[j].newutil)
      break;
    else if (temp >= hostob[j].newutil) {
      hostob[j / 2].newutil = hostob[j].newutil;
      hostob[j / 2].id = hostob[j].id;
      j = 2 * j;
    }
  }
  hostob[j / 2].newutil = temp;
  hostob[j / 2].id = temp_id;
  return;
}

void AllocateVM(Host hostob[], int nhost, int vm_util[], int nvm, int alloc_host_id[]) {

  int max = 100;
  int i, j, k;
  int min;
  for (i = 1; i <= nvm; i++) {
    alloc_host[i] = 0;
    newalloc_host[i] = 0;
  }

  //sort(Vm,nvm);
  for (i = 1; i <= nvm; i++) {
    min = hostob[1].newutil;
    if (min + vm_util[i] <= max) {
      alloc_host[i] = min;
      newalloc_host[i] = min + vm_util[i];
      // cout<<"\n id="<<hostob[1].id<<"\n"; 
      alloc_host_id[i] = hostob[1].id;
      hostob[1].allocated_vm = i;
      hostob[1].newutil = min + vm_util[i];
      min_heapify(hostob, 1, nhost);
    }

  }

}

int main() {
  int nhost, i;
  cout << "Enter no of Host";
  cin >> nhost;
  Host hostob[nhost + 1];
  
  for (i = 1; i <= nhost; i++) {
    cout << "\n" << "Details of Host " << i << "\n";
    hostob[i].get_input();

  }

  for (i = 1; i <= nhost; i++) {
    hostob[i].show_output(i);
  }

  int vm_util[VM_size + 1];
  cout << "Enter Utilization " << VM_size << "VM's" << "\n";
  
  for (int j = 1; j <= VM_size; j++)
    cin >> vm_util[j];
  
  //Creating Heap
  build_minheap(hostob, nhost);

  int alloc_host_id[nhost + 1];
  for (i = 1; i <= nhost; i++)
    alloc_host_id[i] = -99;
  
  AllocateVM(hostob, nhost, vm_util, VM_size, alloc_host_id);
  
  //Final result after VM with particular utility is shifted from 1 host to other
  for (i = 1; i <= VM_size; i++) {
    cout << i << " Vm with util " << vm_util[i] << " is allocated to Host with ";
    cout << "  previous utili=" << alloc_host[i] << " and new util=" << newalloc_host[i];
    cout << "\n";

  }
  getch();
  return 0;

}