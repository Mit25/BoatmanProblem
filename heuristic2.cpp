#include <bits/stdc++.h>
#include <time.h>
using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<long> vl;
typedef vector<ll> vll;

#define si(x) scanf("%d",&x)
#define sl(x) scanf("%ld",&x)
#define sll(x) scanf("%lld",&x)

#define pi(x) printf("%d",x)
#define pl(x) printf("%ld",x)
#define pll(x) printf("%lld",x)
#define pn printf("\n")
#define pt printf("\t")
#define ps printf(" ")

const ll mod=1000000007ll;
const ll Mod=1000000009ll;
const ll inf=(ll)5e18;
const ld eps=1e-12;
const ll N=1000005;
const ll LOGN=19;
const ld PI=3.14159265358979323846;

#define sf(x) sort(x.begin(),x.end(),func)
#define s(x) sort(x.begin(),x.end())

#define all(v) v.begin(),v.end()
#define rs(v) { s(v) ; r(v) ; }
#define r(v) {reverse(all(v));}

#define pb push_back
#define mp make_pair
#define F first
#define S second

#define f(i,n) for(ll i=0;i<n;i++)
#define rep(i,a,b) for(ll i=a;i<=b;i++)

#define len(a) sizeof(a)/sizeof(a[0])
#define printArray(a) for(ll i=0;i<length(a);i++){cout << a[i];cout << " ";}cout << endl;

template <class T>T max2(T a,T b){return a<b?b:a;}
template <class T>T min2(T a,T b){return a<b?a:b;}
template <class T>T max3(T a,T b,T c){return max2(max2(a,b),c);}
template <class T>T min3(T a,T b,T c){return min2(min2(a,b),c);}
template <class T>T max4(T a,T b,T c,T d){return max2(max2(a,b),max2(c,d));}
template <class T>T min4(T a,T b,T c,T d){return min2(min2(a,b),max2(c,d));}

void print(ll a[],ll s,ll e){for(ll i=s;i<=e;i++)cout<<a[i]<<" ";cout<<"\n";}
void print(vector<ll> &v,ll s,ll e){for(ll i=s;i<=e;i++)cout<<v[i]<<" ";cout<<"\n";}
void print(vector<ll> &v){for(ll i=0;i<v.size();i++)cout<<v[i]<<" ";cout<<"\n";}

ll mul(ll a,ll b,ll m=Mod){return (ll)(a*b)%m;}
ll add(ll a,ll b,ll m=Mod){a+=b; if(a>=m) a-=m; if(a<0) a+=m; return a;}
ll power(ll a,ll b,ll m=mod){if(b==0) return 1; if(b==1) return (a%m); ll x=power(a,b/2,m); x=mul(x,x,m); if(b%2) x=mul(x,a,m); return x;}

vector<ll> v;
ll minTime;

void printVector(set<pair<ll,ll> > v){
    set<pair<ll,ll> >::iterator it;
    for(it=v.begin();it!=v.end();it++){
        printf("(%lld,%lld) ",it->F,it->S);
    }
    printf("\n");
    return;
}


class Graph{
    ll n,V;
    set<pair<ll,ll> > *array;
    
    public:
    Graph(ll n1,ll v1){
        n=n1;
        V=v1;
        array=new set<pair<ll,ll> >[V];
    }

    void addEdge(ll u,ll v,ll w){
        array[u].insert(mp(v,w));
    }

    void calExpDis(vector<ll> &exp_dist){
        for(ll i=0;i<V;i++){
            for(ll j=0;j<n;j++){
                if(((i&(1<<j))>>j) == 0){
                    exp_dist[i]++;
                }
            }
        }
    }

    vector<ll> dijkstra(ll src){
    	priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > pq;
        vector<ll> dist(V,INT_MAX);
        vector<ll> exp_dist(V,0); calExpDis(exp_dist);
        /*for(int i=0;i<V;i++){
            cout<<i<<" "<<exp_dist[i];pn;
        }pn;*/
        pq.push(mp(0,src));
        dist[src]=0;
        vector<ll> backtrack(V,-1);
        bool flag=false;
        ll ext = 0;
        while(!pq.empty()){
            ext++;
            ll u=pq.top().second;
            pq.pop();
            if(u==V-1)
            	flag=true;
            if(u!=V-1 && flag)
            	continue;
            set<pair<ll,ll> >::iterator it;
            for(it=array[u].begin();it!=array[u].end();it++){
                ll v=it->F;
                ll weight=it->S;
                if(dist[v]>dist[u]+weight){
                    dist[v]=dist[u]+weight;
                    backtrack[v] = u;
                    pq.push(mp(dist[v]+exp_dist[v],v));
                }
            }
        }
        ll curr = V-1;
        vector<ll> path;
        path.push_back(curr);
        while(backtrack[curr]!=-1){
            path.push_back(backtrack[curr]);
            curr = backtrack[curr];
        }
        minTime=dist[V-1];
        reverse(path.begin(),path.end());
        cout <<"Extensions: "<<ext<<endl;
        return path;
    }

