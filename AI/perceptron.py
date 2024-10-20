import random

def sign(x):
    if x > 0:
        return 1
    else:
        return -1

def perceptron(inputs, weights, bias):
    weighted_sum = sum([w * x for w, x in zip(weights, inputs)]) + bias
    return sign(weighted_sum)


def train_perceptron(training_data, learning_rate, epochs):
    n = len(training_data[0][0])  # number of inputs
    weights = [random.random() for _ in range(n)] #random initialisation
    bias = random.random()

    for epoch in range(epochs):
        for inputs, expected_output in training_data:
            prediction = perceptron(inputs, weights, bias)
            error = expected_output - prediction
            for i in range(n):
                weights[i] += learning_rate * error * inputs[i]
            bias += learning_rate * error

    return weights, bias

#training data is [(inputs), expected_output], OR gate
training_data = [
        ([0, 0], -1), 
        ([0, 1], 1),
        ([1, 0], 1),
        ([1, 1], 1)
    ]
    
learning_rate = 0.1
epochs = 10
    
weights, bias = train_perceptron(training_data, learning_rate, epochs)
    
test_inputs = [1, 0]
print(f"Test result: {perceptron(test_inputs, weights, bias)}")



