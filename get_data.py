import numpy as np
import pandas as pd


def get_data(filename, keep_hv=False, split_hv=False):
    if split_hv and not keep_hv:
        print("Assuming keep_hv...")
        keep_hv = True
    path = "data/" + filename
    with open(path, "r") as f:
        data = f.read()[:-1]
        df = pd.DataFrame([x.split(' ') for x in data.split('\n')])
    df.drop([1] if keep_hv else [0, 1], axis=1, inplace=True)
    ignore = int(keep_hv)  # change this if leaving more data
    tags = pd.unique(df[df.columns[ignore:]].values.ravel('K'))
    tags = np.array([None] + [i for i in tags if i is not None])
    df.replace(tags, np.arange(tags.shape[0]), inplace=True)
    if split_hv:
        return {'H': df[df[0] == 'H'].to_numpy(), 'V': df[df[0] == 'V'].to_numpy()}
    return df.to_numpy()


filenames = {
    "a": "a_example.txt",
    "b": "b_lovely_landscapes.txt",
    'c': 'c_memorable_moments.txt',
    'd': 'd_pet_pictures.txt',
    'e': 'e_shiny_selfies.txt'
}
if __name__ == '__main__':
    print(get_data(filenames['e'], keep_hv=True, split_hv=True))
