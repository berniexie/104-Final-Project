#include "../webpage/WebPage.h"
#include <string>

WebPage::WebPage(){
}

WebPage::WebPage(string filename){
  this->file_name = filename;
  ifstream file (filename);
    if (file.bad()){
    throw filename;
  }
  while (!file.eof()){
    char character = file.get();
    content.push_back(character);
    //cout << character << endl;
  }
    //cout << "building webpage!" << endl;
  content.pop_back();
  content.push_back('\n');
  file.close();
}


WebPage::~WebPage(){

}

mySet<string> WebPage::allWords() const{
  return word_set;
}

ostream & operator<< (ostream& os, const WebPage& page){
  string print_out = page.content;
  bool is_markdown = false;
  for (unsigned int i = 0; i < print_out.size(); i++){
    if (print_out[i] == '['){
      is_markdown = true;
      print_out.erase(i, 1);
    }
    if (print_out[i] == ']' && print_out[i+1] == '(' && is_markdown == true){
      int j = i;
      while(print_out[j] != ')'){
        j++;
      }
      print_out.erase(i, j-i+1);
    }
  }
  os << print_out << endl;
  return os;
}

bool WebPage::operator== (const WebPage & rhs) const{
  if (this->content == rhs.content){
    return true;
  }
  else return false;
}

bool WebPage::operator< (const WebPage & rhs) const{
  if (this->file_name < rhs.file_name){
    return true;
  }
  else return false;
}

mySet<WebPage*> WebPage::allOutgoingLinks () const{
  return outgoinglink_set;
}


mySet<WebPage*> WebPage::allIncomingLinks () const{
  return incominglink_set;
}

void WebPage::parse(std::map<string, WebPage*>* linkedwpmap){
  string link = "";
  string convert = content;
  string word, anchor;
  bool is_link = false, is_anchor = false;
  for (unsigned int i = 0; i < content.length(); i++){
    if (convert[i] == '['){
      is_anchor = true;
    }
    if (convert[i] == ']'){
      is_anchor = false;
    }
    if (convert[i] == '('){
      is_link = true;
    }
    if (convert[i] == ')'){
      is_link = false;
    }
    if (isalnum(convert[i])){
      if (isalpha(convert[i]) && isupper(convert[i])){
        word.push_back(tolower(convert[i]));
      }
      else if(isalnum(convert[i])) {
        word.push_back(convert[i]);
      }
    }
    if (!isalnum(convert[i]) && is_link == false && is_anchor == false){
        if (word != ""){
          word_set.insert(word);
        }
      word.clear();
    }
    if (!isalnum(convert[i]) && is_link == false && is_anchor == true){
        if (word != ""){
          anchor_set.insert(word);
          word_set.insert(word);
        }
      word.clear();
    }
    if (!isalnum(convert[i]) && is_link == true && is_anchor == false){
      word.clear();
    }

    //parsing links.
    if (is_link == true && content[i] == '('){
      for (int j = i+1; content[j] != ')'; j++){
        link.push_back(content[j]);
      }
      //this needs to look up a map of webpages, find the right on with the link
      //and respectively add them to each other's incoming/outgoing link sets
      //if (this->file_name != link){
        WebPage* wp = linkedwpmap->at(link);
        wp->addIncomingLink(this);
        this->addOutgoingLink(wp);
      //}
      link.clear();
    }
  }
}

string WebPage::get_content () const{
  string print_out = this->content;
  bool is_markdown = false;
  for (unsigned int i = 0; i < print_out.size(); i++){
    if (print_out[i] == '['){
      is_markdown = true;
      print_out.erase(i, 1);
    }
    if (print_out[i] == ']' && print_out[i+1] == '(' && is_markdown == true){
      int j = i;
      while(print_out[j] != ')'){
        j++;
      }
      print_out.erase(i, j-i+1);
    }
  }
  return print_out;
}

string WebPage::get_contentwlinks () const{
  return this->content;
}

double WebPage::get_pagerank() const{
  return this->pagerank_value;
}

void WebPage::set_pagerank(double pagerank){
  this->pagerank_value = pagerank;
}

int WebPage::get_clicks() const{
  return this->num_clicks;
}

void WebPage::increment_clicks(){
  this -> num_clicks++;
}

void WebPage::set_clicks(int clicks_num){
  this -> num_clicks = clicks_num;
}

string WebPage::filename () const{
  return this->file_name;
}
      /* Returns the filename from which this page was read. */

void WebPage::addIncomingLink (WebPage* start){
  if (!incominglink_set.contains(start)){
    this->incominglink_set.insert(start);
  }
}
      /* Adds a link from start to the current page 
         in the current page's storage. */

void WebPage::addOutgoingLink (WebPage* target){
  if(!outgoinglink_set.contains(target)){
    this->outgoinglink_set.insert(target);
  }
}
      /* Adds a link from the current page to the target
         in the current page's storage. */