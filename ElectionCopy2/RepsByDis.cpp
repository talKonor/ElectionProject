#include "RepsByDis.h"

RepsByDis::RepsByDis(){}

RepsByDis::~RepsByDis(){}

int RepsByDis::getlSize()const
{
	return repsByDis.size();
}

const Reps& RepsByDis::getRepsArrByDis(int disId) const 
{
	for (int i = 0; i < repsByDis.size();i++) {
		if (repsByDis[i].getDisNum() == disId)
			return repsByDis[i];
	}
}

void RepsByDis::addDistrict(const District* district)
{
	repsByDis.push_back(*(new Reps(district)));
}

void RepsByDis::addRep(const Citizen* rep, int disId)
{
	for (int i = 0; i < repsByDis.size(); i++) {
		if (repsByDis[i].getDisNum() == disId) {
			repsByDis[i].addRepresentative(rep);
		}
	}
}

void RepsByDis::saveRepsArr(ofstream& file)const
{
	int size = repsByDis.size();
	file.write(rcastcc(&size), sizeof(int));
	for (int i = 0; i < size; i++) {
		repsByDis[i].saveReps(file);
	}
}

void RepsByDis::loadReps(ifstream& file, const DistrictArr& disList)
{
	int size;
	Reps* newReps = nullptr;
	file.read(rcastc(&size), sizeof(int));
	if (!file.good())
		throw "problem occurred while loading data from the file";

	repsByDis.erase(repsByDis.begin(), repsByDis.end());
	for (int i = 0; i < size; i++) {
		try
		{
			newReps = new Reps(file, disList);
		}
		catch (std::bad_alloc& ex)
		{
			cout << ex.what() << endl;
			exit(1);
		}
		repsByDis.push_back(*newReps);
		newReps = nullptr;
	}
	newReps = nullptr;
	delete newReps;
}

const Reps& RepsByDis::operator[](int i) const
{
	return repsByDis[i];
}