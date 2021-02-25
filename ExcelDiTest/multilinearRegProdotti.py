
import pandas as pd
import numpy as np
from sklearn import linear_model
from sklearn import preprocessing

import sys

import os
if os.path.exists("Coefficent.txt"):
  os.remove("Coefficent.txt")
  
fileName = "Prodotti.csv"
testMode = "random"
testPct =  0.8;

print ("PYTHON SCRIPT multilinearRegProdotti.py\n")

if len(sys.argv) - 1 == 3:
	fileName = sys.argv[1]
	testMode = sys.argv[2]
	testPct =  float(sys.argv[3])
	if testPct > 0.9:
		testPct = 0.8

print ("PARAMETRO 1: %s" % fileName)
print ("PARAMETRO 2: %s" % testMode)
print ("PARAMETRO 3: %2f"% testPct)

# read the data
df = pd.read_csv(fileName, sep = ';', decimal=",")

# delete first row
df=df.tail(-1)

print(df)

print ("TOTALI RIGHE: %d" % len(df))
print ("TOTALI COLONNE: %d" % len(df.columns))

df = df[(df != 0).all(1)]

print ("righe utilizzate nel modello: %d" % len(df))


# labels encoding
str_cols = df.columns[df.columns.str.contains('(?:class|instrument)')]
clfs = {c:LabelEncoder() for c in str_cols}
for col, clf in clfs.items():
    df[col] = clfs[col].fit_transform(df[col])

#print (df)

print ("REGRESSIONE MULTILINEARE...")
multi_regr = linear_model.LinearRegression()

# select some features 
cdf = df[['PESO[g]','SUPERFICE [mm^2]','PREPARAZIONE ALLA VERNICIATURA [min]','TEMPO IMBALLAGGIO [min]','% RICHIAMI', 'PREZZO']]


# SPLIT DATASET into TRAIN dataset and TEST dataset (80% of the entire data for training, and the 20% for testing)
msk = np.random.rand(len(df)) < testPct

# OPTION: this is not random calculation

if (testMode == "fixed"):
	maxN = len(df.index)
	for x in range(maxN):
		if x < maxN*testPct:
			msk[x] = True
		else:
			msk[x] = False
#print (testPct)	  
#print (msk)

train = cdf[msk] # train datataset
test = cdf[~msk] # test dataset

multi_x = np.asanyarray(train[['PESO[g]','SUPERFICE [mm^2]','PREPARAZIONE ALLA VERNICIATURA [min]', 'TEMPO IMBALLAGGIO [min]', '% RICHIAMI']])
# multi_x = preprocessing.StandardScaler().fit(multi_x).transform(multi_x)

multi_y = np.asanyarray(train[['PREZZO']])
# multi_y = preprocessing.StandardScaler().fit(multi_y).transform(multi_y)

multi_regr.fit (multi_x, multi_y)

# The coefficients
# print ('Following coeff and intercept are param of the fit line.\nScikit-learn uses "Ordinary Least Squares" method to solve\n')
print ('Multi linear coefficients: ', multi_regr.coef_)
print ('Multi linear intercept: ',multi_regr.intercept_)

# prediction (test the model)
y_hat= multi_regr.predict(test[['PESO[g]','SUPERFICE [mm^2]', 'PREPARAZIONE ALLA VERNICIATURA [min]','TEMPO IMBALLAGGIO [min]', '% RICHIAMI']])
x = np.asanyarray(test[['PESO[g]','SUPERFICE [mm^2]', 'PREPARAZIONE ALLA VERNICIATURA [min]','TEMPO IMBALLAGGIO [min]', '% RICHIAMI']])
y = np.asanyarray(test[['PREZZO']])

print("Residual sum of squares: %.2f" % np.mean((y_hat - y) ** 2))

# Explained variance(𝑦,𝑦̂ )=1−𝑉𝑎𝑟{𝑦−𝑦̂ }/𝑉𝑎𝑟{𝑦}
print('Variance score (near 0.99 is good): %.2f' % multi_regr.score(x, y)) # 1 is perfect prediction
	

 
file = open("Coefficent.txt", "w") 
file.write(str(multi_regr.coef_)) 
file.close()


coeff_a = multi_regr.coef_[0][0]
coeff_b = multi_regr.coef_[0][1]
coeff_c = multi_regr.coef_[0][2]
coeff_d = multi_regr.coef_[0][3]
coeff_e = multi_regr.coef_[0][4]

print("coeff_a:")
print(coeff_a)
print("coeff_b:")
print(coeff_b)
print("coeff_c:")
print(coeff_c)
print("coeff_d:")
print(coeff_d)
print("coeff_e:")
print(coeff_e)