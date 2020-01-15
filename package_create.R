library(Rcpp)

# compiling code
sourceCpp("put_down_and_in.cpp")


Rcpp.package.skeleton("blawok",
                      example_code = FALSE,
                      cpp_files = c("put_down_and_in.cpp"))

# compileAttributes("blawok")



install.packages("blawok.zip", 
                 type = "binaries", repos = NULL)
library(blawok)

getDownInPutPrice(0.9)



# arguments values of values of function
expiry <- seq(0.01, 0.5, by = 0.001)
result <- sapply(expiry, getDownInPutPrice)

# plot using ggplot2 package
library(ggplot2)
qplot(x = expiry,
      y = result,
      xlab = "time to maturity",
      ylab = "Price of European put option",
      main = "Price of European put option vs. time  to maturity")


# arguments values of values of function
Vol <- seq(0.1, 0.3, by = 0.001)
result <- sapply(Vol, getDownInPutPrice)

# plot using ggplot2 package
library(ggplot2)
qplot(x = Vol,
      y = result,
      xlab = "Volatility",
      ylab = "Price of European put option",
      main = "Price of European put option vs. Volatility")


