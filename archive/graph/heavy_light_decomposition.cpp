// @title 树剖
// @description heavy_light_decomposition(need to test)
// @prefix heavy_light_decomposition hld shupou
class heavy_light_decomposition {
    const int _n;
    const vector<vector<int>> &_v;
    vector<int> _fa, _dep, _siz, _son, _top, _dfn;
    int cnt = 1;

   public:
    heavy_light_decomposition(const vector<vector<int>> &v, const int &&root)
        : _n(v.size()),
          _v(v),
          _fa(_n + 1),
          _dep(_n + 1),
          _siz(_n + 1),
          _son(_n + 1),
          _top(_n + 1),
          _dfn(_n + 1) {
        auto dfs1 = [&](auto dfs1, int c, int pre) -> int {
            _siz[c] = 1;
            _fa[c] = pre;
            _dep[c] = _dep[pre] + 1;
            _top[c] = c;
            for (auto to : _v[c]) {
                if (to == pre) continue;
                if ((_siz[to] = dfs1(dfs1, to, c)) > _siz[_son[c]])
                    _son[c] = to;
                _siz[c] += _siz[to];
            }
            return _siz[c];
        };

        auto dfs2 = [&](auto dfs2, int c, int pre) -> void {
            _top[_son[c]] = _top[c];
            _dfn[c] = cnt++;
            if (_son[c]) dfs2(dfs2, _son[c], c);
            for (auto to : v[c]) {
                if (to == pre || to == _son[c]) continue;
                dfs2(dfs2, to, c);
            }
        };
        dfs1(dfs1, root, 0);
        dfs2(dfs2, root, 0);
    }
    auto modify(int x, int y, int a) {
        while (_top[x] != _top[y]) {
            if (_dep[_top[x]] < _dep[_top[y]]) swap(x, y);
            // seg.insert(_dfn[_top[x]], _dfn[x], a);
            x = _fa[_top[x]];
        }
        if (x == y) return;
        if (_dep[x] < _dep[y]) swap(x, y);
        // seg.insert(_dfn[y] + 1, _dfn[x], a);
    }
    auto dfn(int x) { return _dfn[x]; }
    auto dep(int x) { return _dep[x]; }
};