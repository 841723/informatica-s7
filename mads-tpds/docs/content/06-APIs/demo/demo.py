import pandas as pd
import json
import requests

##############################################
# 1. Get Request
##############################################

endpoint = 'https://jsonplaceholder.typicode.com/users'
response = requests.get(endpoint)
data = response.json()


# Parsing JSON data
len(data)
data[0]

parsed_data = []
for user in data:
    userdata = {}
    userdata['id'] = user['id']
    userdata['name'] = user['name']
    userdata['street'] = user['address']['street']
    userdata['zipcode'] = user['address']['zipcode']
    parsed_data.append(userdata)

pd.DataFrame(parsed_data)

##############################################
# 2. Parametrized Queries
##############################################

# Using the URL
url = f'https://jsonplaceholder.typicode.com/users?userId=1&_limit=3'
response = requests.get(url)
response.json()

# Params argument
params = {'userId': 1, '_limit': 3}
response = requests.get(endpoint, params=params)
response.json()

##############################################
# 3. Write to JSON file / read from JSON file
##############################################

response = requests.get(endpoint)
data = response.json()  # Converts JSON response into Python list or dict

# Saving JSON response to file
with open('users.json', 'w') as f:
    json.dump(data, f)

# Loading JSON data from file
with open('users.json', 'r') as f:
    users = json.load(f)


##########################################
# 4. JSON <-> Pandas DataFrame
##########################################

df = pd.read_json('users.json')

# Splitting dictionary columns
adresses = df.address.apply(pd.Series)

# Normalize nested JSON
pd.json_normalize(data)
pd.json_normalize(data, max_level=1, sep='_')


##########################################
# 5. Post Request
##########################################

data = {
    'userId': 1,
    'name': 'Max Mustermann'
}
response = requests.post(endpoint, json=data)
print(response.json())
