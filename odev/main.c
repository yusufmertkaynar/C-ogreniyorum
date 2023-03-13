#include <stdio.h>
#include <stdlib.h>
#include<string.h>


struct Kisi{
char ad[20], soyad[20], tel[20], adres[20], parola[20], id[20], parolaTekrar[20];
};

void kullaniciGiris()
{
    int sonuc= 0;
    static int adet =0;
    printf("\nKullanici Giris Ekrani \n");
    char id[20], parola[20];

    printf("Kullanici adi ( ID )    :"); scanf("%s",&id);
    printf("Parola                       :");

    int i=0;
    char ch;
    ch= getch();

    while( ch!=13 )
    {
        parola[i] = ch;
        printf(" * ");
        ch= getch();
        i++;
    }
    parola[i] = '\0' ;


     FILE *ptr = fopen("kullanicilar.dat"  , "r+b");
     struct Kisi k1;
     if( ptr!=NULL )
     {
         while(  (   fread ( &k1, sizeof(struct Kisi),1,ptr ) ) !=NULL   );
         {
             if(strcmp(id,k1.id)==0  &&  strcmp(parola,k1.parola))
             {
                 printf("Giris Basarili\n\n ");
                printf("Hos Geldiniz %s %s \n",k1.ad,strupr( k1.soyad));
                sonuc=1;

             }
         }

     }
    else
    {
        printf("Veritabani erisim hatasi");
    }
    if( sonuc==0 )
    {
        printf("\nKullanici adi veya parola hatali\n");
        adet ++;
        if( adet==3 )
        {
            printf("\nCok fazla deneme yaptiniz , ana menuye yonlendiriliyorsunuz...\n\n");
            return 0;
        }

        kullaniciGiris();
    }

}
void yeniKayit(  )
{
    printf("\n\nYeni Kayit Ekrani \n\n");
    struct Kisi k1;

    printf("Ad                :"); scanf("%s",&k1.ad);
    printf("Soyad          :"); scanf("%s",&k1.soyad);
    printf("GSM            :"); scanf("%s",&k1.tel);
    printf("Adres          :"); scanf("%s",&k1.adres);
    printf("ID                :"); scanf("%s",&k1.id);
    printf("parola ( en az 8 karakter uzunlugunda )     :");
    int i=0;
    char ch;
    ch= getch();

    while( ch!=13 )
    {
        k1.parola[i] = ch;
        printf(" * ");
        ch= getch();
        i++;
    }
    k1.parola[i] = '\0' ;


    printf("\nParola Tekrar    :");

    i=0;
    ch;
    ch= getch();

    while( ch!=13 )
    {
        k1.parolaTekrar[i] = ch;
        printf(" * ");
        ch= getch();
        i++;
    }
    k1.parolaTekrar[i] = '\0' ;
    int  n=strlen(k1.parola);
    if(n<8)
    {
        printf("\nparola uzunlugu en az 8 karakter olmali\n");
        yeniKayit();
    }
    else if(  strcmp (k1.parola, k1.parolaTekrar)!=0  )
    {
         printf("\nparola tekrari eslesmiyor\n");
         yeniKayit();
    }
    else
    {
         FILE *ptr = fopen("kullanicilar.dat"  , "a+b");

    if( ptr!= NULL )
        {
            fwrite ( &k1, sizeof(struct Kisi), 1,ptr );
            fclose(ptr);
            printf("\nyeni kayit islemi basarili \n");

        }
    else
        {
            printf("\nkayit isleminde veritabani hatasi !!!  \n");
        }
    }



}

int menu()
{
    int secim;
    printf("\n\nANA MENU\n\n");
    printf("1- Kullanici Girisi \n");
    printf("2- Yeni Kayit \n");
    printf("3- Cikis\n");
    printf("Seciminiz: "); scanf("%d",&secim);
    return secim;
}






int main()
{

    int secim;
    secim=menu();
    while(secim!=3)
    {
        switch(secim)
        {
            case 1:kullaniciGiris(); break;
            case 2:yeniKayit(); break;
            case 3:printf("Cikis Yaptiniz");break;
            default : printf("Hatali Secim Yapilmistir \n");
         }
         secim=menu();
    }
    return 0;
}
