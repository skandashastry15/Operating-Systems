#include <stdio.h>
#include <stdlib.h>

int gcd(int a,int b){
    if(b==0)
    return a;
    else
    gcd(b,a%b);
}

int lcm(int a,int b){
    return((a*b)/gcd(a,b));
}

int hyperperiod(int period[],int n){
    int k=period[0];
    n--;
    while(n>=1){
        k=lcm(k,period[n--]);
    }
    return k;
}

int main(){
    int period[10], cput[10], n, i, temp, hyp;

    printf ("Enter no. of processes:\n");
    scanf ("%d",&n);

    printf ("Enter period and processing time:\n");
    for (i=0;i<n;i++){
        scanf ("%d %d", &period[i], &cput[i]);
    }
    hyp = hyperperiod(period, n);
    printf ("Hyperperiod=%d\n",hyp);
    int util[n];
    float utilization=0;

    for (i=0;i<n;i++){
        util[i]=hyp/period[i];
        util[i]*=cput[i];
        utilization+=util[i];
        printf ("Util %d: %d\n",i+1,util[i]);
    }
    utilization/=hyp;
    printf ("Utilization=%f\n",utilization);
    return 0;
}
