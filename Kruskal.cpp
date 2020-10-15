#include <iostream>

const int maxn = 10, maxm = 20;

struct Canh {
	int u, v, c;
	bool connected;
};

int n, m;
int root[maxn + 1];
Canh canh[maxm + 1];

void init() {
	for (int i = 1; i <= n; i++) root[i] = -1;
	for (int i = 1; i <= m; i++) canh[i].connected = false;
}

void docf() {
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> canh[i].u >> canh[i].v >> canh[i].c;
	}
}

void swap(int tr, int ph) {
	Canh tm;
	tm = canh[tr];
	canh[tr] = canh[ph];
	canh[ph] = tm;
}

void quicksort(int l, int r) {
	if (l > r) return;
	int tr = l, ph = r, gi = canh[(l + r) / 2].c;
	do {
		while (canh[tr].c < gi) tr++;
		while (canh[ph].c > gi) ph--;
		if (tr <= ph) {
			swap(tr, ph);
			tr++;
			ph--;
		}
	} while (tr <= ph);
	quicksort(l, ph);
	quicksort(tr, r);
}

int getRoot(int u) {
	while (root[u] > 0) u = root[u];
	return u;
}

void doUnion(int u, int v) {
	int t = root[u] + root[v];
	if (root[u] > root[v]) {
		root[u] = v;
		root[v] = t;
	}
	else {
		root[v] = u;
		root[u] = t;
	}
}

void kruskal() {
	int t = 0, ru, rv;
	for (int i = 1; i <= m; i++) {
		ru = getRoot(canh[i].u);
		rv = getRoot(canh[i].v);
		if (ru != rv) {
			doUnion(ru, rv);
			t += canh[i].c;
			canh[i].connected = true;
		}
	}
	std::cout << t << std::endl;
	for (int i = 1; i <= m; i++) {
		if (canh[i].connected)
			std::cout << canh[i].u << " " << canh[i].v << std::endl;
	}
}

int main() {
	freopen("file.inp", "r", stdin);
	freopen("file.out", "w", stdout);

	docf();
	init();
	quicksort(1, m);
	kruskal();

	return 0;
}