import random

def generate_arrays(sizes, num_arrays, min_val=-100, max_val=100):
    for size in sizes:
        for i in range(num_arrays):
            array = [random.randint(min_val, max_val) for _ in range(size)]
            with open(f'array_{size}_{i+1}.txt', 'w') as f:
                f.write(' '.join(map(str, array)))

sizes = [100, 1000, 10000, 100000, 1000000]
num_arrays = 100
generate_arrays(sizes, num_arrays)