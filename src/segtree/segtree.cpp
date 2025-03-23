// [l, r)
template<class Info>
struct SegmentTree {
    inline i32 cl(i32 x) { return x << 1; }
    inline i32 cr(i32 x) { return (x << 1) | 1; }
    i32 n;
    vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(i32 n_, Info v_ = Info()) { init(n_, v_); }
    template<class T>
    SegmentTree(vector<T> init_) { init(init_); }

    void init(i32 n_, Info v_ = Info()) { init(vector(n_, v_)); }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function<void(i32, i32, i32)> build = [&](i32 p, i32 l, i32 r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            i32 m = (l + r) >> 1;
            build(cl(p), l, m);
            build(cr(p), m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(i32 p) { info[p] = merge(info[cl(p)], info[cr(p)]); }

    void modify(i32 p, i32 l, i32 r, i32 x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        i32 m = (l + r) >> 1;
        if (x < m) modify(cl(p), l, m, x, v);
        else modify(cr(p), m, r, x, v);
        pull(p);
    }
    void modify(i32 p, const Info &v) { modify(1, 0, n, p, v); }

    Info rangeQuery(i32 p, i32 l, i32 r, i32 x, i32 y) {
        if (l >= y || r <= x) return Info();
        if (l >= x && r <= y) return info[p];
        i32 m = (l + r) >> 1;
        return merge(rangeQuery(cl(p), l, m, x, y), rangeQuery(cr(p), m, r, x, y));
    }
    Info rangeQuery(i32 l, i32 r) { return rangeQuery(1, 0, n, l, r); }

    template<class F>
    i32 findFirst(i32 p, i32 l, i32 r, i32 x, i32 y, F &&pred) {
        if (l >= y || r <= x) return -1;
        if (l >= x && r <= y && !pred(info[p])) return -1;
        if (r - l == 1) return l;
        i32 m = (l + r) >> 1;
        i32 res = findFirst(cl(p), l, m, x, y, pred);
        if (res == -1) res = findFirst(cr(p), m, r, x, y, pred);
        return res;
    }
    template<class F>
    i32 findFirst(i32 l, i32 r, F &&pred) { return findFirst(1, 0, n, l, r, pred); }

    template<class F>
    i32 findLast(i32 p, i32 l, i32 r, i32 x, i32 y, F &&pred) {
        if (l >= y || r <= x) return -1;
        if (l >= x && r <= y && !pred(info[p])) return -1;
        if (r - l == 1) return l;
        i32 m = (l + r) >> 1;
        i32 res = findLast(cr(p), m, r, x, y, pred);
        if (res == -1) res = findLast(cl(p), l, m, x, y, pred);
        return res;
    }
    template<class F>
    i32 findLast(i32 l, i32 r, F &&pred) { return findLast(1, 0, n, l, r, pred); }
};