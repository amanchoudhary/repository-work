#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include <bitset>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <map>
#include <cassert>
#define mod 1000000009
#define ull unsigned long long
#define ill long long int
#define pii pair<int,int>
#define pb(x) push_back(x)
#define F(i,a,n) for(i=(a);i<(n);++i)
#define FD(i,a,n) for(i=(a);i>=(n);--i)
#define FE(it,x) for(it=x.begin();it!=x.end();++it)
#define V(x) vector<x>
#define S(x) scanf("%d",&x)
#define S1(x) scanf("%lld",&x)
#define epsilon 0.000001

using namespace std;


#define REP(i,a,b) for(typeof(a) i=(a);i<(b);i++)
#define ll long long int
#define ii pair<int,int>
#define CLEAR(x,val) memset(x,val,sizeof(x))
#define SZ(v) (v).size()
#define N 500006

char str[N];                        //  input
int rr[N], pos[N];                //  output
int cnt[N], nn[N];                //internal
bool bh[N], b2h[N];

// Compares two suffixes according to their first characters
bool smaller_first_char (int a, int b){
  return str[a] < str[b];
}

void suffixSort(int n)
{
  //sort suffixes according to their first characters
    for (int i=0; i<n; ++i){
        pos[i] = i;
    }
    sort(pos, pos + n, smaller_first_char);
    //{pos contains the list of suffixes sorted by their first character}

    for (int i=0; i<n; ++i){
        bh[i] = i == 0 || str[pos[i]] != str[pos[i-1]];
        b2h[i] = false;
    }

    for (int h = 1; h < n; h <<= 1){
        //{bh[i] == false if the first h characters of pos[i-1] == the first h characters of pos[i]}
        int buckets = 0;
        for (int i = 0, j; i < n; i = j){
            j = i + 1;
            while (j < n && !bh[j]) j++;
                nn[i] = j;
                buckets++;
            }
            if (buckets == n) break; // We are done! Lucky bastards!
            //{suffixes are separted in buckets containing strings starting with the same h characters}

            for (int i = 0; i < n; i = nn[i]){
                cnt[i] = 0;
                for (int j = i; j < nn[i]; ++j){
                    rr[pos[j]] = i;
                }
            }

            cnt[rr[n - h]]++;
            b2h[rr[n - h]] = true;
            for (int i = 0; i < n; i = nn[i]){
                for (int j = i; j < nn[i]; ++j){
                    int s = pos[j] - h;
                    if (s >= 0){
                        int head = rr[s];
                        rr[s] = head + cnt[head]++;
                        b2h[rr[s]] = true;
                    }
                }
                for (int j = i; j < nn[i]; ++j){
                    int s = pos[j] - h;
                    if (s >= 0 && b2h[rr[s]]){
                        for (int k = rr[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
                    }
                }
            }
            for (int i=0; i<n; ++i){
                pos[rr[i]] = i;
                bh[i] |= b2h[i];
            }
    }

    for (int i=0; i<n; ++i){
        rr[pos[i]] = i;
    }
}
// End of suffix array algorithm


// Begin of the O(n) longest common prefix algorithm
// Refer to "Linear-Time Longest-Common-Prefix Computation in Suffix
// Arrays and Its Applications" by Toru Kasai, Gunho Lee, Hiroki
// Arimura, Setsuo Arikawa, and Kunsoo Park.

int height[N];

// height[i] = length of the longest common prefix of suffix pos[i] and suffix pos[i-1]
// height[0] = 0

void getHeight(int n)
{
    for (int i=0; i<n; ++i) rr[pos[i]] = i;
    height[0] = 0;

    for (int i=0, h=0; i<n; ++i){
        if (rr[i] > 0){
            int j = pos[rr[i]-1];
            while (i + h < n && j + h < n && str[i+h] == str[j+h]) h++;
            height[rr[i]] = h;
            if (h > 0) h--;
        }
    }
}
// End of lcp part

int get (int n, int x)
{
    if (x == 0) {
        return 0;
    }
    int sum,i;
    sum = 0;
    F (i, 0, n) {
        if (i+x > n) {
            sum = sum + (n-i);
            continue;
        }
        sum = sum + x;
    }

    //cout << x << " " << sum << endl;

    return sum;
}

int main()
{
    freopen ("input.txt", "r", stdin);
    int t;
    int ix;
    ix = 1;
    S (t);
    while (t--) {

        printf ("Case %d: ", ix++);
        scanf ("%s", str);
        int i,sum=0,n = strlen (str),a,b;

        S (a);      S(b);

        suffixSort(n);
        getHeight(n);

 
        sum = get (n, b) - get (n, a-1);

        F (i, 1, n) {
            int xx = height[i];
            if (xx >= a) {
                xx = min (xx, b);
                int yy = xx-a+1;
                sum = sum - yy;
            }
        }
        printf ("%d\n", sum);

    }

    return 0;
}




// problem: http://www.lightoj.com/volume_showproblem.php?problem=1314