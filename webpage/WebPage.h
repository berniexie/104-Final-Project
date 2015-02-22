#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include "../lib/mySet.h"

class WebPage {
  public:
    WebPage ();    // constructor that creates an empty page
    WebPage (string filename);
      /* constructor that initializes the page from the given file.
         Should throw an exception if the file does not exist
         or has other problems. */
    ~WebPage ();   // destructor

    mySet<string> allWords () const;
      /* Returns a set containing all individual words on the web page. */   

    friend ostream & operator<< (ostream & os, const WebPage & page);
      /* Declares an operator we can use to print the web page. */
    // to be used in set
    //you should not print the Markdown information. 
    //When there is a link, you should just print the anchor text, but not the brackets, 
    //parentheses, or the file name.

    bool operator== (const WebPage & rhs) const;
    bool operator< (const WebPage & rhs) const;

    mySet<WebPage*> allOutgoingLinks () const;
      /* Returns "pointers" to all webpages that this page has links to. 
         As discussed above, this could be as a set or via an iterator,
         and it could be as actual pointers, or as strings, 
         or possibly other. */   

    mySet<WebPage*> allIncomingLinks () const;
      /* Returns "pointers" to all webpages that link to this page. 
         Same consideration as previous function. */   

    string filename () const;
      /* Returns the filename from which this page was read. */

    /* Based on which overall architecture you choose, you may 
       also need/want some or all of the following functions. */
    string get_content() const;
    string get_contentwlinks() const;

    double get_pagerank() const;
    void set_pagerank(double pagerank);

    int get_clicks() const;
    void set_clicks(int click_num);
    void increment_clicks();

    void parse (std::map<string, WebPage*>* linkedwpmap);
      /* actually parses the content of the filename that was passed 
         to the constructor into the object. */

    void addIncomingLink (WebPage* start);
      /* Adds a link from start to the current page 
         in the current page's storage. */

    void addOutgoingLink (WebPage* target); 
      /* Adds a link from the current page to the target
         in the current page's storage. */

  private:
    string content;
    string file_name;
    set<string> anchor_set;
    mySet<string> word_set;
    mySet<WebPage*> outgoinglink_set, incominglink_set;
    double pagerank_value;
    int num_clicks;
};

struct AlphaStrComp {
    bool operator()(const WebPage* lhs, const WebPage* rhs) 
    {
      return lhs->filename() < rhs->filename(); 
    }
  };

struct RankComp {
    bool operator()(const WebPage* lhs, const WebPage* rhs) 
    { 
		if (lhs->get_clicks()>rhs->get_clicks())
		{
			return true;
		}
		else if (lhs->get_clicks()==rhs->get_clicks())
		{
			return lhs->get_pagerank() > rhs->get_pagerank(); 
		}
		else
		{
			return false;
		}
    }
  };

#endif

