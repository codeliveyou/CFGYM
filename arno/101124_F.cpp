#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

const int BASE = 100;

int pow(int x, int p, int m) {
    if (p == 0) return 1;
    int y = pow(x, p / 2, m);
    y = y * y % m;
    if (p&1) y = y * x % m;
    return y;
}

struct longint {
    vector<int> a;
    int s;

    longint(int x = 0) {
        if (x < 0) {
            s = -1; x = -x;
        } else s = 1;
        while (x > 0) {
            a.push_back(x % BASE);
            x /= BASE;
        }
    }

    longint(const longint& x) {
        this->a = x.a;
        this->s = x.s;
    }

    longint(string s) {
        size_t b = 0;
        int bb = BASE;
        while( bb > 1) {
            bb /= 10; b++;
        }

        if (s[0] == '-') {
            this->s = -1; s = s.substr(1);
        } else {
            this->s = 1;
        }
        
        reverse(s.begin(), s.end());

        for (size_t i = 0; i < s.length(); i += b) {
            int r = 0;
            int p = 1;
            for (size_t j = 0; j < b; j++) if (i + j < s.length()) {
                r = r + p* (s[i + j] - '0');
                p *= 10;
            }
            this->a.push_back(r);
        }
    }

    longint operator + (const longint& K) const {
        longint res;
        for (size_t i = 0; i < max(K.a.size(), a.size()); i++) {
            int t = 0;
            if (i < K.a.size()) t += K.a[i];
            if (i <   a.size()) t +=   a[i];
            res.a.push_back(t);
        }
        res.norm();
        return res;
    }

    longint operator - (const longint& K) const {
        longint res;
        for (size_t i = 0; i < max(K.a.size(), a.size()); i++) {
            int t = 0;
            if (i < K.a.size()) t -= K.a[i];
            if (i <   a.size()) t +=   a[i];
            res.a.push_back(t);
        }
        res.norm();
        return res;
    }

    longint operator * (int K) const {
        longint res;
        res.s = this->s;
        if (K < 0) {
            res.s *= -1;
            K *= -1;
        }
        for (size_t i = 0; i < a.size(); i++) res.a.push_back(K * a[i]);
        res.norm();
        return res;
    }

    void norm() {
        for (size_t i = 0; i + 1 < a.size(); i++) {
            a[i] += BASE * BASE * 2;
            a[i+1] -= BASE * 2;
            a[i + 1] += a[i] / BASE;
            a[i] %= BASE;
        }
        while (a.size() && a.back() >= BASE) {
            int t = a.back() / BASE;
            a.back() %= BASE;
            a.push_back(t);
        }
        while (a.size() && a.back() == 0) a.pop_back();
    }

    int mod(int M) const {
        int res = 0;
        for (size_t i = a.size(); i; i--) res = (res * BASE + a[i - 1]) % M;
        if (this->s < 0) res = -res;
        return (res + M)%M;
    }

    bool operator < (const longint& K) const {
        if (a.size() != K.a.size()) return a.size() < K.a.size();
        for (size_t i = a.size(); i; i--)
            if (a[i - 1] != K.a[i - 1]) return a[i - 1] < K.a[i - 1];
        return false;
    }

    bool operator == (const longint& K) const {
        if (a.size() != K.a.size()) return false;
        for (size_t i = 0; i < a.size(); i++)
            if (a[i] != K.a[i]) return false;
        return true;
    }

    string toString() const {
        stringstream str;
        
        if (!a.size()) str << 0; else {
            if (s < 0) str << "-";
            str << a.back();
            for (int i = (int)a.size() - 2; i >= 0; i--) {
                int b = BASE / 10;
                while (b > 1) {
                    if (a[i] < b) str << 0;
                    b /= 10;
                }
                str << a[i];
            }
        }

        return str.str();
    }
};

bool div(longint A, longint B, longint& C) {

    A.norm();
    B.norm();

    int al = (int)A.a.size();
    int bl = (int)B.a.size();
    C.a.resize(al);
    if (al == 0) return true;
    if (bl == 0) return false;

    for (int i = al - 1; i >= 0; i--) {
        int cl = (int)A.a.size() - i;

        bool ok = cl >= bl;
        if (cl == bl) {
            for (int j = cl - 1; j >= 0; j--) 
            {
                if (B.a[j] != A.a[j+i]) {
                    ok = A.a[j+i] > B.a[j];
                    break;
                }
            }
        }

        if (ok) {
            C.a[i]++;
            for (int j = bl - 1; j >= 0; j--) A.a[i+j] -= B.a[j];
            A.norm();
            i++;
        }
    }
    
    if (A.a.size()) 
        return false;

    C.s = A.s * B.s;
    C.norm();
    return true;
}

