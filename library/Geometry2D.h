//
// Created by Lukas Huwald on 31.05.18.
//

#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H

#include <cmath>
#include <stdexcept>
#include "Prelude.h"

// 2d point struct
struct point {
    double x,y;

    point() { x = y = 0; }
    point(double _x, double _y) { x = _x; y = _y; }

    bool operator== (point other) const {
        return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS);
    }

    bool operator!= (point other) const {
        return !(*this == other);
    }

    point operator+ (point other) {
        return point(x + other.x, y + other.y);
    }

    point operator- (point other) {
        return point(x - other.x, y - other.y);
    }
};

// 2d line, given by ax + by + c = 0
// we fix b = 0 for vertical lines and b = 1 for non-vertical lines
struct line {
    double a, b, c;

    line(double _a, double _b, double _c) { a = _a; b = _b; c = _c; }

    bool operator == (line other) {
        return (fabs(a - other.a) < EPS && fabs(b - other.b) < EPS && fabs(c - other.c) < EPS);
    }
};

// 2d circle
struct circle {
    point centre;
    double radius;

    circle(point _centre, double _radius) {
        centre = _centre;
        radius = _radius;
    }
};

// 2d triangle
struct triangle {
    point a, b, c;

    triangle(point _a, point _b, point _c) {
        a = _a; b = _b; c = _c;
    }
};

// polygon as vector of points, last point must be first point
typedef std::vector<point> polygon;

// euclidian distance
double distance(point p1,point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

// rotate around origin ccw, theta given in radiants
point rotate(point p, double theta) {
    return point(p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta));
}

// rotate around c ccw, theta given in radiants
point rotate(point p, point c, double theta) {
    point trans = p - c;
    point rotated = rotate(trans, theta);
    return rotated + c;
}

// get line from two points
line pointsToLine(point p1, point p2) {
    if (fabs(p1.x - p2.x) < EPS) {
        return line(1, 0, -p1.x);
    }
    else {
        double a = -(p1.y - p2.y) / (p1.x - p2.x);
        double b = 1;
        double c = -(a * p1.x) - p1.y;
        return line(a, b, c);
    }
}

// get point on line with given x coordinate
point atX(line l, double x) {
    if (l.b == 0) {
        throw std::invalid_argument("Vertical line");
    }
    double y = (-l.a * x - l.c) / l.b;
    return point(x, y);
}

// get point on line with given y coordinate
point atY(line l, double y) {
    if (l.a == 0) {
        throw std::invalid_argument("Horizontal line");
    }
    double x = (-l.b * y - l.c) / l.a;
    return point(x, y);
}

// check whether lines are parallel
bool areParallel(line l1,line l2) {
    return (fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS);
}

// get intersection of two non parallel lines
point intersection(line l1, line l2) {
    if (areParallel(l1, l2)) {
        throw std::invalid_argument("Parallel lines do not intersect");
    }
    double x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    double y;
    if (fabs(l1.b) > EPS) {
        y = -(l1.a * x + l1.c);
    }
    else {
        y = -(l2.a * x + l2.c);
    }
    return point(x, y);
}

// scale point
point scale(point p, double a) {
    return point(a * p.x, a * p.y);
}

