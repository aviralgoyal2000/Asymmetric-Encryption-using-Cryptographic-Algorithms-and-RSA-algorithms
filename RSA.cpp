#include<iostream>
#include<cstdio> 
#include<math.h> 
#include<cstring> 
#include<stdlib.h> 
#include<fstream> 
#include<cstdio> 
#include<time.h> 
using namespace std;

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], 
en[100],i,enckey,deckey;
char msg[100];
int prime(long int); 
void ce();
long int cd(long int); 
void encrypt();
void decrypt();

int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0) 
            return 0;
    }
    return 1;
}

int primegenerator(int low,int high)
{
    int primearr[1000],i,j=0,flag=0,sizert,secret; srand(time(0));
    while (low < high)
    {
        flag = 0;
        for(i = 2; i <= low/2; ++i)
        {
            if(low % i == 0)
            {
                flag = 1; 
                break;
            }
        }
        
        if (flag == 0)
        {
            primearr[j]=low;
            ++j;
        }
        ++low;
    }
    
    secret = rand() % (j);
    return(primearr[secret]);
}

int main()
{
    int choice;
    cout<<"\nLevel of Encryption"; 
    cout<<"\n1.Mobile/Portable"; 
    cout<<"\n2.Intermediate"; 
    cout<<"\n3.Crucial\n"; 
    cout<<"\nEnter your choice:"; 
    cin>>choice;
    
    switch(choice)
    {
        case 1: p=primegenerator(63,126);
                q=primegenerator(65,152); 
                break;
        case 2: p=primegenerator(75,200);
                q=primegenerator(73,205); 
                break;
        case 3: p=primegenerator(124,263);
                q=primegenerator(139,230); 
                break;
        default: cout<<"Wrong Choice"; 
        exit(1);
    }
    
    cout<<"\nENTER MESSAGE\n"; 
    fflush(stdin);
    gets(msg);
    
    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];
        
    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    fstream f("public.dat",ios::out | ios::binary); 
    fstream f1("private.dat",ios::out | ios::binary);
    srand(time(0));
    int ee= rand()%20;
    enckey= e[ee]; 
    deckey= d[ee];
    f<<enckey<<n;
    f1<<deckey<<n;
    f.close();
    f1.close();
    
    cout<<"\nPOSSIBLE VALUES OF e AND d ARE\n";
    for (i = 0; i < j - 1; i++)
        cout<<e[i]<<"\t"<<d[i]<<"\n";
        
    encrypt(); 
    decrypt(); 
    return 0; 
    getchar();
}
    
    void ce()
    {
        int k; k = 0;
        for (i = 2; i < t; i++)
        {
            if (t % i == 0) 
                continue;
            
            flag = prime(i);
            if (flag == 1 && i != p && i != q)
            {
                e[k] = i;
                flag = cd(e[k]);
                
                if (flag > 0)
                {
                    d[k] = flag; k++;
                }
                
                if (k == 99)
                    break;
            }
        }
    }
    
    long int cd(long int x)
    {
        long int k = 1; 
        
        while (1)
        {
            k = k + t;
            if (k % x == 0) 
                return (k / x);
        }
    }
    
    void encrypt()
    {
        ofstream f;
        f.open("enc.dat",ios::out | ios::binary);
        long int pt, ct, key = e[4], k, len; 
        i = 0;
        len = strlen(msg); 
        while (i != len)
        {
            pt = m[i];
            pt = pt - 96; k = 1;
            for (j = 0; j < key; j++)
            {
                k = k * pt; k = k % n;
            }
            temp[i] = k; ct = k + 96; en[i] = ct; 
            i++;
        }
        
        en[i] = -1;
        char writestr[500];
        
        for(i=0 ; en[i] != -1 ; i++)
        {
            writestr[i]=en[i];
        }
        
        f.write(writestr,strlen(writestr)); f.close();
        cout << "\nTHE ENCRYPTED MESSAGE IS\n";
        cout<<"\n"<<writestr<<"\n";
    }
    
    void decrypt()
    {
        long int pt, ct, key = d[4], k; 
        i = 0;
        while (en[i] != -1)
        {
            ct = temp[i]; k = 1;
            for (j = 0; j < key; j++)
            {
                k = k * ct; 
                k = k % n;
            }
            pt = k + 96;
            m[i] = pt; 
            i++;
        }
        
        m[i] = -1;
        cout << "\n\nTHE DECRYPTED MESSAGE IS\n";
        for (i = 0; m[i] != -1; i++)
            printf("%c", m[i]);
    }