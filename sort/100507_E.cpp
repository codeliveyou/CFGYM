#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-9;
const double pi = atan2(0., -1.);

bool doubleEqual(double x, double y)
{
	return fabs(x - y) < eps;
}
bool doubleLess(double x, double y)
{
	return x < y && !doubleEqual(x, y);
}
bool doubleLessOrEqual(double x, double y)
{
	return x < y || doubleEqual(x, y);
}
bool doubleGreater(double x, double y)
{
	return x > y && !doubleEqual(x, y);
}
bool doubleGreaterOrEqual(double x, double y)
{
	return x > y || doubleEqual(x, y);
}

double sqr(double x)
{
	return x * x;
}
double mySqrt(double x)
{
	if (doubleLess(x, 0) )
		throw 42;
	if (x < 0)
		return 0;
	return sqrt(x);
}

double my_atan2(double x, double y)
{
	double ans = atan2(x, y);
	//if (ans < 0)
	//	ans = 2. * pi + ans;
	return fabs(ans);
}

struct Point
{
	double x, y, z;
	Point() : x(), y(), z() {}
	Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	Point operator + (Point A) { return Point(x + A.x, y + A.y, z + A.z); }
	Point operator - (const Point &A) const { return Point(x - A.x, y - A.y, z - A.z); }
	Point operator * (double a) { return Point(x * a, y * a, z * a); }
	Point operator / (double a) { return Point(x / a, y / a, z / a); }
	double operator % (const Point &A) const { return x * A.x + y * A.y + z * A.z; }
	Point operator * (Point A) { return Point(
			y * A.z - z * A.y,
			z * A.x - x * A.z,
			x * A.y - y * A.x
			); }
	double length() { return mySqrt(*this % *this); }
	double distTo(const Point &A) const { return (*this - A).length(); }
	Point normalize(double l = 1.)
	{
		double len = length();
		if (doubleEqual(len, 0.) )
			throw 42;
		return *this * (l / len);
	}
	Point projectOnPlane(Point A, Point n)
	{
		Point v = (*this - A);
		double d = v % n;
		return *this - n * d;
	}

	bool operator == (const Point &A) const
	{
		return doubleEqual(distTo(A), 0.);
	}
	void read()
	{
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	void print()
	{
		fprintf(stderr, "%.10lf %.10lf %.10lf\n", x, y, z);
	}
};

Point getNByStart(Point O, Point S, Point v)
{
	return (v * (O - S) ).normalize();
}

void getNewStart(Point O1, Point O2, Point S, Point v, Point &T, Point &u)
{
	Point n = getNByStart(O1, S, v);
	double R = O1.distTo(S);
	Point O2_ = O2.projectOnPlane(O1, n);
	Point dir = (O2_ - O1).normalize(R);
	

	T = O1 + dir;
	u = (n * dir).normalize(); // check sign
}

struct Arc
{
	const static int tpiter = 100;//200;
	const static int bpiter = 100;
	Point O, S, T, n;
	Arc() : O(), S(), T(), n() {}
	Arc(Point _O, Point _S, Point _T, Point _n) : O(_O), S(_S), T(_T), n(_n) 
	{
		n = n.normalize();
	}

	double getR()
	{
		return O.distTo(S);
	}

	double getLen()
	{
		double sinaRR = ( (S - O) * (T - O) ) % n;
		double cosaRR = (S - O) % (T - O);
		double angle = my_atan2(sinaRR, cosaRR);
//		fprintf(stderr, "angle = %.10lf\n", angle);
		return angle * getR();
	}

	Point getSomePoint(double x)
	{
		double R = getR();
		Point v = (S - O) * (1. - x) + (T - O) * x;
		return O + v.normalize(R);
	}

	Point getMidPoint()
	{
		Point v = (T - S) * n;
		if (v.length() < eps)
			return S;
		return O + v.normalize(getR() );
	}

	Point getLowerPoint()
	{
		double l = 0, r = 1;
		for (int i = 0; i < tpiter; i++)
		{
			double m1 = (2 * l + r) / 3.;
			double m2 = (l + 2 * r) / 3.;
			Point M1 = getSomePoint(m1); 
			Point M2 = getSomePoint(m2);
			if (M1.z < M2.z)
				r = m2;
			else
				l = m1;
		}
		return getSomePoint(l);
	}
	
