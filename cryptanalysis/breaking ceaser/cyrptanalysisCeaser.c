#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h> 
#include<math.h>


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
            int val=ciphertext[i]-'a'-key;
            
            // printf("%c\t%d\t%d\n",ciphertext[i],ciphertext[i],val);
            if(val<0)
            {
                plaintext[i]='z'+val+1;
                // printf("hi\n");
            }
            else{
                plaintext[i]=val+'a';
            }
            // printf("%c\t%d\t%d\t%c\t%d\n",ciphertext[i],ciphertext[i],val,plaintext[i],plaintext[i]);
        }
    }
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
void Decrypter( char * plaintext ,char * ciphertext)
{
    int caps=Preprocess(ciphertext);
    
    int key,i;
    printf("Enter decryption ceaser key\n");
    scanf("%d",&key);
    // for(i=1;i<27;i++)
    // {
    //     key=i;
    //     CaeserDecrypt(key,plaintext,ciphertext);
    
    //     if(caps==1)
    //     {
    //         Postprocess(plaintext);
    //     }
    //     printf("%d:\n\n",i);
    //     printf("%s\n\n",plaintext);
    // }
    CaeserDecrypt(key,plaintext,ciphertext);
    
    if(caps==1)
    {
        Postprocess(plaintext);
    }
    

}
void bubblesort(double*arr,int len)
{
    int i,j;
    double temp;
    printf("%ld",sizeof(arr));
    for(i=0;i<len;i++)
    {
        for(j=0;j<len-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
void Encrypter( char * plaintext, char * ciphertext)
{
    int caps=Preprocess(plaintext);
    
    int key;
    printf("Enter encryption ceaser key\n");
    scanf("%d",&key);
    CaeserEncrypt(key,plaintext,ciphertext);
    
    if(caps==1)
    {
        Postprocess(ciphertext);
    }
    
}

float error(float* freq, float* freq_calc)
{
    float err=0.0;
    int i;
    for(i=0;i<26;i++)
    {
        err=err+fabs(freq[i]-freq_calc[i]);
    }
    // printf("%f\n",err);
    return err;
}

// void max3(int a[])

void codeBreaker(char * plaintext,char * ciphertext)
{
    int caps=Preprocess(ciphertext);
    
    float freq[26]={  0.08167,  0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
                    0.02015,  0.06094, 0.06996, 0.00153, 0.00772, 0.04025,
                    0.02406,  0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
                    0.06327,  0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
                    0.01974,  0.00074 };
    float freqcipher[26]={  0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,0.0,};
    float freqempty[26]={  0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,0.0,};
    float maxfreq=0.0;
    // int pos=0;
    int i,j;
    int keypred;

    float counter=0;
    //finding the frequency
    for(j=0;j<26;j++)
    {
        char val='a'+j;
        for(i=0;i<strlen(ciphertext);i++)
        {
            // printf("%c ",ciphertext[i]);
            if(ciphertext[i]==val)
            {
                // printf("")
                freqcipher[j]++;
            }
        }   
    }
    //displaying it in ratio terms
    for(j=0;j<26;j++)
    {
        freqcipher[j]=freqcipher[j]/strlen(ciphertext);
        // printf("%f ",freqcipher[j]);
        if(j%5==0){
            // printf("\n");
        }
    }
    printf("\n");


//calc the top 3 max values
    float maxs[3]={0.002,0.001,0.0};
    int pos[3];

    for(i=0;i<26;i++)
    {
        if(freqcipher[i]>maxs[0])
        {
            maxs[0]=freqcipher[i];
            pos[0]=i;
        }
        else if(freqcipher[i]>maxs[1])
        {
            maxs[1]=freqcipher[i];
            pos[1]=i;
        }
        else if(freqcipher[i]>maxs[2])
        {
            maxs[2]=freqcipher[i];
            pos[2]=i;
        }
    }

    // freq
    // int keys[3];

    //review section
    // maxfreq=freq[0];
    // posfreq=0;
    // for(i=0;i<26;i++)
    // {
    //     if(freq[i]>maxfreq)
    //     {
    //         maxfreq=freqcipher[i];
    //         posfreq=i;
    //     }
    // }


    int maxchar='e';
    for(j=0;j<3;j++)
    {
        keypred='a'+pos[j];

        if(keypred<maxchar){
            keypred=keypred+26-maxchar;
            printf("hi\n");
        }
        else
        {
            keypred=keypred-maxchar;
        }
        
        
        printf("the key is : %d\n",keypred);
        // printf("the pos is : %d\n",pos);

        CaeserDecrypt(keypred,plaintext,ciphertext);
        if(caps==1)
        {
            Postprocess(plaintext);
        }
        puts(plaintext);
    }

}

void main()
{
    int op;
    while(!(op<4 && op>0))
    {
        printf("Operation :\n");
        printf("1 : Encrypt\n");
        printf("2 : Decrypt\n");
        printf("3 : Break\n");

        scanf("%d",&op);
        if(!(op<4 && op>0))
        {
            printf("invalid key pls enter again\n\n");
        }
    }

    printf("You have chosen ceaser cipher and %d operation\n",op);


// printf("hi\n");
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
    else if(op==3)
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
        Encrypter(buffer,result);
        fp=fopen("ciphertext.txt","w");
        if( !fp ) perror("ciphertext.txt"),exit(1);

        printf("Encrypted : %s\n",result);
        fputs(result,fp);
    }
    else if(op==2)
    {
        Decrypter(result,buffer);
        fp=fopen("plaintext.txt","w");
        if( !fp ) perror("plaintext.txt"),exit(1);

        printf("Decrypted : %s\n",result);
        fputs(result,fp);
    }
    else if(op==3)
    {
        printf("top 3 results : \n");
        codeBreaker(result,buffer);
        
        // printf("Decrypted : %s\n",result);
        fp=fopen("plaintext.txt","w");
        if( !fp ) perror("plaintext.txt"),exit(1);
    }

    
    fclose(fp);
    free(buffer);
    free(result);

}





//
//beginnning of error calc 

    // float val_err;
    // float min_err=100.0;;
    // float maxs[3]={0.002,0.001,0.0};
    // int pos[3];
    // int k_pred[3];
    // int k_predict;
    // // char maxchars[3]={'e','t','a'}
    // for(i=0;i<26;i++)
    // {
    //     if(freqcipher[i]>maxs[0])
    //     {
    //         maxs[0]=freqcipher[i];
    //         pos[0]=i;
    //     }
    //     else if(freqcipher[i]>maxs[1])
    //     {
    //         maxs[1]=freqcipher[i];
    //         pos[1]=i;
    //     }
    //     else if(freqcipher[i]>maxs[2])
    //     {
    //         maxs[2]=freqcipher[i];
    //         pos[2]=i;
    //     }
    // }
    // for(i=0;i<3;i++)
    // {
    //     k_pred[i]=(pos[i]-4+26)%26;
    //     for(j=0;j<26;j++)
    //     {   
    //         freqempty[j]=freqcipher[(j-k_pred[i]+26)%26];
    //     }
    //     val_err=error(freq,freqempty);
    //     printf("\nfreq[0] : %f\tfreq_empty[0] : %f\tpos : %d\tkey : %d\terror : %f\n",freq[0],freqempty[0],pos[i],k_pred[i],val_err);
    //     if(min_err>val_err)
    //     {
    //         min_err=val_err;
    //         k_predict=k_pred[i];
    //     }
    // }
    
    // end of the error calc ^


    // for(i=1;i<26;i++)
    // { 
    //     for(j=0;j<26;j++)
    //     {   
    //         freqempty[j]=freqcipher[(j-i+26)%26];
    //     }
    //     val_err=error(freq,freqempty);
    //     if(min_err>val_err)
    //     {
    //         min_err=val_err;
    //         k_predict=i;
    //     }
    // }
