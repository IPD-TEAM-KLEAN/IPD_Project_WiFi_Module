from random import *

import requests
import numpy as np
import pandas as pd

class http_get :

    def __init__(self,url):
        self.url = url
    
    def get_data_to_pandas(self,rename):
        resp = requests.get(url=self.url).json()
        shuffle(resp)
        resp = sorted(resp,key=lambda d: d['sewerId'])
        df = pd.DataFrame(resp).rename(columns={"value":f"{rename}"})
        df_stats = df[f'{rename}'].describe()

        return df, df_stats

class csv_get : 
    
    def __init__(self,file):
        self.file = file 

    def get_data_to_pandas(self,rename):
        return 

class data_process :

    def __init__(self,data):
        self.data = data

    def time_distrubutor(self):
        time_series = [(time_series[:time_series.find("T")],time_series[time_series.find("T")+1:]) \
            for time_series in self.data['localDateTime'].values]
        dates = [ymd[0].split('-') for ymd in time_series]
        times = [times[1].split(':') for times in time_series]
        return dates, times