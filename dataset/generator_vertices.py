import csv
import random
import os

def random_number(start, end, vertex):
    random_num = random.randint(start, end)
    while 1:
        if random_num == vertex:
            random_num = random.randint(start, end)
        else:
            break

    return random_num


def create_adjacent_vertices(number_of_vertices):
    adjacent_vertice_list = []
    for vertex in range(number_of_vertices):

        count_of_adjacent_vertices = random.randint(1, 4)

        for adjacent_vertice in range(count_of_adjacent_vertices):
            adjacent_vertice_list.append((vertex, random_number(0, 100, vertex), random.randint(0, 100)))

    length_of_adjacent_vertice_list = len(adjacent_vertice_list)
    for i in range(length_of_adjacent_vertice_list):
        adjacent_vertice_list.append(
            (adjacent_vertice_list[i][1], adjacent_vertice_list[i][0], adjacent_vertice_list[i][2]))

    return adjacent_vertice_list

if __name__ == '__main__':
    os.chdir('data')
    folders = ['06']
    datas = [100, 500, 1000, 5000, 10000, 25000, 50000, 100000,
             250000, 500000, 1000000]
    for folder in folders:
        try:
            os.mkdir(folder)
        except FileExistsError:
            continue
        os.chdir(folder)
        for i in datas:
            FILENAME = f'{i}.csv'
            with open(FILENAME, "w", newline="") as file:
                dataset = csv.writer(file, delimiter=' ')
                dataset.writerow([i])
                a = create_adjacent_vertices(i)

                for j in range(len(a)):
                    dataset.writerow([a[j][0], a[j][1], a[j][2]])


        os.chdir('..')

    print('Done')