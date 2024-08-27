#include<iostream>
using namespace std;

float BruteForce(int num)
{
    //base case
    if(num==0)
    {
        return 1.0;
    }
    
    float sum=0.0;
    for(int i=0;i<num;i++)
    {
        sum+=BruteForce(i);
    }
    return (2.00/num)*sum +num;
}

double arr[50];

void arr_declare(double arr[])
{
    for(int i=0;i<50;i++)
    {
            arr[i]=-1;
    }
}
float DP_TopDownApproach(int num)
{
    if(num == 0)
    {
        return 1.0;
    }
    //if arr[num] is not -1 ,it will simply return value of index num
    if(arr[num]==-1)
    {
        float sum=0.0;

        for(int i=0;i<num;i++)
        {
            sum+=DP_TopDownApproach(i);
        }
        arr[num] = (2.00/num)*sum +num;
    }
    return arr[num];
}
float DP_BottomUpApproach(int n)
{
    double a[50];
    if(n==0)
    {
        return 1.0;
    }
    arr_declare(a);
    
    a[0]=1.0;
    for(int i=1;i<=n;i++)
    {
        float sum=0.0;
        for(int j=0;j<i;j++)
        {
            sum+=a[j];
        }
        a[i] = 2.0 *sum/i +i;
    }
    return a[n];
}
int main()
{
    int n=5;
    cout<<"\tBrute force solution for n=5\n\n";
    cout<<"\ti \tvalue \n";
    for(int i=0;i<n;i++)
    {
        cout<<"\t"<<i<<"\t"<<BruteForce(i)<<"\n";
    }
    cout<<"\n\t Time : O(n^2)\n";
    cout<<"\n\t----------------------\n";

    cout<<"\tTop down Approach for n=5\n\n";
    cout<<"\ti \tvalue \n";
    arr_declare(arr);
    for(int t=0;t<n;t++)
    {
        cout<<"\t"<<t<<"\t"<<DP_TopDownApproach(t)<<"\n";
    }
    cout<<"\n\t Time : O(n^2)\n";
    cout<<"\n\t----------------------\n";
    
    for(int t=0;t<n;t++)
    {
    cout<<"\t"<<DP_BottomUpApproach(t)<<"\n";
    }
    
    
    cout<<"\n\t Time : O(n)\n";
    cout<<"\n\t----------------------\n";
    
    return 0;
}