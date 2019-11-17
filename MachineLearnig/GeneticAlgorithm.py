import random
import copy

class GeneticAlgorithm:
    def __init__(self, gen_len, gen_num, mutate_rate, elite_rate):
        self.gen_len = gen_len
        self.gen_num = gen_num
        self.mutate_rate = mutate_rate
        self.elite_rate = elite_rate

        self.best_gene = None
        self.max_score = None
        self.min_score = None

        self.genoms = self.create_genoms(self.gen_num)
        
    def create_genoms(self,num):
        genoms = []
        for _ in range(num):
            genom = [random.randint(0,1) for _ in range(self.gen_len)]
            genoms.append((self.eval(genom), genom))
        return genoms

    def eval(self, genom):
        return sum(genom)

    def sort(self, genoms):
        return sorted(genoms, reverse=True)
    
    def two_point_crossover(self, parent1, parent2):
        r1 = random.randint(0, self.gen_len-1)
        r2 = random.randint(r1, self.gen_len-1)
        
        child = copy.deepcopy(parent1)
        child[r1:r2] = parent2[r1:r2]
        return child

    def select_elites(self):
        sorted_genoms = self.sort(self.genoms)
        elites = sorted_genoms[:int(self.gen_num * self.elite_rate)]
        return elites

    def mutate(self, parent):
        r = random.randint(0, self.gen_len-1)
        child = copy.deepcopy(parent)
        child[r] = 1 if child[r]==0 else 0
        return child

    def next_generation(self):
        elites = self.select_elites()
        self.genoms = elites

        while len(self.genoms) < self.gen_num:
            if random.random() < self.mutate_rate:
                m = random.randint(0, len(elites)-1)
                child = self.mutate(elites[m][1])
            else:
                m1 = random.randint(0, len(elites)-1)
                m2 = random.randint(0, len(elites)-1)
                child = self.two_point_crossover(elites[m1][1], elites[m2][1])
            self.genoms.append((self.eval(child), child))

    def get_min_score(self):
        pop = self.sort(self.genoms)
        return pop[-1][0]

    def get_max_score(self):
        pop = self.sort(self.genoms)
        return pop[0][0]
    def get_best_gene(self):
        pop = self.sort(self.genoms)
        return pop[0][1]

        
def test():
    ga = GeneticAlgorithm(gen_len=100, gen_num=100, mutate_rate=0.1, elite_rate=0.2)
    epoch = 40

    print("SCORE min:{}  max:{}".format(ga.get_min_score(), ga.get_max_score()))
    print("BEST GENE <{}>".format(ga.get_best_gene()))

    for _ in range(epoch):
        ga.next_generation()
    
    print("SCORE min:{}  max:{}".format(ga.get_min_score(), ga.get_max_score()))
    print("BEST GENE <{}>".format(ga.get_best_gene()))
if __name__ == '__main__':
    test()
