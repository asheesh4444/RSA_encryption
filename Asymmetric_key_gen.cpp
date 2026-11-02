//asymmetric encrypter
//key generation for a person
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>   //idk if i need this or boolean is just native now
#include <unistd.h>  //this is for more randomness
bool isPrime(long long int num)
{
	if (num % 2 == 0) 
	{
		return false;
	}
	for(long long int i=3;i<=sqrt(num);i=i+2)   //i=i+2 cuz then we wont check for i=4,6,8 etc.
	{
		 if (num % i == 0) 
		 {
		 	return false;
		 }
	}
	return true;
}
long long int extendedGcd(long long int t_n, long long int e, long long int *x, long long int *y)
{
	if(e==0)
	{
		*x=1;
		*y=0;
		return t_n;
	}
	long long int x1,y1;
	long long int gcd=extendedGcd(e,(t_n%e),&x1,&y1);    // Recursive calling
	
	*x=y1;
	*y=x1-(t_n/e)*y1;
	return gcd;
}

int main()
{
	restart:
	//select two prime numers p and q between 2^30 and 2^31
	long long int lower= 1073741827LL; //this LL is added cuz else the compiler takes it is a unsigned number
	long long int upper= 2147483647LL;
	srand(time(NULL) ^ getpid());
	long long int p,q;
	for(;;)
	{
		long long int width= (upper - lower) + 1;
		long long int randomNum = lower + (rand() % width);
		if(isPrime(randomNum))
		{
			p=randomNum;
			break;
		}
	}
	for(;;)
	{
		long long int width= (upper - lower) + 1;
		long long int randomNum = upper - (rand() % width);
		if(isPrime(randomNum)&&randomNum!=p)
		{
			q=randomNum;
			break;
		}
	}
    printf("p = %lld\n",p);
    printf("q = %lld\n",q);
    
    //now we calculate modulus n
    long long int n=p*q;
    printf("n = %lld\n",n);
    
    //now we find euler's totient of n with the formula
    long long int t_n=(p-1)*(q-1);
    printf("totient of n = %lld\n",t_n);
    long long int e=65537;
    printf("e = %lld\n",e);
    
    if((p-1)%e==0||(q-1)%e==0)
    {
    	//generate the primes again
    	goto restart;
	}
	
	//now we have t_n and e
	long long int x,y;
	long long int gcd=extendedGcd(t_n,e,&x,&y);
	if(gcd==1)
	{
		printf("gcd(t_n , e) = 1\n");
	}
	if(y<0)
	{
		y=y+t_n;  //this will make it so that there is a positive y value which is between 0 and t_n
	}
	long long int d=y;
	printf("d = %lld\n",d);
	printf("public key = (n,e) = (%lld,%lld)\n",n,e);
	printf("private key = (n,d) = (%lld,%lld)\n",n,d);
	return 0;
}
