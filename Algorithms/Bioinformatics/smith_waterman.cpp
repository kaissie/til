#include <iostream>
#include <string>
#include <vector>
#include <ios>
#include <iomanip>

class Cell {
private:
  static int count;
  int score = 0;
  Cell* prev = nullptr;
public:
  int index;
  Cell(){index = count; ++count;}
  inline int getScore() { return this->score; };
  inline void setScore(int score) { this->score = score;};
  inline Cell* getPrev() { return this->prev; };
  inline void setPrev(Cell* prev) { this->prev = prev;};
  friend std::ostream& operator<<(std::ostream& stream, const Cell& value);
};

int Cell::count = 0;
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    os << std::right << std::setw(3) << cell.score;
    return os;
}

class SmithWaterman {
private:
  std::string sequence1;
  std::string sequence2;
  int row_size;
  int col_size;
  std::vector<std::vector<Cell*>> table;
  int match_score    =  1;
  int mismatch_score = -1;
  int gap_score      = -2;
  Cell* high_score_cell = nullptr;

public:
  SmithWaterman(std::string s1, std::string s2) : sequence1(s1), sequence2(s2) {
    table = std::vector<std::vector<Cell*>>( s2.size() + 1, std::vector<Cell*>(s1.size() + 1));
    for(auto seq = this->table.begin(); seq != this->table.end(); ++seq) {
      for(auto e = (*seq).begin(); e != (*seq).end(); ++e){
        *e = new Cell();
      }
    }
    row_size = s2.size() + 1;
    col_size = s1.size() + 1;
  }

  inline std::vector<std::vector<Cell*>> get_table() {
    return this->table;
  }

  void fillTable() {
    this->high_score_cell = this->table[0][0];
    int row = 1, col = 1;
    for(auto seq = ++this->table.begin(); seq != this->table.end(); ++seq) {
      for(auto e = ++(*seq).begin(); e != (*seq).end(); ++e){
        bool is_match = this->sequence2[row - 1] == this->sequence1[col - 1];
        fillInCell(is_match, *e, table[row - 1][col], table[row][col - 1], table[row - 1][col - 1]);
        ++col;
      }
      col = 1;
      ++row;
    }
  }

  void fillInCell(bool match, Cell* cell, Cell* above, Cell* left, Cell* above_left) {
    int rowSpaceScore = above->getScore() + this->gap_score;
    int colSpaceScore = left->getScore() + this->gap_score;
    int matchOrMismatchScore = above_left->getScore();
    if (match) matchOrMismatchScore += this->match_score;
    else matchOrMismatchScore += this->mismatch_score;
    if (rowSpaceScore >= colSpaceScore ){
      if (matchOrMismatchScore >= rowSpaceScore){
        if (matchOrMismatchScore > 0){
          cell->setScore(matchOrMismatchScore);
          cell->setPrev(above_left);
        }
      } else if (rowSpaceScore > 0){
        cell->setScore(rowSpaceScore);
        cell->setPrev(above);
      }
    } else {
      if (matchOrMismatchScore >= colSpaceScore){
        if (matchOrMismatchScore > 0){
          cell->setScore(matchOrMismatchScore);
          cell->setPrev(above_left);
        }
      } else if (colSpaceScore > 0){
        cell->setScore(colSpaceScore);
        cell->setPrev(left);
      }
    }
    if (cell->getScore() > this->high_score_cell->getScore())
      this->high_score_cell = cell;
  }

  void getTraceback() {
    std::string align1Buf = "";
    std::string align2Buf = "";

    Cell* current = this->high_score_cell;
    Cell* prev = current->getPrev();
    std::string offset1Seq = this->sequence1;
    std::string offset2Seq = this->sequence2;
    while (current->getScore() > 0) {
      if (current->index  - prev->index != 1) {
        std::string s{this->sequence1[current->index %col_size - 1]};
        align1Buf.insert(0,s);
      } else {
        align1Buf.insert(0,"-");
      }
      if (current->index - prev->index  != row_size ) {
        std::string s{this->sequence2[current->index / col_size - 1]};
        align2Buf.insert(0,s );
      } else {
        align2Buf.insert(0, "-");
      }
      current = prev;
      prev = current->getPrev();
    }
    if(this->high_score_cell->index % col_size > this->high_score_cell->index / col_size)
      offset2Seq = std::string(this->sequence1.size() - align2Buf.size(), '-') + offset2Seq;
    else
      offset1Seq = std::string(this->sequence2.size() - align2Buf.size(), '-') + offset1Seq;
    std::cout << offset1Seq << '\n';
    std::cout << offset2Seq << '\n';
    std::cout << align1Buf << '\n';
    std::cout << align2Buf << '\n';

  }

  void print_table() {
    std::cout << "    ";
    for(auto s1: this->sequence1) std::cout << std::right << std::setw(3) <<s1;
    std::cout << '\n';
    int i = -1;
    for(auto seq: this->table) {
      if( i != -1) std::cout << this->sequence2[i];
      else std::cout << " ";
      for(auto e: seq) std::cout << *e;
      std::cout << '\n';
      ++i;
    }
  }
};

int main(int argc, char const *argv[]) {
  std::string s1 ="GCCCTAGCG";
  std::string s2 ="GCGCAATG";
  SmithWaterman sw(s1,s2);
  sw.fillTable();
  sw.print_table();
  sw.getTraceback();
  return 0;
}