typedef vector<longint> t_row;
typedef vector<t_row> t_mat;

vector<int> md;
vector< vector<int> > inv;

void update(longint& x, const longint& m, int y, int z) {
    int k = ((y-x.mod(z)) * pow(m.mod(z), z - 2, z) % z + z) % z;
    x = x + m * k;
}

void sign(longint& x, const longint& m) {
    longint y = m - x;
    if (y < x) {
        x = y;
        x.s = -1;
    }
}

longint det(const t_mat& A, t_mat& INV) {
    longint res(0);
    longint mod(1);
    int N = (int)A.size();
    for (size_t i = 0; i < INV.size(); i++) for (size_t j = 0; j < INV[i].size(); j++) INV[i][j] = longint(0);

    for (size_t im = 0; im < md.size(); im++) {
        int M = md[im];
        const vector<int>& I = inv[im];

        vector< vector<int> > a(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                a[i].push_back(A[i][j].mod(M));
            for (int j = 0; j < N; j++)
                a[i].push_back(i==j);
        }

        int D = 1;
        bool bad = false;

        for (int k = 0; k < N; k++) {
            int i0 = -1;
            for (int i = k; i < N; i++) if (a[i][k] != 0) {
                i0 = i;
                break;
            }

            if (i0 < 0) {
                bad = true;
                continue;
            }

            if (k != i0) {
                D = M - D;
                for (size_t j = 0; j < a[k].size(); j++) swap(a[k][j], a[i0][j]);
            }
            a[k][k] = (a[k][k] + M) % M;
            D = D*a[k][k] % M;

            int X = I[a[k][k]];
            for (size_t j = 0; j < a[k].size(); j++) a[k][j] = a[k][j] * X % M;
            
            for (int i = 0; i < N; i++) if (i != k) {
                int X = a[i][k];
                for (size_t j = 0; j < a[i].size(); j++)
                    a[i][j] = (a[i][j] - X * a[k][j]) % M;
            }
        }

        if (bad) continue;

        for (int i = 0; i < N; i++) for (size_t j = 0; j < a[i].size(); j++)
            a[i][j] = (a[i][j] + M) % M;

        update(res, mod, D, M);
        for (size_t i = 0; i < INV.size(); i++) for (size_t j = 0; j < INV.size(); j++)
            update(INV[i][j], mod, (a[i][j+N] * D) % M, M);

        mod = mod * M;
    }

    sign(res, mod);
    for (size_t i = 0; i < INV.size(); i++) for (size_t j = 0; j < INV.size(); j++)
        sign(INV[i][j], mod);

    return res;
}

void solve() {
    int n;
    cin >> n;
    t_mat A(n, t_row(n)), C(n, t_row(n));
    vector< vector<int> > a(n, vector<int>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        cin >> a[i][j];
        A[i][j] = a[i][j];
    }

    string delta;
    cin >> delta;
    longint del(delta);

    longint D = det(A, C);

    if (D.s == del.s && D == del) {
        cout << "1 1 " << a[0][0] << endl;
        return;
    }

    vector< pair<int, int> > pos;
    vector< longint > val;

    longint M(1);
    for (size_t mi = 0; mi < md.size(); mi++) M = M * md[mi];

    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        longint v = M;
        if (del.s < 0) v = v - del; else v = v + del;
        if (D.s < 0) v = v + D; else v = v - D;
        longint w = C[j][i] * a[i][j];
        if (w.s < 0) v = v - w; else v = v + w;

        if (v < M) sign(v, M); else v = v - M;

        longint dv;
        if (div(v, C[j][i], dv)) {
            pos.push_back(make_pair(i, j));
            val.push_back(dv);
        }
    }

    if (pos.size()) {
        cout << pos[0].first + 1 << ' ' << pos[0].second + 1 << ' ' << val[0].toString() << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    int st = 10000;
    while (md.size() < 50) {
        bool ok = true;
        for (int i = 2; i*i <= st; i++) if (st % i == 0) ok = false;
        if (ok) {
            md.push_back(st);
            vector<int> in(st);
            for (int j = 0; j < st; j++) in[j] = pow(j, st - 2, st);
            inv.push_back(in);
        }
        st++;
    }
    solve();
    return 0;
}
