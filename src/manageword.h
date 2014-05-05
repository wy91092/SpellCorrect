#ifndef _MANAGEWORD_H_
#define _MANAGEWORD_H_
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
class ManageWord
{
private:
  std::vector<std::string> _word_vector;
public:
  ManageWord();
  ~ManageWord();
  void read_word(const std::string &filename);
  
};
#endif
