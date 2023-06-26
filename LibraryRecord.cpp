#include "LibraryRecord.hpp"
/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the vector of checked-out books.
 **/
bool LibraryRecord::checkOut(const Book& record){
    if(remove(record)){
    book_check_out.push_back(record);
    return true;
    }
   return false; 
}
  /** @param:   A reference to a Book object to be checked in
    @return:  returns true if a book was successfully added to items_, false otherwise
    @post:    adds book to items_.
 **/
bool LibraryRecord::checkIn(const Book& check_in){
    if(add(check_in)){return true;}
    return false;
}
 /**
  @param:   A reference to a Book object
  @return:  The number of times (int) the referenced Book has been checked out
*/
int LibraryRecord::getCheckOutHistory(const Book& repeat) const{
    int count = 0;
    for(int i = 0; i < book_check_out.size(); i++){
        if(repeat == book_check_out[i]){count++;}
    }
    return count;
}
 /**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock() {
    int num_of_items = getCurrentSize();
    if(isEmpty() || (num_of_items *2 > DEFAULT_CAPACITY )){return false;}
    for(int i = 0; i < num_of_items; i++){
        add(items_[i]);
    }
    return true;
}
/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been cheked out

      For each Book in the LibraryRecord you will output:
             "[title_] is written by [author_]. Page Count: [page_count_]. [It is / It is not] available digitally.\n
             It has been checked out [_] times.\n"
  **/
void LibraryRecord::display() const{
    for(int i = 0; i < getCurrentSize(); i++){
        items_[i].display();
        std::cout<<"It has been checked out "<<getCheckOutHistory(items_[i]) << "times.\n";
        }
}
 /**
  @post:    Prints the title of each Book in the LibraryRecord
  Example:
  "title1, title2, title3, title4!\n" Note the commas and exclamation mark.
*/
void LibraryRecord::displayTitles() const{
    std::string title_string = "";
    for(int i = 0; i < getCurrentSize(); i++){ title_string += items_[i].getTitle() + ", ";}
    std::cout<<title_string.substr(0, title_string.size()-2 ) + "!"<<"\n";
    
}
 /**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::removeStock(const Book& to_remove){
    bool removed = false;
    while(contains(to_remove)){
        remove(to_remove);
        removed = true;
    }
    return removed;
}
/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the same contents (including the same number of duplicates for each book), regardless of their order. For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
  and those of the referenced LibraryRecord are [book3, book1, book2], it will return true.

  However, [book1, book2, book2, book3] is not equivalent to [book1, book2, book3, book3], because it contains two copies of book2 and only one copy of book3


**/
bool LibraryRecord::equivalentRecords(const LibraryRecord& second_library_record){
     if (getCurrentSize()!=second_library_record.getCurrentSize()){
        return false;
    }
    for (int i=0;i<getCurrentSize();i++){
        if (getFrequencyOf(items_[i]) != second_library_record.getFrequencyOf(items_[i])){return false;}
    }
    return true;
};
 /**
    @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, including duplicates.
    Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

    IMPORTANT: We are carrying over the number of times a book has been checked out. For example, if we have LibraryRecord1 += LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the += operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
void LibraryRecord::operator+=(const LibraryRecord& rhs){
    for (int i=0; i<rhs.getCurrentSize();i++){
        add(rhs.items_[i]);
        for (int j=0; j<rhs.getCheckOutHistory(rhs.items_[i]);j++){
            book_check_out.push_back(rhs.items_[i]);
        }
    }
};
/** @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, EXCLUDING duplicates.
    Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

    IMPORTANT: We are carrying over the number of times a book has been checked out. For example, if we have LibraryRecord1 /= LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the /= operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
void LibraryRecord::operator/=(const LibraryRecord& rhs){
for (int i=0; i<rhs.getCurrentSize();i++){
    if (!contains(rhs.items_[i])){
          for (int j=0; j<rhs.getCheckOutHistory(rhs.items_[i]);j++){
            book_check_out.push_back(rhs.items_[i]);
        }
        add(rhs.items_[i]);
    }
}
};
  
