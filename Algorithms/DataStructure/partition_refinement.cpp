#include <list>
#include <iostream>
#include <vector>


struct PartitionClass;
struct PartitionItem;

struct PartitionClass {
  PartitionClass* parent = nullptr;
  std::list<int> items{};
  void append(int);
};

struct PartitionItem {
  PartitionClass* theclass;
  int value;
  PartitionItem(int value_, PartitionClass* class_) : theclass(class_), value(value_){
    theclass->append(value);
  };
  void remove();
};

void PartitionClass:: append(int item) {
  items.push_back(item);
}

void PartitionItem:: remove() {
  theclass->items.remove(value);
}

struct PartiotionRefinement {
  std::list<PartitionClass*> classes;
  std::vector<PartitionItem> items;
  PartiotionRefinement(std::size_t N)  {
    PartitionClass* c = new PartitionClass();
    for (size_t i = 0; i < N; i++)
      items.push_back(PartitionItem(i,c));
    classes.push_back(c);
  }
  
  void refine(std::vector<int> pivot) {
    std::vector<PartitionClass*> has_split;
    for(auto i: pivot) {
      PartitionItem& item = items[i];
      PartitionClass& c = *item.theclass;
      if (c.parent == nullptr){
        c.parent = new PartitionClass();
        std::cout << "create new partition" << '\n';
        has_split.push_back(&c);
        classes.push_back(c.parent);
      }
      item.remove();
      item.theclass = c.parent;
      c.parent->items.push_back(i);
    }
    for (auto s: has_split) {
      s->parent = nullptr;
      if (s->items.size() == 0){
        classes.remove(s);
        delete s;
      }
    }
  }

  void print() {
    std::cout << "Partition size =>" << classes.size() << '\n';
    size_t i = 0;
    for (auto c: classes) {
      std::cout << "Partition "<< i++ << '\n';
      for (auto item: c->items) {
        std::cout << i <<" : " << item << '\n';
      }
    }
  }
};


int main(int argc, char const *argv[]) {
  std::cout << "initialize" << '\n';
  PartiotionRefinement data(10);
  data.refine({0,3,5});
  data.refine({2,4,5});
  data.print();
  return 0;
}
