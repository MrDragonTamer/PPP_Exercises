#pragma once
#include<string>

class Patron{ 
	public:
		std::string name() const;
		long ID() const;
		double fee() const;

		std::string name(std::string newName);
		long ID(long newID);
		double fee(double newFee);

		Patron(std::string name, long id, double fee) : _name(name), _id(id), _fee(fee) {}
	private:
		std::string _name;
		long _id;
		double _fee = 0;
};

bool hasFees(const Patron& p);
