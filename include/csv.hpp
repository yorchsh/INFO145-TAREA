#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

namespace csv {
    // leer y devolver info. del csv
	template<typename T>
	std::vector<T> read(const std::string& path) {
		std::vector<T> v;
		std::ifstream f(path);
		if (!f.is_open())
			return v;

		std::string token;
		char c;
		while (f.get(c)) {
			if (c == ',' || c == '\n' || c == '\r' || c == ' ' || c == '\t') {
				if (!token.empty()) {
					v.push_back((T) std::strtoll(token.c_str(), nullptr, 10));
					token.clear();
				}
			} else {
				token += c;
			}
		}
		if (!token.empty())
			v.push_back((T) std::strtoll(token.c_str(), nullptr, 10));

		return v;
	}

    template<typename T>
	bool write(const std::string& path, const std::vector<T>& v) {
		std::ofstream f(path);
		if (!f.is_open())
			return false;

		for (std::size_t i = 0; i < v.size(); i++) {
			if (i) f << ",";
			f << v[i];
		}
		f << "\n";
		return true;
	}
}


namespace Generar {
    using namespace std;

    static random_device rd;
    static mt19937 generador(rd());

    template<typename T>
    vector<T> vectorUniforme(int n) {
        vector<T> v;
        v.reserve(n);

        uniform_int_distribution<T> distribucion(
            numeric_limits<T>::min(),
            numeric_limits<T>::max()
        );

        for (int i = 0; i < n; ++i)
            v.push_back(distribucion(generador));

        return v;
    }

}
