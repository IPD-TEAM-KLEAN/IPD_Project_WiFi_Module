from url_get import http_get
import pandas as pd

dist = 'http://211.57.119.81:8080/change/block/list'
temp = 'http://211.57.119.81:8080/change/temperature/list'

dist_datas, dist_stats = http_get(dist).get_data_to_pandas('distance')
temp_datas, temp_stats = http_get(temp).get_data_to_pandas('temperature')

All_datas = pd.concat([dist_stats,temp_stats],axis=1)

print(All_datas)