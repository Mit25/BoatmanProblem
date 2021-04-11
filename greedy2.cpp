#include <bits/stdc++.h>
using namespace std;

int findTime(int arr[], int n){
	multiset<int> left;
	multiset<int> right;
	int i,j;
	for(i=0;i<n;i++)
		left.insert(arr[i]);
	bool flag=true;
	int ans=0;
	multiset<int> :: iterator it;
	while(left.size()>0){
		//cout <<left.size()<<" ";
		if(flag){
			flag = !flag;
			if(left.size()>2){
				it = left.begin();
				it++;
				//cout <<*it<<" "<< *left.begin()<<" ";
				ans += *left.begin() + *it;
				right.insert(*it);
				left.erase(it);
			}
			else{
				//cout <<"AA"<<" ";
				it = left.begin();
				//cout <<*left.begin()<<endl;
				it++;
				ans += *it;
				while(left.size()>0)
					left.erase(left.begin());
				//cout <<"GAYA"<<" ";
			}
		}
		else{
			flag = !flag;
			it = left.end();
			it--;
			//cout <<*it<<" ";
			ans += *it;
			right.insert(*it);
			left.erase(it);
			it = left.end();
			it--;
			right.insert(*it);
			left.erase(it);
			//cout <<*right.begin()<<" ";
			if(!left.empty()){
				ans += *right.begin();
				left.insert(*right.begin());
				right.erase(right.begin());
			}
		}
	}
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