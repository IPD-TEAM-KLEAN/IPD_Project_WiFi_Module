from random import *

import requests
import numpy as np
import pandas as pd

class http_get :

    def __init__(self,url):
        self.url = url
    
    def get_data_to_pandas(self,name):
        resp = requests.get(url=self.url).json()
        shuffle(resp)
        resp = sorted(resp,key=lambda d: d['sewerId'])
        df = pd.DataFrame(resp).rename(columns={"value":f"{name}"})
        df_stats = df[f'{name}'].describe()

        return df, df_stats