#include <iostream>
using namespace std;

class Patient {
  public:
	int index;
	int a;
	int s;
	int f;
	int w;
	int p;
	bool arrived = 0;
};


int main() {
	const int MAXN = 101;
	int n;
   	cin >> n;

	Patient people[MAXN];

	for (int i = 1; i <= n; ++i) {
		people[i].index = i;
		cin >> people[i].a;
	}

	for (int i = 1; i <= n; ++i) {
		cin >> people[i].s;
	}
	
	int k, t;
	char temp;
	cin >> k >> temp >> t;


	bool is_watching = 0;
	Patient* watching = nullptr;
	Patient* next_arrival = people + 1;
	Patient* next_watch = people + 1;
	int cur_time = 0;
	int xt = -1;

	while (next_watch) {
		int p = next_arrival->index - next_watch->index + is_watching + next_arrival->arrived;
		if (cur_time == t) xt = p;

		// 看完
		if (is_watching && cur_time >= watching->f) {
			watching->f = cur_time;
			is_watching = 0;
			watching = nullptr;
		}

		// arrival
		if (next_arrival && !next_arrival->arrived && cur_time >= next_arrival->a) {
			next_arrival->arrived = true;
			next_arrival->p = p;
			if (next_arrival->index != n) {
				next_arrival++;
			}
		}

		// 叫號
		if (!is_watching && next_watch && next_watch->arrived) {
			// cerr<< "登～登" << cur_time << " " << next_watch->index << endl;

			watching = next_watch;
			if (next_watch->index != n) {
				next_watch++;
			} else {
				next_watch = nullptr;
			}
			watching->w = cur_time - watching->a;
			watching->f = cur_time + watching->s;
			is_watching = 1;
		}
		cur_time++;
	}
	
	cout << people[k].f << ",";
	cout << people[k].w << ",";
	cout << people[k].p << ",";
	if (xt < 0) {
		if (t > people[n].f) xt = 0;
		else xt = 1;
	}
	cout << xt << endl;
}
