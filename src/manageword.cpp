#include"../inc/manageword.h"
using namespace std;

ManageWord::ManageWord():_word_vector(){}

ManageWord::~ManageWord()
{
}

static std::ifstream &open_file(std::ifstream &is, const std::string &filename)
{
  is.close();
  is.clear();
  is.open(filename.c_str());
  return is;
}

void ManageWord::read_word(const std::string &filename)
{
  std::ifstream infile;
  int num=0;
  if(!open_file(infile, filename))
  {
   std::cout<<"open file failed!"<<std::endl;
  }
  std::string word;
  std::string line;
  while(getline(infile, line)){
   for(int ix=0;ix!=line.size();++ix){
    if(line[ix]>='a'&&line[ix]<='z') {}
    else if(line[ix]>='A'&&line[ix]<='Z') {}
    else line[ix]=' ';
    }
   istringstream stream(line);
    while(stream>>word)
    {
    _word_vector.push_back(word);
    num++;
    }
  }
  std::cout<<"num= "<<num<<std::endl;
}

std::vector<std::string> &ManageWord::get_vector(){
   return _word_vector;
}
