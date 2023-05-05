// @title segtree for max or min values
// @description dynamic-nodes segtree for max or min values
// @prefix segtree_max segtree_min
template <class T, decltype(auto) Max, class Idx = int>
struct SegTree {
   public:
    SegTree(Idx l, Idx r, const T &&def)
        : _def(def),
          _l(l),
          _r(r),
          _list{{_def, _list.end(), _list.end()}},
          _head(_list.begin()),
          _void(_head) {}
    void insert(Idx p, const T &x) {
        // assert(p >= _l && p <= _r);
        _insert(_head, p, x, _l, _r);
    }
    const T getmax(Idx a, Idx b) { return _getmax(_head, a, b, _l, _r); }

   private:
    struct Node {
        T _val;
        decltype(list<Node>().begin()) _ls, _rs;
    };
    const T _def;
    const Idx _l, _r;
    list<Node> _list;
    decltype(_list.begin()) _head, _void;

    auto _getNode(decltype(_list.begin()) &k) {
        if (k == _void)
            k = _list.insert(_list.end(), {_def, _list.begin(), _list.begin()});
        return forward_as_tuple(k->_ls, k->_rs);
    }
    void _insert(decltype(_list.begin()) &k, Idx p, const T &x, Idx l, Idx r) {
        auto [ls, rs] = _getNode(k);
        if (l == r) {
            k->_val = x;
            return;
        }
        Idx mid = (l + r) >> 1;
        if (p <= mid)
            _insert(ls, p, x, l, mid);
        else
            _insert(rs, p, x, mid + 1, r);
        k->_val = Max(ls->_val, rs->_val);
    };
    const T _getmax(decltype(_list.begin()) k, Idx a, Idx b, Idx l, Idx r) {
        auto [ls, rs] = _getNode(k);
        if (a <= l && r <= b) return k->_val;
        Idx mid = (l + r) >> 1;
        T lans = _def, rans = _def;
        if (a <= mid && ls != _void) lans = _getmax(ls, a, b, l, mid);
        if (b > mid && rs != _void) rans = _getmax(rs, a, b, mid + 1, r);
        return Max(lans, rans);
    };
};

auto Max = [](auto a, auto b) { return (a > b) ? a : b; };
SegTree<int, Max, long long> seg(0, 1000000, INT_MIN);