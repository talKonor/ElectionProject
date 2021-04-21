#pragma once
#include"FileManger.h"
#include "PartyArr.h"

class Party;

class DistrictResult
{
	struct DistrictVotes {

		const Party* party;
		int numberOfVoters;
		int numOfReps;
		DistrictVotes(const Party* party=nullptr, int numberOfVoters=0,int numOfReps=0) {
			this->party = party;
			this->numberOfVoters= numberOfVoters;
			this->numOfReps = numOfReps;
		}
		//this function load Districts votes from file
		DistrictVotes(ifstream& file,const  PartyArr& partyList);
	};
private:

	DynamicArray<DistrictVotes>	results;

public:
	DistrictResult();
	~DistrictResult();
	DistrictResult(const DistrictResult& res);
	
	/****************Getters*************/
	int   getNumOfVotes(int partyId)const;
	int   getLSize()const;

	//this function add a pointer to a party in the results arr 
	void addParty(const Party* party);

	//this funtion save the results arr to a file
	void saveResults(ofstream& file)const;

	//this funtion loads the results arr from a file
	void loadDistricResults(ifstream& file, const PartyArr& partyList);

	DistrictVotes& operator[](int ind) { 
		return results[ind];
	}
	const DistrictVotes& operator[](int ind) const { 
		return results[ind]; 
	}
	const DistrictResult& operator=(const DistrictResult& origin);
};

