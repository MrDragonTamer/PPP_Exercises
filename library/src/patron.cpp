#include"patron.h"

std::string Patron::name() const {
	return _name;
}
long Patron::ID() const {
	return _id;
}
double Patron::fee() const {
	return _fee;
}

std::string Patron::name(std::string newName) {
	_name = newName;
	return _name;
}
long Patron::ID(long newID) {
	_id = newID;
	return _id;
}
double Patron::fee(double newFee) {
	_fee = newFee;
	return _fee;
}

bool hasFees(const Patron& p) {
	if(p.fee() == 0) {
		return false;
	}
	return true;
}
