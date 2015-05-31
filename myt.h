#include <sys/time.h>

class mytimer
{
public:
	struct timeval start_t, end_t;
	//double start;
	//double end;

	mytimer()
    {
        gettimeofday(&start_t, 0);
    }

	double result()
	{
        gettimeofday(&end_t, 0);
		return ((end_t.tv_sec - start_t.tv_sec) * 1000.0 + (end_t.tv_usec - start_t.tv_usec)/1000.0);//1000.0;
	}
};
