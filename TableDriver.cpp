#include "TableSortedList.h"
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
#include "ListDoublyLinkedIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   TableSortedList<CD>* slt = new TableSortedList<CD>(&CD::compare_items, &CD::compare_keys);

   //DO THIS
   //thoroughly test your table
   ListArrayIterator<CD>* iter = cds->iterator();
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      slt->tableInsert(cd);
	  
	  cd = slt->tableRetrieve(cd->getKey());
	  cd->displayCD();
   }
   delete iter;
   
   ListArrayIterator<CD>* iterTest = cds->iterator();
   
   CD* cdTest = iterTest->next();
   
   cout << slt->tableSize() << endl;										//tests duplicate inserts
   slt->tableInsert(cdTest);
   cout << slt->tableSize() << endl;
   
   
   

	ListDoublyLinkedIterator<CD>* iters = slt->iterator();
	
	while(iters->hasNext())
	{
		CD* cd = iters->next();
		
		slt->tableRemove(cd->getKey());
		bool remove = slt->tableRemove(cd->getKey());		//tests nonexistent removals
		CD* retrieve = slt->tableRetrieve(cd->getKey());	//tests nonexistent retrievals
		
		if(remove == true)
			cout << "false remove" << endl;
		if(retrieve != NULL)
			cout << "false retrieve" << endl;
			
		cout << slt->tableSize()<< endl;
	}
	delete iters;
	





   deleteCDs(cds);
   delete cds;
   delete slt;
   return 0;
}
