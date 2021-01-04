#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h> 


void CaeserEncrypt(int key,char * plaintext, char * ciphertext)
{
    int i;
    for(i=0;i<strlen(plaintext);i++)
    {
        if(isspace(plaintext[i]))
        {
            ciphertext[i]=plaintext[i];
        }
        else{
            ciphertext[i]=((plaintext[i]-'a'+key)%26)+'a';
        }
        
    }

}

void CaeserDecrypt(int key,char * plaintext,char * ciphertext)
{
    int i;
    for(i=0;i<strlen(ciphertext);i++)
    {
        if(isspace(ciphertext[i]))
        {
            plaintext[i]=ciphertext[i];
        }
        else
        {
            char val=ciphertext[i]-'a'-key;
            if(val<0)
            {
                plaintext[i]='z'-val+1;
            }
            else{
                plaintext[i]=val+'a';
            }
        }
    }
}



void VigenereEncrypt(char * key, char * plaintext, char * ciphertext)
{
    int i;
    int k=0;
    int keylen=strlen(key);
    for(i=0;i<strlen(plaintext);i++)
    {
        // printf("p : %c\n",plaintext[i]);
        // printf("index ,k : %d,%c\n",(k)%keylen,key[(k)%keylen]);

        if(isspace(plaintext[i]))
        {
            ciphertext[i]=plaintext[i];
        }
        else
        {
            ciphertext[i]=(plaintext[i]-'a'+key[(k)%keylen]-'a')%26+'a'; 
            k++;
        }     
    }    
    
}

void VigenereDecrypt(char * key, char * plaintext, char * ciphertext)
{
    int i;
    int k=0;
    int keylen=strlen(key);
    for(i=0;i<strlen(ciphertext);i++)
    {
        printf("p : %c\n",ciphertext[i]);
        printf("index ,k : %d,%c\n",(k)%keylen,key[(k)%keylen]);
       
        if(isspace(ciphertext[i]))
        {
            plaintext[i]=ciphertext[i];
        }
        else
        {
            char val=ciphertext[i]-'a'-(key[(k)%keylen]-'a');
            printf("val : %d\n",val);
            if(val<0)
            {
                plaintext[i]='z'+val+1; 
                
            }
            else
            {
                plaintext[i]=val+'a';
            }
            
            k++;
        }  
        printf("plain : %c\n",plaintext[i]);   
    }    

}


void PlayfairTable(char * key, char table[5][5] )
{
    int i=0;
    int j=0;
    int l =strlen(key);
    char alphabet[26]={"abcdefghijklmnopqrstuvwxyz"};
    char untaken[26];
    int count=0;
    int count2=0;
    int flag=0;
    char current;
    
   

    for(i=0;i<26;i++)
    {
        flag=0;
        current=alphabet[i];
        if(current=='j')
        {
            continue;   
        }
        for(j=0;j<l;j++)
        {
            if(current==key[j])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            untaken[count2]=current;
            count2++;
        }
    }
    untaken[count2]='\0';
    // printf("%s\n",untaken);
    int counter=0;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(counter<l)
            {
                table[i][j]=key[counter];
            }
            else{
                table[i][j]=untaken[counter-l];
            }
            counter++;

            
        }
    }
    //  for(i=0;i<5;i++)
    // {
    //     for(j=0;j<5;j++)
    //     {
    //         printf("%c\t",table[i][j]);
    //     }
    //     printf("\n");
    // }
}
void PlayfairPreProcess(char * plaintext, char * temp)
{
    int i;
    int count=0;
    for(i=0;i<strlen(plaintext);i++)
    {
        temp[count]=plaintext[i];
        if(plaintext[i+1]==plaintext[i])
        {
            // temp[count]=plaintext[i];
            count++;
            temp[count]='x';
        }
        count++;
    }
    int l=strlen(temp);
    if(l%2==1)
    {
        // printf("%c %c %c\n",temp[l-1],temp[l],temp[l+1]);
        temp[l]=temp[l-1];
        temp[l-1]='x';
        temp[l+1]='\0';
    }
    printf("%s\n",temp);
}
void PlayFairTableLookup(char table[5][5],char plain[2],char cipher[2],int method)
{
    int i,j;
    char a=plain[0];
    char b=plain[1];
    int x1,y1,x2,y2;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(table[i][j]==plain[0])
            {
                x1=i;
                y1=j;
            }
            if(table[i][j]==plain[1])
            {
                x2=i;
                y2=j;
            }
        }
    }
    if(x1!=x2 && y1!=y2)
    {
        cipher[0]=table[x1][y2];
        cipher[1]=table[x2][y1];
    }
    else if(method==0)
    {
        if(x1==x2 && y1!=y2)
        {
            cipher[0]=table[x1][(y1+1)%5];
            cipher[1]=table[x2][(y2+1)%5];
        }
        else if(x1!=x2 && y1==y2)
        {
            cipher[0]=table[(x1+1)%5][y1];
            cipher[1]=table[(x2+1)%5][y2];
        }
    }
    else if(method==1)
    {
        if(x1==x2 && y1!=y2)
        {
            if(y1-1>-1)
                cipher[0]=table[x1][(y1-1)];
            else
                cipher[0]=table[x1][4];
            if(y2-1>-1)
                cipher[1]=table[x2][(y2-1)];
            else
                cipher[1]=table[x2][4];
            
        }
        else if(x1!=x2 && y1==y2)
        {
            if(x1-1>-1)
                cipher[0]=table[(x1-1)][y1];
            else
                cipher[0]=table[4][y1];
            if(x2-1>-1)
                cipher[1]=table[(x2-1)][y2];
            else
                cipher[2]=table[4][y2];
        }
    }
    
}
void PlayfairEncrypt(char table[5][5], char * plaintext, char * ciphertext)
{
    int i=0;
    char * temp=calloc(1,2*sizeof(plaintext));
    PlayfairPreProcess(plaintext,temp);
    char two[2];
    char two2[2];


    for(i=0;i<strlen(temp);i++)
    {
        two[i%2]=temp[i];
        if(i%2==1)
        {
            PlayFairTableLookup(table,two,two2,0);
            ciphertext[i-1]=two2[0];
            ciphertext[i]=two2[1];
        }
    }
    free(temp);
}
void PlayfairDecrypt(char table[5][5], char * plaintext, char * ciphertext)
{
    int i=0;
    char * temp=calloc(1,2*sizeof(ciphertext));
    PlayfairPreProcess(ciphertext,temp);
    char two[2];
    char two2[2];


    for(i=0;i<strlen(temp);i++)
    {
        two[i%2]=temp[i];
        if(i%2==1)
        {
            PlayFairTableLookup(table,two,two2,1);
            plaintext[i-1]=two2[0];
            plaintext[i]=two2[1];
        }
    }
    free(temp);
}



