#include<iostream>
using namespace std;
                   
struct pair_hash {
    size_t operator()(const pair<int,char>& p) const {
        return hash<int>()(p.first) ^ (hash<char>()(p.second) << 1);
    }
};


void solve(){
    int n,m;
    cin>>n>>m;
    vector<string> str(n);
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        cin>>str[i];
    }
    if(n==1){
        cout<<-1<<endl;
        return;
    }
    unordered_map<pair<int,char>, int, pair_hash> mp;
    unordered_map<char,int> sum;
    for(int i=0;i<n;i++){
        for(int j=0;j<str[i].length();j++){
            if(sum.find(str[i][j])==sum.end()){
                    sum[str[i][j]]=0;
            }
            if(mp.find({i+1,str[i][j]})==mp.end()){
                mp[{i+1,str[i][j]}]=1;
                sum[str[i][j]]++;
            }
            else{
                mp[{i+1,str[i][j]}]++;
                sum[str[i][j]]++;
            }
        }
    }
    for(int i=0;i<n;i++){
        int intput=m-1;
        int j=0;
        while(j<str[i].length()){
            if(sum[str[i][j]]==mp[{i+1,str[i][j]}]){
                intput=-1;
                break;
            }
            if((sum[str[i][j]]-2*mp[{i+1,str[i][j]}])>=0){
                j++;
                continue;
            }
            int cnt=m-1;
            int temp=sum[str[i][j]]-mp[{i+1,str[i][j]}];
            if((1LL)*temp*m<mp[{i+1,str[i][j]}]){
                intput=-1;
                break;
            }
            cnt=m-((mp[{i+1,str[i][j]}]+temp-1)/temp);
            // while(mp[{i+1,str[i][j]}]>temp && cnt>0){
            //     cnt--;
            //     temp+=sum[str[i][j]]-mp[{i+1,str[i][j]}];
            // }
            if(cnt<=0){
                intput=0;
                break;
            }
            intput=min(intput,cnt);
            j++;
        }
        ans[i]=intput;
    }
    for(auto k:ans){
        cout<<k<<" ";
    }
    cout<<endl;

}

int main(){
//ios::sync_with_stdio(false);
//→ Disables that sync, making cin/cout faster.
//cin.tie(0);
//→ “Unties” cin from cout. Normally, every cin flushes the cout buffer first — disabling it avoids unnecessary waiting.
   ios::sync_with_stdio(false);
   cin.tie(0);
    solve();
   return 0;
}