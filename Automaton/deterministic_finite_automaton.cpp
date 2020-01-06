#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
std::vector<char> str2vec(std::string text){
  auto code = std::vector<char>((int)text.size());
  std::transform(text.begin(), text.end(), code.begin(), [](char x){return x;});
  return code;
}

using trans_table = std::unordered_map<int, std::unordered_map<char, int>>;

class DFA{
private:
  std::set<int> states;
  std::set<char> alphabets;
  int init_state;
  std::set<int> accept_states;
  trans_table transitions;

public:
  DFA(std::set<int> _state, std::set<char> _alphabets, int _init_state, std::set<int> _accept_states, trans_table _transitions){
    states = _state;
    alphabets = _alphabets;
    init_state = _init_state;
    transitions = _transitions;
    accept_states = _accept_states;
  }
  bool run(std::string input_text){
    auto seq = str2vec(input_text);
    int state = this->init_state;
    for(char c: seq){
      if (alphabets.contains(c)){
        state = transitions.at(state).at(c);
      } else {
        std::cout << "ERROR : <" << c << "> isn't contained " << '\n';
      }
    }
    return accept_states.contains(state);
  }
};

int main(int argc, char const *argv[]) {
  std::set<int> states= {0,1,2};
  std::set<char> alphabets= {'0','1'};
  int init_state = 0;
  std::set<int> accept_states = {0};
  trans_table transitions = {
    {0, {{'0',0}, {'1',1}}},
    {1, {{'0',2}, {'1',0}}},
    {2, {{'0',1}, {'1',2}}}
  };

  DFA* dfa = new DFA(states,alphabets,init_state,accept_states,transitions);
  std::string instr;
  while(true){
    std::cout << ">> ";
    std::cin >> instr;
    if (instr == "exit") break;
    std::cout << std::boolalpha <<dfa->run(instr) << '\n';
  }
  return 0;
}
