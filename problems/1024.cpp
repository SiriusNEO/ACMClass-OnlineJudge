#include <iostream> 

class MemoryPoolManager
{
	private:
	    char *head;
	    /*
	        head: the position of the first free block
	    */
	    size_t block_size, block_cnt;
	    /*
	        block_size: the size of each block (in bytes, at least 8);
	        block_cnt: the maximum number of blocks
	    */
	public:
	    MemoryPoolManager(char *ptr, size_t block_size_, size_t block_cnt_) : head(ptr), block_size(block_size_), block_cnt(block_cnt_)
	    {
	        //to do: code whatever you want here to initialize
	        head = ptr;
			block_size = block_size_;
			block_cnt = block_cnt_;
			for (int i = 0; i < block_cnt; ++i) *(ptr+i*block_size) = *(ptr+i*block_size+1) = '$';
		}
	
	    void *allocate()
	    {
	        //to do: return a pointer pointing at a free block (nullptr if no free block left)
			for (int i = 0; i < block_cnt; ++i) {
				bool isFree = true;
				for (int j = 0; j < 2; ++j)
					if (*(head+i*block_size+j) != '$') {
						isFree = false;
						break;
					}
	    		if (isFree) {
					*(head+i*block_size) = 0;
	    			return reinterpret_cast<void*>(head+i*block_size);
				}
			}
			return nullptr;
		}
	
	    void free(void *ptr)
	    {
	        //to do: make a block ready for reuse (we will guarantee that ptr is a block acquired by previous allocation)
			char* tmp = reinterpret_cast<char*>(ptr);
			*tmp = *(tmp+1) = '$';
		}
};

int main() {
	char ptr[233333];
	MemoryPoolManager mpm(ptr, 3, 3);
	std::cout << mpm.allocate() << '\n';
}
