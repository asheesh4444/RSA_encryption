//asymmetric encryptor
#include<stdio.h>
#include<math.h>
long long int multiply(long long int a, long long int b, long long int n)
{
    long long int ans = 0;
    a %= n;
    b %= n;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
        	if (ans >= n - a)
            {
            	ans -= n - a;
			}    
            else
            {
            	ans += a;
			}    
		}
        if (a >= n - a)
        {
        	a -= n - a;
		}
        else
        {
        	a += a;
		}    
        b = b / 2;
    }
    return ans;
}
int main()
{
	printf("Give me the n and e of receiver's' public key\n");
	long long int n,e;
	printf("n= ");
	scanf("%lld", &n);
	printf("e= ");
	scanf("%lld", &e); 
    getchar(); //this is so that fgets does not eat the newline character
	printf("Enter your 5 letter message - m\n");
	char m[6]; //m is the message
	fgets(m, sizeof(m), stdin); //does not overlflow cuz it reads at most one less than the specified size to leave room for the null terminator (\0)
	//we gonna do base 256 encoding to covert the string into a number
	long long int mnum=0;
	for(int i=0;i<5;i++)
	{
		mnum= mnum+ ((pow(256,i))*m[4-i]);
	}
	printf("mnum is %lld\n", mnum);
	
	//now i will encrypt it
	long long int c=1;
	while (e > 0)
    {
        if (e % 2 == 1)
        {
        	c=multiply(c, mnum, n);
		}    
        mnum=multiply(mnum, mnum, n);
        e=e/2;
    }
    
    printf("Encrypted message is (C)= %lld",c);
	
	return 0;
}
