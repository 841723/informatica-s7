import numpy as np

###############################
# Comparing Lists with Arrays #
###############################

#########
# Lists #
#########

mylist = [1, 2, 3]

# Behaviour of math operators
mylist + [10]
mylist * 2
mylist - [3]

# Element-wise math operations are cumbersum
newlist = []
for i in mylist:
    newlist.append(i+10)

# Lists are mutable
mylist[0] = 0        # we can change values in-place
mylist.append(100)   # we can append values in-place

# Lists can contain heterogeneous elements
mylist.extend(['data science', True])


##############
# Numpy arrays
##############
myarray = np.array([1, 2, 3])

# Behaviour of math operators
myarray + 10
myarray * 2
myarray - 3
myarray / 2
myarray // 2
myarray ** 2

# Individual values can be changed (mutability)
myarray[0] = 0
print(myarray)

# ... but the size of an array is immutable
np.append(myarray, 10)
print(myarray)

# Arrays are of homogeneous type
print(myarray.dtype)
myarray[0] = 'data science'
np.append(myarray, 'data science')


########################################################
# Element-wise/vectorized operations and broadcasting  #
########################################################

# Math operators
a = np.array([1, 2, 3, 4])
b = np.array([10, 100, 1000, 10000])
c = np.array([10, 100])
print(a + b)
print(a + 10)      # Broadcasting
print(a + c)

# Many other element-wise Operations
np.sqrt(a)
np.log(a)
np.exp(a)


####################
# Indexing/Slicing #
####################

# Well known indexing logic
x = np.arange(10)
print(x)
x[0]              # zero-based
x[-1]             # negative indexing
x[2:9]            # start-stop (stop is exclusive)
x[::2]            # start-stop-step

# ... on higher dimensions
x = np.arange(100).reshape(10, 10)
print(x)
x[0]
x[:, 0]
x[5, 5]

# Boolean masking
x[x > 50]
np.any(x > 50)
np.all(x > 50)


#####################
# Aggregating
#####################
x.min()
x.min(axis=0)
x.min(axis=1)
x.mean()
np.median(x)

#####################
# Generating Arrays #
#####################
np.zeros((2, 3))
np.ones((2, 3))
np.full((2, 3), 10)
np.arange(start=0, stop=100, step=10)
np.linspace(start=0, stop=100, num=51)
np.arange(start=0, stop=100, num=2).reshape(5, 10)

np.random.random(size=(2, 3))
np.random.standard_normal(size=(2, 3))
np.random.normal(loc=10, scale=3, size=(2, 3))
np.random.uniform(low=10, high=20, size=5)
np.random.choice([1, 9], size=10)


#################################################
# Linear algebra (matrix multiplication, ...)   #
#################################################
x1 = [1, 2]
x2 = [10, 100]
1*10 + 2*100

# Arrays
A1 = np.array(x1)
A2 = np.array(x2)
np.dot(x1, x2)       # Top-level function
x1.dot(x2)           # Instance Method
x1 @ x2              # Matrix multiplication operator

# More linear algebra
np.linalg.norm(x2)        # Norm/length of a vector
np.sqrt(10**2 + 100**2)   # ...by hand