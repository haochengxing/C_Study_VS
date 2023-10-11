#include <iostream>

using namespace std;
int n, m, d;
int w[100][100];
int c[100][100];
int x[100];
int currc[100];
int result[100];
int minx = INT_MAX;
int cp;
int cw;
// bool bound(int t){
// 	int mon=0;
// 	for(int i=1;i<=t;i++){
// 		mon+=c[i][x[i]];
// 		if(mon>d||(mon==d&&t<n)){
// 			return false;
// 		}
// 	}	
// 	return true;
// }
// bool constrant(int t){
// 	int mon=0;
// 	for(int i=1;i<=t;i++){
// 		mon+=w[i][x[i]];
// 		if(mon>=minx){
// 			return false;
// 		}
// 	}
// 	return true;
// }
void backtrack(int t) {
	if (t > n) {
		if (cw < minx) {
			minx = cw;
			for (int i = 1; i < t; i++) {
				result[i] = x[i];
			}
		}
		//		int sum=0;
		//		for(int i=1;i<t;i++){
		//			sum+=w[i][x[i]];
		//		}
		//		if(sum<minx){
		//			minx=sum;
		//			
		//		}
		return;
	}
	for (int i = 1; i <= m; i++) {
		cp += c[t][i];
		cw += w[t][i];
		x[t] = i;
		if (cp <= d && cw < minx) {
			backtrack(t + 1);
		}
		cp -= c[t][i];
		cw -= w[t][i];
	}
}
int test_backtrack() {
	/*cin >> n >> m >> d;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> c[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> w[i][j];
		}
	}*/
	//	for(int i=1;i<=n;i++){
	//		sort(w[i]+1,w[i]+m+1);
	//	}
	//	for(int i=1;i<=n;i++){
	//		for(int j=1;j<=m;j++){
	//			cout<<w[i][j];
	//		}
	//		cout<<endl;
	//	}

	n = 3;
	m = 3;
	d = 4;
	minx = 8;
	c[1][1] = 1;
	c[1][2] = 2;
	c[1][3] = 3;
	c[2][1] = 3;
	c[2][2] = 2;
	c[2][3] = 1;
	c[3][1] = 2;
	c[3][2] = 2;
	c[3][3] = 2;

	w[1][1] = 1;
	w[1][2] = 2;
	w[1][3] = 3;
	w[2][1] = 3;
	w[2][2] = 2;
	w[2][3] = 1;
	w[3][1] = 2;
	w[3][2] = 2;
	w[3][3] = 2;

	backtrack(1);
	cout << minx << endl;
	for (int i = 1; i <= n; i++) {
		cout << result[i] << " ";
	}
	return 0;
}

