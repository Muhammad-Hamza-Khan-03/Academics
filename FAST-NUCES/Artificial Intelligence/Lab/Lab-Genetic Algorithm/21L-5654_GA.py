import numpy as np
import random
#1 3 266
#2 13 442
#3 10 671
#4 9 526
#5 7 388
#6 1 245
#7 8 210
#8 8 145
#9 2 126
#10 9 322
ci = [i for i in range(1,10)]
wi = [3,13,10,9,7,1,8,8,2,9]
vi = [266,442,671,526,388,245,210,145,126,322]

initial_population =[[0,1,0,1 ,1 ,0 ,0 ,1 ,1 ,1],
  [1, 1, 1, 1 ,0 ,1 ,1 ,1 ,0 ,0],
  [0 ,1 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1],
  [0, 0, 1 ,0 ,1 ,1 ,0 ,0 ,0 ,0],
  [0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1],
  [0 ,1 ,0 ,1 ,1 ,0 ,1 ,0, 0, 0],
  [1, 1, 1, 0 ,0 ,0 ,1 ,0 ,1 ,0],
  [0, 0 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,0]]


n= 10
kw =35


def fitness_function(chromosome,n,ci,vi,wi,kw):
  '''
  where, n = chromosome length 
  ci = ith gene 
  vi = ith value 
  wi = ith weight 
  kw = allowed weight
  '''
  fitness =0
  total_value =0
  total_weight=0

  for i in range(n):
    total_value +=chromosome[i]*vi[i]
    total_weight +=chromosome[i]*wi[i]
  if total_weight<=kw:
    return total_value
  else:
    return 0


def crossover_function(chromosome1,chromosome2): #both list
   '''Two Point Cross over is done'''
   chromosome2[3:6],chromosome1[3:6]  = chromosome1[3:6],chromosome2[3:6]
   return chromosome1,chromosome2

def mutation_function(chromosome):
  '''Mutating the chromosome at 2 random points for better results'''
  point1 = random.randint(0,len(chromosome)-1)
  point2 = random.randint(0,len(chromosome)-1)

  point1=1 if point1==0 else 1
  point2=1 if point2==0 else 0

  return chromosome  

def selection_function(initial_population, fitness_scores_list):
    selected_parents = []
    population_size = len(initial_population)
    
    for _ in range(population_size):
        index1, index2 = random.sample(range(population_size), 2)
        
        parent1 = initial_population[index1] if fitness_scores_list[index1] > fitness_scores_list[index2] else initial_population[index2]
        
        index1, index2 = random.sample(range(population_size), 2)
        parent2 = initial_population[index1] if fitness_scores_list[index1] > fitness_scores_list[index2] else initial_population[index2]
        
        selected_parents.append((parent1, parent2))
    
    return selected_parents
best_chromosomes = []
for iteration in range(15):
    fitness_scores_list = [fitness_function(chromosome, n, ci, vi, wi, kw) for chromosome in initial_population]
    print("Fitness scores are:", fitness_scores_list)
    selected_parents = selection_function(initial_population, fitness_scores_list)
    new_generation = [crossover_function(parent1, parent2) for parent1, parent2 in selected_parents]

    mutated_generation = [mutation_function(chromosome) for chromosome in new_generation]

    combined_population = initial_population + mutated_generation

    combined_population.sort(key=lambda chromosome: fitness_function(chromosome, n, ci, vi, wi, kw), reverse=True)
    top_chromosomes = combined_population[:8]  # Keep the top 8 chromosomes

    initial_population = top_chromosomes
    best_chromosomes.append(max(initial_population, key=lambda chromosome: fitness_function(chromosome, n, ci, vi, wi, kw)))

best_chromosome = max(best_chromosomes, key=lambda chromosome: fitness_function(chromosome, n, ci, vi, wi, kw))
print("Best Chromosome:", best_chromosome)

