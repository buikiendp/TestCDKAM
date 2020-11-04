#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define fi first
#define se second
#define PB push_back
#define mp make_pair
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FO(i,a,b) for(int i=a;i<b;i++)
#define FORD(i,a,b) for(int i=a;i>=b;i--)
#define DEBUG(a) {cerr << #a << ": " << (a) << endl; fflush(stderr); }

using namespace std;
template<class T> string i2s(T x) {ostringstream o; o << x; return o.str();}
typedef pair<int, int> II;

ifstream fin("targets.txt");
ofstream fout("input.fasta");

inline char print_code(int c) {
  if (c == 0) return 'A';
  if (c == 1) return 'T';
  if (c == 2) return 'C';
  if (c == 3) return 'G';
  return 'N';
}

vector<string> tokenize(const string& row) {
    vector<string> tokens;
    for(int i=0, pos=0, n=row.size(); i<n; ++i) {
        if(i==n-1 || row[i+1]==' ') {
            string token = row.substr(pos, (i+1)-pos);
            tokens.push_back(token);
            pos = i+2;
        }
    }
    return tokens;
}

string add_noise(string t, int subLength, int errorRate){
	string ans = "";
	int numDI = 4*errorRate*subLength / 1000; /// insert, delete
	int numFF = 6*errorRate*subLength / 1000; /// replace
	for(int i = 0; i < t.size(); i += subLength){
        string s = t.substr(i, subLength);
		set<int> S;
		FOR(step,1,100) {
			if(S.size() == numFF) break;
			S.insert(rand()%subLength);
		}
		for(auto pos : S){
			char c = s[pos];
			while(c == s[pos]){
				s[pos] = print_code(rand()%4);
			}
		}

        int num_delete = rand()%numDI;
        FOR(step, 1, num_delete){
            int pos = rand()%(int)s.size();
            s.erase(pos, 1);
        }
        FOR(step,1,numDI-num_delete){
            int pos = rand()%(int)s.size();
            char c = print_code(rand()%4);
            s.insert(s.begin()+pos, c);
        }
        ans += s;
	}
	return ans;
}

const int maxn = 20000;
int cntFiles = 0;
string file[maxn], taxa[maxn];
set<string> S;
int cntID = 0, Kmer = 31;
LL full_length = 0;

void solve(const string &genome, const string taxa, int readLength, int errorRate){
    int maxx = genome.size();
	FOR(i,1,10000){
	    cntID++;
        LL pos = 1LL*rand()*rand() % (maxx - 4001);
        string tmp = genome.substr(pos, 4000);
        FO(i,0,tmp.size()) if(tmp[i] == 'x') tmp[i] = 'A';
//        fout << ">ide" << cntID << " " << taxa << endl;
//        fout << tmp.substr(0,1000) << endl;
        string tmp2 = add_noise(tmp, 500, errorRate);
        fout << ">ide" << cntID << " " << taxa << endl;
        fout << tmp2.substr(0,readLength) << endl;
	}

}

void generate_data() {
    int id;
    string genome = "";
    while(1) {
        id = rand()%cntFiles + 1;
        ifstream fin(file[id].c_str());
        genome = "";
        string s, genID;
        getline(fin,genID);
        while(getline(fin,s)){
            if(s[0] == '>') break;
            genome += s;
        }
        fin.close();
        int maxx = genome.size();
        if(maxx > 10000) break;
    }

    int readLength = 1000, errorRate = 18;
	cerr << "id = " << id << " " << genome.size() << endl;
	cerr << file[id] << " " << taxa[id] << endl;
	cerr << "readLength = " << readLength << "  errorRate = " << errorRate << endl;
    solve(genome, taxa[id], readLength, errorRate);
}



int main(){
	srand(time(0));
	string s, t[8];

	while(fin >> s){
		cntFiles++;	//if(cntFiles == 5) break;
		file[cntFiles] = "../CDKAM/" + s;
		//cerr << file[cntFiles] << endl;
		FOR(i,1,7) fin >> t[i];
		if(t[1] != "-1" && t[2] != "UNKNOWN"){
			taxa[cntFiles] = t[7] + ' ' + t[6] + ' ' + t[5] + ' ' + t[4] + ' ' + t[3] + ' ' + t[2] + ' ' + t[1];
		}
	}

    generate_data();


	return 0;
}
