struct Scanner {
	char *buf;
	ssize_t wt, rd;
	size_t maxsz;
public:
	Scanner(int size = 1<<16): maxsz(size) {
		buf = (char*)malloc(sizeof(char) * size);
		_read();
	}
	template<class T> T read_int() {
		T ret = 0;
		bool s = true;
		int ch = _chr();
		while (isspace(ch)) ch = nxchar();
		if (ch == '-') {
			s = false;
			ch = nxchar();
		}
		for (; isdigit(ch); ch = nxchar()) ret = ret * 10 + ch - '0';
		return (s ? ret : -ret);
	}
	string read_str() {
		int ch = _chr();
		while (isspace(ch)) ch = nxchar();
		int rd_first = rd;
		string res;
		while (rd <= wt && !isspace(buf[rd])) {
			++rd;
			if (rd == wt) {
				res += string(buf, rd_first, wt - rd_first);
				_read();
				rd_first = 0;
			}
		}
		res += string(buf, rd_first, rd - rd_first);
		return res;
	}
	char read_chr() {
		int ch = _chr();
		while (isspace(ch)) ch = nxchar();
		return ch;
	}
private:
	void _read() {
		ssize_t r = read(0, buf, maxsz);
		if (r < 0) {
			throw runtime_error(strerror(errno));
		}
		wt = r;
		rd = 0;
	}
	inline int nxchar() {
		++rd;
		if (rd == wt) _read();
		return _chr();
	}
	inline int _chr() {
		return rd == wt ? EOF : buf[rd];
	}
} sc;