	Point getUpperPoint()
	{
		double l = 0, r = 1;
		for (int i = 0; i < tpiter; i++)
		{
			double m1 = (2 * l + r) / 3.;
			double m2 = (l + 2 * r) / 3.;
			Point M1 = getSomePoint(m1); 
			Point M2 = getSomePoint(m2);
			if (M1.z > M2.z)
				r = m2;
			else
				l = m1;
		}
		return getSomePoint(l);
	}

	double _getGreater3(double h)
	{
		if (S == T)
			return 0.;

//		print();
		if (S.z > T.z)
		{
			swap(S, T);
			n = Point() - n;
		}
		double l = 0, r = 1;
		for (int i = 0; i < bpiter; i++)
		{
			double m = (l + r) / 2.;
			Point M = getSomePoint(m);
			if (M.z < h)
				l = m;
			else
				r = m;
		}
		double ans = Arc(O, getSomePoint(l), T, n).getLen();
		return ans;
	}
	double _getGreater2(double h)
	{
		if (S == T)
			return 0.;
		Point M = getUpperPoint();
		Arc left = Arc(O, S, M, n);
		Arc right = Arc(O, M, T, n);
		return left._getGreater3(h) + right._getGreater3(h);
	}

	double _getGreater1(double h)
	{
		if (S == T)
			return 0.;
//		print();
		Point M = getLowerPoint();
		Arc left = Arc(O, S, M, n);
		Arc right = Arc(O, M, T, n);
		double answer = left._getGreater2(h) + right._getGreater2(h);
//		fprintf(stderr, "%.10lf\n", answer);
		return answer;
	}

	double getGreater(double h, int cnt = 2)
	{
		if (cnt == 0)
			return _getGreater1(h);
		Point M = getMidPoint();
		Arc left = Arc(O, S, M, n);
		Arc right = Arc(O, M, T, n);
		return left.getGreater(h, cnt - 1) + right.getGreater(h, cnt - 1);
	}

	void print()
	{
		fprintf(stderr, "\n-------- printing Arc -------\n");
		O.print();
		S.print();
		T.print();
		n.print();
		fprintf(stderr, "\n\n");
	}
};

const int maxn = 1005;
Point Mid[maxn];
//Point P[maxn];
//Point dir[maxn];

Arc arc[maxn];


int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
    int tt;
    scanf("%d", &tt);

    for (int ii = 0; ii < tt; ++ii) {

        const int n = 3;
	    double v, g;
    	scanf("%lf%lf", &v, &g);
	
    	Point P = Point();
	    Point dir = Point(0, 0, 1);

    	for (int i = 0; i < n; i++)
	    	Mid[i].read();

    	for (int i = 0; i < n - 1; i++)
	    {
		    Point nP, ndir;
    		getNewStart(Mid[i], Mid[i + 1], P, dir, nP, ndir);
	    	arc[i] = Arc(Mid[i], P, nP, getNByStart(Mid[i], P, dir) );
		    P = nP;
    		dir = ndir;

    //		arc[i].print();
	    }
    	Point lastN = getNByStart(Mid[n - 1], P, dir);
	    arc[n - 1] = Arc(Mid[n - 1], P, Mid[n - 1] * 2 - P, lastN);
    	arc[n] = Arc(Mid[n - 1], Mid[n - 1] * 2 - P, P, lastN);
    //	arc[n - 1].print();
    //  arc[n].print();

    	double H = sqr(v) / 2. / g;

    //	fprintf(stderr, "H = %.10lf\n", H);

	    double answer = 0;
    	for (int i = 0; i < n + 1; i++)
	    {
    //		fprintf(stderr, "i = %d\n", i);
	    	double curans = arc[i].getGreater(H);
		    answer += curans;
    //		fprintf(stderr, "\ni = %d answer = %.10lf\n", i, curans);
	    }
    	printf("%.20lf\n", answer);
    }

	return 0;
}
?
