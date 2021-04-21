#include "Reps.h"
 #include "District.h"
 #include "DistrictArr.h"

Reps::Reps(const District* district)
{
    this->dis = district;
}

Reps::Reps(ifstream& file, const DistrictArr& disList)
{ 
    int size, IDsize, disId;
    char* repId;
    file.read(rcastc(&disId), sizeof(int));
    file.read(rcastc(&size), sizeof(int));
    if (!file.good())
        throw "problem occurred while loading data from the file";
    dis=&disList.getDistrict(disId);
    repArr.erase(repArr.begin(), repArr.end());
    for (int i = 0; i < size; i++) {
        file.read(rcastc(&IDsize), sizeof(int));
        try
        {
            repId = new char[IDsize];
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
        file.read(repId, IDsize);
        if (!file.good())
            throw "A problem has occurred in this file.";
        repId[IDsize] = '\0';
        string id = repId;
        repArr.push_back(disList.findCitizen(id));
    }
}

Reps::~Reps(){}

int Reps::getlSize() const
{
    return repArr.size();
}

int Reps::getDisNum() const
{
    return dis->getIdNum();
}

const District* Reps::getDistrict() const
{
    return dis;
}

const string& Reps::getRepName(int ind) const
{
    return repArr[ind]->getName();
}

const string& Reps::getRepId(int ind) const
{
    return repArr[ind]->getId();
}

void Reps::addRepresentative(const Citizen* rep)
{
    repArr.push_back(rep);
}

void Reps::saveReps(ofstream& file)const
{
    int id= dis->getIdNum();
    int size = repArr.size();
    int repIdNum;
    string repId;
    file.write(rcastcc(&id), sizeof(int));
    file.write(rcastcc(&size), sizeof(int));
    for (int i = 0; i < size; i++) {
        repId = repArr[i]->getId();
        repIdNum = repId.size();
        file.write(rcastcc(&repIdNum), sizeof(int));
        file.write(repId.c_str(), repIdNum);
    }
}

const Citizen& Reps::operator[](int i)
{
    return *repArr[i];
}

const Reps& Reps::operator=(const Reps& reps)
{
    this->dis = reps.dis;
    this->repArr = reps.repArr;
    return *this;
}