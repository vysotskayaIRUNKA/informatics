/*#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto i = 0; i < n; i++) {
    cin >> v[i];
  }
  for (auto i = v.rbegin(); i != v.rend(); i++) {
    cout << *i << ' ';
  }
}*/

/*#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> v1(n), v2(n);
  for (auto i = 0; i < n; i++) {
    cin >> v1[i];
  }
  for (auto i = 0; i < n; i++) {
    cin >> v2[i];
  }
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  cout << boolalpha << (v1 == v2) << endl;
}*/

/*#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
  int n;
  cin >> n;
  vector<int> s1(n), s2(n);
  for (int i = 0; i < n; i++) {
    cin >> s1[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> s2[i];
  }
  vector<int> s = s1;
  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());
  vector<int> intersect;
  set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                   back_inserter(intersect));
  for (auto i : s) {
    auto bebebe = find(intersect.begin(), intersect.end(), i);
    if (bebebe != intersect.end()) {
      cout << i << " ";
      intersect.erase(bebebe);
    }
  }
}*/

/*#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n, k;
  cin >> n;
  vector<int> v(n);
  for (auto i = 0; i < n; i++)
    cin >> v[i];
  cin >> k;
  auto i = 0lu;
  while (i < v.size()) {
    if (v[i] > k) {
      v.erase(v.begin() + i);
    }
    else
      i++;
  }
  for (auto i : v)
    cout << i << " ";
}*/

/*#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> v(n);
  vector<int> chet, nechet;
  for (auto i = 0; i < n; i++) {
    cin >> v[i];
    if (v[i] % 2 == 0)
      chet.push_back(v[i]);
    else
      nechet.push_back(v[i]);
  }
  sort(chet.rbegin(), chet.rend());
  sort(nechet.begin(), nechet.end());
  int i = 0, j = 0;
  for (auto k = 0; k < n; k++) {
    if (v[k] % 2 == 0) {
      cout << chet[i] << " ";
      i++;
    }
    else {
      cout << nechet[j] << " ";
      j++;
    }
  }
}*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
	float n, n_bebebe, sum = 0;
	cin >> n;
	n_bebebe = n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	int counter = 0;
	float sum_h = 0;
	for (auto i = 0; i < n; i++) {
		if (v[i] > 5) {
			counter++;
			sum_h += v[i];
		}
		else {
			if (counter >= 6) {
				sum += sum_h;
			}
			else {
				n_bebebe -= counter;
			}
			sum_h = 0;
			counter = 0;
		}
	}
	cout << fixed << setprecision(1) << sum / n_bebebe << endl;
}
