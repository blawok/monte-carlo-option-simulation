#include<vector>


class MyOption{
public:

	//constructor
	MyOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_
		);

	//destructor
	~MyOption(){};

	//methods
	void generatePath();
	double getMinFromPath();
	double getPutDownAndIn(int nReps);

	//overloaded operator ()
	double operator()(char char1, char char2, int nReps);

	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;

};
