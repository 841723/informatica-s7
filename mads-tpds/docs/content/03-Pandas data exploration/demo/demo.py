import pandas as pd


#################################
# 1. Read DataFrame  #
#################################

# Immediate data source: https://www.kaggle.com/datasets/vinicius150987/titanic3
# Original data source: https://www.encyclopedia-titanica.org/

df = pd.read_csv('titanic.csv')
df.set_index('name', inplace=True)

##################################
# 2. Basic overview              #
##################################

df.head()
df.tail(3)
df.info()
df.describe()
df.shape
df.columns
df.index


###################################
# 3. Subset rows and cols         #
###################################

###########################
# iloc accessor
###########################
# Selection based on integer location
# Start-stop-step logic (same as numpy arrays)
df.iloc[0]               # single row
df.iloc[0:3]             # rows
df.iloc[0:10:2, 0:4]     # rows and columns
df.iloc[:, 0:4]           # all rows


###########################
# loc accessor
###########################
# Selection based on labels

df.loc["Allison, Master. Hudson Trevor"]  # single row
df.loc[:, "fare"]                         # single column
df.loc[:, "fare":"survived"]              # multiple columns
df.loc[:, ["fare", "survived"]]           # multiple columns

# Selection based on boolean mask
df.loc[df.age > 70, ["age", "survived"]]

#################################
# Shorter alternative without loc
#################################

# ... if entire columns are selected
df["age"]
df.age
df[["age", "fare"]]

# ... if entire rows are selected using boolean masks
df[df.age > 70]
df[~(df.age > 70)]                     # negation
df[(df.age > 70) & (df.fare < 8)]      # both conditions must be met
df[(df.age > 70) | (df.fare < 8)]      # at least one must be met
df[df.embarked.isin(["Cherbourg", "Queenstown"])]

# ... using query method
df.query("age > 70")
df.query("age > 70 and fare < 8")
df.query("embarked in ['Cherbourg', 'Queenstown']")


###################################
# 4. Sorting
###################################

df[["fare"]].sort_values("fare")
df[["fare"]].sort_values("fare", ascending=False)[["fare"]]
df[['pclass', 'fare']].sort_values(['pclass', 'fare'], ascending=[True, False])

# Useful shortcuts
df.fare.nlargest(5)
df.fare.nsmallest(5)

# Modify DataFrame permanently
df.sort_values('fare', inplace=True)

# Sort according to index
df.sort_index()               # sorted copy of DataFrame
df.sort_index(inplace=True)   # modify DataFrame inplace


###################################
# 5. Aggregate
###################################

# Standard aggregation functions
df.fare.mean()              # skip missing values
df.fare.mean(skipna=False)  # do not skip missing values
df.fare.min()
df.fare.sum()

# ... applied on entire DataFrame
df.mean()
df.mean(numeric_only=True)

###########################
# agg method
###########################

# Apply list of aggregation functions
df.age.agg(["min", "mean", "max"])

# Apply dictionary of aggregation functions
functions_dict = {"age": "mean", "fare": ["mean", "sum"]}
df.agg(functions_dict)

# Apply custom function
df[["age", "fare"]].agg(lambda x: x.max() - x.min())


###################################
# 6. Groupby method
###################################

# Group by single column
df.groupby('sex').size()         # number of passengers by sex
df.groupby('sex').age.count()    # number of non-missing age values by sex
df.groupby('sex').age.mean()     # average age per sex

# ... multiple columns
df.groupby(['sex', 'pclass']).size()

# ... according to condition
df.groupby(df.age > 70).size()

# Useful shortcuts
df.value_counts('sex')
df.value_counts('sex', normalize=True, sort=False)

# Store groupby object
df_sex = df.groupby('sex')
print(type(df_sex))
df_sex.groups.keys()

df.reset_index(inplace=True)
df_sex.get_group('female').age
