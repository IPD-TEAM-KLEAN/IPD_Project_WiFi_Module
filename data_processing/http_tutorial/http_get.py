from random import *

import requests
import numpy as np
import pandas as pd

distance  = 'http://211.57.119.81:8080/change/block/list'
resp = requests.get(url=distance).json()
shuffle(resp)
resp = sorted(resp,key=lambda d: d['sewerId'])

df = pd.DataFrame(resp)
print(df['value'].describe())

