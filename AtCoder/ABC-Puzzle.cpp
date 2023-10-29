#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 1e18

const ll P = 29, N = 2e5 + 50, mod = 1e9 + 7;

bool flag;
string a, b;
unordered_map<ll, bool> vis;
ll n, grid[6][6], mask, row[6][6], col[6][6], topRow[6], topCol[6];

ll isOk() {
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < n; j++) {
      if (grid[i][j] == 0) { continue; }
      if (topRow[i] == 0) { topRow[i] = grid[i][j]; }
      if (topCol[j] == 0) { topCol[j] = grid[i][j]; }
      row[i][grid[i][j]]++; 
      col[j][grid[i][j]]++;
    }
  }
  ll ok = 1;
  for (ll i = 0; i < n; i++) {
    for (ll j = 1; j <= 3; j++) {
      if (row[i][j] > 1 or col[i][j] > 1) { ok = -1; }
      ok = min({ok, row[i][j], col[i][j]});
      row[i][j] = col[i][j] = 0;
    }
    if ((topRow[i] != 0 and topRow[i] != (a[i] - 'A' + 1)) or (topCol[i] != 0 and topCol[i] != (b[i] - 'A' + 1))) {
      ok = -1;
    }
    topRow[i] = topCol[i] = 0;
  }
  return ok;
}

void solve() {
  if (vis[mask] or flag) { return; }
  vis[mask] = 1;
  ll ok = isOk();
  if (ok == -1) { return; }
  if (ok) {
    flag = 1;
    cout << "Yes\n";
    for (ll i = 0; i < n; i++) {
      for (ll j = 0; j < n; j++) {
        if (grid[i][j] == 0) cout << ".";
        else {
          char ch = (grid[i][j] - 1) + 'A';
          cout << ch;
        }
      }
      cout << "\n";
    }
    return;
  }
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < n; j++) {
      if (grid[i][j] != 0) continue;
      ll prev = grid[i][j];
      for (ll k = 1; k <= 3; k++) {
        grid[i][j] = k;
        mask += (k << (2 * ((n * i) + j)));
        solve();
        if (flag) { return; }
        mask -= (k << (2 * ((n * i) + j)));
      }
      grid[i][j] = prev;
    }
  }
}

int main() {
  //freopen("input.txt", "r", stdin);
  //ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

  ll t = 1;
  for (ll T = 1; T <= t; T++) {
    cin >> n >> a >> b;
    solve();
    if (!flag) cout << "No\n";
  }
  return 0;
}



