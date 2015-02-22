// unordered_map::operator[]
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main ()
{
  unordered_map<string,string> mymap;

  mymap["Bakery"]="Barbara";  // new element inserted
  mymap["Seafood"]="Lisa";    // new element inserted
  mymap["Produce"]="John";    // new element inserted

  string name = mymap["Bakery"];   // existing element accessed (read)
  mymap["Seafood"] = name;              // existing element accessed (written)

  mymap["Bakery"] = mymap["Produce"];   // existing elements accessed (read/written)

  name = mymap["Deli"];      // non-existing element: new element "Deli" inserted!

  mymap["Produce"] = mymap["Gifts"];    // new element "Gifts" inserted, "Produce" written

  for (auto& x: mymap) {
    cout << x.first << ": " << x.second << endl;
  }
  
  for (unordered_map<string,string>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
  {
		cout<<it->first<<" "<<it->second<<endl;
	}
	
  return 0;
}
