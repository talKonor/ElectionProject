#include "DistrictResult.h"

DistrictResult::DistrictResult() {}

DistrictResult::~DistrictResult() {}

DistrictResult::DistrictResult(const DistrictResult& res){
    this->results = res.results;
}

int DistrictResult::getNumOfVotes(int partyId) const{
    return results[partyId].numberOfVoters;
}

int DistrictResult::getLSize() const {
    return  results.size();
}

void DistrictResult::addParty(const Party* party)
{
    results.push_back(party);
}

void DistrictResult::saveResults(ofstream& file)const
{
    int partyid;
    for (int i = 0; i < results.size(); i++) {
        partyid = results[i].party->getPartyID();
        file.write(rcastcc(&partyid), sizeof(int));
        file.write(rcastcc(&(results[i].numberOfVoters)), sizeof(int));
        file.write(rcastcc(&(results[i].numOfReps)), sizeof(int));
        if (!file.good())
            throw "problem occurred while loading data from the file";
    }
}

void DistrictResult::loadDistricResults(ifstream& file,  const PartyArr& partyList)
{
    int size;
   
    file.read(rcastc(&size), sizeof(int));
    if (!file.good())
        throw "problem occurred while loading data from the file";
    results.erase(results.begin(), results.end());
    DistrictVotes* newDisVotes = nullptr;
    for (int i = 0; i < size; i++) {
        try
        {
            newDisVotes = new DistrictVotes(file, partyList);
        }
        catch (bad_alloc& ex)
        {
            cout << "Error:" << ex.what() << endl;
            exit(1);
        }
        if (!file.good())
            throw "problem occurred while loading data from the file";
        results.push_back(*newDisVotes);
        newDisVotes = nullptr;
    }
    delete newDisVotes;
}

DistrictResult::DistrictVotes::DistrictVotes(ifstream& file, const PartyArr& partyList)
{
    int paryId, numOfVotes, numOfReps;
    file.read(rcastc(&paryId), sizeof(int));
    file.read(rcastc(&numOfVotes), sizeof(int));
    file.read(rcastc(&numOfReps), sizeof(int));
    if (!file.good()) {
        throw "problem occurred while loading data from the file";
    }
    this->party = &partyList.getParty(paryId);
    this->numberOfVoters = numOfVotes;
    this->numOfReps = numOfReps;
}

const DistrictResult& DistrictResult::operator=(const DistrictResult& origin)
{
    this->results = origin.results;
    return *this;
}