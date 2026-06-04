#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace csv {
	template<typename T>
	vector<T> read(string path) {
		std::filesystem::path p = path;
		std::ifstream f(path);
	}

	bool write(string path, vector<T>) {
		std::filesystem::path p = path;
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
