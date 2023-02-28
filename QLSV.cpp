#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

//Khai bao bien
struct Diem_thi
{
	float diem1;
	float diem2;
	float diem3;
};
struct Nam_sinh
{
	int ngay;
	int thang;
	int nam;
};
struct Sinh_vien
{
	char id[50];
	char ten[50];
	char gioitinh[10];
	struct Nam_sinh ngaysinh;
	int tuoi;
	struct Diem_thi diem; 
	float diemtb;
	char hocluc[10];
	char lop[10];
};

// Cac ham chuan hoa
void Chuan_hoa_space(char ten[])
{
	int len = strlen(ten);
	// xoa dau cach o giua chuoi
	for (int i=0;i<len;i++)
	{
		if (ten[i]==' ' && ten[i+1]==' ')
		{
			for (int j=i;j<len;j++)
			{
				ten[j]=ten[j+1];
			}
			len--;
			i--;
		}
	}
	
}
void Chuan_hoa(char ten[]) {
    int i;
    Chuan_hoa_space(ten);
    ten[0] = toupper(ten[0]);
    for (i = 1; ten[i] != '\0'; i++) {
        if (ten[i-1] == ' ' && isalpha(ten[i])) {
            ten[i] = toupper(ten[i]); 
        } else {
            ten[i] = tolower(ten[i]);
        }
    }
}
void Chuan_hoa_lop(char lop[])
{
	for (int i = 0; lop[i]!='\0';i++)
	{
		if (isalpha(lop[i]))
		{
			lop[i]=toupper(lop[i]);
		}
	}
}


//Ham nhap sinh vien
void Nhap_sinh_vien(struct Sinh_vien &SV)
{
	int ktrid,ktrdiem;
	do {
        ktrid = 1;
        printf("ID: "); scanf("%s", SV.id);
        for (int i = 0; i < strlen(SV.id); i++) {
            if (SV.id[i] < '0' || SV.id[i] > '9') {
                ktrid = 0;
                break;
            }
        }
        if (ktrid == 0) {
            printf("ID khong hop le. Vui long nhap lai.\n");
        }
    } while (ktrid == 0);
    fflush(stdin);
	printf ("Nhap ten: "); gets(SV.ten);
	Chuan_hoa(SV.ten);
	printf ("Gioi tinh: "); gets(SV.gioitinh);
	Chuan_hoa(SV.gioitinh);
	printf ("Ngay sinh: "); scanf("%d%d%d",&(SV.ngaysinh.ngay),&(SV.ngaysinh.thang),&(SV.ngaysinh.nam));
	do {
        ktrdiem = 1;
        printf ("Diem mon 1: "); scanf("%f", &(SV.diem.diem1));
		printf ("Diem mon 2: "); scanf("%f", &(SV.diem.diem2));
		printf ("Diem mon 2: "); scanf("%f", &(SV.diem.diem3));
            if (SV.diem.diem1<0 || SV.diem.diem1>10 || SV.diem.diem2<0 || SV.diem.diem2>10 || SV.diem.diem3<0 || SV.diem.diem3>10 ) {
                ktrdiem = 0;
                printf("Diem khong hop le. Vui long nhap lai.\n");
       		}
    } while (ktrdiem == 0);
	fflush(stdin);
	printf ("Lop: "); gets(SV.lop); 
	Chuan_hoa_lop(SV.lop);
	
}

//Ham tinh tuoi
void Tinh_tuoi(struct Sinh_vien &SV)
{
	time_t t = time(0);
    struct tm* nam = localtime(&t);
    int namhientai=nam->tm_year;
	SV.tuoi = namhientai - SV.ngaysinh.nam + 1900;
}

//Ham tinh diem
void Tinh_diemtb(struct Sinh_vien &SV)
{
	SV.diemtb =(float)(SV.diem.diem1 + SV.diem.diem2 + SV.diem.diem3) / 3;
}

void Xep_loai (struct Sinh_vien &SV)
{
	float diem = SV.diemtb;
	if (diem>=8.5)
	{
		strcpy(SV.hocluc,"Gioi");
	}
	if (diem<8.5 && diem>=6.5)
	{
		strcpy(SV.hocluc,"Kha");
	}
	if (diem<6.5 && diem>=5)
	{
		strcpy(SV.hocluc,"Trung Binh");
	}
	if (diem<5)
	{
		strcpy(SV.hocluc,"Yeu");
	}
}

//Ham cap nhap sinh vien
void Cap_nhat_sinh_vien(struct Sinh_vien &SV)
{
	Nhap_sinh_vien(SV);
	Tinh_tuoi(SV);
	Tinh_diemtb(SV);
	Xep_loai(SV);
}

//Ham in ra thong tin sinh vien theo bang
void Bang_sinh_vien(struct Sinh_vien SV)
{
	printf("\n");
    printf("| Thong tin sinh vien    \n");
    printf("| %-10s : %-10s \n", "Ten",SV.ten);
    printf("| %-10s : %-10s \n", "ID", SV.id);
    printf("| %-10s : %-10s \n", "Lop", SV.lop);
    printf("| %-10s : %-10s \n", "Gioi tinh", SV.gioitinh);
    printf("| %-10s : %02d/%02d/%-6d \n", "Ngay sinh", SV.ngaysinh.ngay, SV.ngaysinh.thang, SV.ngaysinh.nam);
    printf("| %-10s : %-10d \n", "Tuoi", SV.tuoi);
    printf("| %-10s : %-10g \n", "Diem TB", SV.diemtb);
    printf("| %-10s : %-10s \n", "Hoc luc", SV.hocluc);
   
}



