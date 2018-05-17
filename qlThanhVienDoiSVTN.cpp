#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
using namespace std;

typedef struct Member
 {
	int ID;
    char Name[200];
    int Age;
    int Group_ID;
 }Member;
 
 int n;
 int  size   =   sizeof(Member);
 void AddMember();
 void UpdateMember();
 void DeleteMember();
 void print();
 
 int main()
 {
 	char ch;
 	while (1)
 	{
    	system("cls");
 	    printf( "Chuong trinh quan ly thanh vien Doi SVTN") ;
 	    printf("\n 1.Bo sung danh sach ") ;
 	    printf("\n 2.Sua thong tin thanh vien");
 	    printf("\n 3.Xoa thanh vien");
 	    printf("\n 4.In danh sach");
 	    printf("\n 5. Xuat FILE");
 	    printf("\n Bam 1-3 de chon,bam phim bat ki de thoat");
 	    fflush(stdin);
		ch = getch();
		if(ch == '1') AddMember();
		else if(ch == '2') UpdateMember();
		else if(ch == '3') DeleteMember();
		else if(ch == '4') printList();
		else if(ch == '5') xuatFile();
		
		{
			fflush(stdin);
			printf("\n chan roi a ? Y/N");
			ch = getch();
			if(ch == 'Y' || ch == 'y') break;
		}
 	}
 	return 0;
 }
 void AddMember()
 {
 	Member TV;
    FILE *fs;
    fs = fopen("ds.txt","ab");
    
    fseek(fs, 0, 2);
    n = ftell(fs)/size;
    while(1){
        printf("nguoi thu %d :\n", n+1);
        printf("\nID: ");
        fflush(stdin);
        gets(TV.ID);
        printf("Ho va ten: ");
        fflush(stdin);
        gets(TV.Name);
        if(TV.Name[0] == '\0') break;
        format(TV.Name);
        printf("\nTuoi:");
        scanf("%d", &TV.Age);
        
        printf("\nGroup_ID: ");
        scanf("%f", &TV.Group_ID);
        n++;
        fwrite(&TV,size,1,fs);
    }
    fclose(fs);
 }
 void UpdateMember()
 {
 	Member TV;
    FILE *fs;
    int i;
    fs = fopen("ds.txt","r+b");
    while(1){
        printf("sua nguoi thu <nhap so 0 va nhan enter de huy viec chinh sua!>: ");
        int i;
        scanf("%d",&i);
        if(i  == '\0') break;
        fseek(fs,(i-1)*size,0);
        printf("\nnhap ID : ");
        fflush(stdin);
            gets(TV.ID);
        printf("\nnhap Name: ");
        fflush(stdin);
            gets(TV.Name);
        if(TV.Name[0] == '\0') break;
        format(TV.Name);
        printf("\nnhap Age : ");
            scanf("%d",&TV.Age);
        
        printf("\nnhap Group_ID : ");
            scanf("%f", &TV.Group_ID);
        fseek(fs, (i-1)*size, 0);
        fwrite(&TV, size,1,fs);
    }
    fclose(fs);
 }
 void DeleteMember(int &n, Member memberList[])
 {
 	int ID_Del;
	printf("Nhap ID thanh vien can xoa: ");
	scanf("%d",&ID_Del);
	int k = findMember(n, memberList, ID_Del);
	for(int i = k; i < n; i++){
		memberList[i] = memberList[i+1];
	}
	n--;
	
 }
 void printList(){
    FILE *fs;
    Member TV;
    fs = fopen("ds.txt","rb");
    int i = 1;
    while(fread(&TV,size,1,fs)  >  0){
    	printf("\nID: %s", TV.ID);
        printf("\nnguoi thu %d:",i);
        printf("\nName: %s", TV.Name);
        printf("\nAge: %d", TV.Age);
        
        printf("\nGroup_ID: %f", TV.Group_ID);
        i++;
        }
    getch();
    fclose(fs);
}
void xuatFile(){
    FILE *fs, *ft;
    int i=0;
    Member TV;
    fs = fopen("ds.txt","r+b");
    ft = fopen("danhsach.txt","w+");
    fprintf(ft,"so ban ghi = %d\n",n);
    fprintf(ft,"%s   ||%s\t\t\t||\t%s\t||\t%s\t||\t%s\n","STT","ID","Name","Age","Group_ID");
    fprintf(ft,"======||================================||==============||==============||===============\n");
    while(fread(&TV,size,1,fs) > 0)
    {
        i++;
        fprintf(ft,"%d     ||",i);
		fprintf(ft,"%s\t||\t",TV.ID);
        if(strlen(TV.Name) <=15)
            fprintf(ft,"%s\t\t\t||\t",TV.Name);
        else
            fprintf(ft,"%s\t\t||\t",TV.Name);
        
        fprintf(ft,"%d\t||\t",TV.Age);
        fprintf(ft,"%2.3f\n",TV.Group_ID);

    }
    printf("DA GHI XONG FILE DANHSACH.TXT!");
    fclose(fs);
    fclose(ft);
    getch();
}

