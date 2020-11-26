#include <iostream>
#include <functional>
#include <vector>

using namespace std;

class Defer {
	private:
		vector <function<void()>> sta;
	
	public:
		Defer(function<void()> func) {
			sta.push_back(func);
		}
		void operator () (function<void()> func) {
			sta.push_back(func);
		}
		~Defer() {
			for (int i = sta.size()-1; i >= 0; --i) 
				sta[i]();
		}
}; 
void hello()
{
    std::cout << "Hello world!" << std::endl;
}
int main() {
	int *p = new int [2];
    Defer defer([&](){delete [] p;});
    defer([&](){std::cout << p[0] << " " << p[1] << std::endl;});
    defer([&](){p[0] = 0, p[1] = 1;});
    defer(hello);
    p[0] = 2, p[1] = 3;
    return 0;
}
