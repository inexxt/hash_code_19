#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<int> cur_lst;

unordered_map<string, int> tag_to_id;
unordered_set<int> avail;

int current_max_id = 0;

using INS = vector<int>;

const int MAXN = 9 * 10001;
const int MAXM = 2*51;

int images[MAXN][MAXM];
int sizes[MAXN];
int in_pair[MAXN];
int i_to_s[MAXN];

bool used[MAXN];

int N, M, K = 500;
char ort;
string tag;

inline int sintersection(int s1, int s2) {
    int res = 0;
    for (int i = 0; i < sizes[s1]; i++) {
        int k = images[s1][i];

        for (int j = 0; j < sizes[s1]; j++) {
            int k2 = images[s2][j];

            if (k == k2) {
                res ++;
            }
        }
    }
    return res;
}

inline int sminus(int s1, int s2) {
    int res = sizes[s1];
    for (int i = 0; i < sizes[s1]; i++) {
        int k = images[s1][i];

        for (int j = 0; j < sizes[s1]; j++) {
            int k2 = images[s2][j];

            if (k == k2) {
                res --;
            }
        }
    }
    return res;
}

int calc_score(int i, int j) {
    int s1 = sintersection(i, j);
    int s2 = sminus(i, j);
    int s3 = sminus(j, i);

//    cout << "Score s1 between " << i << " " << j << " is " << s1 << "\n";
//    cout << "Score s2 between " << i << " " << j << " is " << s2 << "\n";
//    cout << "Score s3 between " << i << " " << j << " is " << s3 << "\n";

    return min(s1, min(s2, s3));
}

int score_list(vector<int>& v) {
    int res = 0;
    for (int i = 0; i<v.size()-1; i++) {
        res += calc_score(i, i+1);
    }
    return res;
}

int num_transitions;

int cout_list() {
    cout << num_transitions << "\n";

    for (auto k: cur_lst) {
        if (in_pair[k] != -1) {
            cout << k << " " << in_pair[k] << "\n";
        } else {
            cout << k << "\n";
        }
    }
}

int prev_V = -1;

void maybe_add_tag(int tag_id, int pv) {
    for (int k = 0; k < sizes[pv]; k++) {
        if (images[pv][k] == tag_id) {
            return;
        }
    }

    images[pv][sizes[pv]++] = tag_id;
}

int identify_tag(string& tag) {
    if (tag_to_id.find(tag) == tag_to_id.end()) {
        tag_to_id[tag] = current_max_id++;
    }
    return tag_to_id[tag];
}

void input_data(int i) {
    if (ort == 'V' && prev_V == -1) {
        prev_V = i;
    }

    cin >> sizes[i];
    avail.insert(i);

    for (int j = 0; j<sizes[i]; j++) {
        cin >> tag;
        int id = identify_tag(tag);

        images[i][j] = id;
    }
}

int main() {
    cin >> N;

    for (int i = 0; i<N; i++) {
        in_pair[i] = -1;
    }

    for (int i = 0; i<N; i++) {
        cin >> ort;

        if (ort == 'V' && prev_V != -1) {
            int size;
            cin >> size;

            in_pair[prev_V] = i;
            used[i] = 1;

            for (int j = 0; j<size; j++) {
                cin >> tag;
                int id = identify_tag(tag);
                maybe_add_tag(id, prev_V);
            }
            prev_V = -1;
        } else {
            input_data(i);
        }
    }

    num_transitions = avail.size();

    cur_lst.push_back(0);
    used[0] = 1;
    avail.erase(0);

//    cout << "Tras " << num_transitions << "\n";

    for (int i = 0; i<num_transitions-1; i++) {

        int max_score = -1;
        int max_score_arg = -1;

        if (i % 100 == 0) {
            cerr << "Current list at step " << i << "\n";
//            cout_list();
        }

        for (int j = 0; j<K; j++) {
            int rr = rand() % N;

            if (!used[rr]) {
                int score = calc_score(cur_lst.back(), rr);
//                cout << "Score between " << cur_lst.back() << " " << rr << " is " << score << "\n";
                if (score >= max_score) {
                    max_score_arg = rr;
                    max_score = score;
                }
            }
        }

        if (max_score_arg == -1) {
//            if (avail.)
            max_score_arg = *avail.begin();
            max_score = calc_score(cur_lst.back(), max_score_arg);
        }

//        cout << "max_score_arg " << max_score_arg << "\n";
        avail.erase(max_score_arg);
        used[max_score_arg] = 1;
        cur_lst.push_back(max_score_arg);
    }

    cout_list();

    cerr << "\n";
    cerr << "Score is " << score_list(cur_lst) << "\n";
    return 0;
}