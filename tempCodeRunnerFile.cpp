int main(){
  // computer Computer();
  std::vector<std::pair<std::string, int>> Dpair{{"one", 1}};
  std::vector<std::pair<std::string, int>> Lpair{{".two", 2}};
  std::string str {"one_.two_r534"};
  
  std::cout << parse(str, Dpair, Lpair) << '\n';

  return 0;
}