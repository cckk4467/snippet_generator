// @title get Lca
// @description get lca
// @prefix lca get_lca
class Lca {
    const vector<vector<int>> &_v;
    vector<int> _dep;
    const int _siz;
    const int _n;
    vector<vector<int>> _lca;

   public:
    Lca(const vector<vector<int>> &v, int root = 1)
        : _v(v),
          _dep(v.size()),
          _siz(v.size()),
          _n(log2(_siz) + 2),
          _lca(_siz, vector<int>(_n)) {
        auto dfs = [&](auto dfs, int c, int pre) -> void {
            _lca[c][0] = pre;
            _dep[c] = _dep[pre] + 1;
            for (int i = 1; i < _n; i++) {
                _lca[c][i] = _lca[_lca[c][i - 1]][i - 1];
            }
            for (auto to : v[c]) {
                if (to == pre) continue;
                dfs(dfs, to, c);
            }
        };
        dfs(dfs, root, 0);
    }
    int get(int x, int y) {
        if (_dep[x] < _dep[y]) swap(x, y);
        for (int i = _n; i >= 0; i--) {
            if (_dep[_lca[x][i]] >= _dep[y]) x = _lca[x][i];
        }
        for (int i = _n; i >= 0; i--) {
            if (_lca[x][i] != _lca[y][i]) x = _lca[x][i], y = _lca[y][i];
        }
        if (x != y) x = _lca[x][0], y = _lca[y][0];
        return x;
    }
};