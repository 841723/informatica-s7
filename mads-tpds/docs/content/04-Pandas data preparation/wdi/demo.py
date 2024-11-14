import pandas as pd


###############################################
# Reading data
###############################################

# Fact Tables
economy = pd.read_csv("data/data1.csv")
health = pd.read_csv("data/data2.csv")
wdi_1999 = pd.read_csv("data/data3.csv")

# Dimension Table
countries = pd.read_csv("data/data4.csv")

###############################################
# A. Merging data
###############################################

df = pd.merge(left=economy,
              right=health,
              on=["iso3", "date"],
              how="inner")

# It is important to check whether the shape of the final data set is as expected!
print("Health: ", health.shape)
print("Economy: ", economy.shape)
print("Merged: ", df.shape)


# Using an outer join with indicator=True, we can check our merge operation
df = pd.merge(left=economy,
              right=health,
              on=["iso3", "date"],
              how="outer",
              indicator=True)
df.sort_values(["iso3", "date"], inplace=True)

df.value_counts("_merge")
print("Merged: ", df.shape)
df[df._merge == 'right_only']


# Let's take our large facts table as given (left table) and merge corresponding metadata on countries (right table) if available --> Left join

df = pd.merge(left=df,
              right=countries,
              left_on="iso3",
              right_on="id",
              how="left",
              indicator="country_merge")
print(df.shape)
df.country_merge.value_counts()


#################
# Concat
#################
# Finally, we want to add the World Development Indicators from 1999
# This is different from before: we do not need to merge on key columns

# Concat appends a DataFrame below another by default (axis=0)
# while merging on the column names

print(df.shape)
print(wdi_1999.shape)
df = pd.concat([df, wdi_1999], axis=0)
df.sort_values(["iso3", "date"], inplace=True, ignore_index=True)
print("Final DataFrame: ", df.shape)


#################################################
# B. Manipulating columns #
#################################################

#######################
# Dropping columns
#######################

# Let's drop selected columns
df.drop(columns=["capitalCity"], inplace=True)

#######################
# Renaming columns
#######################
df.rename(columns={'female_population': 'population_female'}, inplace=True)

#######################
# Creating new columns
#######################

# Average income per person (GDP per capita)
df['gdp_euro'] = df["gdp"] * 0.9
df["gdp_capita"] = df["gdp"] / df["population"]
df[["gdp", "population", "gdp_capita"]]


#######################
# Transform
#######################

# Compare aggregate with transform
df.groupby("date").population.agg('sum')
df.groupby("date").population.transform('sum')

# Let's compute the worlds total population per year, and add this information as a new column to the data
df["world_population"] = df.groupby("date").population.transform('sum')
df[['iso3', 'date', 'population', 'world_population']][df.date == 1999]
df[['iso3', 'date', 'population', 'world_population']][df.date == 2020]

# ... using custom function


def share(x):
    return x / x.sum()


df["world_population_share"] = df.groupby("date").population.transform(share)
df[['iso3', 'date', 'population', 'world_population',
    'world_population_share']][df.date == 2020]


# ... using an annonymous lambda function
df["world_population_share"] = df.groupby(
    "date").population.transform(lambda x: x / x.sum())

df.loc[df.name == "India", ["name", "population",
                            "world_population", "world_population_share"]]

#################################################
# C. Dealing with Indices, Stacking/Unstacking
#################################################

# Here are some examples how we may reshape row/column representation
# of our data using indexes
df_gdp_capita = df[["iso3", "date",  "gdp_capita"]]
df_gdp_capita.set_index(['iso3', 'date'], inplace=True)
df_gdp_capita.index
df_gdp_capita.unstack(level=0)
df_gdp_capita.unstack(level=1)

df_gdp_capita = df[["iso3", "date",  "gdp_capita"]]
pd.pivot(data=df_gdp_capita, index='date', columns='iso3', values='gdp_capita')


##########################
# D. String methods
##########################

# For any string columns / Series we can use Pandas string methods
# which mostly correspond to the usual Python string methods

# Python string operations
'data science'.capitalize()
len('data science')
'data science'[0:8:2]
'data' + ' ' + 'science'
'data science'.split(' ')

# Pandas string operations
df["name_length"] = df.name.str.len()
df["name_firstfour"] = df.name.str[0:4]
df["name_upper"] = df.name.str.upper()
df['iso_name'] = df.iso3 + ' ' + df.name
df.iso_name.str.split(' ', expand=True)


df[['isocode', 'countryname']] = df.iso_name.str.split(' ', expand=True, n=1)
'ZWE Zimbabwe'.split(" ")[1]

# df.iso_name.apply(lambda x: x.split(' ')[1])


##########################
# E. Missing values
##########################

# Get a boolean mask for the presence of missing values NaN
df.isna()
df.inflation.isna()
df[df.inflation.notna()]
df[df.inflation.isna()]

# Count missing values
df.isna().sum(axis=0)  # per column
df.isna().sum(axis=1)  # per row

# Let's drop all columns with more than 10% missing values
percent_missing = df.isnull().sum() / len(df)
cols_to_drop = percent_missing[percent_missing > 0.1].index
df.drop(columns=cols_to_drop, inplace=True)

# Replace missing values by some fixed new value
df.name.fillna("No country name available")
