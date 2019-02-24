/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("praslea.in", "r", stdin);
FILE *fout = freopen("praslea.out", "w", stdout);

const int MAX_N = 1 + 512;
const int MAX_R = 1 + 512;

/*-------- Input data --------*/
int N, risk_max;
int first_time[MAX_N], last_time[MAX_N], strength[MAX_N], risk[MAX_N];
/*-------- Algorithm data --------*/
struct Event {
    int time;
    int index;

    Event(const int _time, const int _index) {
        time = _time;
        index = _index;
    }

    bool operator <(const Event &other) const {
        return this->time < other.time;
    }
};

vector< Event > events;
vector< int > vec;

int knapsack[MAX_R];
bool ok[MAX_R];
long long solution;
/*-------- --------*/

void read_input() {
    scanf("%d%d", &N, &risk_max);
    for(int i = 1; i <= N; i++) {
        scanf("%d%d%d%d", &first_time[i], &last_time[i], &strength[i], &risk[i]);
        events.push_back(Event(first_time[i], i));
        events.push_back(Event(last_time[i] + 1, i));
    }
}

void erase(int value) {
    for(vector< int >::iterator it = vec.begin(); it != vec.end(); it++) {
        if(*it == value) {
            vec.erase(it); return;
        }
    }
}

void reset_knapsack() {
    for(int i = 0; i <= risk_max; i++) {
        knapsack[i] = 0; ok[i] = false;
    }
    ok[0] = true;
}

int run_knapsack() {
    reset_knapsack();

    int answer = 0;
    for(int index : vec) {
        int crt_risk = risk[index];
        int crt_strength = strength[index];

        for(int i = risk_max; i >= crt_risk; i--) {
            if(ok[i - crt_risk] && knapsack[i] < knapsack[i - crt_risk] + crt_strength) {
                ok[i] = true;
                knapsack[i] = knapsack[i - crt_risk] + crt_strength;
                answer = max(answer, knapsack[i]);
            }
        }
    }

    return answer;
}

void process_events() {
    int cursor = 0;
    while(cursor < (int)events.size()) {
        int crt_time = events[cursor].time;

        while(cursor < (int)events.size() && events[cursor].time == crt_time) {
            int index = events[cursor].index;
            if(crt_time == first_time[index]) {
                vec.push_back(index);
            } else {
                erase(index);
            }
            cursor ++;
        }

        int max_strength = run_knapsack();
        if(cursor < (int)events.size()) {
            solution += 1LL * max_strength * (events[cursor].time - events[cursor - 1].time);
        }
    }
}

void write_output() {
    printf("%lld\n", solution);
}

int main() {
    read_input();
    sort(events.begin(), events.end());
    process_events();
    write_output();
    return 0;
}
