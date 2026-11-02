//asymmetric decrytor
#include<stdio.h>
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
	
	printf("Enter your encrypted message(C)= ");
	long long int c;
	scanf("%lld",&c);
	printf("Give me the n and d of receiver's private key\n");
	long long int n,d;
	printf("n= ");
	scanf("%lld", &n);
	printf("d= ");
	scanf("%lld", &d); 
	
	long long int mnum=1;
	while(d>0)
	{
		if (d % 2 == 1)
        {
        	mnum=multiply(mnum, c, n);
		}    
        c=multiply(c, c, n);
        d=d/2;
	}
	
	//now mnum has to be converted to m, i know it was encoded in base 256
	printf("Your message is (M)= ");
	char m[6];
	for(int i=4;i>=0;i--)
	{
		int x=mnum%256;
		m[i]=(char)x;
		mnum=mnum/256;
	}
	m[5]='\0';
	puts(m);
	return 0;
}
