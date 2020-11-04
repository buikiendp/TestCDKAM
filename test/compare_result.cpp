#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FO(i,a,b) for(int i=a;i<b;i++)
#define FORD(i,a,b) for(int i=a;i>=b;i--)
#define DEBUG(a) {cerr << #a << ": " << (a) << endl; fflush(stderr); }
//#define REP(i,n) for (int i=0; i<(n); ++i)
using namespace std;
template<class T> string i2s(T x) {ostringstream o; o << x; return o.str();}
typedef pair<LL, LL> II;
typedef pair<string, int> IIS;




const int Kmer = 25, DIST = 25;
vector<II> V;
map<II, int> M;
int testSpecies[3000005], testGenus[3000005];
int nameFamily[3000005], nameGenus[3000005];
IIS parent[3000001];
int total, TP, FP, FN, TN, VP;
double PRE, SEN, F1;



vector<string> tokenizeNode(const string& row) {
    vector<string> tokens;
    for(int i=0, pos=0, n=row.size(); i<n; ++i) {
        if(i==n-1 || row[i+1]=='|') {
            string token = row.substr(pos, (i+1)-pos);
            tokens.push_back(token);
            pos = i+2;
        }
    }
    return tokens;
}

vector<string> tokenize(const string& row) {
    vector<string> tokens;
    for(int i=0, pos=0, n=row.size(); i<n; ++i) {
        if(i==n-1 || row[i+1]=='\t' || row[i+1]==' ' || row[i+1]==',') {
            string token = row.substr(pos, (i+1)-pos);
            tokens.push_back(token);
            pos = i+2;
        }
    }
    return tokens;
}

int toNum(string s){
    if(s == "NA" || s == "UNKNOWN") return -1;
    int ans = 0;
    FO(i,0,s.size()) ans = ans*10 + s[i] - 48;
    return ans;
}

int findFamily(int taxa){
    if(taxa == -1) return -1;
    int st = taxa;
    while(st != 131567){
        if(st <= 2 ) break;
        if(parent[st].fi == "family") return st;
        st = parent[st].se;
    }
    return taxa;
}

int findGenus(int taxa){
    if(taxa == -1) return -1;
    int st = taxa;
    while(st != 131567){
        if(st <= 2 ) break;
        if(parent[st].fi == "genus") return st;
        st = parent[st].se;
    }
    return taxa;
}

int findSpecies(int taxa){
    if(taxa == -1) return -1;
    int st = taxa;
    while(st != 131567){
        if(st <= 2 ) break;
        if(parent[st].fi == "species") return st;
        st = parent[st].se;
    }
    return taxa;
}

void print_ans(){
    //FP = total - TP - TN - FN;
	SEN = 1.0*TP / (TP+FN+FP+VP);
	PRE = 1.0*TP / (TP+FP);
	F1 = 2*SEN*PRE / (SEN + PRE) * 100;

	cerr << TP << " " << FP << " " << FN << " " << TN << " VP = " << VP <<  "\t" << SEN << " " << PRE << " " << F1 << endl;
}

void count_kraken_species(string file){
    ifstream fin2(file.c_str());
    string s;
	total = 0;	TP = 0;  FP = 0; FN = 0; TN = 0; VP = 0;
	while(getline(fin2,s)){
        total++;
        vector<string> V = tokenize(s);
        if(V[0] == "U") {
            if(testSpecies[total] == 0)
                TN++;
            else
                FN++;
        }
        else {
            int taxa = toNum(V[2]);
            if(findSpecies(taxa) == testSpecies[total]){
                TP++;
            }
            else if(findSpecies(taxa) == testGenus[total])
                VP++;
            else
                FP++;
        }
	}
	fin2.close();
	cerr << "Species level, total reads = " << total << endl;
	print_ans();
}

void count_kraken_genus(string file){
    ifstream fin2(file.c_str());
    string s;
	total = 0;	TP = 0;  FP = 0; FN = 0; TN = 0; VP = 0;
	int cntFamily = 0;
	while(getline(fin2,s)){
        total++;
        vector<string> V = tokenize(s);
        if(V[0] == "U") {
            if(testSpecies[total] == 0)
                TN++;
            else
                FN++;
        }
        else {
            int taxa = toNum(V[2]);
            if(taxa == findFamily(taxa)) cntFamily++;
            if(findGenus(taxa) == testGenus[total] || findSpecies(taxa) == testSpecies[total]){
                TP++;
            }
            else
                FP++;
        }
	}
	fin2.close();
	cerr << "Genus level, total reads = " << total << endl;
	print_ans();
}

void count_CDKAM_species(string file){
    ifstream fin2(file.c_str());
    string s;
	total = 0;	TP = 0;  FP = 0; FN = 0; TN = 0; VP = 0;
    int stt, taxa, len, hit;
	while(fin2 >> s >> len >> taxa){
        total++;
        if(taxa == -1) {
            if(testSpecies[total] == 0)
                TN++;
            else
                FN++;
        }
        else {
            if(findSpecies(taxa) == testSpecies[total]){
                TP++;
            }
            else if(findSpecies(taxa) == testGenus[total])
                VP++;
            else
                FP++;
        }
	}
	fin2.close();
	cerr << "Species level, total reads = " << total << endl;
	print_ans();
}

void count_CDKAM_genus(string file){
    ifstream fin2(file.c_str());
    string s;
	total = 0;	TP = 0;  FP = 0; FN = 0; TN = 0; VP = 0;
    int stt, taxa, len, hit;
	while(fin2 >> s >> len >> taxa){
        total++;
        if(taxa == -1) {
            if(testSpecies[total] == 0)
                TN++;
            else
                FN++;
        }
        else {
            if(findGenus(taxa) == testGenus[total] || findSpecies(taxa) == testSpecies[total]){
                TP++;
            }
            else
                FP++;
        }
	}
	fin2.close();
	cerr << "Genus level, total reads = " << total << endl;
	print_ans();
}

int main(){
    ifstream fin("input.fasta"); //  test2error0.fasta    test3length1000.fasta
    ifstream fin3("../CDKAM/DTB/taxonomy/nodes.dmp");


    FOR(i,1,3000000) parent[i] = IIS("",0);
    string t;
    while(getline(fin3, t)){
        vector<string> V = tokenizeNode(t);
        FOR(i,0,2) V[i].erase(V[i].size()-1,1);
        FOR(i,1,2) V[i].erase(0, 1);
        int u = toNum(V[0]);
        int v = toNum(V[1]);
        parent[u] = IIS(V[2], v);
    }

    DEBUG("NODES");


    string genID, id, s, seq;
    int cnt = 0;
    while(getline(fin,id)){
        cnt++;
        getline(fin, seq);
        vector<string> V = tokenize(id);
        testGenus[cnt] = toNum(V[5]);
        testSpecies[cnt] = toNum(V[6]);
	}
	fin.close();

    cerr << "CDKAM result" << endl;
    count_CDKAM_genus   ("out_CDKAM.txt");
    count_CDKAM_species ("out_CDKAM.txt");

    cerr << endl << "Kraken2 result" << endl;
    count_kraken_genus  ("out_kraken.txt");
    count_kraken_species("out_kraken.txt");


	return 0;
}
