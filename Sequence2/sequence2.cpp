#include "sequence2.h"
#include "node2.h"
#include <cassert> //grants assert
#include <cstdlib> //grants NULL and size_t
using namespace std;

namespace assignment_sequence2
{
	sequence::sequence( ){
		current_ptr = head_ptr = tail_ptr = prev_ptr = NULL;
		many_nodes = 0;
	}
	sequence::sequence(const sequence& source){
	    many_nodes = source.many_nodes;
	    list_copy(source.head_ptr, head_ptr, tail_ptr);
	    start();
	    if (many_nodes > 0){ for (node* temp = source.head_ptr; temp != source.current_ptr; temp = temp->link()) { advance(); }
	    } else { head_ptr = tail_ptr = NULL; }
	}
	sequence::~sequence( ){
		list_clear(head_ptr);
		head_ptr = tail_ptr = current_ptr = prev_ptr = NULL;
		many_nodes = 0;
	}
	void sequence::start( ){
		prev_ptr = NULL;
		current_ptr = head_ptr;
	}
	void sequence::advance( ){
		assert(is_item());
		prev_ptr = current_ptr;
		current_ptr = current_ptr->link();
	}
	void sequence::insert(const value_type& entry){
		if(is_item()){
            if (current_ptr == head_ptr){
                list_head_insert(head_ptr, entry);
                start();
            } else {
                list_insert(prev_ptr, entry);
                current_ptr = prev_ptr->link();
            }
        } else {
            list_head_insert(head_ptr, entry);
            start();
        } ++many_nodes;
	}
	void sequence::attach(const value_type& entry){
		if(is_item()){
			if (current_ptr == tail_ptr){
				list_insert(tail_ptr, entry);
				prev_ptr = tail_ptr;
				tail_ptr = current_ptr = tail_ptr->link();
			} else {
				list_insert(current_ptr, entry);
				prev_ptr = current_ptr;
				current_ptr = current_ptr->link();
			}
		} else if (size() == 0) {
			list_head_insert(head_ptr, entry);
			tail_ptr = current_ptr = head_ptr;
		} else {
			list_insert(tail_ptr, entry);
			prev_ptr = tail_ptr;
			tail_ptr = current_ptr = tail_ptr->link();
		} ++many_nodes;
	}
	void sequence::remove_current( ){
	    if (many_nodes == 0){ return; }
	    else if (many_nodes == 1) {
	        list_head_remove(head_ptr);
            current_ptr = prev_ptr = head_ptr = tail_ptr = NULL;
	    } else if (current_ptr == tail_ptr){ //if curr points to last item
	        current_ptr = NULL;
	        tail_ptr = prev_ptr;
	        list_remove(tail_ptr);
        } else if (current_ptr == head_ptr) { //if curr points to first item
            list_head_remove(head_ptr);
            current_ptr = head_ptr;
            prev_ptr = NULL;
        } else { //if curr is somewhere besides the first/last node
            current_ptr = current_ptr->link();
            list_remove(prev_ptr);
        } --many_nodes;
	}
	void sequence::operator =(const sequence& source){
	    if (this == &source) return;
        list_clear(head_ptr);
		many_nodes = source.many_nodes;
	    list_copy(source.head_ptr, head_ptr, tail_ptr);
	    start();
	    if (many_nodes > 0){ for (node* temp = source.head_ptr; temp != source.current_ptr; temp = temp->link()) { advance(); }
	    } else { head_ptr = tail_ptr = NULL; }
	}
	size_t sequence::size( ) const{ return many_nodes; }
	bool sequence::is_item( ) const{ return current_ptr != NULL; }
	node::value_type sequence::current( ) const{ return current_ptr->data(); }
}



