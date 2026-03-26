#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld eps = 1e-12;

struct pt {
    ld x, y;
    pt operator-(pt p) const { return {x - p.x, y - p.y}; }
    pt operator+(pt p) const { return {x + p.x, y + p.y}; }
    pt operator*(ld d) const { return {x * d, y * d}; }
    ld operator^(pt p) const { return x * p.y - y * p.x; }
};

struct Line {
    pt p, v; // Point and direction vector
    ld angle;
    Line() {}
    Line(pt a, pt b) : p(a), v(b - a) { angle = atan2(v.y, v.x); }
    
    // Check if point is to the left of the line
    bool out(pt q) { return (v ^ (q - p)) < -eps; }
};

pt intersect(Line a, Line b) {
    ld s = ((b.p - a.p) ^ b.v) / (a.v ^ b.v);
    return a.p + a.v * s;
}

// Standard O(N log N) Half-plane Intersection
vector<pt> intersect_all(vector<Line>& lines) {
    sort(lines.begin(), lines.end(), [](Line a, Line b) {
        if (abs(a.angle - b.angle) > eps) return a.angle < b.angle;
        return (a.v ^ (b.p - a.p)) > 0; // Keep the leftmost line if parallel
    });

    vector<Line> q;
    for (int i = 0; i < lines.size(); i++) {
        if (i > 0 && abs(lines[i].angle - lines[i-1].angle) < eps) continue;
        while (q.size() >= 2 && lines[i].out(intersect(q[q.size() - 2], q.back()))) q.pop_back();
        while (q.size() >= 2 && lines[i].out(intersect(q[0], q[1]))) q.erase(q.begin());
        q.push_back(lines[i]);
    }
    while (q.size() >= 3 && q[0].out(intersect(q[q.size() - 2], q.back()))) q.pop_back();
    while (q.size() >= 3 && q.back().out(intersect(q[0], q[1]))) q.erase(q.begin());

    if (q.size() < 3) return {};
    vector<pt> res;
    for (int i = 0; i < q.size(); i++) res.push_back(intersect(q[i], q[(i + 1) % q.size()]));
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; ld P, Q;
    cin >> n >> P >> Q;

    vector<Line> lines;
    // Bounding box for the first quadrant (adjust if negative coordinates possible)
    lines.push_back(Line({0, 0}, {1, 0}));
    lines.push_back(Line({1, 0}, {1, 1}));
    lines.push_back(Line({1, 1}, {0, 1}));
    lines.push_back(Line({0, 1}, {0, 0}));

    for (int i = 0; i < n; i++) {
        ld a, b; cin >> a >> b;
        // Line: ax + by = 1 -> Intercepts (1/a, 0) and (0, 1/b)
        // Direction vector ensures (0,0) is in the "left" half-plane
        lines.push_back(Line({0, 1/b}, {1/a, 0}));
    }

    auto poly = intersect_all(lines);
    ld ans = 0;
    for (auto& p : poly) ans = max(ans, p.x * P + p.y * Q);

    cout << fixed << setprecision(15) << ans << endl;
    return 0;
}