#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

class str
{
	public:
	    char* ss;
	    int length;
	public:
	    str() {
	    	ss = nullptr;
			length = 0;
		}
	    str(const char &c) {
	    	ss = new char [2];
			*ss = c;
			*(ss+1) = '\0';
			length = 1;
		}
		
		str(int len_) {
			ss = new char [len_+1];
			*(ss+len_) = '\0';
			length = len_;
		}
		
	    str(const char *&& s_) {
	    	length = strlen(s_);
			ss = new char [length+1];
			for (int i = 0; i < length; ++i) *(ss+i) = s_[i];
			*(ss+length) = '\0';
		}
	
	    str &operator = (const char *&& s_) {
	    	if (ss == s_) return *this;
			delete [] ss;
			length = strlen(s_);
			ss = new char [length+1];
			for (int i = 0 ; i < length; ++i) *(ss+i) = s_[i];
			*(ss+length) = '\0';
			return *this;
		}
	
	    str(const str &other) {
	    	length = other.length;
			ss = new char [length+1];
	    	for (int i = 0; i < length; ++i) *(ss+i) = *(other.ss+i);
	    	*(ss+length) = '\0';
		}
	
	    str &operator = (const str &other) {
			if (ss == other.ss) return *this; 
			delete [] ss;
			length = other.length;
			ss = new char [length+1];
	    	for (int i = 0; i < length; ++i) *(ss+i) = *(other.ss+i);
			return *this;
		}
	
	    char &operator[](size_t pos) {
	    	return *(ss+pos);
		}
	
	    size_t len() const {
			return size_t(length);
		}
	
	    str join(const std::vector<str> &strs) const {
			int tmplen = 0, cnt = 0;
			for (int i = 0; i < strs.size(); ++i) tmplen += strs[i].length;
			tmplen += (strs.size()-1)*length;
			str ret(tmplen);
			for (int i = 0; i < strs.size(); ++i) {
				for (int j = 0; j < strs[i].length; ++j) {
					ret[cnt++] = *(strs[i].ss+j);
				}
				for (int j = 0; j < length; ++j) {
					ret[cnt++] = *(ss+j);
				}
			}
			ret[ret.length] = '\0';
			return ret;
		}
	
	    str slice(size_t l, size_t r) const {
	    	str ret(int(r-l));
	    	for (int i = 0; i < ret.length; ++i) *(ret.ss+i) = ss[l+i];
	    	*(ret.ss+ret.length) = '\0';
			return ret;
		}
	
	    ~str() {
	    	if (ss) 
				delete [] ss;
		}
};

int main() {
	std::cout << str("12345").slice(1, 4).ss;
	//return 0;
	std::cout << str(", ").join(std::vector<str>{'1', '2', '3'}).ss;
} 
