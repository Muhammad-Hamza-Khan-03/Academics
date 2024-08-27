rm(list=ls())
p = 0.4
n = 15
x = 10

print(sum(dbinom(3:8,n,p)))

p = 0.03
#a
n= 20
x= 1
prob =sum(dbinom(x:n,n,p))
n=10
p=20/10
x=1
sum(dbinom(3,n,prob))

####################################
prob = 0.32
prob = 1-prob
#work independently
components = 6
working = 1:components
sum(dbinom(working,6,prob))
##########################################
rm(list=ls())
male = 32
female = 26
comm = 7
selection = 7
total_members = male+female
prob = selection/female
prob
sum(dbinom(x= 6,total_members,prob))

my_function<-function(u){
  return (u**3)
}
print(x = my_function(3))
print(sum(dhyper(6:26,26,32,7)))

mu = 8
sample = 10
x = 2
dpois(x,mu)

###################################################

redslots=blackslots=18
greenslots=1
prob=18/37
dgeom(5,prob)

dhyper(4,5,4,6)
dhyper(2,4,5,6)

prob = dhyper(

####################################################

M=c(1,10,100,1000,10000,100000)
x=1:6
pr=c()

for(i in 1:length(M))
{
sam = sample(x,M[i],replace=TRUE)
nx=length(which(sam==6))
pr[i] = nx/M[i]
}

plot(1:length(M),pr,type="l",lty=2)
lines(1:length(M),rep(1/6,length(M)),type="l")

#########################################

y=203*u^3 - 6*U - 7
5000 U(0,1)
##########################################
rm(list=ls())
U<- function(u)
{
return (203*u^3 - 6*u - 7)
}
pop = rnorm(5000, 0,1)
y = U(pop)
length(y)
par(mfrow=c(2,1))
hist(y,main='red')

boxplot(y,horizontal=T)

pr=mean(y>9)
pr

U=runif(5000,0,1)
y=203*u^3 - 6*u - 7
hist(y,xlab="y")
boxplot(y)
qqnorm(y)
qqline(y)
hist(y,xlab="y")

#########################################

rm(list=ls())
pop = c(10,30,50,100,300,1000)
x =1:2
pr=c()
for(i in 1:length(M))
{
	sam = sample(x,pop[i],replace=T)
	nx = length(which(sam ==1))
	pr[i] = nx/pop[i]
}
plot(1:length(pop),pr,type='l',color='red')
line(1:length(pop),rep( 1/6,length(pop)
),type="l")

####################################################

# Create vector containing M values 
M <- c(10, 30, 50, 100, 300, 1000) 

# Calculate empirical probability of success for each M value 
empirical_prob <- M / M 

# Plot empirical probability of success against classical probability of success 
plot(M, empirical_prob, type = "b", 
     main = "Probability of Success", 
     xlab = "Number of Tosses (M)", 
     ylab = "Probability of Success") 

# Add classical probability of success line to plot 
abline(h = 0.5, col = "red")

