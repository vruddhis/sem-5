import random

def objective_function(chromosome):
    a, b, c, d = chromosome
    return abs((a + 2 * b + 3 * c + 4 * d) - 30)

def initialize_population(pop_size, gene_length):
    population = []  
    for _ in range(pop_size):  
        chromosome = []  
        for _ in range(gene_length):  
            gene = random.randint(0, 30)  
            chromosome.append(gene) 
        population.append(chromosome)  
    return population

def calculate_fitness(population):
    fitness_scores = [1 / (1 + objective_function(chromosome)) for chromosome in population]
    total_fitness = sum(fitness_scores)
    return [fitness / total_fitness for fitness in fitness_scores]


def select_population(population, fitness_probs):
    cumulative_probs = [sum(fitness_probs[:i+1]) for i in range(len(fitness_probs))]
    new_population = []
    for _ in range(len(population)):
        r = random.random()
        for i, chromosome in enumerate(population):
            if r <= cumulative_probs[i]:
                new_population.append(chromosome)
                break
    return new_population


def crossover(parent1, parent2, crossover_rate=0.25):
    if random.random() < crossover_rate:
        point = random.randint(1, len(parent1) - 1)
        return parent1[:point] + parent2[point:], parent2[:point] + parent1[point:]
    return parent1, parent2

def mutate(chromosome, mutation_rate=0.1):
    if random.random() < mutation_rate:
        mutation_point = random.randint(0, len(chromosome) - 1)
        chromosome[mutation_point] = random.randint(0, 30)
    return chromosome


def genetic_algorithm(pop_size=6, gene_length=4, generations=100, crossover_rate=0.25, mutation_rate=0.1):
    population = initialize_population(pop_size, gene_length)
    
    for generation in range(generations):
        fitness_probs = calculate_fitness(population)
        population = select_population(population, fitness_probs)
        
    
        new_population = []
        for i in range(0, pop_size, 2):
            parent1, parent2 = population[i], population[(i + 1) % pop_size]
            offspring1, offspring2 = crossover(parent1, parent2, crossover_rate)
            new_population.extend([offspring1, offspring2])
        
        population = [mutate(chromosome, mutation_rate) for chromosome in new_population]
        
        best_solution = min(population, key=objective_function)
        best_fitness = objective_function(best_solution)
        
        print(f"Generation {generation+1}: Best Solution: {best_solution}, Fitness: {best_fitness}")
        
        if best_fitness == 0:
            break
    
    return best_solution

best_solution = genetic_algorithm()
print(f"\nSolution found: {best_solution}")

