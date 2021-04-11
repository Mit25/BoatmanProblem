#include <bits/stdc++.h>
using namespace std;

int findTime(int arr[], int n){
	if(n<=2)
		return arr[n-1];
	int i,ans=0;
	for(i=1;i<n;i++)
		ans += arr[i];
	ans += (n-2)*arr[0];
	return ans;
}

int main() {
	int n;
    cin >>n;
    int arr[n];
    int i;
    for(i=0;i<n;i++)
		cin >>arr[i];
    cout << findTime(arr, n); 
    return 0;
}