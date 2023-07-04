#include<bits/stdc++.h>
using namespace std;
using DO = double;

const DO pi = acos(-1);

struct Point3 {
	DO x, y, z;
	Point3(DO x = 0, DO y = 0, DO z = 0) : x(x), y(y), z(z) {}
	Point3 operator + (const Point3 & a) const {
		return Point3(x + a.x, y + a.y, z + a.z);
	}
	Point3 operator - (const Point3 & a) const {
		return Point3(x - a.x, y - a.y, z - a.z);
	}
	DO operator * (const Point3 & a) const {
		return x * a.x + y * a.y + z * a.z;
	}
	void print() {
		printf("%.10lf %.10lf %.10lf\n", x, y, z);
	}
};

void generate_by_rotate(DO & x, DO & y, DO t) {
	DO si = sin(t);
	DO co = cos(t);
	DO tx = x * si + y * co;
	DO ty = x * -co + y * si;
	x = tx;
	y = ty;
}

vector<Point3> operator + (vector<Point3> a, vector<Point3> b) {
	static mt19937 rnd;
	const DO ra = pi * rnd() / rnd.max();
	const DO rb = pi * rnd() / rnd.max();
	const DO rc = pi * rnd() / rnd.max();
	for(int i = 0; i < b.size(); i ++) {
		generate_by_rotate(b[i].x, b[i].y, ra);
		generate_by_rotate(b[i].y, b[i].z, rb);
		generate_by_rotate(b[i].x, b[i].z, rc);
	}
	vector<Point3> res;
	for(Point3 x : a) {
		for(Point3 y : b) {
			res.push_back(x + y);
		}
	}
	return res;
}

vector<Point3> convex[11] = {
	{},
	{
		{0.000000000,0.000000000,0.000000000},
		{1.000000000,0.000000000,0.000000000},
	},
	{
		{0.000000000,0.000000000,0.000000000},
		{1.000000000,0.000000000,0.000000000},
		{0.500000000,0.866025404,0.000000000},
	},
	{
		{0.500000000,0.000000000,-0.353553391},
		{-0.50000000, 0.00000000, -0.353553391},
		{0.000000000,0.500000000,0.353553391},
		{0.000000000,-0.50000000, 0.353553391},
	},
	{
		{0.707106781,0.000000000,0.000000000},
		{-0.707106781,0.00000000, 0.000000000},
		{0.000000000,0.707106781,0.000000000},
		{0.000000000,-0.707106781,0.000000000},
		{0.000000000,0.000000000,0.707106781},
		{0.000000000,0.000000000,-0.707106781},
	},
	{
		{0.000000000,0.500000000,0.809016994},
		{0.000000000,-0.50000000, 0.809016994},
		{0.000000000,0.500000000,-0.809016994},
		{0.000000000,-0.50000000, -0.809016994},
		{0.500000000,0.809016994,0.000000000},
		{0.500000000,-0.809016994,0.000000000},
		{-0.50000000, 0.809016994,0.000000000},
		{-0.50000000, -0.809016994,0.000000000},
		{0.809016994,0.000000000,0.500000000},
		{0.809016994,0.000000000,-0.500000000},
		{-0.809016994,0.00000000, 0.500000000},
		{-0.809016994,0.00000000, -0.500000000},
	},
};

int main() {
	convex[6] = convex[3] + convex[3], convex[7] = convex[3] + convex[4];
	convex[8] = convex[4] + convex[4], convex[9] = convex[4] + convex[5];
	convex[10] = convex[6] + convex[4];
	int n;
	cin >> n;
	printf("%d\n", convex[n].size());
	for(int i = 0; i < convex[n].size(); i ++) {
		convex[n][i].print();
	}
	return 0;
}

