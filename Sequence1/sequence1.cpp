#include <cstdlib>
#include <cassert>
using namespace std;
#include "sequence1.h"

namespace weimin_csc212{
	sequence1::sequence1( ){ curr_ind = 0, length = 0; } //default constructor
	void sequence1::start( ){ //moves pointer to beginning of array
		if(length > 0) curr_ind = 0;
	}
	void sequence1::advance( ){ //moves pointer forward by one
		if(is_item()) ++curr_ind;
	}
	void sequence1::insert(const value_type& entry){ //inserts entry *before* current index
		assert(size( ) < CAPACITY);
		if(is_item() != 1){ curr_ind = 0; }
		for (size_type i = length++; i > curr_ind; --i){
			data[i] = data[i-1];
		}
		data[curr_ind] = entry;
	}
	void sequence1::attach(const value_type& entry){ //inserts entry *after* current index
		assert(size( ) < CAPACITY);
		if ((curr_ind + 1) < length){
			++curr_ind;
			insert(entry);
		} else {
			data[length++] = entry;
			if (length > 1){ ++curr_ind; }
		}
	}
	void sequence1::remove_current( ){ //removes item in current index
		assert(is_item());
		for (size_type i = curr_ind; i < length; ++i){
			data[i] = data[i+1];
		} --length;
	}
	sequence1::size_type sequence1::size( ) const{ //returns size of array
		return length;
	}
	bool sequence1::is_item( ) const{ //checks if current() can be called
		return ((curr_ind < length) && (curr_ind >= 0));
	}
	sequence1::value_type sequence1::current( ) const{ //returns item in current index
		assert(is_item());
		return data[curr_ind];
	}
}
