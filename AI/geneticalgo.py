import random


POPULATION_SIZE = 100  # number of individuals in the population
GENOME_LENGTH = 10      # length of the binary genome
MUTATION_RATE = 0.01    # probability of mutation
GENERATIONS = 10      # number of generations

def fitness_function(individual): #square of decimal from binary
    x = 0
    for i in range(GENOME_LENGTH):
        x += individual[i] * (2 ** (GENOME_LENGTH - 1 - i))  
    return x ** 2  

#randomly select any 2
def select_parents(population):
    return random.choices(population, weights=[fitness_function(ind) for ind in population], k=2)

#single point crossover randomly choosing point
def crossover(parent1, parent2):
    crossover_point = random.randint(1, GENOME_LENGTH - 1)
    offspring = parent1[:crossover_point] + parent2[crossover_point:]
    return offspring

def mutate(individual):
    for i in range(GENOME_LENGTH):
        if random.random() < MUTATION_RATE:
            individual[i] = 1 - individual[i]  
    return individual

def create_individual():
    return [random.randint(0, 1) for _ in range(GENOME_LENGTH)]

def genetic_algorithm():

    population = [create_individual() for _ in range(POPULATION_SIZE)]
    
    for generation in range(GENERATIONS):
        new_population = []
        
        for _ in range(POPULATION_SIZE // 2):
            parent1, parent2 = select_parents(population)
            offspring1 = crossover(parent1, parent2)
            offspring2 = crossover(parent2, parent1)
            new_population.extend([mutate(offspring1), mutate(offspring2)])
        
        population = new_population
        best_fitness = max(fitness_function(ind) for ind in population)
        print('Generation' + str(generation + 1) + ': Best Fitness =' + str(best_fitness))

    
    best_individual = max(population, key=fitness_function)
    best_value = 0
    for i in range(GENOME_LENGTH):
        best_value += best_individual[i] * (2 ** (GENOME_LENGTH - 1 - i))  # Calculate decimal value
    
    print(f'Best Individual: {best_individual}, Best Value (x): {best_value}, Fitness: {fitness_function(best_individual)}')

genetic_algorithm()
