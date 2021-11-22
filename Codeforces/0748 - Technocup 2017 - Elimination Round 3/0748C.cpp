#include <bits/stdc++.h>
using namespace std;
//Compiler version g++ 6.3.0

int main() {
	int n, ans = 0;
	string s;
	cin >> n >> s;
	
	int op1 = 0, op2 = 0;
	map<char, int> mp{
		{'L', 1}, {'U', 2}, {'R', 3}, {'D', 4}
	};
	
	for (int i = 0; i < n; ++i) {
		int tmp = mp[s[i]];
		if (op1 == 0) {
			op1 = tmp;
		}
		else if (op1 != tmp and op2 == 0) {
			if (~(op1 ^ tmp) & 1) ++ans, op1 = tmp;
			else op2 = tmp;
		}
		else if (op1 != tmp and op2 != tmp) {
			++ans, op1 = tmp, op2 = 0;
		}
		// cout << op1 << " " << op2 << "\n";
	}
	
	if (op1) ++ans;
	
	cout << ans << "\n";
	
	return 0;
}