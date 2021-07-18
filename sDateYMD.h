#ifndef _sDateYMD_HG_
#define _sDateYMD_HG_

struct sDateYMD
{
	// This is an "initializer list", which sets data just like below...
	sDateYMD(): year(0), month(0), day(0) {};
// ... equivaent to:
//	sDateYMD() 
//	{
//		this->year(0);
//		this->month(0);
//		this->day(0);
//	};
	
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

#endif // _sDateYMD_HG_
