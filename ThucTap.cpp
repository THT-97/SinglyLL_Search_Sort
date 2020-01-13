// Tim kiem va sap xep tren danh sach lien ket don OOP
#include "libs.h"	
using namespace std;

class node{
	private:
		int value;
		node *next;
	//--------------------------
		void setNode(int i){
			value = i;
			next = NULL;
		}
	friend class list;
};

class list{
	private:
		node *first;
		node *last;
	//--------------------	
		void linkNode(node *&p);
		void swapData(node *&p1, node *&p2);
		node* getLast(node *f);
		node* partition(node *pfirst, node *plast, node *&f, node *&l, char dir);
		void halveList(node *f, node *&l1, node *&l2);
		void mergeLists(node *&f, node *l1, node *l2, char dir);
		void keyList();
		void randList();
		void fileList();
		void bubbleSort(char dir);
		void selectionSort(char dir);
		void insertionSort(char dir);
		void mergeSort(node *&f, char dir);	
		void quickSort(node *&pfirst, node *&plast, char dir);
	public:
		list(){first = NULL; last = NULL;}
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
 node* list::getLast(node *f){
 	if(f!=NULL) while(f->next!=NULL) f = f->next;
 	return f;
 }
//----------------------------------------------------------------
 node* list::partition(node *pfirst, node *plast, node *&f, node *&l, char dir){
	node *flag = plast; //danh dau nut cuoi danh sach
	node *i = pfirst;
	node *prev = NULL;
	node *temp;
	node *t = flag;
	//bat dau phan doan danh sach
	while(i!=flag){
		//nut dang xet nho/lon hon nut danh dau
		if((i->value < flag->value && dir =='1')or(i->value > flag->value && dir=='2')){
			//dat nut dang xet lam nut dau danh sach phan doan
			if(f==NULL) f = i;
			prev = i;
			i = i->next;
		}
		//cac truong hop con lai
		else{
			//dat nut dang xet ra sau nut cuoi danh sach
			if(prev) prev->next = i->next;
			temp = i->next;//luu vi tri tiep theo cua nut dang xet
			t->next = i;
			i->next = NULL;
			t = i;
			i = temp;//duyet tiep danh sach
		}
	}
	//neu danh sach chua phan doan
	if(f==NULL) f = flag; //dat nut danh dau lam dau danh sach phan doan
	l = t; //dat nut cuoi lam nut cuoi cua danh sach phan doan
	return flag;
}
//----------------------------------------------------------------
 void list::halveList(node *f, node *&l1, node *&l2){
	node *i = f;
	node *j = i->next;
	//tang j 2 buoc, tang i 1 buoc
	while(j!=NULL){
		j = j->next;
		if(j!=NULL){
			i = i->next;
			j = j->next;
		}
	}
	//i nam truoc nut giua danh sach
	//chia doi danh sach
	l1 = f;
	l2 = i->next;
	i->next = NULL;
 }
//----------------------------------------------------------------
 void list::mergeLists(node *&f, node *l1, node *l2, char dir){
 	f = NULL;
 	if(l1==NULL) f = l2;
 	else if(l2==NULL) f = l1;	
	else if((l1->value < l2->value && dir=='1') or (l1->value > l2->value && dir=='2')){
		f = l1;
		mergeLists(f->next, l1->next, l2, dir);
	}
	else{
		f = l2;
		mergeLists(f->next, l1, l2->next, dir);
	}
 }
//----------------------------------------------------------------
 void list::keyList(){
	string key;
	int i;
	node *p;
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
	srand(time(NULL)); //tao seed cho ham random
	do{
		cout<<"Nhap do dai danh sach: ";
		getline(cin, key);
		stringstream s(key);
		if(s>>n){
			for(c=0; c<n; c++){
				p = new node;
				i = rand()%101; //lay ngau nhien gia tri 0 - 100
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
	//Thuc hien tim kiem khi danh sach co nut
	if(first!=NULL){
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
 void list::bubbleSort(char dir){
 	int temp;
	node *i, *j;
	i = first;
	while(i!=last){
		j = i->next;
		while(j!=NULL){
			if((i->value > j->value && dir=='1')or(i->value < j->value && dir=='2'))
				swapData(i, j);
			j = j->next;
		}
		i = i->next;
	}
}
//----------------------------------------------------------------
 void list::selectionSort(char dir){
	node *flag = first; //danh dau node can sap xep
	node *i, *m;
	while(flag!=last){
		m = flag; //dat node danh dau la node be/lon nhat
		i = flag->next;
		while(i!=NULL){
			if((i->value < m->value  && dir=='1')or(i->value > m->value && dir=='2'))
				m = i; //cap nhat node be/lon nhat
			i = i->next;
		}
		if((m->value < flag->value && dir=='1')or(m->value > flag->value && dir=='2'))
			swapData(m, flag); //thay doi gia tri node dau danh sach
		flag = flag->next;
	}
 }
//----------------------------------------------------------------
 void list::insertionSort(char dir){
 	node *sorted = NULL; //tao danh sach sap xep
 	node *p = first;
 	node *pn;
 	while(p!=NULL){		//duyet danh sach
 		pn = p->next;	//luu nut tiep thep cua p vi nut nay se bi thay doi
 		//neu danh sach sap xep rong hoac nut p nho/lon hon nut dau
 		if(sorted == NULL or (sorted->value >= p->value && dir=='1')
		 	or (sorted->value < p->value && dir=='2')){
			//them nut p vao dau danh sach
 			p->next = sorted;
 			sorted = p;
		}
		//tim vi tri thich hop de chen nut p vao danh sach sap xep
		else{
			node *i = sorted;
			//duyet danh sach de tim nut co nut sau lon/nho hon nut p
			while(i->next!=NULL && ((i->next->value < p->value && dir =='1')
			 or(i->next->value > p->value && dir=='2')))
				i = i->next;
			//chen nut p vao sau nut tim duoc
			p->next = i->next;
			i->next = p;
		}
 		p = pn; //duyet nut tiep theo cua p
	}
	first = sorted; //chuyen con tro dau sang danh sach da sap xep
 }
//----------------------------------------------------------------
 void list::quickSort(node *&pfirst, node *&plast, char dir){
 	//neu phan doan co nhieu hon 2 nut
 	if(pfirst!=NULL && pfirst != plast){
 		node *temp;
		node *f=NULL;
 		node *l=NULL;
		node *flag = partition(pfirst, plast, f, l, dir);
 		//neu dau phan doan khac nut danh dau
 		if(f!=flag){
 			temp = f;
			while(temp->next != flag) temp = temp->next;
 			temp->next = NULL;	//cat phan doan moi tu phia ben trai danh sach
 			quickSort(f, temp, dir); //lap lai cac buoc sap xep cho phan doan moi	
 			temp = getLast(f);	//tim nut cuoi cua phan doan moi
 			temp->next = flag;	//lien ket phan doan moi vao lai danh sach
		}
		//lam tuong tu voi phia ben phai danh sach
		quickSort(flag->next, l, dir);
		//cap nhat dau phan doan
		pfirst = f;
	}
 }
//----------------------------------------------------------------
 void list::mergeSort(node *&f, char dir){
 	node *l1;
	node *l2;
	if(f!=NULL && f->next!=NULL){
		halveList(f, l1, l2);//chia doi danh sach
		//tiep tuc chia doi tung doan danh sach
		mergeSort(l1, dir);
		mergeSort(l2, dir);
		mergeLists(f, l1, l2, dir);//tron danh sach
	}
 }
//----------------------------------------------------------------
 void list::sortList(){
 	char opt, dir;
 	//tien hanh sap xep neu danh sach co nhieu hon mot nut
 	if(first!=NULL && first->next!=NULL){
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
		//chon chieu danh sach
		cout<<"\nChon chieu sap xep\n";
		cout<<"1. Tang dan\n";
		cout<<"2. Giam dan\n";
		do{
			cout<<"Lua chon: ";
			cin>>dir;
		}while(dir!='1' && dir!='2');
		fflush(stdin); //xoa cache
		//Cac phuong thuc sap xep
		switch(opt){
 			case('1'): {
			  	bubbleSort(dir);
				break;
			 	}
			case('2'):{
			  	selectionSort(dir);
				break;
			}
			case('3'):{
				insertionSort(dir);
				break;
			}
			case('4'):{
				quickSort(first, last, dir);
				break;
			}
			case('5'):{
				mergeSort(first, dir);
				break;
			}
		}
		
		cout<<"\nDanh sach sau khi sap xep:";
		fprintf(f,"\nDanh sach da sap xep:\n");
		fclose(f);
		getList();
	}
 }
//----------------------------------------------------------------
int main(){
	clearfile(f); //Xoa noi dung co san trong file ket qua
	list *l = new list;
	cout<<"---CHUONG TRINH TIM KIEM VA SAP XEP DANH SACH LIEN KET---\n";
	l->createList();
	l->search();
	l->sortList();
	cout<<"\nNhan nut bat ki de dong chuong trinh";
	_getch();
	return 0;
}