//Ham tim kiem sinh vien
void Tim_sinh_vien(struct Sinh_vien ds[], int n)
{
    char id[50];
    printf("\nNhap ID sinh vien can tim: ");
    scanf("%s", &id);
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].id,id)) {
            Bang_sinh_vien(ds[i]); 
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien co ID %lld\n", id);
    }
}


//Ham tim diem trung binh cao nhat
float Tim_max_diemtb(struct Sinh_vien ds[], int n)
{
	float max = ds[0].diemtb;
	for (int i=0;i<n;i++)
	{
		if (ds[i].diemtb>max)
		{
			max = ds[i].diemtb;
		}
	}
	return max;
}

//In ra sinh vien co diem trung binh cao nhat
void Sinh_vien_diemtb_max(struct Sinh_vien ds[],int n)
{
	float max = Tim_max_diemtb(ds,n);
	for (int i=0;i<n;i++)
	{
		if (ds[i].diemtb == max )
		{
			Bang_sinh_vien(ds[i]);
		}
	}
}

//Ham xoa sinh vien
void Xoa_sinh_vien(struct Sinh_vien ds[], int &n)
{
    char id[50];
    printf("\nNhap ID sinh vien can xoa: ");
    scanf("%s", &id);
    bool found = false;
    for (int i = 0; i < n; i++) 
    {
        if (strcmp(ds[i].id,id))
        {
            found = true;
            for (int j = i; j < n - 1; j++)
            {
                ds[j] = ds[j + 1];
            }
            n--;
            break;
        }
    }
    if (!found)
    {
        printf("Khong tim thay sinh vien co ID %lld\n", id);
    }
}


//Ham them sinh vien
void Them_sinh_vien(struct Sinh_vien ds[], int &n)
{
	int them;
	printf("\nNhap so luong sinh vien can them: "); scanf("%d",&them);
	if (them >= 100 - n) 
	{
    	printf("Danh sach sinh vien da day, khong the them sinh vien moi!\n");
    	return;
	}
	int m = n+1;
	for (int i=n;i<n+them;i++)
	{
		printf ("Nhap sinh vien thu %d: \n",m);
		m++;
		Cap_nhat_sinh_vien(ds[i]); 
	}
	n = n+them; 
	printf("\nDa them sinh vien thanh cong %d sinh vien!\n",them);
}

//Ham sap xep theo ten
void Sap_xep_ten(struct Sinh_vien ds[],int n)
{
	for (int i=0;i<n-1;i++)
	{
		for (int j=i+1;j<n;j++)
		{
			if (strcmp(ds[i].ten,ds[j].ten)>0)
			{
				struct Sinh_vien temp;
				temp = ds[i];
				ds[i] = ds[j];
				ds[j] = temp;
			}
		}
	}
}

//Ham sap xep theo diem trung binh
void Sap_xep_diemtb(struct Sinh_vien ds[],int n)
{
	for (int i=0;i<n-1;i++)
	{
		for (int j=i+1;j<n;j++)
		{
			if (ds[i].diemtb<ds[j].diemtb)
			{
				struct Sinh_vien temp;
				temp = ds[i];
				ds[i] = ds[j];
				ds[j] = temp;
			}
		}
	}
}

//Ham in ra tat ca sinh vien
void In_sinh_vien(struct Sinh_vien ds[], int n)
{
	for (int i=0;i<n;i++)
	{
		Bang_sinh_vien(ds[i]);
	}
}
int main ()
{
	struct Sinh_vien ds[100];
	int n=0;
	int chucnang;
	while (true)
	{
		printf("\n");
        printf("********************************************\n");
        printf("**     CHUONG TRINH QUAN LY SINH VIEN     **\n");
        printf("**       1. Nhap du lieu                  **\n");
        printf("**       2. Sinh vien co DTB cao nhat     **\n");
        printf("**       3. Xoa du lieu sinh vien         **\n");
        printf("**       4. Tim du lieu sinh vien         **\n");
        printf("**       5. In sinh vien SX theo ten 	  **\n");
        printf("**       6. In sinh vien SX theo DTB 	  **\n");
        printf("**       0. Thoat                         **\n");
        printf("********************************************\n");
        printf("       Nhap lua chon cua ban: ");
       	scanf ("%d",&chucnang);
		switch (chucnang) 
		{
        	case 1:
        		printf("\nBan da chon chuc nang nhap du lieu sinh vien!\n");
				Them_sinh_vien(ds,n);
            	break;
        	case 2:
        		printf("\nBan da chon chuc nang in du lieu sinh vien co DTB cao nhat!\n");
        		if (n==0)
        		{
        			printf ("\nChua co thong tin sinh vien!\n");	
				}
				else 
				{
					Sinh_vien_diemtb_max(ds,n);
				}
        		break;
        	case 3:
        		printf("\nBan da chon chuc nang xoa du lieu sinh vien!\n");
        		Xoa_sinh_vien(ds,n);
        		break;
        	case 4:
        		printf("\nBan da chon chuc nang tim du lieu sinh vien!\n");
        		Tim_sinh_vien(ds,n);
        		break;
        	case 5:
        		printf("\nBan da chon chuc nang in du lieu sinh vien theo ten!\n");
        		if (n==0)
        		{
        			printf ("\nChua co thong tin sinh vien!\n");	
				}
				else 
				{
					Sap_xep_ten(ds,n);
					In_sinh_vien(ds,n);
				}
        		break;
        	case 6:
        		printf("\nBan da chon chuc nang in du lieu sinh vien theo DTB!\n");
        		if (n==0)
        		{
        			printf ("\nChua co thong tin sinh vien!\n");	
				}
				else 
				{
					Sap_xep_diemtb(ds,n);
					In_sinh_vien(ds,n); 
				}
        		
        		break;
        	case 0:
        		return 0;
       		default:
       		    printf("\nMoi nhap lai!");
        		break;
    	}
	}
	return 0;

}

