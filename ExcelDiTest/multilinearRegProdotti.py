
import pandas as pd
import numpy as np
from sklearn import linear_model

# read the data
df = pd.read_excel("Prodotti.xlsx")
print (df)

print ("\n\n..START MULTI LINEAR REGRESSION..")
multi_regr = linear_model.LinearRegression()

	
# select some features 
cdf = df[['PESO[g]','SUPERFICE [mm^2]','PREPARAZIONE ALLA VERNICIATURA [min]','TEMPO IMBALLAGGIO [min]','% RICHIAMI', 'PREZZO']]


# SPLIT DATASET into TRAIN dataset and TEST dataset (80% of the entire data for training, and the 20% for testing)
msk = np.random.rand(len(df)) < 0.8
train = cdf[msk] # train datataset
test = cdf[~msk] # test dataset

multi_x = np.asanyarray(train[['PESO[g]','SUPERFICE [mm^2]','PREPARAZIONE ALLA VERNICIATURA [min]', 'TEMPO IMBALLAGGIO [min]']])
multi_y = np.asanyarray(train[['PREZZO']])
multi_regr.fit (multi_x, multi_y)

# The coefficients
print ('Following coeff and intercept are param of the fit line.\nScikit-learn uses "Ordinary Least Squares" method to solve\n')
print ('Multi linear coefficients: ', multi_regr.coef_)
print ('Multi linear intercept: ',multi_regr.intercept_)

# prediction (test the model)
y_hat= multi_regr.predict(test[['PESO[g]','SUPERFICE [mm^2]', 'PREPARAZIONE ALLA VERNICIATURA [min]','TEMPO IMBALLAGGIO [min]']])
x = np.asanyarray(test[['PESO[g]','SUPERFICE [mm^2]', 'PREPARAZIONE ALLA VERNICIATURA [min]','TEMPO IMBALLAGGIO [min]']])
y = np.asanyarray(test[['PREZZO']])

print("Residual sum of squares: %.2f" % np.mean((y_hat - y) ** 2))

# Explained variance(𝑦,𝑦̂ )=1−𝑉𝑎𝑟{𝑦−𝑦̂ }/𝑉𝑎𝑟{𝑦}
print('Variance score: %.2f' % multi_regr.score(x, y)) # 1 is perfect prediction
	

 
file = open("Coefficent.txt", "w") 
file.write(str(multi_regr.coef_)) 
file.close()

print ("Program has terminated !")