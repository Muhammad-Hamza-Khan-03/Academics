#include<iostream>
using namespace std;


/*In brute force , Calculate the sum of c(i)
and then perform the operation*/
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
/*declare an array globaly to obtain the summations of C(i) so that 
it gives an optimal structure and reduces the time complexity into linear function*/

double Global_arr[50];

void arr_declare(double arr[])/* initializing all indices of the array to -1*/
{
    for(int i=0;i<50;i++)
    {
            arr[i]=-1;
    }
}

/*In the top Down Approach , n Recursive calls are made and the result is 
stored in Global_arr so that Overlaping sub problem could be calculated only once*/
float DP_TopDownApproach(int num)
{
    if(num == 0)
    {
        return 1.0;
    }
    //if arr[num] is not -1 ,it will simply return value of index num
    if(Global_arr[num]==-1)
    {
        float sum=0.0;

        for(int i=0;i<num;i++)
        {
            sum+=DP_TopDownApproach(i);
        }
        Global_arr[num] = (2.00/num)*sum +num;
    }
    return Global_arr[num];
}

/*In the bottom Up approach ,the result is calculated itteratively and satisfy properties:
 1.Overlaping Subproblem
 2.Optimal Structure
 */
float DP_BottomUpApproach(int n)
{
    Global_arr[0]=1.0;
    for(int i=1;i<=n;i++)
    {
        float sum=0.0;
        for(int j=0;j<i;j++)
        {
            sum+=Global_arr[j];
        }
        Global_arr[i] = 2.0 *sum/i +i;
    }
    return Global_arr[n];
}
int main()
{
    int n=5;
    cout<<"Brute Force:O(2^n)\n";
    for(int i=0;i<n;i++)
        cout<<"\t"<<i<<"\t"<<BruteForce(i)<<"\n";
    
    cout<<"Top down Approach O(n):\n";
    arr_declare(Global_arr);
    for(int t=0;t<n;t++)
    {
        cout<<"\t"<<t<<"\t"<<DP_TopDownApproach(t)<<"\n";
    }
    cout<<"Bottom Up approach O(n^2):\n";
    arr_declare(Global_arr);
    for(int t=0;t<n;t++)
    {
        cout<<"\t"<<t<<"\t"<<DP_BottomUpApproach(t)<<"\n";
    }    
    return 0;
}