    void print(){
        for(int i=0;i<V;i++){
            printf("%d: ",i);
            printVector(array[i]);
        }
    }

    void generate(vector<ll> time){
        for(ll i=0;i<V;i++){
            if(i&(1<<n)){
                for(ll j=0;j<n;j++){
                    if(((i&(1<<j))>>j)==1){
                        ll mask=~(1<<j);
                        ll z=i&mask;
                        mask=~(1<<n);
                        z=z&mask;
                        //cout<<i<<" "<<z<<" "<<time[j]<<" "<<j<<endl;
                        addEdge(i,z,time[j]);
                    }
                }
            }
            else{
                //torch is on left side
                for(ll j=0;j<n;j++){
                    for(ll k=j+1;k<n;k++){
                        if((((i&(1<<j))>>j))==0 && (((i&(1<<k)))>>k)==0){
                            ll z=i|(1<<j|1<<k|1<<n);
                            //cout<<i<<" "<<z<<" "<<max2<int>(time[j],time[k])<<" "<<j<<" "<<k<<endl;
                            addEdge(i,z,max2<int>(time[j],time[k]));
                        }
                    }
                }
            }
        }
    }
    
};

void binrepre(int m,int n){
    int a = pow(2,n);
    while(a>0){
        if((m & a) > 0)
            cout << 1;
        else
            cout <<0;
        a = a/2;
    }
    cout <<" ";
}

void cls(int n){
	for(int i=0;i<n;i++)
		pn;
}

void fill(vector<int> &s,vector<int> &d,int m,int n){
	for(int i=0;i<n;i++){
		if(((m>>i)&1) == 0)
			s.pb(v[i]);
		else
			d.pb(v[i]);
	}
}

int main(){
	ll n;cout<<"Enter no. of people: ";cin>>n;
    if(n>=20){
        cout<<"Abort!!!"<<endl;
    }
    cout<<"Enter time for each person: "<<endl;
	for(ll i=0;i<n;i++){
		ll tmp;
		cin>>tmp;
		v.pb(tmp);
	}
	char ch;
    pn;pn;pn;pn;
    pt;pt;pt;pt;cout<<"******************"<<endl;
	pt;pt;pt;pt;cout<<"* Calculating... *"<<endl;
    pt;pt;pt;pt;cout<<"******************"<<endl;
	scanf("%c", &ch);

	Graph g(n,pow(2,n+1));
    g.generate(v);
    //g.print();
    clock_t t; 
    t = clock();
    vector<ll> v1=g.dijkstra(0);
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("Execution Time: %f s\n", time_taken); 
    //cout<<"State Transitions: "<<endl;

    for(int i=0;i<v1.size();i++){
    	cls(24);
    	vector<int> src,des;
    	fill(src,des,v1[i],n);

    	cout<<"*****************************************************************"<<endl;
    	cout<<"Source:\t\t";
    	if((v1[i]>>n) == 0)
    		cout<<"Torch\t";
    	else
    		cout<<"\t";
    	for(int j=0;j<src.size();j++)
    		cout<<src[j]<<" ";pn;
    	cout<<"*****************************************************************"<<endl;
    	pn;pn;pn;pn;pn;pn;pn;pn;
    	cout<<"*****************************************************************"<<endl;
    	cout<<"Destination:\t";
    	if((v1[i]>>n) == 1)
    		cout<<"Torch\t";
    	else
    		cout<<"\t";
    	for(int j=0;j<des.size();j++)
    		cout<<des[j]<<" ";pn;
    	cout<<"*****************************************************************"<<endl;

    	cls(5);
    	scanf("%c", &ch);
    }
    cls(24);
    pt;pt;cout<<"*************************************************"<<endl;
    pt;pt;cout<<"*\tMinimum Time to cross the bridge: "<<minTime<<" s\t*"<<endl;
    pt;pt;cout<<"*************************************************"<<endl;
    cls(10);
    return 0;
}