// Tim kiem va sap xep tren danh sach lien ket OOP
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class node{
	protected:
		int value;
		node *next;
		void setNode(int n){
			value = n;
			next = NULL;
		}
	friend class list; //class list co the truy xuat class node
};

class list{
	private:
		node *first;
		node *last;
		void link(node *&p);
		void keyList();
		void randList();
		void fileList();
		void bubbleSort(bool ascend);
	public:
		void createList();
		void getList();
		void search();
		void sortList();
};

void list::link(node *&p){
	if(first==NULL) first = p;
	else last->next = p;
	last = p;
}

void list::keyList(){
	string key;
	int i;
	node *p;
	first = NULL; //khoi tao danh sach
	do{
		cout<<"Nhap so nguyen (Nhap ky tu trong de dung): ";
		getline(cin, key);
		stringstream s(key);
		if(s>>i){
			//tao va lien ket node vao danh sach
			p = new node;
			p->setNode(i);
			link(p);
			//----------------------
		}
	}while(key!="");
}

void list::randList(){
	string key;
	int n;
	int i;
	node *p;
	first = NULL; //khoi tao danh sach
	do{
		cout<<"Nhap do dai danh sach: ";
		getline(cin, key);
		stringstream s(key);
		if(s>>n){
			for(int c=0; c<n; c++){
				p = new node;
				i = rand()%1000; //lay ngau nhien gia tri 0 - 999
				p->setNode(i);
				link(p);
			}
			break; //thoat vong vap khi da tao duoc danh sach
		}
	}while(1);
}

void list::fileList(){
	
}

void list::createList(){
	char opt; //lua chon cach tao danh sach
	do{
		cout<<"Chon cach nhap danh sach:\n";
		cout<<"1. Nhap tu ban phim\n";
		cout<<"2. Lay so ngau nhien\n";
		cout<<"3. Doc so tu file\n";
		cout<<"4. Thoat\n";
		cout<<"Lua chon: ";
		cin>>opt;
	}while(opt!='1' && opt!='2' && opt!='3' && opt!='4');
	fflush(stdin); //xoa cache
	cout<<endl; //xuong dong
	//tao danh sach theo lua chon hoac thoat
	if(opt=='1') keyList();
	else if(opt=='2') randList();
	else if(opt=='3') fileList();
	if(opt!='4') getList(); //in danh sach sau khi tao
}

void list::getList(){
	node *cursor = first;
	cout<<"\nDanh sach:\n";
	while(cursor!=NULL){
		cout<<cursor->value<<" ";
		cursor = cursor->next;
	}
	cout<<endl;
}

int main(){
	char option; //lua chon
	list l;
	cout<<"---CHUONG TRINH MO PHONG TIM KIEM VA SAP XEP DANH SACH LIEN KET---\n";
	l.createList();
	return 0;
}
