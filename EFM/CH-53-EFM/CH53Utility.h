#ifndef __EFM_UTILITY__
#define __EFM_UTILITY__

//void InitLogFile();
//void DeInitLogFile();
//void WriteToLogFile(const char* str);

// simple buffer helper
// reduce repeating malloc()/free()
//class UtilBuffer
//{
//private: // disallow copying
//	UtilBuffer(const UtilBuffer& other) {};
//	UtilBuffer& operator=(const UtilBuffer& other) { return *this; };
//
//public:
//	double* vec; // array
//	int capacity; // amount of elements in array
//	//int used; // amount of elements in use
//
//	UtilBuffer()
//		: vec(NULL)
//		, capacity(0)
//	{}
//	UtilBuffer(const int vertices)
//		: vec(NULL)
//		, capacity(0)
//	{
//		getVec(vertices);
//	}
//	~UtilBuffer()
//	{
//		// cleanup on destroy (exiting scope)
//		if (vec != NULL)
//		{
//			free(vec);
//			vec = NULL;
//		}
//	}
//
//	// support growing as needed
//	double* getVec(const int vertices)
//	{
//		if (vertices > capacity)
//		{
//			free(vec);
//			capacity = vertices;
//			vec = (double*)malloc(vertices*sizeof(double));
//		}
//		return vec;
//	}
//
//	void copyVec(const int vertices, const double* src)
//	{
//		size_t toCopy = vertices*sizeof(double);
//		double* dest = getVec(vertices); // check for size
//		memcpy(dest, src, toCopy);
//	}
//};

// Struct to define a set of data with a given number of dimenions and points
typedef struct {
	int nDimension;
	int* nPoints;
} ND_INFO;


// Simple upper and lower limiter
double limit(double input, double lower_limit, double upper_limit);

#endif //__EFM_UTILITY__