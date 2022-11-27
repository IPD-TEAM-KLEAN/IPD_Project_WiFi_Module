from url_get import http_get

dist = 'http://211.57.119.81:8080/change/block/list'
temp = 'http://211.57.119.81:8080/change/temperature/list'

dist_datas = http_get(dist).get_data_to_pandas()
temp_datas = http_get(temp).get_data_to_pandas()

print(dist_datas['value'].describe())
print('--'*100)
print(temp_datas['value'].describe())