// dot product
double dot(point p1, point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

// cross product
double cross(point p1, point p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

// squared norm
double squaredNorm(point p1) {
    return p1.x * p1.x + p1.y * p1.y;
}

// squared euclidean distance
double squaredDistance(point p1, point p2) {
    return squaredNorm(p2 - p1);
}

// distance between point and line
double distance(point p, line l) {
    double part = fabs(l.a * p.x + l.b * p.y + l.c);
    return part / hypot(l.a, l.b);
}

// get closest point on line through ab from p
point closestPointFromLine(point p, point a, point b) {
    point ap = p - a;
    point ab = b - a;
    double u = dot(ap, ab) / squaredNorm(ab);
    return a + scale(ab, u);
}

// get closest point on line segment ab from p
point closestPointFromSegment(point p, point a, point b) {
    point ap = p - a;
    point ab = b - a;
    double u = dot(ap, ab) / squaredNorm(ab);
    if (u < 0) {
        return point(a.x, a.y);
    }
    else if (u > 1) {
        return point(b.x, b.y);
    }
    else {
        return a + scale(ab, u);
    }
}

// computes angle aob
double angle(point a, point o, point b) {
    point oa = a - o;
    point ob = b - o;
    return acos(dot(oa, ob) / sqrt(squaredNorm(oa) * squaredNorm(ob)));
}

// check whether point p is ccw from line segment ab
bool isCCWOfLine(point p, point a, point b) {
    point ab = b - a;
    point ap = p - a;
    return cross(ab, ap) > EPS;
}

// triangle perimeter
double perimeter(triangle t) {
    return distance(t.a, t.b) + distance(t.b, t.c) + distance(t.c, t.a);
}

// heron's formula for triangle area
double heronsFormula(double a, double b, double c) {
    double s = a + b + c / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// triangle area
double area(triangle t) {
    double d1 = distance(t.a, t.b);
    double d2 = distance(t.b, t.c);
    double d3 = distance(t.c, t.a);
    return heronsFormula(d1, d2, d3);
}

// check if three points are colinear
bool colinear(point a, point b, point c) {
    point ab = b - a;
    point ac = c - a;
    return fabs(cross(ab, ac)) < EPS;
}

// construct circle through two points with given radius
// reverse p1, p2 for the other circle
circle pointsAndRadiusToCircle(point p1, point p2, double r) {
    double d2 = squaredDistance(p1, p2);
    double det = r * r / d2 - 0.25;
    if (det < EPS) {
        throw std::invalid_argument("Radius too small");
    }
    double h = sqrt(det);
    double x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
    double y = (p1.y + p2.y) * 0.5 + (p2.x - p1.y) * h;
    return circle(point(x, y), r);
}

// check whether point is inside circle
bool insideCircle(circle c, point p) {
    return distance(c.centre, p) <= c.radius;
}

// circle circumference
double circumference(circle c) {
   return 2 * M_PI * c.radius;
}

// arc length
double arcLength(circle c, double theta) {
    return circumference(c) * theta / (2 * M_PI);
}

// chord length
double chordLenth(circle c, double theta) {
    return 2 * c.radius * sin(theta / 2);
}

// circle area
double area(circle c) {
    return M_PI * c.radius * c.radius;
}

// sector area
double sectorArea(circle c, double theta) {
    return area(c) * theta / (2 * M_PI);
}

// segment area
double segmentArea(circle c, double theta) {
    double secArea = sectorArea(c, theta);
    double chordLen = chordLenth(c, theta);
    double trigArea = heronsFormula(c.radius, c.radius, chordLen);
    return secArea - trigArea;
}

// polygon perimeter
double perimeter(polygon p) {
    double result = 0.0;
    int n = p.size() - 1;
    REP(i, n) {
        result += distance(p[i], p[i+1]);
    }
    return result;
}

// polygon area
double area(polygon p) {
    double result = 0.0;
    int n = p.size() - 1;
    REP(i, n) {
        result += (p[i].x * p[i+1].y - p[i+1].x * p[i].y);
    }
    return fabs(result) / 2.0;
}

// check if polygon is convex
bool isConvex(polygon p) {
    int n = p.size();
    if (n <= 3) { return false; }
    bool isLeft = isCCWOfLine(p[0], p[1], p[2]);
    for (int i = 1; i < n-1; ++i) {
        if (isCCWOfLine(p[i], p[i+1], p[i+2 == n ? 1 : i+2]) != isLeft) {
            return false;
        }
    }
    return true;
}

// check if point is in polygon
bool inPolygon(point pt, polygon p) {
    int n = p.size() - 1;
    double sum = 0.0;
    REP(i, n) {
        if (isCCWOfLine(pt, p[i], p[i+1])) {
            sum += angle(p[i], pt, p[i+1]);
        }
        else {
            sum -= angle(p[i], pt, p[i+1]);
        }
    }
    return fabs(fabs(sum) - 2*M_PI) < EPS;
}

// intersect line segment p-q with line r-s
point intersectSegmentWithLine(point p, point q, point r, point s) {
    double a = s.y - r.y;
    double b = r.x - s.x;
    double c = s.x * r.y - r.x * s.y;
    double u = fabs(a * p.x + b * p.y + c);
    double v = fabs(a * q.x + b * q.y + c);
    double resX = (p.x * v + q.x * u) / (u + v);
    double resY = (p.y * v + q.y * u) / (u + v);
    return point(resX, resY);
}

// cut polygon along line a-> b and return the polygon left of the line
polygon cutPolygon(point a, point b, polygon q) {
    polygon p;
    int n = q.size();
    REP(i, n) {
        double left1 = cross(b - a, q[i] - a);
        double left2 = 0.0;
        if (i != n-1) {
            left2 = cross(b - a, q[i+1] - a);
        }
        if (left1 > -EPS) {
            p.push_back(q[i]);
        }
        if (left1 * left2 < -EPS) {
            p.push_back(intersectSegmentWithLine(q[i], q[i+1], a, b));
        }
    }
    if (!p.empty() && !(p.back() == p.front())) {
        auto front = p.front();
        p.push_back(front);
    }
    return p;
}

// compare angles with respect to pivot
bool angleComparator(point pivot, point a, point b) {
    if (colinear(pivot, a, b)) {
        return distance(pivot, a) < distance(pivot, b);
    }
    double d1x = a.x - pivot.x;
    double d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x;
    double d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

// compute convex hull in ccw order of polygon using monotone chain
polygon convexHull(polygon p) {
    int n = p.size();
    if (n == 1) { return p; }
    int k = 0;
    polygon hull(2*n);
    std::sort(p.begin(), p.end(), [](point p1, point p2) {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    });
    REP(i, n) {
        while (k >= 2 && !isCCWOfLine(hull[k-2], hull[k-1], p[i])) {
            k--;
        }
        hull[k++] = p[i];
    }
    int t = k+1;
    for (int i = n-2; i >= 0; --i) {
        while (k >= t && !isCCWOfLine(hull[k-2], hull[k-1], p[i])) {
            k--;
        }
        hull[k++] = p[i];
    }
    hull.resize(k);
    hull.pop_back();
    return hull;
}

#endif //GEOMETRY2D_H
