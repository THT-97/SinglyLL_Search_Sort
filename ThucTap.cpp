// Tim kiem va sap xep tren danh sach lien ket OOP
#include <iostream>	//cin, cout
#include <sstream>	//stringstream
#include <stdio.h>	//cac thao tac tren file
#include <time.h>	//ham random
#include <string>

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
		void linkNode(node *&p);
		void swapData(node *&p1, node *&p2);
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
void list::linkNode(node *&p){
	if(first==NULL) first = p;
	else last->next = p;
	last = p;
}
//----------------------------------------------------------------
void list::swapData(node *&p1, node *&p2){
	int temp = p1->value;
	p1->value = p2->value;
	p2->value = temp;
}
//----------------------------------------------------------------
 void list::revertList(){
	node *t1 = first;
	node *t2 = NULL;
	while(first!=NULL){
		t1 = first;			// [t2]<-[],[t1=first]
		first = first->next;// [t1]->[first]->
		t1->next = t2;		// [t2]<-[t1],[first]->
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
			linkNode(p);
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
				linkNode(p);
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
			linkNode(p);
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
	cout<<endl; //xuong dong
	//tao danh sach theo lua chon hoac thoat
	fflush(stdin); //xoa cache
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
	fflush(stdin); //xoa cache
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
	while(i!=last){
		j = i->next;
		while(j!=NULL){
			if(i->value > j->value){
				swapData(i, j);
			}
			j = j->next;
		}
		i = i->next;
	}
}
//----------------------------------------------------------------
 void list::selectionSort(){
	node *flag = first; //danh dau node can sap xep
	node *i, *min;
	while(flag!=last){
		min = flag; //dat node danh dau la node be nhat
		i = flag->next;
		while(i!=NULL){
			if(i->value < min->value) min = i; //cap nhat node be nhat
			i = i->next;
		}
		if(min->value < flag->value) swapData(min, flag); //thay doi gia tri node dau danh sach
		flag = flag->next;
	}
 }
//----------------------------------------------------------------
 void list::insertionSort(){
 	node *sorted = NULL; //tao danh sach sap xep
 	node *p = first;
 	node *pn;
 	while(p!=NULL){		//duyet danh sach
 		pn = p->next;	//luu nut tiep thep cua p vi nut nay se bi thay doi
 		//neu danh sach sap xep rong hoac nut p nho hon, them nut p vao dau danh sach
 		if(sorted == NULL || sorted->value >= p->value){
 			p->next = sorted;
 			sorted = p;
		}
		//tim vi tri thich hop de chen nut p vao danh sach sap xep
		else{
			node *i = sorted;
			//duyet danh sach de tim nut co nut sau lon hon nut p
			while(i->next!=NULL && i->next->value < p->value) i = i->next;
			//chen nut p vao sau nut tim duoc
			p->next = i->next;
			i->next = p;
		}
 		p = pn; //duyet nut tiep theo cua p
	}
	first = sorted; //chuyen con tro dau sang danh sach da sap xep
 }
//----------------------------------------------------------------
 void list::quickSort(){}
//----------------------------------------------------------------
 void list::mergeSort(){}
//----------------------------------------------------------------
 void list::sortList(){
 	char opt;
 	//tien hanh sap xep neu danh sach 
 	if(first->next!=NULL){
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
		fflush(stdin); //xoa cache
		
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
		fflush(stdin); //xoa cache
		if(opt=='2') revertList(); //dao nguoc danh sach neu chon chieu giam dan
		cout<<"\nDanh sach sau khi sap xep:";
		fprintf(f,"\nDanh sach da sap xep:\n");
		fclose(f);
		getList();
	}
 }
//----------------------------------------------------------------
int main(){
	clearfile(f); //Xoa noi dung co san trong file ket qua
	list l;
	cout<<"---CHUONG TRINH MO PHONG TIM KIEM VA SAP XEP DANH SACH LIEN KET---\n";
	l.createList();
	l.search();
	l.sortList();
	cout<<"\nNhan Enter de dong chuong trinh";
	getchar();
	return 0;
}
