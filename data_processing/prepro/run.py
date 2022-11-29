from data_get import http_get, csv_get, data_process

import pandas as pd
import matplotlib.pyplot as plt

dist = 'http://211.57.119.81:8080/change/block/list'
temp = 'http://211.57.119.81:8080/change/temperature/list'

dist_datas, dist_stats = http_get(dist).get_data_to_pandas('distance')
temp_datas, temp_stats = http_get(temp).get_data_to_pandas('temperature')

All_stats = pd.concat([dist_stats,temp_stats],axis=1)
print(All_stats)

# dates,times = data_process(dist_datas).time_distrubutor()
# plt.plot(dist_datas['distance'].keys(),dist_datas['distance'].values)
# plt.show()
# print(times)