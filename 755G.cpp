#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

#define TRACE(x) x
#define WATCH(x) TRACE(cout << #x" = " << x << endl)
#define WATCHR(a, b) TRACE(for (auto it=a; it!=b;) cout << *(it++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end());})

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;

template<typename T> struct FFT {
    int deg;
    vector<int> rev;

    T deg_inv;

    FFT(int _deg, T _deg_inv) {
        assert(__builtin_popcount(_deg) == 1);
        deg = _deg;
        deg_inv = _deg_inv;
        rev.resize(deg);

        for (int i = 1, j = 0; i < deg; i++) {
            int bit = deg / 2;
            for (; j >= bit; bit /= 2)
                j -= bit;
            j += bit;
            rev[i] = j;
        }
    }

    void transform(vector<T> &poly, bool invert) {
        assert(poly.size() == deg);

        for (int i = 1; i < deg; i++)
            if(rev[i] > i)
                swap(poly[i], poly[rev[i]]);

        for (int len = 2; len <= deg; len *= 2) {
            T base = T::unity_root(deg, deg/len * (invert ? -1 : 1));

            for (int i = 0; i < deg; i += len) {
                T w = T::one();

                for (int j = 0; j < len / 2; j++) {
                    T u = poly[i+j];
                    T v = w * poly[i+j+len/2];

                    poly[i+j] = u + v;
                    poly[i+j+len/2] = u - v;

                    w = w * base;
                }
            }
        }

        if(invert) {
            for (int i = 0; i < deg; i++)
                poly[i] = poly[i] * deg_inv;
        }
    }
};

// complex number FFT
struct cnum {
    static constexpr double PI = 2 * atan2(1, 0);
    static constexpr cnum one() { return { 1, 0 }; }

    double a, b;
    cnum operator+(const cnum &c) { return { a + c.a, b + c.b }; }
    cnum operator-(const cnum &c) { return { a - c.a, b - c.b }; }
    cnum operator*(const cnum &c) { return { a*c.a - b*c.b, a*c.b + b*c.a }; }

    // returns x^pow for x such that x^deg = 1, x^(deg-1) != 1
    static cnum unity_root(int deg, int pow) {
        double ang = pow * 2 * PI / deg;
        return { cos(ang), sin(ang) };
    }
}; 

// number theoretic FFT
struct modnum {
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(15);
}

