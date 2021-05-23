import csv
import random
import os
import multiprocessing

def create_adjacent_vertices(vertice: int, vertices_list):
    possible_numbers = []
    for i in range(vertice):
        if i not in vertices_list and i != vertice:
            possible_numbers.append(i)
    number_of_adjacent_vertice = random.choice(possible_numbers)
    return number_of_adjacent_vertice

def write_first_five_vertices(writer):
    for i in range(4):
        weight = random.randint(1, 100)
        writer.writerow([i, i+1, weight])
        writer.writerow([i+1, i, weight])

def create_dataset(folders, datas):
    try:
        os.mkdir(folders)
    except FileExistsError:
        pass
    os.chdir(folders)
    for i in datas:
        FILENAME = f'{i}.csv'
        with open(FILENAME, "w", newline="") as file:
            dataset = csv.writer(file, delimiter=' ')
            write_first_five_vertices(dataset)
            count_of_edges = 4
            list_of_lists = []

            for vertice in range(4, i):
                list_of_lists.append([])
                count_of_adjacent_vertices = random.randint(1, 4)
                if count_of_edges >= i:
                    break

                for adjacent_vertice in range(count_of_adjacent_vertices):
                    count_of_edges += 1
                    number_of_adjacent_vertice = create_adjacent_vertices(vertice, list_of_lists[vertice - 4])
                    list_of_lists[vertice - 4].append(number_of_adjacent_vertice)
                    weight = random.randint(1, 100)
                    dataset.writerow([vertice, number_of_adjacent_vertice, weight])
                    dataset.writerow([number_of_adjacent_vertice, vertice, weight])


if __name__ == '__main__':
    os.chdir('data')
    folders1 = ['01', '02', '03', '04', '05']
    datas = [100, 500, 1000, 5000, 10000, 25000, 50000, 100000,
             250000, 500000, 1000000]
    for b in folders1:
        my_thread = multiprocessing.Process(target=create_dataset, args=(b, datas,))
        my_thread.start()



    print('Done')