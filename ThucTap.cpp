// Tim kiem va sap xep tren danh sach lien ket don OOP
#include "libs.h"	
int W; //do rong man hinh

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
		node* partition(node *pfirst, node *plast, node *&f, node *&l, int dir);
		void halveList(node *f, node *&l1, node *&l2);
		void mergeLists(node *&f, node *l1, node *l2, int dir);
		void keyList();
		void randList();
		void fileList();
		void bubbleSort(int dir);
		void selectionSort(int dir);
		void insertionSort(int dir);
		void mergeSort(node *&f, int dir);	
		void quickSort(node *&pfirst, node *&plast, int dir);
	public:
		list(){first = NULL; last = NULL;}
		void createList();
		void getList();
		void writeList();
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
 node* list::partition(node *pfirst, node *plast, node *&f, node *&l, int dir){
	node *flag = plast; //danh dau nut cuoi danh sach
	node *i = pfirst;
	node *prev = NULL;
	node *temp;
	node *t = flag;
	//bat dau phan doan danh sach
	while(i!=flag){
		//nut dang xet nho/lon hon nut danh dau
		if((i->value < flag->value && dir == 1)or(i->value > flag->value && dir== 2)){
			//dat nut dang xet lam nut dau phan doan
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
	if(f==NULL) f = flag; //dat nut danh dau lam dau phan doan
	l = t; //dat nut cuoi lam nut cuoi cua phan doan
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
 void list::mergeLists(node *&f, node *l1, node *l2, int dir){
 	f = NULL;
 	if(l1==NULL) f = l2;
 	else if(l2==NULL) f = l1;	
	else if((l1->value < l2->value && dir==1) or (l1->value > l2->value && dir==2)){
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
		cout<<"Nhap so nguyen (Nhan Enter trong de dung): ";
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
	int opt = 1; //lua chon cach tao danh sach
	int key;
	TextColor(ColorCode_DarkWhite);
	cout<<"Chon cach nhap danh sach:\n";
	TextColor(ColorCode_White);
	cout<<">1. Nhap tu ban phim\n";
	cout<<" 2. Lay so ngau nhien\n";
	cout<<" 3. Doc so tu file 'list_input.txt'\n";
	cout<<" 4. Thoat\n";
	gotoXY(0,2);
	do{
		int old = opt;
		key = inputKey();
		if(key == key_Up && opt>1) opt--;
		else if(key == key_Down && opt<4) opt++;
		if(old!=opt){
			gotoXY(0,whereY());
			cout<<" ";
			gotoXY(0, 1+opt);
			cout<<">";	
		}
	}while(key!=13);
	cout<<endl; //xuong dong
	//tao danh sach theo lua chon hoac thoat
	clrscr();
	if(opt==1) keyList();
	else if(opt==2) randList();
	else if(opt==3) fileList();
	if(opt!=4) {
		getList(); //in danh sach
		writeList(); //ghi danh sach ra file
	}
}
//----------------------------------------------------------------
 void list::search(){
	int i;
	if(first!=NULL){	//Thuc hien tim kiem khi danh sach co nut
		writefile(f); 	//ghi tiep vao file ket qua
		node *cursor;
		int c = 0;		//dem so node tim duoc
		cout<<"\nNhap gia tri can tim: ";
		cin>>i;
		fflush(stdin); //xoa cache
		clrscr();
		cout<<"Gia tri can tim: "<<i;
		fprintf(f, "\nGia tri can tim: %d\n", i);
		getList();
		cursor = first;
		gotoXY(0, 2);
		while(cursor != NULL){
			if(cursor->value==i){
				c++;
				TextColor(11);
			}
			else TextColor(ColorCode_Yellow);	
			printf("%3d ", cursor->value);
			Sleep(300);
			cursor = cursor->next;
		}
		TextColor(ColorCode_White);
		if(c==0){
			cout<<"\nKhong tim thay gia tri\n";
			fprintf(f,"Khong tim thay gia tri\n");
		}
		else{
			cout<<"\nDa tim thay "<<c<<" nut co gia tri "<<i<<endl;
			fprintf(f,"Da tim thay %d nut co gia tri %d\n", c, i);
		}
		fclose(f);
	}
}
//----------------------------------------------------------------
 void list::getList(){
	node *cursor = first;
	if(cursor==NULL) cout<<"\nDanh sach trong\n";
	else{
		cout<<"\nDanh sach:\n";
		while(cursor!=NULL){
			printf("%3d ", cursor->value);
			cursor = cursor->next;
		}
		cout<<endl;
	}
}
//----------------------------------------------------------------
 void list::writeList(){
 	node *cursor = first;
 	writefile(f); //tao file ket qua
 	cout<<"\nDang luu ket qua...\n";
 	if(cursor==NULL) fprintf(f, "Danh sach trong\n");
	else{
		fprintf(f, "Danh sach:\n");
		while(cursor!=NULL){
			fprintf(f, "%d ", cursor->value);
			cursor = cursor->next;
		}
		fprintf(f, "\n");
	}
	cout<<"Da luu thanh cong\n";
	fclose(f); //dong file sau khi ghi ket qua
 }
//----------------------------------------------------------------
 void list::bubbleSort(int dir){
 	int temp;
 	COORD ipos;
 	COORD jpos;
	node *i, *j;
	i = first;
	ipos = {0,2};
	while(i!=last){
		//dat lai vi tri con tro
		gotoXY(ipos.X, ipos.Y);
		//cap nhat vi tri nut j
		jpos.X = ipos.X+4;
		lineCheck(jpos, ipos, W);
		j = i->next;
		//----------------------
		while(j!=NULL){
			//in vi tri i, j dang xet
			TextColor(ColorCode_Yellow);
			gotoXY(ipos.X, ipos.Y);
			printf("%3d", i->value);
			gotoXY(jpos.X, jpos.Y);
			printf("%3d", j->value);
			Sleep(500);
			//------------------------
			if((i->value > j->value && dir==1)or(i->value < j->value && dir==2)){
				swapData(i, j);
				TextColor(ColorCode_Cyan);
			}
			else TextColor(ColorCode_White);
			//in lai i, j
			gotoXY(ipos.X, ipos.Y);
			printf("%3d", i->value);
			gotoXY(jpos.X, jpos.Y);
			printf("%3d", j->value);
			//cap nhat lai vi tri nut j
			jpos.X = whereX() + 1;
			lineCheck(jpos, W);
			//sang nut j tiep theo
			j = j->next;
			Sleep(300);
		}
		//cap nhat vi tri nut i
		ipos.X+=4;
		lineCheck(ipos, W);
		//sang nut i tiep theo
		i = i->next;
	}
}
//----------------------------------------------------------------
 void list::selectionSort(int dir){
	node *flag = first; //danh dau node can sap xep
	node *i, *m;
	COORD ipos, mpos, fpos;
	fpos = {0,2};
	while(flag!=last){
		m = flag; 			//dat node danh dau la node be/lon nhat
		mpos = fpos;		//cap nhat vi tri node be/lon nhat
		i = flag->next;		//bat dau duyet tu node tiep theo
		ipos.X = fpos.X+4;	//cap nhat vi tri node i
		lineCheck(ipos, fpos, W);
		while(i!=NULL){
			//in lai node flag, i
			TextColor(ColorCode_Red);
			gotoXY(fpos.X, fpos.Y);
			printf("%3d", flag->value);
			TextColor(ColorCode_Grey);
			gotoXY(ipos.X, ipos.Y);
			printf("%3d", i->value);
			Sleep(300);
			if((i->value < m->value  && dir=='1')or(i->value > m->value && dir=='2')){
				//in lai node m hien tai
				if(mpos.X!=fpos.X) TextColor(ColorCode_White);
				gotoXY(mpos.X, mpos.Y);
				printf("%3d", m->value);
				m = i; //cap nhat node m
				mpos = ipos;
				TextColor(ColorCode_Yellow);//chuyen node i thanh mau vang
			}
			else TextColor(ColorCode_White);//chuyen node i thanh mau trang
			//in lai node i
			gotoXY(ipos.X, ipos.Y);
			printf("%3d", i->value);
			//cap nhat vi tri node i
			ipos.X +=4;
			lineCheck(ipos,W);
			i = i->next;
			Sleep(300);
		}
		if((m->value < flag->value && dir=='1')or(m->value > flag->value && dir=='2')){
			swapData(m, flag); //thay doi gia tri node dau danh sach
			//in lai cac node bi thay doi
			TextColor(ColorCode_Cyan);
			gotoXY(fpos.X, fpos.Y);
			printf("%3d", flag->value);
			gotoXY(mpos.X, mpos.Y);
			printf("%3d", m->value);
			Sleep(300);
			TextColor(ColorCode_White);//chuyen node flag hien tai thanh mau trang
		}
		//in lai node flag
		gotoXY(fpos.X, fpos.Y);
		printf("%3d", flag->value);
		//cap nhat vi tri node flag
		fpos.X += 4;
		lineCheck(fpos, W);
		flag = flag->next;
	}
 }
//----------------------------------------------------------------
 void list::insertionSort(int dir){
 	node *sorted = NULL; //tao danh sach sap xep
 	node *p = first;
 	node *pn;
 	while(p!=NULL){		//duyet danh sach
 		pn = p->next;	//luu nut tiep thep cua p vi nut nay se bi thay doi
 		//neu danh sach sap xep rong hoac nut p nho/lon hon nut dau
 		if(sorted == NULL or (sorted->value >= p->value && dir==1)
		 	or (sorted->value < p->value && dir==2)){
			//them nut p vao dau danh sach
 			p->next = sorted;
 			sorted = p;
		}
		//tim vi tri thich hop de chen nut p vao danh sach sap xep
		else{
			node *i = sorted;
			//duyet danh sach de tim nut co nut sau lon/nho hon nut p
			while(i->next!=NULL && ((i->next->value < p->value && dir == 1)
			 or(i->next->value > p->value && dir==2)))
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
 void list::quickSort(node *&pfirst, node *&plast, int dir){
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
 void list::mergeSort(node *&f, int dir){
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
 	int opt = 1;
	int dir = 1;
	int y, key;
 	//tien hanh sap xep neu danh sach co nhieu hon mot nut
 	if(first!=NULL && first->next!=NULL){
 		writefile(f);
 		TextColor(ColorCode_White);
 		cout<<"\nChon phuong phap sap xep:\n";
 		y = whereY();
 		cout<<">1. Bubble sort\n";
 		cout<<" 2. Selection sort\n";
 		cout<<" 3. Insertion sort\n";
 		cout<<" 4. Quick sort\n";
 		cout<<" 5. Merge sort\n";
 		gotoXY(0,y);
 		do{
 			int old = opt;
 			key = inputKey();
 			if(key == key_Up && opt>1) opt--;
 			else if(key == key_Down && opt<5) opt++;
 			if(old != opt){
 				gotoXY(0,whereY());
				cout<<" ";
				gotoXY(0, y-1+opt);
				cout<<">";
			}
		}while(key != key_Enter);
		clrscr();
		cout<<"Chon chieu sap xep\n";
		cout<<">1. Tang dan\n";
		cout<<" 2. Giam dan\n";
		gotoXY(0,1);
		do{
			key = inputKey();
			int old = dir;
 			if(key == key_Up && dir>1) dir--;
 			else if(key == key_Down && dir<2) dir++;
 			if(old != dir){
 				gotoXY(0,whereY());
				cout<<" ";
				gotoXY(0, dir);
				cout<<">";
			}
		}while(key != key_Enter);
		clrscr();
		getList();
		//Cac phuong thuc sap xep
		switch(opt){
 			case(1): {
			  	bubbleSort(dir);
				break;
			 	}
			case(2):{
			  	selectionSort(dir);
				break;
			}
			case(3):{
				insertionSort(dir);
				break;
			}
			case(4):{
				quickSort(first, last, dir);
				break;
			}
			case(5):{
				mergeSort(first, dir);
				break;
			}
		}
		TextColor(15);
		cout<<"\nDanh sach da sap xep:\n";
		getList();
		fprintf(f,"\nDanh sach da sap xep:\n");
		fclose(f);
		writeList();
	}
 }
//----------------------------------------------------------------
int main(){
	clearfile(f); //Xoa noi dung co san trong file ket qua
	list *l = new list;
	W = getScreen();
	//Tiep tuc chuong trinh neu man hinh du rong (80 ki tu tro len)
	if(W>=79){
		gotoXY(W/10, 0);
		TextColor(14);
		cout<<"---CHUONG TRINH MO PHONG TIM KIEM VA SAP XEP TREN DANH SACH LIEN KET---\n";
		TextColor(15);
		l->createList();
		l->search();
		l->sortList();
	}
	cout<<"\nNhan nut bat ki de dong chuong trinh";
	_getch();
	return 0;
}
