import pandas as pd
import numpy as np

def get_data(filename):
    path = "data/" + filename
    with open(path, "r") as f:
        n = int(next(f))
        data = f.read()[:-1]
        df = pd.DataFrame([x.split(' ') for x in data.split('\n')])
    df.drop([0, 1], axis = 1, inplace=True)
    ignore = 0 # change this if leaving more data
    tags = pd.unique(df[df.columns[ignore:]].values.ravel('K'))
    tags = np.array([None] + [i for i in tags if i is not None])
    df.replace(tags, np.arange(tags.shape[0]), inplace=True)
    return df.to_numpy()

filenames = {
    "a": "a_example.txt", 
    "b": "b_lovely_landscapes.txt", 
    'c': 'c_memorable_moments.txt', 
    'd': 'd_pet_pictures.txt', 
    'e':'e_shiny_selfies.txt'
}
if __name__ == '__main__':
    print(get_data(filenames['a']))
