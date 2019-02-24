/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("ydist.in", "r", stdin);
FILE *fout = freopen("ydist.out", "w", stdout);

const int MAX_N = 1 + 100000;

/*-------- Input data --------*/
struct Point {
    int x, y;
    int index;

    Point() {}

    Point(const int _x, const int _y, const int _index) {
        this->x = _x;
        this->y = _y;
        this->index = _index;
    }

    bool operator <(const Point &other) const{
        if(1LL * this->x * other.y != 1LL * this->y * other.x) {
            return (1LL * this->x * other.y < 1LL * this->y * other.x);
        } else {
            if(this->index * other.index == 0) {
                return this->index < other.index;
            } else {
                return this->x < other.x;
            }
        }
    }
};

int point_count, line_count;
Point points[MAX_N << 1];
/*-------- Solving events --------*/
int event_count;
int stack_size;
int stack[MAX_N];

double solution[MAX_N];
/*-------- --------*/

void read_input() {
    scanf("%d%d", &point_count, &line_count);
    for(int i = 1; i <= point_count; i++) {
        points[i].index = 0;
        scanf("%d%d", &points[i].x, &points[i].y);
    }
    for(int i = 1; i <= line_count; i++) {
        points[point_count + i].index = i;
        scanf("%d%d", &points[point_count + i].x, &points[point_count + i].y);
    }

    event_count = line_count + point_count;
}

bool larger_slope(const Point p1, const Point p2, const Point q1, const Point q2) {
    int x1 = p2.x - p1.x, y1 = p2.y - p1.y;
    int x2 = q2.x - q1.x, y2 = q2.y - q1.y;

    return (1LL * y1 * x2 >= 1LL * y2 * x1);
}

void solve_events() {
    for(int i = 1; i <= event_count; i++) {
        if(points[i].index == 0) {
            /* avem un nou punct de adaugat la infasuratoare */
            while(stack_size > 0 && points[stack[stack_size]].x >= points[i].x) {
                stack_size --;
            }

            while(stack_size > 1 && larger_slope(points[stack[stack_size - 1]], points[stack[stack_size]],
                                                 points[stack[stack_size]], points[i])) {
                stack_size --;
            }

            stack[++ stack_size] = i;
        } else {
            /* avem un query pe dreapta */
            Point origin = Point(0, 0, 0);
            while(stack_size > 1 && larger_slope(points[stack[stack_size - 1]], points[stack[stack_size]],
                                                 origin, points[i])) {
                stack_size --;
            }

            solution[points[i].index] = (double) points[stack[stack_size]].y -
                                        (double) points[stack[stack_size]].x * points[i].y / points[i].x;
        }
    }
}

void write_output() {
    for(int i = 1; i <= line_count; i++) {
        printf("%.10f\n", solution[i]);
    }
}

int main() {
    read_input();
    sort(points + 1, points + event_count + 1);
    solve_events();
    write_output();

    return 0;
}
