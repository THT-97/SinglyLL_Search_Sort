// Tim kiem va sap xep tren danh sach lien ket OOP
#include <iostream> //cin, cout, getline()
#include <sstream> //stringstream
#include <stdio.h> //cac thao tac tren file
#include <time.h> //ham random

#define readfile(f) FILE *f = fopen("./list_input.txt","r")
#define writefile(f) FILE *f = fopen("./results.txt","a")
#define clearfile(f) \
		FILE *f = fopen("./results.txt", "w");\
		fprintf(f, " ");\
		fclose(f)
		
using namespace std;

class node{
	protected:
		int value;
		node *next;
		void setNode(int i){
			value = i;
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
		void revertList();
		void bubbleSort();
		void selectionSort();
		void insertionSort();
		void quickSort();
		void mergeSort();
	public:
		void createList();
		void getList();
		void search();
		void sortList();
};
//----------------------------------------------------------------
void list::link(node *&p){
	if(first==NULL) first = p;
	else last->next = p;
	last = p;
}
//----------------------------------------------------------------
 void list::revertList(){
	node *t1 = first;
	node *t2 = NULL;
	while(first!=NULL){
		t1 = first;			// [t2]<-[],[t1=first]
		first = first->next;// [t1]->[first]->
		t1->next = t2;		// [t1]->[t2],[first]->
		t2 = t1;			// [t1=t2],[first]
	}
	first = t1;				// ..<-[first=t1]
}
//----------------------------------------------------------------
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
		else if(key!="") cout<<"Du lieu nhap khong dung\n";
	}while(key!="");
}
//----------------------------------------------------------------
 void list::randList(){
	string key;
	int n, c, i;
	node *p;
	first = NULL; //khoi tao danh sach
	srand(time(NULL)); //tao seed cho ham random
	do{
		cout<<"Nhap do dai danh sach: ";
		getline(cin, key);
		stringstream s(key);
		if(s>>n){
			for(c=0; c<n; c++){
				p = new node;
				i = rand()%1000-0; //lay ngau nhien gia tri 0 - 999
				p->setNode(i);
				link(p);
			}
		}
		else cout<<"Do dai khong hop le\n";
	}while(c<n || n<1);
}
//----------------------------------------------------------------
 void list::fileList(){
	readfile(f);
	if(f==NULL) cout<<"Khong tim thay file\n";
	else{
		node *p;
		int i;
		first = NULL; //khoi tao danh sach
		do{
			fscanf(f, "%d", &i);
			p = new node;
			p->setNode(i);
			link(p);
		}while(fgetc(f)!=EOF); //doc den ki tu cuoi file
	}
	fclose(f); //dong file sau khi doc
}
//----------------------------------------------------------------
 void list::createList(){
	char opt; //lua chon cach tao danh sach
	cout<<"Chon cach nhap danh sach:\n";
	cout<<"1. Nhap tu ban phim\n";
	cout<<"2. Lay so ngau nhien\n";
	cout<<"3. Doc so tu file 'list_input.txt'\n";
	cout<<"4. Thoat\n";
	do{
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
//----------------------------------------------------------------
 void list::search(){
	int i;
	writefile(f); //ghi tiep vao file ket qua
	node *cursor;
	cout<<"\nNhap gia tri can tim: ";
	cin>>i;
	fprintf(f, "\nGia tri can tim: %d\n", i);
	cursor = first;
	while(cursor != NULL && cursor->value != i) cursor = cursor->next;
	if(cursor == NULL){
		cout<<"Khong tim thay gia tri\n";
		fprintf(f,"Khong tim thay gia tri\n");
	}
	else{
		cout<<"Da tim thay gia tri: "<<cursor->value<<endl;
		fprintf(f,"Da tim thay gia tri: %d\n", cursor->value);
	}
	fclose(f);
}
//----------------------------------------------------------------
 void list::getList(){
	node *cursor = first;
	writefile(f); //tao file ket qua
	if(cursor==NULL){
		cout<<"\nDanh sach trong\n";
		fprintf(f, "Danh sach trong\n");
	}
	else{
		cout<<"\nDanh sach:\n";
		fprintf(f, "Danh sach:\n");
		while(cursor!=NULL){
			cout<<cursor->value<<" ";
			fprintf(f, "%d ", cursor->value);
			cursor = cursor->next;
		}
		cout<<endl;
		fprintf(f, "\n");
	}
	fclose(f); //dong file sau khi ghi ket qua
}
//----------------------------------------------------------------
 void list::bubbleSort(){
 	int temp;
	node *i, *j;
	i = first;
	while(i->next!=NULL){
		j = i->next;
		while(j!=NULL){
			if(i->value > j->value){
				temp = i->value;
				i->value = j->value;
				j->value = temp;
			}
			j = j->next;
		}
		i = i->next;
	}
}
//----------------------------------------------------------------
 void list::selectionSort(){}
//----------------------------------------------------------------
 void list::insertionSort(){}
//----------------------------------------------------------------
 void list::quickSort(){}
//----------------------------------------------------------------
 void list::mergeSort(){}
//----------------------------------------------------------------
 void list::sortList(){
 	char opt;
 	writefile(f);
 	cout<<"\nChon phuong phap sap xep:\n";
 	cout<<"1. Bubble sort\n";
 	cout<<"2. Selection sort\n";
 	cout<<"3. Insertion sort\n";
 	cout<<"4. Quick sort\n";
 	cout<<"5. Merge sort\n";
 	
 	do{
 		cout<<"Lua chon: ";
 		cin>>opt;
	}while(opt!='1' && opt!='2' && opt!='3' && opt!='4' && opt!='5');
	//Cac phuong thuc sap xep mac dinh la sap xep tang dan
	switch(opt){
 		case('1'): {
		  	bubbleSort();
			break;
		 	}
		case('2'):{
		  	selectionSort();
			break;
		}
		case('3'):{
			insertionSort();
			break;
		}
		case('4'):{
			quickSort();
			break;
		}
		case('5'):{
			mergeSort();
			break;
		}
	}
	opt = 0; //dat lai bien lua chon
	//chon chieu danh sach
	cout<<"\nChon chieu sap xep\n";
	cout<<"1. Tang dan\n";
	cout<<"2. Giam dan\n";
	do{
		cout<<"Lua chon: ";
		cin>>opt;
	}while(opt!='1' && opt!='2');
	if(opt=='2') revertList(); //dao nguoc danh sach neu chon chieu giam dan
	cout<<"\nDanh sach sau khi sap xep:";
	fprintf(f,"\nDanh sach da sap xep:\n");
	fclose(f);
	getList();
 }
//----------------------------------------------------------------
int main(){
	clearfile(f); //Xoa noi dung co san trong file ket qua
	list l;
	cout<<"---CHUONG TRINH MO PHONG TIM KIEM VA SAP XEP DANH SACH LIEN KET---\n";
	l.createList();
	l.search();
	l.sortList();
	return 0;
}