int Preprocess(char * text)
{
    if(text[0]>=65 && text[0]<=90 && text[1]>=65 && text[1]<=90 )
    {
        int i;
        for(i=0;i<strlen(text);i++)
        {
            text[i]=text[i]+32;
        }
        return 1;
    }
    return 0;
}

void Postprocess(char * text)
{
    int i=0;
    for(i=0;i<strlen(text);i++)
        {
            text[i]=text[i]-32;
        }
}
void Decrypter(int cipher, char * plaintext ,char * ciphertext)
{
    int caps=Preprocess(ciphertext);
    
    if(cipher==1)
    {
        int key;
        printf("Enter decryption ceaser key\n");
        scanf("%d",&key);
        CaeserDecrypt(key,plaintext,ciphertext);
    }
    if(cipher==2)
    {
        char key[10];
        printf("Enter decryption vignere key\n");
        scanf("%s",key);
        
        VigenereDecrypt(key,plaintext,ciphertext);

    }
    if(cipher==3)
    {
        char key[10];
        char table[5][5];
        int i=0;
        int j;
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                table[i][j]='a';
            }
        }
        
        printf("Enter decryption vignere key\n");
        scanf("%s",key);
        PlayfairTable(key,table);
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                printf("%c\t",table[i][j]);
            }
            printf("\n");
        }
        PlayfairDecrypt(table,plaintext,ciphertext);
        
    }
    if(caps==1)
    {
        
        Postprocess(plaintext);
    }
    

}
void Encrypter(int cipher, char * plaintext, char * ciphertext)
{
    int caps=Preprocess(plaintext);
    if(cipher==1)
    {
        int key;
        printf("Enter encryption ceaser key\n");
        scanf("%d",&key);
        CaeserEncrypt(key,plaintext,ciphertext);
    }
    if(cipher==2)
    {
        char key[10];
        printf("Enter encryption vignere key\n");
        scanf("%s",key);
        
        VigenereEncrypt(key,plaintext,ciphertext);
    }
    if(cipher==3)
    {
        char key[10];
        char table[5][5];
        int i=0;
        int j;
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                table[i][j]='a';
            }
        }
        
        printf("Enter encryption vignere key\n");
        scanf("%s",key);
        PlayfairTable(key,table);
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                printf("%c\t",table[i][j]);
            }
            printf("\n");
        }
        PlayfairEncrypt(table,plaintext,ciphertext);
        
    }
    if(caps==1)
    {
        Postprocess(ciphertext);
    }

}



void main()
{
    int cipherMethod=5;
    int op;

    while(!(cipherMethod<4 && cipherMethod>0))
    {
        printf("Menu :\n");
        printf("1 : Caeser Cipher\n");
        printf("2 : Vigenere Cipher\n");
        printf("3 : Playfair Cipher\n");
        scanf("%d",&cipherMethod);
        if(!(cipherMethod<3 && cipherMethod>0))
        {
            printf("invalid key pls enter again\n\n");
        }
    }
    while(!(op<3 && op>0))
    {
        printf("Operation :\n");
        printf("1 : Encrypt\n");
        printf("2 : Decrypt\n");
        scanf("%d",&op);
        if(!(op<3 && op>0))
        {
            printf("invalid key pls enter again\n\n");
        }
    }

    printf("You have chosen %d cipher and %d operation\n",cipherMethod,op);


    FILE *fp;
    char *buffer;
    char *result;
    long lSize;

    if(op==1)
    {
        fp=fopen("plaintext.txt","r");
        if( !fp ) perror("plaintext.txt"),exit(1);
    }
    else if(op==2)
    {
        fp=fopen("ciphertext.txt","r");
        if( !fp ) perror("ciphertext.txt"),exit(1);
    }
    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    result = calloc( 1, lSize+1 );

    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);
    if( !result ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
    fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);

    /* do your work here, buffer is a string contains the whole text */
    // printf("plaintext : %s\n",buffer);
    if(op==1)
    {
        Encrypter(cipherMethod,buffer,result);
        fp=fopen("ciphertext.txt","w");
        if( !fp ) perror("ciphertext.txt"),exit(1);

        printf("Encrypted : %s\n",result);
        fputs(result,fp);
    }
    else if(op==2)
    {
        Decrypter(cipherMethod,result,buffer);
        fp=fopen("plaintext.txt","w");
        if( !fp ) perror("plaintext.txt"),exit(1);

        printf("Decrypted : %s\n",result);
        fputs(result,fp);
    }
    fclose(fp);
    free(buffer);
    free(result);
    
}